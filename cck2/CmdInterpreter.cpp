#include "CmdInterpreter.h"

#include "Iostream.h"
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Debug.h"

using std::istream;
using std::string;

CmdInterpreter::CmdInterpreter(istream * input) : input{ input }, world{ this } {
	if (!input) input = &cin;
	keyHandle = GetStdHandle(STD_INPUT_HANDLE);
	processInput();
}

CmdInterpreter::~CmdInterpreter() { delete input;  }

//finish interface
//start movement around map
//maybe add menu class to cmdInterpreter. The menu isnt really part of the world whereas movement is

void CmdInterpreter::processInput(void) {
	const int movementMode = 1;
	const int menuMode = 2;
	const int sleepTime = 150; //milliseconds
	int currentMode = movementMode;

	string command;

	while (true) {
		const int buffer = 10;

		if (currentMode == menuMode) {
			*input >> command;
		}
		else if (currentMode == movementMode) {
			if (isPressed(VK_LEFT) || isPressed('A')) {
				world.movePlayer(VK_LEFT);
				Sleep(buffer);
			}
			else if (isPressed(VK_RIGHT) || isPressed('D')) {
				world.movePlayer(VK_RIGHT);
				Sleep(buffer);
			}
			else if (isPressed(VK_UP) || isPressed('W')) {
				world.movePlayer(VK_UP);
				Sleep(buffer);
			}
			else if (isPressed(VK_DOWN) || isPressed('S')) {
				world.movePlayer(VK_DOWN);
				Sleep(buffer);
			}
		}

		/* Regardless of input, make sure the world is properly animated. For 
		example: enemies should still patrol if the player chooses to not press anything */
		world.animateWorld();
	}
}

bool CmdInterpreter::isPressed(const int key) {
	const int pressed = 0x800; 

	//check if the high-order bit is set as well as the key being pressed
	return GetKeyState(key) & 0x800; 
}

void CmdInterpreter::testSpacePress(void) {
	/* Another better way to handle input. Painfully slow though. Figure out later */
	HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD events = 0;
	INPUT_RECORD ir;
	DWORD inputSize = 1;

	FlushConsoleInputBuffer(inputHandle);
	ReadConsoleInput(inputHandle, &ir, inputSize, &events);

	if (ir.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) Debug::write("right");
}