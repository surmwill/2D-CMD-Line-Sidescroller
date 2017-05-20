#pragma once
#include <memory>
#include <vector>
#include "Observer.h"
#include <Windows.h>

struct DisplayImpl;

class Display final : public Observer {
	std::unique_ptr <DisplayImpl> displayImpl;

	virtual void addressTileChange(
		const Coordinate & tile,
		const char newDesign) override;

	void updateCursorPos(const int numWrites, COORD & cursor);
	void writeConsole(const WCHAR toWrite, const DWORD length, const COORD & cursor);

public:
	Display();
	~Display();
	void refreshScreen(void);
	void refreshMap(
		const std::vector <std::vector <char>> & newTiles
	);
};

