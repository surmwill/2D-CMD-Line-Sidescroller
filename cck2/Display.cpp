#include "Display.h"
#include "Iostream.h"
#include "DisplayImpl.h"
#include "Coordinate.h"
#include "DisplayCommands.h"
#include <utility>
#include <cwchar>
#include <string>
#include <cmath>

//#define NOMINMAX
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


using std::make_unique;
using std::vector;
using std::move;
using std::make_pair;
using std::wcscpy;
using std::string;

//to delete
#include "Iostream.h"
#include "Debug.h"
using std::to_string;
using std::unique_ptr;

/* Intializes the console screen by setting its dimensions and 
hiding the flashing cursor */
Display::Display(unique_ptr <DisplayCommands> cmd): displayImpl(make_unique <DisplayImpl> (std::move(cmd))) {
	adjustTextProperties();
	setConsoleProperties();
	setConsoleDimensions();
	disableConsoleCursor();
	drawUI();
	clearDialogue();

	drawDialogue("sabrina", "hey", true);
	drawDialogue("will", "01234567890 1234567890 1234567890 1234567890 1234567890 12345678904 ad dsa gred frefre fwedew 01234567890 1234567890 12 frefre fwedew 01234567890 1234567890 12 frefre fwedew 01234567890 1234567890 12 frefre fwedew 01234567890 1234567890 12 frefre fwedew 01234567890 1234567890 12");
	//drawDialogue("will", "hi");
	//drawDialogue("sabrina", "hey");
	//drawDialogue("tom", "yo");
}

Display::~Display() {}

/* Hides the flashing console cursor */
void Display::disableConsoleCursor(void) {
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(displayImpl->hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(displayImpl->hOut, &cci);
}

/* Sets the console's x and y position to the top left of the screen.
Also disables resizing the console, and going fullscreen */
void Display::setConsoleProperties(void) {
	HWND hConsole;
	//MENUITEMINFO mii; 
	const int updateTime = 10;
	const int dontCareDim = 0;

	/* Sets the title and allows time for the console to update */
	SetConsoleTitle(displayImpl->title);
	Sleep(updateTime);

	// Gets a handle to the console window
	hConsole = FindWindow(NULL, displayImpl->title);

	/* Sets the console to appear in the top left (0, 0) of the screen. The
	screen will be resized later so the dimensions don't matter */
	MoveWindow(hConsole, 0, 0, dontCareDim, dontCareDim, FALSE);

	// Gets a handle to the menu in order to adjust console options
	HMENU hMenu = GetSystemMenu(hConsole, FALSE);
	
	DeleteMenu(hMenu, 1, MF_BYPOSITION); // disable 'Move'
	DeleteMenu(hMenu, 1, MF_BYPOSITION); // disable 'Size'

	DeleteMenu(hMenu, 2, MF_BYPOSITION); // disable 'Maximize'
	//DeleteMenu(hMenu, 3, MF_BYPOSITION); // disable 'Close or X'
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

/* Adjusts the text size and font */
void Display::adjustTextProperties(void) {
	CONSOLE_FONT_INFOEX cfi;

	//size of the structure
	cfi.cbSize = sizeof(cfi);

	//index of the front of the console's font table
	cfi.nFont = 0;

	//set to 24pt font
	cfi.dwFontSize.X = 0; 
	cfi.dwFontSize.Y = 24;

	//we are using the default font
	cfi.FontFamily = FF_DONTCARE;

	//no bold
	cfi.FontWeight = FW_NORMAL;

	/* setting the font type to "Consolas". Any other font screws 
	with the printing */
	wcscpy_s(cfi.FaceName, L"Consolas");

	//applying the font changes
	SetCurrentConsoleFontEx(displayImpl->hOut, FALSE, &cfi);
}

/* shorthand for FillConsoleOutput since displayImpl->hOut
and &charsWritten are always the same. Also updates the cursor to
the next open position in the buffer */
void Display::writeConsole(const WCHAR toWrite, const DWORD length) {
	DWORD charsWritten;

	FillConsoleOutputCharacter(
		displayImpl->hOut,
		toWrite,
		length,
		displayImpl->cursor,
		&charsWritten
	);

	updateCursorPos(length);
}

/* Draws a string in the console, starting wherever the cursor
is located */
void Display::writeStringToConsole(const string strToWrite, bool slowType) {
	char toWrite = displayImpl->tokenTile;
	int numWrites = 0;

	/* the amount of time we wait (ms) between printing batches of characters. Since we don't
	expect many repeated adjacent characters in dialogue, it should display smoothly */
	const DWORD slowTypeSpeed = 10;

	/* The same algorithim as redrawScreen. Store as many repeats of the
	same character in the buffer as possible and write them all at once when
	a different character is encountered */
	for (auto c : strToWrite) {
		if (toWrite == displayImpl->tokenTile) toWrite = c;

		if (c == toWrite) numWrites++;
		else {
			writeConsole(toWrite, numWrites);

			// pause for a brief moment between outputs for a "typewriter effect"
			if (slowType) Sleep(slowTypeSpeed); 

			toWrite = c;
			numWrites = 1;
		}
	}

	/* Again, the buffer is once step behind what is actually drawn of the screen.
	Print whatever's left in the buffer */
	writeConsole(toWrite, numWrites);
}

/* updates the cursor position based on how many characters we
have just written to the screen */
void Display::updateCursorPos(const int numWrites) {
	const int rowsToAdd = (displayImpl->cursor.X + numWrites) / displayImpl->consoleWidth;

	displayImpl->cursor.Y += rowsToAdd;
	displayImpl->cursor.X = 
		(displayImpl->cursor.X + numWrites) - (rowsToAdd * displayImpl->consoleWidth);
}

/* Updates the portion of the map we are displaying */ //maybe rename to refresh screen
void Display::drawMap(vector <vector <char>> & newTiles) {
	DWORD numWrites = 0;

	//We begin redrawing the screen from the top left
	setNextDrawPosition(0, 0);

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
		displayImpl->mapHeight, 
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
				writeConsole(toWrite, numWrites);

				// and add the correct number of spaces to printed to the buffer
				adjustWriteProperties(numSpaces, ' ');
			}

			//print the spaces
			writeConsole(toWrite, numWrites);

			// resets toWrite and numWrites to their default values
			adjustWriteProperties(0, displayImpl->tokenTile);

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
					writeConsole(toWrite, numWrites);
					adjustWriteProperties(numSpaces, ' ');
				}

				writeConsole(toWrite, numWrites);
				adjustWriteProperties(0, displayImpl->tokenTile);

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
				if (toWrite == displayImpl->tokenTile) toWrite = newTiles[i][j];

				// If we have multiple of the same character, draw the batch all at once
				if (newTiles[i][j] == toWrite) numWrites++; //note that numWrites starts at 0
				else {
					/* Draws the updated tile(s) and adjusts the cursor to the next drawing poistion */
					writeConsole(toWrite, numWrites);

					/* Sets the buffer to the next tile design to be printed. Since we already 
					encountered 1 of the tile, it follos that we print at least 1 */
					adjustWriteProperties(1, newTiles[i][j]);
				} 
			}
			else { //Main case: for every newTile that is the same as its previous draw:
				/* If there are tile(s) to be printed in the buffer. Print them first
				as we will be updating the cursor to jump over the un-changed tile */
				if (numWrites != 0) {
					writeConsole(toWrite, numWrites);
					adjustWriteProperties(0, displayImpl->tokenTile);
				}

				/* moves the cursor one forward, skipping the tile. If the tile
				is the same there as the last draw, there is no need to redraw it */
				updateCursorPos(1);
			} 
		} 

	} 

	/* The screen's output is always one step behind the buffer. Thus, one final
	write is needed to print the final char(s) left in the buffer */
	writeConsole(toWrite, numWrites);

	// Our previous display becomes what was just drawn
	displayImpl->prevDisplay = move(prevDraw);
}

/* Draws our U.I. The U.I. is not redrawn unless a menu screen is pulled up */
void Display::drawUI(void) {
	/* start drawing the line after the bottom of the map. The map is in charge
	of updating it's own section of the display */
	setNextDrawPosition(displayImpl->uiStarts, 0);

	writeConsole(' ', displayImpl->consoleWidth); //draw a line of blank spaces for clarity
	writeConsole('~', displayImpl->consoleWidth); //draw a line of '~' to section off the menu

	//3 spaces on either side to center the u.i
	const string uiLine = "   (I)nventory | (S)elf | (M)ap | (T)alents | (C)raft | (R)eligion | (O)ptions   ";
	writeStringToConsole(uiLine);

	writeConsole('~', displayImpl->consoleWidth); //draw a line of blank spaces for clarity
}

/* Clears the dialogue section with spaces and sets the
next draw position to the first line of the dialogue section */
void Display::clearDialogue(void) {
	// start at the beginning of where dialogue is drawn
	setNextDrawPosition(displayImpl->dialogueStarts, 0);

	const int numRows = displayImpl->consoleHeight - displayImpl->dialogueStarts;
	const int numWrites = numRows * displayImpl->consoleWidth;

	//clear the entire dialogue section
	writeConsole(' ', numWrites);

	// our next draw position is at the beginning of where dialogue is drawn
	setNextDrawPosition(displayImpl->dialogueStarts, 0);
	displayImpl->currentDialogueLine = displayImpl->dialogueStarts;
}

/* Displays the dialogue on the bottom the screen. We have 4 lines for dialogue so
the line parameter can be set to {0, 1, 2, 3} */
void Display::drawDialogue(
	const string & name, 
	const string & dialogue,
	bool finalDialogue,
	bool slowType) {
	string toWrite;
	if(name != "") toWrite = name + ": " + dialogue; // ": " is Appended after a name to pretty print the dialogue
	// Otherwise, if no name is provided there is no need to format anything

	int nextLineBreak = displayImpl->consoleWidth; // The character that needs to be a space in it's respected line
	unsigned int lineBreak = nextLineBreak; // The actual character we are testing to see if it's a space. unsigned b/c I don't like warnings

	// additional spaces may be padded so a word is not split between 2 lines
	int spacesNeeded = 0;

	const unsigned int spaceLeft = (displayImpl->consoleHeight - displayImpl->currentDialogueLine) *
		displayImpl->consoleWidth;

	while (toWrite.length() > lineBreak) {
		/* If the current dialogue toWrite (with formatted spaces) is longer 
		than what can be drawn on an entirely screen, print an error */
		if (toWrite.length() > displayImpl->maxDialogueLength) {
			toWrite = "TEXT ERROR: formatted dialogue length is: " + to_string(toWrite.length())
				+ " characters, the maximum length it  can be is: " + to_string(displayImpl->maxDialogueLength) 
				+ " characters.";
			break;
		}
		/* If the current dialogue toWrite (with formatted spaces) is longer 
		than what can be drawn on the current screen (which may contain previous dialogue), 
		wait for the player to press space to continue the dialogue so they don't miss
		anything */
		else if (toWrite.length() > spaceLeft) {
			displayImpl->currentDialogueLine = displayImpl->consoleHeight - 1; // print the message on the bottom of the screen
			/* The message takes up one line, pushing our currentDialogue line equal to the console height (calculated later in this fn)
			which triggers the "press space to continue" */
			toWrite = "Press space to continue reading... "; 
			break;
		}
	
		/* If a word is split between two lines, find the last character of the
		last full word that fits on the current line. -1 to adjust for the 0th index
		in a string */
		while (toWrite[lineBreak - 1] != ' ') {
			lineBreak--;
			spacesNeeded++;
		}

		// A word is split between lines, pad with spaces
		if (spacesNeeded != 0) {
			/* copy toWrite up to and including the (lineBreak - 1)th index 
			(the last character of the last word to be printed on the line)  */
			string dialogueOne = toWrite.substr(0, (lineBreak));

			// pad spaces to correctly split the dialogue
			for (int i = 0; i < spacesNeeded; i++) {
				dialogueOne += ' ';
			}

			/* dialogueOne copies characters: 0 to lineBreak - 1, dialogueTwo copies
			the rest of the characters starting from lineBreak */
			string dialogueTwo = toWrite.substr(lineBreak);
	
			toWrite = dialogueOne + dialogueTwo; // reconstruct the string
			spacesNeeded = 0;
		}

		// check if the next line needs to be split up
		nextLineBreak += displayImpl->consoleWidth;
		lineBreak = nextLineBreak;
	}

	// the 2 double casts are neeeded to avoid the truncating of the division before ceil()
	const int linesNeeded = static_cast <int> (ceil(
		static_cast <double> (toWrite.length()) / static_cast <double> (displayImpl->consoleWidth)));

	// -1 b/c currentDialogueLine is empty and avalible for writing
	if (displayImpl->currentDialogueLine - 1 + linesNeeded >= displayImpl->consoleHeight) clearDialogue();
	else setNextDrawPosition(displayImpl->currentDialogueLine, 0);
	
	// adjust where the next empty line for dialgoue drawing is
	displayImpl->currentDialogueLine += linesNeeded;

	// draw the dialogue
	writeStringToConsole(toWrite, slowType);

	/* If the current dialogue box is filled or it is the final part of
	the conversation wait for the user to press space to clear the dialogue box */
	if (finalDialogue || displayImpl->currentDialogueLine >= displayImpl->consoleHeight) {
		while(!displayImpl->cmd->spacePressed()) {}
	}
	
	// next steps: pass cmdInterpreter to display so when there is too much text they have to press a key
	// to clear the rpevious text and display the new one.
}

/* Sets the cursor position which corresponds to the next place a character is drawn */
void Display::setNextDrawPosition(const int row, const int col) {
	displayImpl->cursor.Y = row;
	displayImpl->cursor.X = col;
}
