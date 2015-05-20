#include "battle.h"
#include "creature.h"
#include "weapons.h"
#include "time.h"
#include <cstdlib>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

// Maximum weapon damage, inclusive (lower bound is zero)
#define WEAPON_MAX_DAMAGE 100

Battle::Battle() {
}

Battle::Battle(const Battle& battleObj) {
	Weapon* weaponTemp;
	Creature* creatureTemp;
	CreatureFactory tempFactory;
	int armySize2 = battleObj.creature2_army.size(), armySize1 = battleObj.creature1_army.size();
	//Copy Weapons
	for (int i = 0; i < battleObj.weapon_types.size(); i++) {
		weaponTemp = new Weapon(battleObj.weapon_types[i]->getWeaponType(), battleObj.weapon_types[i]->getDamage());
		weapon_types.push_back(weaponTemp);
	}
	//Copy Creatures from Army 1
	for (int i = 0; i < armySize1; i++) {
		weaponTemp = battleObj.creature1_army[i]->getCreatureWeapon();
		creatureTemp = tempFactory.create(battleObj.creature1_army[i]->getCreatureType());
		creatureTemp->setWeapon(weaponTemp->getWeaponType(), weaponTemp->getDamage());
		creature1_army.push_back(creatureTemp);
	}
	//Copy Creatures from Army 2
	for (int i = 0; i < armySize2; i++) {
		weaponTemp = battleObj.creature2_army[i]->getCreatureWeapon();
		creatureTemp = tempFactory.create(battleObj.creature2_army[i]->getCreatureType());
		creatureTemp->setWeapon(weaponTemp->getWeaponType(), weaponTemp->getDamage());
		creature2_army.push_back(creatureTemp);
	}
}

Battle::~Battle() {
	// Delete contents of vectors to avoid memory leak.

	for (int i = 0; i < weapon_types.size(); i++) {
		delete weapon_types[i];
		weapon_types[i] = NULL;
	}

	for (int i = 0; i < creature1_army.size(); i++) {
		delete creature1_army[i];
		creature1_army[i] = NULL;
	}

	for (int i = 0; i < creature2_army.size(); i++) {
		delete creature2_army[i];
		creature2_army[i] = NULL;
	}
}

/**
 * Creates a random set of weapon types from which creatures will choose 
 * amongst when they are created.
 */
void Battle::createWeapons() {
	// Clear out any existing weapons
	for (int i = 0; i < weapon_types.size(); i++) {
		delete weapon_types[i];
	}
	weapon_types.clear();

	// Create some types of weapons, with cool names and damages between 0 and 100
	// Added a bunch of lord of the ring weapons 
	srand(time(NULL));
	Weapon* weapon = new Weapon("Megaspear", rand() % (WEAPON_MAX_DAMAGE + 1));
	weapon_types.push_back(weapon);
	weapon = new Weapon("Nerd-Slayer", rand() % (WEAPON_MAX_DAMAGE + 1));
	weapon_types.push_back(weapon);
	weapon = new Weapon("Homewrecker", rand() % (WEAPON_MAX_DAMAGE + 1));
	weapon_types.push_back(weapon);
	weapon = new Weapon("Aeglos", rand() % (WEAPON_MAX_DAMAGE + 1));
	weapon_types.push_back(weapon);
	weapon = new Weapon("Anglachel", rand() % (WEAPON_MAX_DAMAGE + 1));
	weapon_types.push_back(weapon);
	weapon = new Weapon("Black Arrow", rand() % (WEAPON_MAX_DAMAGE + 1));
	weapon_types.push_back(weapon);
	weapon = new Weapon("Glamdring", rand() % (WEAPON_MAX_DAMAGE + 1));
	weapon_types.push_back(weapon);
}

void Battle::createArmyCreature1(string name_creature, int num_creature) {
	// Set up a creature factory and discard any existing creatures in the army
	CreatureFactory creatureFactory = CreatureFactory();
	for (int i = 0; i < creature1_army.size(); i++) {
		delete creature1_army[i];
	}
	creature1_army.clear();

	// Populate army with a bunch of creatures
	for (int i = 0; i < num_creature; i++) {
		Creature* c = creatureFactory.create(name_creature);
		Weapon* w = weapon_types[rand() % weapon_types.size()];
		c->setWeapon(w->getWeaponType(), w->getDamage());
		creature1_army.push_back(c);
	}
}

void Battle::createArmyCreature2(string name_creature, int num_creature) {
	// Set up a creature factory and discard any existing creatures in the army
	CreatureFactory creatureFactory = CreatureFactory();
	for (int i = 0; i < creature2_army.size(); i++) {
		delete creature2_army[i];
	}
	creature2_army.clear();

	// Populate army with a bunch of creatures
	for (int i = 0; i < num_creature; i++) {
		Creature* c = creatureFactory.create(name_creature);
		//cout << "created creature 'c'" << endl;
		Weapon* w = weapon_types[rand() % weapon_types.size()];
		//cout << "retrieved weapon 'w'. Value of c = " << (c == NULL) << " " << c << " Value of w = " << (w == NULL) << " " << w << endl;
		c->setWeapon(w->getWeaponType(), w->getDamage());
		//cout << "setting the weapon of the creature with the values of 'w'" << endl;
		creature2_army.push_back(c);
		//cout << "adding the new creature 'c' to the vector" << endl;
	}
}

void Battle::printScoutSummary() const {
	cout << name << "     (" << creature2_army.size() << " " << creature2_army[0]->getCreatureType() << ")" << endl;
}

/**
 * Prints the current state of the two armies, including number of creatures 
 * and their Total health for each army and the health of monsters with the greatest
 * health.
 */
void Battle::reportStats() {
	if (creature1_army.size() > 0) {
		int numLivingArmy1 = 0, totalHealthArmy1 = 0, army1TopHealth = 0;
		for (int i = 0; i < creature1_army.size(); i++) {
			int health = creature1_army[i]->getHealth();
			if (health > 0) {
				totalHealthArmy1 += health;
				numLivingArmy1++;
				if (health > army1TopHealth)
					army1TopHealth = creature1_army[i]->getHealth();
			}
		}

		// Print statistics to console
		cout << "Army 1: " << numLivingArmy1 << " alive, total health of " << totalHealthArmy1 << endl;
		cout << "Army 1 creature with the most health has " << army1TopHealth << " hp" << endl;
	} else {
		cout << "Army 1 is dead." << endl;
	}

	// Find the number of living creatures in army 2
	// Find the average health of creatures in army 2
	if (creature2_army.size() > 0) {
		int numLivingArmy2 = 0, totalHealthArmy2 = 0, army2TopHealth = 0;
		for (int i = 0; i < creature2_army.size(); i++) {
			int health = creature2_army[i]->getHealth();
			if (health > 0) {
				totalHealthArmy2 += health;
				numLivingArmy2++;
				if (health > army2TopHealth)
					army2TopHealth = creature2_army[i]->getHealth();
			}
		}

		// Print statistics to console
		cout << "Army 2: " << numLivingArmy2 << " alive, total health of " << totalHealthArmy2 << endl;
		cout << "Army 2 creature with the most health has " << army2TopHealth << " hp" << endl;
	} else {
		cout << "Army 2 is dead." << endl;
	}
}

/**
 * Lists the types of weapons used for this battle.
 * Note that all weapons are not necessarily used -Matthew. 
 */
void Battle::reportWeaponTypes() {
	cout << "List of Weapons: " << endl;
	for (int i = 0; i < weapon_types.size(); i++) {
		cout << weapon_types[i]->getWeaponType() << ": Damage " << weapon_types[i]->getDamage() << endl;
	}
}

/**
 * Reports the creature type of the army. The army must already be created 
 * with >= 1 creature in it for this function to work.
 */
void Battle::reportArmyCreature1() {
	string creatureType = creature1_army[0]->getCreatureType();
	cout << "Army 1 is an army of " << creature1_army.size() << " " << creatureType << "s." << endl;
}

/**
 * Reports the creature type of the army. The army must already be created 
 * with >= 1 creature in it for this function to work.
 */
void Battle::reportArmyCreature2() {
	string creatureType = creature2_army[0]->getCreatureType();
	cout << "Army 2 is an army of " << creature2_army.size() << " " << creatureType << "s." << endl;
}

/**
 * Fights one round of the battle, consisting of a random attack from one 
 * creature from one army upon a random creature from the other army.
 */
void Battle::creature1Attacks() {
	// Note: Counts on srand() being called somewhere else

	// An empty army cannot attack, and cannot attack an empty army
	if (creature1_army.size() <= 0 || creature2_army.size() <= 0) {
		return;
	}

	// Select a random creature from both armies
	int army1Index = rand() % creature1_army.size();
	int army2Index = rand() % creature2_army.size();
	Creature* army1Creature = creature1_army[army1Index];
	Creature* army2Creature = creature2_army[army2Index];

	// Make one creature attack the other
	army2Creature->addDamage(army1Creature->doAttack());

	// Remove the hit creature from its army if it is dead
	if (army2Creature->getHealth() <= 0) {
		delete creature2_army[army2Index];
		creature2_army.erase(creature2_army.begin() + army2Index);
	}
}

/**
 * Fights one round of the battle, consisting of a random attack from one 
 * creature from one army upon a random creature from the other army.
 */
void Battle::creature2Attacks() {
	// Note: Counts on srand() being called somewhere else

	// An empty army cannot attack, and cannot attack an empty army
	if (creature1_army.size() <= 0 || creature2_army.size() <= 0) {
		return;
	}

	// Select a random creature from both armies
	int army1Index = rand() % creature1_army.size();
	int army2Index = rand() % creature2_army.size();
	Creature* army1Creature = creature1_army[army1Index];
	Creature* army2Creature = creature2_army[army2Index];

	// Make one creature attack the other
	army1Creature->addDamage(army2Creature->doAttack());

	// Remove the hit creature from its army if it is dead
	if (army1Creature->getHealth() <= 0) {
		delete creature1_army[army1Index];
		creature1_army.erase(creature1_army.begin() + army1Index);
	}
}

/**
 * Returns false if any army has no living creatures left in it
 */
bool Battle::areCreaturesAlive() {
	bool anArmyIsDead = false;

	// Check whether army 1 is slain
	int deadCritters = 0;
	for (int i = 0; i < creature1_army.size(); i++) {
		if (creature1_army[i]->getHealth() <= 0) {
			deadCritters++;
		}
	}
	if (deadCritters >= creature1_army.size()) {
		anArmyIsDead = true;
	}

	//  Check whether army 2 is slain
	deadCritters = 0;
	for (int i = 0; i < creature2_army.size(); i++) {
		if (creature2_army[i]->getHealth() <= 0) {
			deadCritters++;
		}
	}
	if (deadCritters >= creature2_army.size()) {
		anArmyIsDead = true;
	}

	return !anArmyIsDead;
}

/**
 * returns the name of the army that is still alive.  There cannot be a draw, 
 * since attacks are sequential, not simultaneous, and there has to be a final
 * creature to kill the second-to-final creature.
 */
string Battle::victor() {
	// Check whether army 1 is slain
	bool army1Wins = true;
	int army1Dead = 0;
	for (int i = 0; i < creature1_army.size(); i++) {
		if (creature1_army[i]->getHealth() <= 0) {
			army1Dead++;
		}
	}
	if (army1Dead >= creature1_army.size()) {
		army1Wins = false;
	}

	if (army1Wins) {
		return "Riders of Rohan";
	} else {
		return "Armies of Mordor";
	}
}
