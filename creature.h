#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include "weapons.h"

using std::string;

class Creature
{
	protected:
		string creature_type;
		Weapon* creature_weapon;
		int creature_health;
	public:
		Creature();
		Creature(string new_type, string weapon_type, int damage, int new_health);
		virtual ~Creature();
		string getCreatureType() {return creature_type;}
		virtual Weapon* getCreatureWeapon() {return creature_weapon;}
		int getHealth(){return creature_health;}
		void setCreatureType(string new_type) {creature_type = new_type;}
		void setWeapon(string weapon_type, int damage);  
		void setHealth(int new_health) {creature_health = new_health;}
		
        virtual int doAttack(); 
        void addDamage (int damage){creature_health -= damage;}
};

class CreatureCompare
{
public:
	bool operator() (Creature* creature1, Creature* creature2) const
	{
		return creature1->getHealth() > creature2->getHealth();
	}
};

class CreatureFactory {
	public:
		Creature* create(string creature_name);
};


#endif
