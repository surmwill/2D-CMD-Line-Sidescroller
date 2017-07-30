#include "Enemy.h"
#include "Coordinate.h"

using std::make_unique;
using std::shared_ptr;
using std::string;
using std::move;

shared_ptr <Observer> Enemy::map = nullptr;

Enemy::Enemy(
	const char tile,
	const int aggroRange, 
	const int threat) : 
	tile{ tile },
	aggroRange{ aggroRange }, 
	threat{ threat } {}

// Spawns an enemy at a specific position on the map
void Enemy::spawn(const Coordinate & origin) { this->position = origin; }

Enemy::~Enemy(void) {};

void Enemy::moveLeft(void) {}

void Enemy::moveRight(void) {}

void Enemy::moveUp(void) {}

void Enemy::moveDown(void) {}

void Enemy::giveDialogue(const string & text) {

}

void Enemy::patrol(void) {

}