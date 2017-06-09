#pragma once

// basic statistics
struct Statistics {
	int maxHealth; // The health pool
	int currentHealth; // The current health relative to the health pool
	int strength; // Used for physical weapons and wearing heavy armour
	int dexterity; // Used for range/accuracy with bows
	int agility; // Used for more action points and greater dodge chance
	int perception; // Used for critcal strikes
	int intelligence; // Used to lower cooldowns on abilites and learn new ones
	int spellPower; // Used to increase damage and duration on spells
	int tenacity; // Lowers the duration of deabilitating affects (stuns, silences, etc..)
	int armour; // Mitigates physical damage
	int magicAbsorbtion; // Mitigates magic damage
	int carryCapacity; // How much the player can carry
};

struct EnemyStats : public Statistics {
	int kindness; // Kidness determines if an enemy aggros and can unlock additionl dialogue for the player
	int cleverness; // How easily the enemy/player is fooled
	int leadership; // High leadership gives boosts to party members
};

struct PlayerStats : public EnemyStats {
	/* The player has additional social traits. They are meaningless with
	respect to combat but gives the player a more in depth view of the character 
	they built */
	int altruism; 
	int ego;
};

/* Equipment (weapons and armour) can boost any of the player's basic 
statistics as well as having their own unique properties listed below. */

struct ArmourStats : public Statistics {
	int durability; // every piece of armour/weapon will eventually break
	int weight; // every peice of armour/weapon has a weight
};

struct WeaponStats : public ArmourStats {
	int damage; // Weapons have an additional damage statistic
};