#ifndef HUMAN_H
#define HUMAN_H

#include "creature.h"

class Human : public Creature
{
	public:
		Human();
        Human(string new_type, string weapon_type, int damage, int new_health):
        	Creature( new_type, weapon_type, damage, new_health){};
		int doAttack();
};

#endif
