#pragma once
#include <memory>
#include <vector>
#include "Observer.h"
#include <Windows.h>


//to delete
#include <fstream>

struct DisplayImpl;

class Display final : public Observer {
	std::unique_ptr <DisplayImpl> displayImpl;
	std::ofstream ofs{ "Debug.txt" };

	virtual void addressTileChange(
		const Coordinate & tile,
		const char newDesign) override;

	void updateCursorPos(const int numWrites, COORD & cursor);
	void writeConsole(const WCHAR toWrite, const DWORD length, COORD & cursor);
	void setConsoleDimensions(void);
	void disableConsoleCursor(void);

public:
	Display();
	~Display();
	void refreshScreen(void);
	void refreshMap(
		const std::vector <std::vector <char>> & newTiles
	);
};

