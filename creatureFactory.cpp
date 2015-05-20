#include "creature.h"
#include "demon.h"
#include "human.h"
#include "balrog.h"
#include "orc.h"

// Factory class to that creates creature objects
Creature* CreatureFactory::create(string creature_name)
{
	if (creature_name == "demon") 
		return new Demon;
	else if (creature_name == "human")
		return new Human;
	else if (creature_name == "balrog")
		return new Balrog;
	else if (creature_name == "orc")
		return new Orc;
	else 
		return new Creature;
}
