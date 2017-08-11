#include "TalDoonCultist.h"
#include "Coordinate.h"
#include "Debug.h"

using std::string;

TalDoonCultist::TalDoonCultist(const Coordinate & origin) : 
	Enemy(origin, 'T', 10, 0) {
}

TalDoonCultist::~TalDoonCultist()
{
}

Coordinate & TalDoonCultist::moveLeft(void) {
	return position;
}

Coordinate & TalDoonCultist::moveRight(void) {
	return position;
}

Coordinate & TalDoonCultist::moveUp(void) {
	return position;
}

Coordinate & TalDoonCultist::moveDown(void) {
	return position;
}

void TalDoonCultist::patrol(void) {

}

void TalDoonCultist::takeTurn(void) {
	giveDialogue(" ");
}
