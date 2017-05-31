//***************************************************************************80
#pragma once

#include <vector>

struct Coordinate;

class Observer
{
public:
	virtual void addressTileChange( 
		Coordinate & tile,
		const char newDesign) = 0;

	inline virtual ~Observer() = default;

protected:
	Observer() = default;
};

