#include "human.h"
#include <cstdlib>

Human::Human() : Creature()
{
	creature_type = "human";
};

int Human::doAttack()
{
	int damage = creature_weapon -> getDamage();
	int chanceDoubling = rand() % 100 + 1;
	if (chanceDoubling <= 15)
	{
		damage = damage * 2;
	}
	return damage;
};
