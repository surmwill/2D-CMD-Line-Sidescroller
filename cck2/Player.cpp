#include "Player.h"
#include "PlayerImpl.h"

//to delete
#include "Iostream.h"
#include <vector>
#include "Coordinate.h"
#include "Debug.h"

using std::vector;
using std::make_unique;
using std::string;

/* Adds the map as one of the player's observers. When
the player moves, we update the portion of the map the player
can see. */
Player::Player(Observer * const map, const Coordinate playerStart, const Dialogue & userInterface):
	playerImpl(make_unique <PlayerImpl> (playerStart, userInterface)) {
	addObserver(map);
}

Player::~Player() {
}

Coordinate & Player::moveLeft(void) {
	// The hypothetical next position on the map
	const Coordinate possiblePosition{ 
		playerImpl->position.x - 1, 
		playerImpl->position.y };

	/* If the next position is valid (no walls, etc...) update
	the player's position */
	if (notifyTileChange(
		possiblePosition,
		playerImpl->playerTile)) playerImpl->position = possiblePosition;

	return playerImpl->position;
}

Coordinate & Player::moveRight(void) {
	const Coordinate possiblePosition{
		playerImpl->position.x + 1,
		playerImpl->position.y };

	if (notifyTileChange(
		possiblePosition,
		playerImpl->playerTile)) playerImpl->position = possiblePosition;

	return playerImpl->position;
}

Coordinate & Player::moveUp(void) {
	const Coordinate possiblePosition{
		playerImpl->position.x,
		playerImpl->position.y - 1 };

	if (notifyTileChange(
		possiblePosition,
		playerImpl->playerTile)) playerImpl->position = possiblePosition;

	return playerImpl->position;
}

Coordinate & Player::moveDown(void) {
	//we are reading lines further down in the file hence the "y + 1"
	const Coordinate possiblePosition{
		playerImpl->position.x,
		playerImpl->position.y + 1};

	if (notifyTileChange(
		possiblePosition,
		playerImpl->playerTile)) playerImpl->position = possiblePosition;

	return playerImpl->position;
}

Coordinate & Player::position(void) {
	return playerImpl->position;
}

void Player::giveDialogue(const string & text, bool slowType) {
	playerImpl->userInterface.displayDialogue("", "What should I do?", 0, 0, slowType);
}

void Player::takeTurn(void) {
	giveDialogue("test");
}