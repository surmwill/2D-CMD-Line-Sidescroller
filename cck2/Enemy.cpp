#include "Enemy.h"
#include "EnemyImpl.h"

using std::make_unique;
using std::shared_ptr;

shared_ptr <Observer> Enemy::map = nullptr;

Enemy::Enemy(const Coordinate & origin, const char tile) :
	enemyImpl(make_unique <EnemyImpl>(origin, tile)) {

}