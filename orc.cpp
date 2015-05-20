#include "orc.h"

Orc::Orc() : Creature()
{
	creature_type = "orc";
}

int Orc::doAttack()
{
	int damage = creature_weapon -> getDamage();
	return damage;
}
