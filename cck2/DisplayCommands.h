#pragma once
#include "CmdInterpreter.h"
#include <Windows.h>

// The purpose of this class is to restrict the display's access to the cmdInterpreter's public functions 
class DisplayCommands {
	CmdInterpreter * const cmd;

public:
	DisplayCommands(CmdInterpreter * const cmd) : cmd{ cmd } {};

	/* Returns true when a key is pressed. For example, we
	may want to know if the space has been pressed before
	we clear dialog */
	bool keyPressed(const int vkey) {
		return cmd->isPressed(vkey);
	}

};