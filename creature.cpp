#include <iostream>
#include <string>
#include <cstdlib>
#include "creature.h"
#include "weapons.h"
using namespace std;

Creature::Creature() : creature_type("Default Creature Type"), creature_health(rand()%100+1) {
    creature_weapon = new Weapon();
}	
Creature::Creature(string new_type, string weapon_type, int damage, int
new_health){
    creature_type = new_type;
    creature_weapon = new Weapon(weapon_type, damage);
    creature_health = new_health;
}
Creature::~Creature(){
    delete creature_weapon;
    creature_weapon = NULL;    
}

void Creature::setWeapon(string weapon_type, int damage){
    creature_weapon->setWeaponType(weapon_type);
    creature_weapon->setDamage(damage);
}

int Creature::doAttack(){
    int damage = creature_weapon -> getDamage();
    cout << "Default Attack" << endl;    
    return damage;
}
