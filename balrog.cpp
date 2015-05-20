#include "balrog.h"

Balrog::Balrog() : Creature()
{
	creature_type = "balrog";
};

int Balrog::doAttack()
{
	int numAttacks = 3;
	int damage = creature_weapon -> getDamage();
	return numAttacks * damage;
};
