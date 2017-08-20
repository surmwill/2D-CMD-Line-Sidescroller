#pragma once
#include "World.h"
#include <iosfwd>
#include <Windows.h>

class CmdInterpreter
{
	std::istream * input;
	World world;

	HANDLE keyHandle;

	void processInput(void);

public:
	CmdInterpreter(std::istream * input = nullptr);
	~CmdInterpreter();

	bool isPressed(const int key);
	void testSpacePress(void);
};

