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
 #include <vector>
 
 // an enumeration of different effects
 enum statusEffect { EFFECT_NONE=0x00, EFFECT_POISON=0x01, EFFECT_ELECTRIC=0x02, EFFECT_BURN=0x03 };
 
 // adt class
 class battleAction {
 	public:
		battleAction();
		
		// reset the entire action
		virtual void clear();
		
		// methods to work on internal buffer
		virtual void addByte(char);
		virtual void addBuffer(std::string buf, bool clear=false);
		
		// get the first byte from the buffer
		char header() const {return (char) buffer[0];}
		
		// build the complete action
		virtual void build();
		bool isBuilt() const {return built;}
		
		// return the internal buffer of bytes
		std::string getBuffer() const {return buffer;}
		
	protected:
		// internal buffer
		std::string buffer;
		
		// is this action ready to be used?
		bool built;
};
 
 // a class to manage data about an attack
 class attackAction: public battleAction {
 	public:
		// constructors
		attackAction();
		attackAction(int damage, int mana_reduc);
		
		// clear the entire action
		virtual void clear();
		
		// methods to work on internal buffer
		virtual void addByte(char);
		virtual void addBuffer(std::string buf, bool clear=false);
		
		// simple action access functions
		void setDamage(int _damage) {attack_damage=_damage;}
		int getDamage() const {return attack_damage;}
		
		void setManaReduction(int _reduction) {mana_reduction=_reduction;}
		int getManaReduction() const {return mana_reduction;}
		
		void setPoisonous(bool p) {poisonous=p;}
		bool isPoisonous() const {return poisonous;}
		
		void setElectrifying(bool e) {electrifying=e;}
		bool isElectrifying() const {return electrifying;}
		
		void setBurning(bool b) {burning=b;}
		bool isBurning() const {return burning;}
		
		void setStrong(bool s) {strong=s;}
		bool isStrong() const {return strong;}
		
		// (virtual) build the complete action
		virtual void build();
		
	protected:
		int attack_damage; // damage to be taken
		int mana_reduction; // mana to be reduced
		
		// effects
		bool poisonous, electrifying, burning, strong;
};

// class to manage info about a special type of attack
class spAttackAction: public attackAction {
	public:
		spAttackAction();
		spAttackAction(int damage, int mana_reduc, int count=1);
		
		// methods to work on internal buffer
		virtual void addByte(char);
		virtual void addBuffer(std::string buf, bool clear=false);
		
		void addTurnEffect(int turn, statusEffect effect, bool replace=false); // add an effect to take place on a specific turn
		statusEffect getTurnEffect(int turn) const {return effects[turn];}
		
		// (virtual) build the complete action
		virtual void build();
		
	protected:
		std::vector<statusEffect> effects; // effects on turn, TODO: multiple effects per turn
		int count;
};

// class to manage info about a magic attack
class magicAttackAction: public spAttackAction {
	public:
		magicAttackAction();
		magicAttackAction(int damage, int mana_reduc, int count=1, statusEffect effect=EFFECT_NONE);
		
		// methods to work on internal buffer
		virtual void addByte(char);
		virtual void addBuffer(std::string buf, bool clear=false);
		
		// (virtual) build the complete action
		virtual void build();
		
	protected:
		std::string name; // attack name
};
