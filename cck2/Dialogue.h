#pragma once
#include "Display.h"
#include <string>

/* The purpose of this class is to ensure the enemy/player class 
can only call Display's drawDialogue function and not it's drawMap
function */
class Dialogue
{
	Display * const display;

public:
	Dialogue(Display * const display) : display{ display } {};
	~Dialogue() = default;

	void displayDialogue(std::string name, std::string dialogue,  bool slowType = true) {
		display->drawDialogue(name, dialogue, slowType);
	}
};

