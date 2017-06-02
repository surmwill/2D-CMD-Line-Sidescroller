//***************************************************************************80
#pragma once

#include <vector>

struct Coordinate;

class Observer
{
public:
	/* Signals that a tile needs to be changed. Returns false
	if that tile cannot be changed */
	virtual bool addressTileChange( 
		const Coordinate & tile,
		const char newDesign) = 0;

	inline virtual ~Observer() = default;

protected:
	Observer() = default;
};

