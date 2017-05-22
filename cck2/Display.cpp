#include "Display.h"
#include "Iostream.h"
#include "DisplayImpl.h"

//#define NOMINMAX
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using std::make_unique;
using std::vector;
using std::move;

//to delete
#include "Iostream.h"

// MIL - Get the Win32 handle representing standard output
Display::Display(): displayImpl(make_unique <DisplayImpl> ()) {
	COORD bufferSize{ displayImpl->consoleWidth , displayImpl->consoleHeight };

	/* Specifies the dimensions of the console screen in lines. 
	The parameters are left, top, right, bottom respectivly. Note the 
	area of the console is the same as that of that of the bufferSize. An
	equal sized console and buffer eliminates the scrollbar. */
	SMALL_RECT consoleBounds{
		0,
		0,
		displayImpl->consoleWidth - 1,
		displayImpl->consoleHeight - 1 };

	// Sets the buffer size and console size
	SetConsoleScreenBufferSize(displayImpl->hOut, bufferSize);
	SetConsoleWindowInfo(displayImpl->hOut, TRUE, &consoleBounds);

	//refresh();
}

Display::~Display() {}


void Display::addressTileChange(const Coordinate & tile, const char newDesign) {
	cout << "notified" << endl;
}

/* shorthand for FillConsolOutput since displayImpl->hOut
and &charsWritten are always the same. Also updates the cursor to
the next open position in the buffer */
void Display::writeConsole(const WCHAR toWrite, const DWORD length, COORD & cursor) {
	DWORD charsWritten;

	FillConsoleOutputCharacter(
		displayImpl->hOut,
		toWrite,
		length,
		cursor,
		&charsWritten
	);

	updateCursorPos(length, cursor);
}

/* updates the cursor position based on how many characters we
have just written to the screen */
void Display::updateCursorPos(const int numWrites, COORD & cursor) {
	const int rowsToAdd = (cursor.X + numWrites) / displayImpl->consoleWidth;

	cursor.Y += rowsToAdd;
	cursor.X = (cursor.X + numWrites) - (rowsToAdd * displayImpl->consoleWidth);
}

/* Updates the portion of the map we are displaying */
void Display::refreshMap(const vector <vector <char>> & newTiles) {
	DWORD numWrites = 0;
	COORD cursor{ 0, 0 };

	//inital value that will NEVER appear on a map. Only ' ' will be used for whitespace
	WCHAR toWrite = '\t';

	std::ofstream ofs{ "Debug.txt" };

	/* this will be updated as newTiles get written to the screen, prevDisplay
	will eventually be set equal to this */
	vector <vector <char>> prevDraw(
		displayImpl->consoleHeight, 
		vector <char>(displayImpl->consoleWidth, ' '));

	/* Go through the previous visible area and redraw only the
	characters that differ */
	for (unsigned int i = 0; i < displayImpl->prevDisplay.size(); i++) {
		/* Special case: If the visible area is smaller than the entire screen (height wise) which 
		newTiles covers, populate the rows of the map we cannot see with spaces */
		if (i >= newTiles.size()) {
			const int rows = displayImpl->prevDisplay.size() - newTiles.size();
			const int numSpaces = rows * displayImpl->consoleWidth;

			/* If spaces are already in the buffer simply add on to the number of
			spaces we print */
			if (toWrite == ' ') numWrites += numSpaces;
			else { //otherwise print what's in the buffer and add the correct number of spaces to the buffer
				writeConsole(toWrite, numWrites, cursor);
				numWrites = numSpaces;
				toWrite = '+';
			}

			writeConsole(toWrite, numWrites, cursor);
			numWrites = 0;

			//Since these are the final rows in the console, there is nothing left to print after
			break; 
		}

		for (unsigned int j = 0; j < displayImpl->prevDisplay[0].size(); j++) {
			/* Special case: If the visible area is smaller than the entire screen (width wise), 
			populate the columns at the end of the row with spaces*/
			if (j >= newTiles[0].size()) {
				int numSpaces = displayImpl->prevDisplay[0].size() - newTiles[0].size();

				if (toWrite == ' ') numWrites += numSpaces; 
				else { 
					writeConsole(toWrite, numWrites, cursor);
					numWrites = numSpaces;
					toWrite = '+';
				}

				//prints the spaces and resets toWrite and numWrites to their default values
				writeConsole(toWrite, numWrites, cursor);
				toWrite = '\t';
				numWrites = 0;

				//continue on to printing the next row
				break;
			}

			/* as we print the newTiles we also store them as previously drawn, for
			the next set of newTiles. This was not needed for the cases before b/c
			prevDraw is already initialized to spaces. */
			prevDraw[i][j] = newTiles[i][j];

			//Main case: For every newTile that differs from its previous draw
			if (newTiles[i][j] != displayImpl->prevDisplay[i][j]) {
				//writeConsole(newTiles[i][j], 1, cursor);
				ofs << displayImpl->prevDisplay[i][j] << newTiles[i][j] << ' ';

				// initializes toWrite to the first character that needs to be redrawn
				if (toWrite == '\t') toWrite = newTiles[i][j];

				// If we have multiple of the same character, draw the batch all at once
				if (newTiles[i][j] == toWrite) numWrites++; //note that numWrites starts at 0
				else {
					//Draws the updated tile(s) and adjusts the cursor to the next drawing poistion
					writeConsole(toWrite, numWrites, cursor);

					numWrites = 1; //we reset the count to only 1 character
					toWrite = newTiles[i][j]; //the next character to be drawn
				} 
			}
			else {
				if (numWrites != 0) {
					writeConsole(toWrite, numWrites, cursor);
					toWrite == '\t';
					numWrites = 0;
				}
				//writeConsole('+', 1, cursor);
				cursor.X++;
			} 
		} 

	} 

	/* The screen's output is always one step behind the buffer. Thus, one final
	write is needed to print the final char(s) left in the buffer */
	writeConsole(toWrite, numWrites, cursor);

	ofs << '\n';

	for (auto row : prevDraw) {
		for (auto col : row) {
			ofs << col;
		}
		ofs << '\n';
	}

	displayImpl->prevDisplay = move(prevDraw);
}

/* Redraws the entire screen. This is called whenever the 
player moves to redraw the section of the map we can see. 
From Cameron's stackoverflow answer: http://stackoverflow.com/questions/34842526/update-console-without-flickering-c/34843181 */
void Display::refreshScreen(void) {
	/* Contains information about the console window such
	as width and height */
	COORD topLeft = { 0, 0 };

	/* cout uses a buffer to batch writes to the underlying console. We need 
	to flush that to the console because we're circumventing std::cout entirely;
	after we clear the console, we don't want stale buffered text to be randomly 
	written out */
	cout.flush();

	/* Retrieves information about the specified console screen buffer.
	This includes the width and height */
	if (!GetConsoleScreenBufferInfo(displayImpl->hOut, &displayImpl->csbi)) return;

	// The number of character cells to which a character should be written
	DWORD length = displayImpl->csbi.dwSize.X * displayImpl->csbi.dwSize.Y;
	
	// The number of characters actually written
	DWORD written;
	
	// Flood fill the console with spaces to clear it
	FillConsoleOutputCharacter(displayImpl->hOut, TEXT('a'), length, topLeft, &written);
	
	/* Reset the attributes of every character to the default. 
	This clears all background colour formatting, if any */
	FillConsoleOutputAttribute(displayImpl->hOut, displayImpl->csbi.wAttributes, length, topLeft, &written);
	
	/* Move the cursor back to the top left for the next 
	sequence of writes */
	SetConsoleCursorPosition(displayImpl->hOut, topLeft);
}

