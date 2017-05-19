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

/* Updates the tiles at tileCoords of a change in design */
void Subject::notifyMultiTileChanges(
	vector <char> * const tiles,
	vector <Coordinate> * const tileCoords) {

	for (auto coord = tileCoords->rbegin(); coord != tileCoords->rend(); ++coord) {
		notifyTileChange(*coord, tiles->back());
		tiles->pop_back();
	}
}

//Adds a single observer to the subject's notification list
Subject & Subject::addObserver(Observer * const obs) {
	observers.emplace_back(obs);
	return *this;
}
