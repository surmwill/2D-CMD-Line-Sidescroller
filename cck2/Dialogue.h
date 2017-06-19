#pragma once
#include "Display.h"
#include <string>

class Dialogue
{
	Display * display;

public:
	Dialogue(Display * display) : display{ display } {};
	~Dialogue() = default;

	void displayDialogue(std::string text) {
		//display->drawDialogue(0, "tom", "tom", false);
	}
};

