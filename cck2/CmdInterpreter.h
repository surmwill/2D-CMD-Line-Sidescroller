#pragma once
#include "World.h"
#include <iosfwd>

class CmdInterpreter
{
	std::istream * input;
	World world;

	void processInput(void);
	bool isPressed(const int key);

public:
	CmdInterpreter(std::istream * input = nullptr);
	~CmdInterpreter();
};

