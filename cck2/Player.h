#pragma once
#include <memory>
#include "Combatent.h"
#include "Subject.h"
#include "Coordinate.h"

class Observer;
struct PlayerImpl;

class Player final : public Subject, public Combatent {
	std::unique_ptr <PlayerImpl> playerImpl;

public:
	Player(Observer * const map, const Coordinate playerStart);
	~Player();

	Player & moveLeft(void);
	Player & moveRight(void);
	Player & moveUp(void);
	Player & moveDown(void);
};

