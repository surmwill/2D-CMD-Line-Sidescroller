#pragma once
#include <memory>
#include <vector>
#include "Observer.h"

struct DisplayImpl;

class Display final : public Observer {
	std::unique_ptr <DisplayImpl> displayImpl;

	virtual void addressTileChange(
		const Coordinate & tile,
		const char newDesign) override;

	virtual void addressFullTileChange(
		const std::vector <std::vector <char>> & newTiles
	) override;

public:
	Display();
	~Display();
	void refreshScreen(void);
};

