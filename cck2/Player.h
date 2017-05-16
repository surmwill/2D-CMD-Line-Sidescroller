#pragma once
#include "Subject.h"
#include <memory>

class Observer;
struct PlayerImpl;

class Player final : public Subject {
	std::unique_ptr <PlayerImpl> playerImpl;

public:
	Player(Observer * const map);
	~Player();

	Player & moveLeft(void);
	Player & moveRight(void);
	Player & moveUp(void);
	Player & moveDown(void);
};

