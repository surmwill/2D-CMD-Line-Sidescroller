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

	void displayDialogue(
		std::string name, 
		std::string dialogue, 
		bool slowType = true) {
		/* Dialogue is not allowed to be batch written, no implementation to do so.
		Since there is no batch writes, there is no need for indentation or drawing on 
		multiple liens */
		display->drawDialogue(name, dialogue, 0, 0, false, slowType);
	}
};

