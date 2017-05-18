#include "Subject.h"
#include "Observer.h"
#include "Coordinate.h"

using std::vector;
using std::pair;

Subject::~Subject() {};

/* Notifies the map/display (depending on the subject) 
when a tile changes value. */
void Subject::notifyTileChange(
	const Coordinate & tile,
	const char newDesign) {
	for (auto &obs : observers) {
		obs->addressTileChange(tile, newDesign);
	}
}

void Subject::notifyMultiTileChanges(
	vector <char> * const tiles,
	bool entireScreen,
	vector <Coordinate> * const tileCoords) {

	/* If it's a full screen we don't need to know which tiles need changing
	b/c they all do. Otherwise we individually notify each tile that needs changing */
	if (!entireScreen) {
		for (auto coord = tileCoords->rbegin(); coord != tileCoords->rend(); ++coord) {
			notifyTileChange(*coord, tiles->back());
			tiles->pop_back();
		}
	}
	else {
		for (auto &obs : observers) {
			obs->addressFullTileChange(*tiles);
		}
	}
}

//Adds a single observer to the subject's notification list
Subject & Subject::addObserver(Observer * const obs) {
	observers.emplace_back(obs);
	return *this;
}
