#ifndef WEAPONS_H
#define WEAPONS_H

#include <iostream>
#include <string>

using std::string;

class Weapon
{
	private:
		string weapon_type;
		int damage;
	public:
		Weapon(){weapon_type = "unknown"; damage = 0;}
		Weapon(string new_weapon, int new_damage){weapon_type = new_weapon; damage = new_damage;}
		string getWeaponType() { return weapon_type;}
		int getDamage() { return damage;}
		void setWeaponType(string new_weapon) {weapon_type = new_weapon;}
		void setDamage(int new_damage) {damage = new_damage;}
};

#endif
