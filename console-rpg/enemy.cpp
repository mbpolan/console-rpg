/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
 *   kanadakid@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
 #include <iostream>
 
 #include "enemy.h"
 
enemy::enemy() {
	x=0;
	y=0;
	layer=0;

	hp=100;
	mp=60;
	name="";
	
	luck=1;
	power=10;
	strength=10;
	defense=10;
	mlevel=10;
	
	isPoisonous=false;
	isElectric=false;
	isBurning=false;
	isStrong=false;
	
	attack_type=ATTACK_MELEE;
};

enemy::enemy(std::string _name, int _spawnX, int _spawnY, int _layer) {
	x=_spawnX;
	y=_spawnY;
	layer=_layer;
	
	hp=100;
	mp=60;
	name=_name;
	
	luck=1;
	power=10;
	strength=10;
	defense=10;
	
	isPoisonous=false;
	isElectric=false;
	isBurning=false;
	isStrong=false;
	
	attack_type=ATTACK_MELEE;
};

// method for changing attack damage based on skills
int enemy::enhanceAttack(int orig_damage) {
	switch(attack_type) {
		case ATTACK_MELEE: return ((orig_damage+strength)+(orig_damage+power)); break;
		case ATTACK_MAGIC: return ((orig_damage*mlevel)-10); break;
		case ATTACK_STRONG: return ((orig_damage+strength)+(orig_damage+power)+((orig_damage*mlevel)-50));
		default: return 0; break;
	}
};

// method for changing the damage about to be taken based on defense skill
int enemy::blockAttack(int orig_damage) {
	switch(attack_type) {
		case ATTACK_MELEE: return (orig_damage-defense*2); break;
		case ATTACK_MAGIC: return (orig_damage-defense+20); break;
		default: return 0; break;
	}
};

// method for adding some more damage if this enemy has special attributes
int enemy::addExtraDamageEffect(int orig_damage) {
	if (isPoisonous)
		orig_damage+=25;
	
	if (isElectric)
		orig_damage+=50;
		
	if (isBurning)
		orig_damage+=100;
	
	if (isStrong)
		orig_damage+=500;
};

void enemy::receiveAttack(battleAction *battle_act) {
	if (battle_act->getBuffer()[1] != 0x01 || !battle_act->isBuilt())
		return;
	
	attackAction *act=dynamic_cast<attackAction*> (battle_act);
	
	int damage=act->getDamage();
	
	// start parsing attack
	damage=blockAttack(damage); // block initial attack
	
	// apply any effects
	if (act->isBurning())
		isBurned=true;
	
	if (act->isElectrifying())
		isElectrified=true;
	
	if (act->isPoisonous())
		isPoisoned=true;
	
	this->hp-=damage;
	this->mp-=act->getManaReduction();
};
