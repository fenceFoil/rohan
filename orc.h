#ifndef ORC_H
#define ORC_H

#include "creature.h"
class Orc : public Creature
{
	public:
		Orc();
        Orc(string new_type, string weapon_type, int damage, int new_health):
        	Creature(new_type, weapon_type, damage, new_health) {}
		int doAttack();
};
#endif
