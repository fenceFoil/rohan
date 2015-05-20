#ifndef DEMON_H
#define DEMON_H

#include "creature.h"

class Demon : public Creature 
{
	public:
		Demon();
        Demon(string new_type, string weapon_type, int damage, int new_health):
			Creature(new_type, weapon_type, damage, new_health) {};
		int doAttack();
};

#endif
