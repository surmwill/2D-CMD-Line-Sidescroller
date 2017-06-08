#pragma once

//ToDo finish list of statistics in the game

// statistics for living things in the game (player and enemies)
struct LivingStatistics {
	int maxHealth; // The health pool
	int currentHealth; // The current health relative to the health pool
	int strength; // Used for physical weapons and wearing heavy armour
	int dexterity; // Used for range/accuracy with bows
	int agility; // Used for more action points and greater dodge chance
	int perception; // Used for critcal strikes
	int intelligence; // Used to lower cooldowns on abilites and learn new ones
	int spellPower; // Used to increase damage and duration on spells
	int tenacity; // Lowers the duration of deabilitating affects (stuns, silences, etc..)
};

struct PlayerStats : public LivingStatistics {

};

struct EnemyStats : public LivingStatistics {

};

// Statistics for equipment in the game (weapons and armour)
struct EquipmentStatistics {
	int durability;
};

struct WeaponStats : public EquipmentStatistics {
	int attack;
};

struct ArmourStats : public EquipmentStatistics {
	int armour;
};