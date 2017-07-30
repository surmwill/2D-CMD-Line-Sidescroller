#include "TalDoonCultist.h"
#include "Coordinate.h"
#include "Debug.h"

using std::string;

TalDoonCultist::TalDoonCultist(void) : 
	Enemy('T', 10, 0) {
}

TalDoonCultist::~TalDoonCultist()
{
}

void TalDoonCultist::moveLeft(void) {}

void TalDoonCultist::moveRight(void) {}

void TalDoonCultist::moveUp(void) {}

void TalDoonCultist::moveDown(void) {}

void TalDoonCultist::giveDialogue(const string & text) {
	Debug::write(text);
}

void TalDoonCultist::patrol(void) {

}
