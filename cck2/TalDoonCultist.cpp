#include "TalDoonCultist.h"
#include "Coordinate.h"

using std::string;

const int TalDoonCultist_aggroRange = 10;
const int TalDoonCultist_threat = 10;

TalDoonCultist::TalDoonCultist(const Coordinate & origin, const char tile) : 
	Enemy(origin, tile, TalDoonCultist_aggroRange, TalDoonCultist_threat) {
}


TalDoonCultist::~TalDoonCultist()
{
}

void TalDoonCultist::moveLeft(void) {}

void TalDoonCultist::moveRight(void) {}

void TalDoonCultist::moveUp(void) {}

void TalDoonCultist::moveDown(void) {}

void TalDoonCultist::giveDialogue(const string & text) {

}

void TalDoonCultist::patrol(void) {

}
