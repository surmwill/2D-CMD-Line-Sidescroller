#pragma once
#include <memory>
#include "Subject.h"
#include "Coordinate.h"
#include "Combatent.h"

class Observer;
struct PlayerImpl;

class Player final : public Subject, public Combatent {
	std::unique_ptr <PlayerImpl> playerImpl;

public:
	Player(Observer * const map, const Coordinate playerStart);
	~Player();

	void moveLeft(void) override;
	void moveRight(void) override;
	void moveUp(void) override;
	void moveDown(void) override;
};

