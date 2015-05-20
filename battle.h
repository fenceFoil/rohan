#ifndef BATTLE_H
#define BATTLE_H

#include "creature.h"
#include "weapons.h"
#include "time.h"
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Battle {
private:
	string name; // The place where the battle is held.
	vector<Weapon*> weapon_types;
	vector<Creature*> creature1_army;
	vector<Creature*> creature2_army;
public:
	Battle();
	Battle(const Battle& battleObj);
	~Battle();
	void setName(string newName) {
		name = newName;
	}
	string getName() const {
		return name;
	}
	void createWeapons();
	void setArmy1(vector<Creature*>& army) {
		creature1_army = army;
	}
	void setArmy2(vector<Creature*>& army) {
		creature2_army = army;
	}
	void createArmyCreature1(string name_creature, int num_creature);
	void createArmyCreature2(string name_creature, int num_creature);
	void reportStats();
	void reportWeaponTypes();
	void reportArmyCreature1();
	void reportArmyCreature2();
	void creature1Attacks();
	void creature2Attacks();
	bool areCreaturesAlive();
	int getArmy1Size() {
		return creature1_army.size();
	}
	int getArmy2Size() {
		return creature2_army.size();
	}
	string victor();
	void printScoutSummary() const;
};

#endif
