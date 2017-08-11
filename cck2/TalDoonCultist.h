#pragma once
#include "Enemy.h"
#include <string>
#include "Coordinate.h"

class TalDoonCultist : public Enemy {

public:
	TalDoonCultist(const Coordinate & origin);
	virtual ~TalDoonCultist();

	/* Overwrites from Enemy */
	virtual Coordinate & moveLeft(void) override;
	virtual Coordinate & moveRight(void) override;
	virtual Coordinate & moveUp(void) override;
	virtual Coordinate & moveDown(void) override;

	virtual void patrol(void) override;
	virtual void takeTurn(void) override;
	/* End of overwrites from combatent */

};

