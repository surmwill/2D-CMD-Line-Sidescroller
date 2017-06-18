#include "Enemy.h"
#include "EnemyImpl.h"
#include "Coordinate.h"

using std::make_unique;
using std::shared_ptr;

shared_ptr <Observer> Enemy::map = nullptr;

Enemy::Enemy(const Coordinate & origin, const char tile) :
	enemyImpl(make_unique <EnemyImpl>(origin, tile)) {

}

Enemy::~Enemy(void) {};

void Enemy::moveLeft(void) {}

void Enemy::moveRight(void) {}

void Enemy::moveUp(void) {}

void Enemy::moveDown(void) {}