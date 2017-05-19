//***************************************************************************80
#pragma once

#include <vector>

struct Coordinate;

class Observer
{
public:
	virtual void addressTileChange( 
		const Coordinate & tile,
		const char newDesign) = 0;

	virtual void addressFullTileChange(
		const std::vector <std::vector <char>> & newTiles
	);

	inline virtual ~Observer() = default;

protected:
	Observer() = default;
};

