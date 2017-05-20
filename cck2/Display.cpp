#include "Display.h"
#include "Iostream.h"
#include "DisplayImpl.h"

//#define NOMINMAX
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using std::make_unique;
using std::vector;

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
and &charsWritten are always the same */
void Display::writeConsole(const WCHAR toWrite, const DWORD length, const COORD & cursor) {
	DWORD charsWritten;

	FillConsoleOutputCharacter(
		displayImpl->hOut,
		toWrite,
		length,
		cursor,
		&charsWritten
	);
}

/* updates the cursor position based on how many characters we
have just written to the screen */
void Display::updateCursorPos(const int numWrites, COORD & cursor) {
	const int rowsToAdd = numWrites / displayImpl->consoleWidth;
	if (rowsToAdd != 0) cursor.X = 0;

	cursor.Y += rowsToAdd;
	cursor.X += rowsToAdd - (rowsToAdd * displayImpl->consoleWidth);
}

/* Updates the portion of the map we are displaying */
void Display::refreshMap(const vector <vector <char>> & newTiles) {
	//to remove
	return;

	int prevScreenMaxRow = displayImpl->prevDisplay.size();
	int prevScreenMaxCol = displayImpl->prevDisplay[0].size();
	DWORD numWrites = 0;
	COORD cursor{ 0, 0 };
	WCHAR toWrite = '\t'; //inital value that will NEVER appear on a map. Only ' ' will be used for whitespace

	/* Go through the previous visible area and redraw only the 
	characters that differ */
	for (int i = 0; i < displayImpl->prevDisplay.size(); i++) {
		for (int j = 0; j < displayImpl->prevDisplay[0].size(); j++) {
			//If we have a tile that differs from its previous draw
			if (newTiles[i][j] != displayImpl->prevDisplay[i][j]) {
				// initializes toWrite to the first character that needs to be redrawn
				if (toWrite == '\t') toWrite = newTiles[i][j];

				// If we have multiple of the same character, draw the batch all at once
				if (newTiles[i][j] == toWrite) numWrites++; //note that numWrites starts at 0
				else { 
					//Draws the updated tile(s)
					writeConsole(toWrite, numWrites, cursor);

					// adjust the cursor to the next drawing poistion
					updateCursorPos(numWrites, cursor);

					numWrites = 1; //we reset the count to only 1 character
					toWrite = newTiles[i][j]; //the next character to be drawn
				}
			}
			else cursor.X++;
		}
	}

	/* Because we draw the characters in batches, we are always one
	step behind the display. Thus, the last character(s) won't be drawn. 
	A final writeConsole fixes the problem. */
	writeConsole(toWrite, numWrites, cursor);

	//reset these vars, as we enter an (near) identical loop as above
	numWrites = 0;
	toWrite = '\t';

	/* The previous visible area may be smaller than updated visible area. 
	These new characters automatically differ and must be printed */
	for (int i = displayImpl->prevDisplay.size(); i < newTiles.size(); i++) {
		for (int j = displayImpl->prevDisplay[0].size(); j < newTiles[0].size(); j++) {
			if (toWrite == '\t') toWrite = newTiles[i][j];

			if (newTiles[i][j] == toWrite) numWrites++; //again note that numWrites starts at 0
			else {
				writeConsole(toWrite, numWrites, cursor);

				// adjust the cursor to the next drawing poistion
				updateCursorPos(numWrites, cursor);

				numWrites = 1; //we reset the count to only 1 character
				toWrite = newTiles[i][j]; //the next character to be drawn
			}
		}
	}

	//same problem (and solution) as before
	writeConsole(toWrite, numWrites, cursor);

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

