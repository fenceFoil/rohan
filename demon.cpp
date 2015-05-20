#include <iostream>
#include <cstdlib>

#include "demon.h"

//Constructor Default 
Demon::Demon() : Creature()
{
	creature_type = "demon";
}

int Demon::doAttack()
{
	int damage = creature_weapon -> getDamage();
	int percent = rand() % 100 + 1;
	if(percent <= 25)
	{
		damage = damage + 50;
	}
	return damage;
}
