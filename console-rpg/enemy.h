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
 
 #include "creature.h"
 #include "battlesystem.h"
 
 // ways to attack
 enum ATTACKS { ATTACK_MELEE=0x00, ATTACK_MAGIC=0x01, ATTACK_STRONG=0x02 };
 
 // attack type
 typedef ATTACKS attack_t;
 
 // a class for monsters and creatures that are attackable
 class enemy: public creature {
 	public:
		enemy();
		enemy(std::string, int, int, int);
		
		// some simple functions (from creature.h)
		virtual int getHP() const {return hp;}
		virtual void setHP(int _hp) {hp=_hp;}

		virtual int getMP() const {return mp;}
		virtual void setMP(int _mp) {mp=_mp;}

		virtual void setName(std::string _n) {name=_n;}
		virtual std::string getName() const {return name;}

		virtual void setLuck(int _l) {luck=_l;}
		virtual int getLuck() const {return luck;}

		virtual void setPower(int _p) {power=_p;}
		virtual int getPower() const {return power;}

		virtual void setStrength(int _s) {strength=_s;}
		virtual int getStrength() const {return strength;}
		
		virtual void setDefense(int _d) {defense=_d;}
		virtual int getDefense() const {return defense;}
		
		// accessor methods
		void setPoisonous(bool x) {isPoisonous=x;}
		bool poisonous() const {return isPoisonous;}
		
		void setElectric(bool x) {isElectric=x;}
		bool electric() const {return isElectric;}
		
		void setBurning(bool x) {isBurning=x;}
		bool burning() const {return isBurning;}
		
		void setStrong(bool x) {isStrong=x;}
		bool strong() const {return isStrong;}
		
		void setLayer(int _layer) {layer=_layer;}
		int getLayer() const {return layer;}
		
		// battle methods
		int enhanceAttack(int);
		int blockAttack(int);
		int addExtraDamageEffect(int);
		void receiveAttack(battleAction*);
		
		// map coordinates
		int x, y;
		
	private:
		int hp, mp, mlevel; // hitpoints, mana, and magic level
		std::string name; // name
		
		int luck, power, strength, defense; // melee attributes
		int layer; // what layer this enemy is on
		
		// enemy's special attributes
		bool isPoisonous, isElectric, isBurning, isStrong;
		
		attack_t attack_type; // the prefered way to attack
};
