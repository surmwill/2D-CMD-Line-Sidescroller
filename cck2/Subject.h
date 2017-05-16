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

protected:
	Subject & addObserver(Observer * const obs);
	Subject() = default;
	virtual ~Subject() = 0;

private:
	std::vector <Observer*> observers;
};

