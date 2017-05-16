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
	const vector <char> tiles,
	bool entireScreen,
	vector <Coordinate> * const tileCoords) {
	//if not entireScreen call notifyTileChange on each of the tileCoords
	//else call a new Observer abstract addressMultiTileChang fne which map and display will both have to implemenet
}

//Adds a single observer to the subject's notification list
Subject & Subject::addObserver(Observer * const obs) {
	observers.emplace_back(obs);
	return *this;
}
