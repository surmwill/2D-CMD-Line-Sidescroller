#include "Display.h"
#include "Iostream.h"
#include "DisplayImpl.h"
#include "Coordinate.h"

//#define NOMINMAX
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using std::make_unique;
using std::vector;
using std::move;

//to delete
#include "Iostream.h"

/* Intializes the console screen by setting its dimensions and 
hiding the flashing cursor */
Display::Display(): displayImpl(make_unique <DisplayImpl> ()) {
	setConsoleDimensions();
	disableConsoleCursor();
}

Display::~Display() {}

/* Hides the flashing console cursor */
void Display::disableConsoleCursor(void) {
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(displayImpl->hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(displayImpl->hOut, &cci);
}

/* Adjusts the console screen size and buffer size according to displayImpl::consoleWidth
and displayImpl::consoleHeight. The buffer is adjusted to perfectly match the screen size,
eliminating the scroll bar */
void Display::setConsoleDimensions(void) {
	// Specifies the dimensions of the buffer
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

}

/* Updates and displays a singular tile on the visible map. */
void Display::addressTileChange(const Coordinate & tile, const char newDesign) {
	COORD cursor{ tile.x, tile.y };

	writeConsole(newDesign, 1, cursor);
	displayImpl->prevDisplay[tile.y][tile.x] = newDesign;
}

/* shorthand for FillConsoleOutput since displayImpl->hOut
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

	/* lambda to set numWrites and toWrite values. Main purpose is to help clean the code */
	auto adjustWriteProperties = [&numWrites, &toWrite](const int newNum, const char newChar) {
		numWrites = newNum;
		toWrite = newChar;
	};

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
			else { 
				//otherwise print what's in the buffer
				writeConsole(toWrite, numWrites, cursor);

				// and add the correct number of spaces to printed to the buffer
				adjustWriteProperties(numSpaces, ' ');
			}

			//print the spaces
			writeConsole(toWrite, numWrites, cursor);

			// resets toWrite and numWrites to their default values
			adjustWriteProperties(0, '\t');

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
					adjustWriteProperties(numSpaces, ' ');
				}

				writeConsole(toWrite, numWrites, cursor);
				adjustWriteProperties(0, '\t');

				//continue on to printing the next row
				break;
			}

			/* as we print the newTiles we also store them as what was previously drawn 
			on the screen, for the next set of newTiles. This was not needed for the cases 
			before b/c prevDraw is already initialized to spaces. */
			prevDraw[i][j] = newTiles[i][j];

			//Main case: For every newTile that differs from its previous draw
			if (newTiles[i][j] != displayImpl->prevDisplay[i][j]) {

				// initializes toWrite to the first character that needs to be redrawn
				if (toWrite == '\t') toWrite = newTiles[i][j];

				// If we have multiple of the same character, draw the batch all at once
				if (newTiles[i][j] == toWrite) numWrites++; //note that numWrites starts at 0
				else {
					/* Draws the updated tile(s) and adjusts the cursor to the next drawing poistion */
					writeConsole(toWrite, numWrites, cursor);

					/* Sets the buffer to the next tile design to be printed. Since we already 
					encountered 1 of the tile, it follos that we print at least 1 */
					adjustWriteProperties(1, newTiles[i][j]);
				} 
			}
			else { //Main case: for every newTile that is the same as its previous draw:
				/* If there are tile(s) to be printed in the buffer. Print them first
				as we will be updating the cursor to jump over the un-changed tile */
				if (numWrites != 0) {
					writeConsole(toWrite, numWrites, cursor);
					adjustWriteProperties(0, '\t');
				}

				/* moves the cursor one forward, skipping the tile. If the tile
				is the same there as the last draw, there is no need to redraw it */
				updateCursorPos(1, cursor);
			} 
		} 

	} 

	/* The screen's output is always one step behind the buffer. Thus, one final
	write is needed to print the final char(s) left in the buffer */
	writeConsole(toWrite, numWrites, cursor);

	// Our previous display becomes what was just drawn
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

