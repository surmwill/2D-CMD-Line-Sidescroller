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

	void updateCursorPos(const int numWrites);
	void writeConsole(const WCHAR toWrite, const DWORD length);
	void setConsoleDimensions(void);
	void disableConsoleCursor(void);
	void drawMenu(void);
	void menuSetup(void);
	void nextDrawPosition(const int row, const int col);
	void adjustTextProperties(void);

public:
	Display();
	~Display();
	void redrawScreen(
		std::vector <std::vector <char>> & newTiles
	);
};

