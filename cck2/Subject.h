//***************************************************************************80
#pragma once
#include <vector>

class Observer;
struct Coordinate;

class Subject {
public:
	void notifyTileChange(
		const Coordinate & tile,
		const char newDesign);

	void notifyMultiTileChanges(
		std::vector <char> * const tiles,
		std::vector <Coordinate> * const tileCoords);

	void notifyMultiTileChanges(
		std::vector <std::vector <char>> * const fullTiles
	);

protected:
	Subject & addObserver(Observer * const obs);
	Subject() = default;
	virtual ~Subject() = 0;

private:
	std::vector <Observer*> observers;
};

