#pragma once
#include <Windows.h>


//displayImpl->hOut(GetStdHandle(STD_OUTPUT_HANDLE))

struct DisplayImpl {
	DisplayImpl() : hOut(GetStdHandle(STD_OUTPUT_HANDLE)) {};

	const HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	const int consoleWidth = 81; //chars across (81)
	const int consoleHeight = 25; //number of lines (25)
};
