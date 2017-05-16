#include "Display.h"
#include "Iostream.h"
#include "DisplayImpl.h"

//#define NOMINMAX
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using std::make_unique;

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

	refresh();
}

Display::~Display() {}

//from Cameron's stackoverflow answer: http://stackoverflow.com/questions/34842526/update-console-without-flickering-c/34843181
void Display::refresh(void) {
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

	//some comment
	
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

