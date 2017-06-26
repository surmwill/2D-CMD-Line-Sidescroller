#include "CmdInterpreter.h"

#include "Iostream.h"
#include <string>
#include <conio.h>
#include <Windows.h>

using std::istream;
using std::string;

CmdInterpreter::CmdInterpreter(istream * input) : input{ input }, world{ this } {
	if (!input) input = &cin;
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

	}
}

bool CmdInterpreter::isPressed(const int key) {
	const int pressed = 0x800;
	return GetKeyState(key) & 0x800;
}