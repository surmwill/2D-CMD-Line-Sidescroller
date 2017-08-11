#include "Enemy.h"
#include "Coordinate.h"

using std::make_unique;
using std::shared_ptr;
using std::string;
using std::move;

Observer * Enemy::map;

Enemy::Enemy(
	const Coordinate & origin,
	const char tile,
	const int aggroRange, 
	const int threat) : 
	position { origin },
	tile{ tile },
	aggroRange{ aggroRange }, 
	threat{ threat } {}

// Spawns an enemy at a specific position on the map
void Enemy::spawn(const Coordinate & origin) { this->position = origin; }

Enemy::~Enemy(void) {};

Coordinate & Enemy::moveLeft(void) {
	return position;
}

Coordinate & Enemy::moveRight(void) {
	return position;
}

Coordinate & Enemy::moveUp(void) {
	return position;
}

Coordinate & Enemy::moveDown(void) {
	return position;
}

void Enemy::giveDialogue(const string & text, bool slowType) {

}

void Enemy::patrol(void) {

}

bool Enemy::aggrod(const Coordinate & playerPosition) {
	return true;
}
