#pragma once
#include "CmdInterpreter.h"
#include <Windows.h>

// The purpose of this class is to restrict the display's access to the cmdInterpreter's public functions 
class DisplayCommands {
	CmdInterpreter * const cmd;

public:
	DisplayCommands(CmdInterpreter * const cmd) : cmd{ cmd } {};

	/* Returns true when space is pressed so we know for example: 
	when the player wants to clear already read dialogue */
	bool spacePressed(void) {
		return cmd->isPressed(VK_SPACE);
	};

};