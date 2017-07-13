#pragma once
#include "World.h"
#include <iosfwd>

class CmdInterpreter
{
	std::istream * input;
	World world;

	void processInput(void);

public:
	CmdInterpreter(std::istream * input = nullptr);
	~CmdInterpreter();

	bool isPressed(const int key);
};

