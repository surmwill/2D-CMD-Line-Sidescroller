#pragma once
#include "Enemy.h"
#include <string>
#include "Coordinate.h"

class TalDoonCultist : public Enemy {

public:
	TalDoonCultist(void);
	virtual ~TalDoonCultist();

	/* Overwrites from Enemy */
	virtual void moveLeft(void) override;
	virtual void moveRight(void) override;
	virtual void moveUp(void) override;
	virtual void moveDown(void) override;

	virtual void giveDialogue(const std::string & text) override;
	virtual void patrol(void) override;
	/* End of overwrites from combatent */

};

