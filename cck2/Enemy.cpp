#include "Enemy.h"
#include "Coordinate.h"

using std::make_unique;
using std::shared_ptr;
using std::string;
using std::move;

shared_ptr <Observer> Enemy::map = nullptr;

Enemy::Enemy(
	const Coordinate & origin,
	const char tile,
	const int aggroRange,
	const int threat) : 
	position(origin), tile(tile), aggroRange(aggroRange), threat(threat) {

}

Enemy::~Enemy(void) {};

void Enemy::moveLeft(void) {}

void Enemy::moveRight(void) {}

void Enemy::moveUp(void) {}

void Enemy::moveDown(void) {}

void Enemy::giveDialogue(const string & text) {

}

void Enemy::patrol(void) {

}