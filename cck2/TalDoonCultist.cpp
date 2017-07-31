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

void TalDoonCultist::moveLeft(void) {}

void TalDoonCultist::moveRight(void) {}

void TalDoonCultist::moveUp(void) {}

void TalDoonCultist::moveDown(void) {}

void TalDoonCultist::giveDialogue(const string & text) {
	Debug::write(std::to_string(position.x));
}

void TalDoonCultist::patrol(void) {

}
