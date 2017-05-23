#include "Player.h"
#include "PlayerImpl.h"

//to delete
#include "Iostream.h"
#include <vector>
#include "Coordinate.h"
using std::vector;

using std::make_unique;

/* Adds the map as one of the player's observers. When
the player moves, we update the portion of the map the player
can see. */
Player::Player(Observer * const map):
	playerImpl(make_unique <PlayerImpl> ()) {
	addObserver(map);
}

Player::~Player() {
}

Player & Player::moveLeft(void) {
	playerImpl->position.x -= 1;
	notifyTileChange(
		playerImpl->position, 
		playerImpl->playerTile
	);

	return *this;
}

Player & Player::moveRight(void) {
	playerImpl->position.x += 1;
	notifyTileChange(
		playerImpl->position,
		playerImpl->playerTile
	);

	return *this;
}

Player & Player::moveUp(void) {
	playerImpl->position.y -= 1;
	notifyTileChange(
		playerImpl->position,
		playerImpl->playerTile
	);

	return *this;
}

Player & Player::moveDown(void) {
	//we are reading lines further down in the file hence the '+'
	playerImpl->position.y += 1; 
	notifyTileChange(
		playerImpl->position,
		playerImpl->playerTile
	);

	return *this;
}