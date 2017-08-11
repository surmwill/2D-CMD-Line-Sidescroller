#pragma once

#include "Coordinate.h"
#include "Milestones.h"
#include "Statistics.h"
#include "Dialogue.h"

struct PlayerImpl {
	PlayerImpl(const Coordinate playerStart, const Dialogue & userInterface) :
		position(playerStart),
		userInterface(userInterface) {};

	Coordinate position;
	const char playerTile = '+';

	// Used to track the player's progression through the game
	Milestones milestones;

	// Information about the player (attack, health, etc..)
	PlayerStats stats;

	Dialogue userInterface;
};
