#ifndef BALROG_H
#define BALROG_H

#include "creature.h"

class Balrog : public Creature
{
	public:
		Balrog();
        Balrog(string new_type, string weapon_type, int damage, int new_health):
        	Creature( new_type, weapon_type, damage, new_health){};
		int doAttack();
};

#endif
