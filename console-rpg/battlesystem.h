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
 
 // a class to manage data about an attack
 class attackAction {
 	public:
		// constructors
		attackAction();
		attackAction(int damage, int mana_reduc);
		
		// clear the entire action
		void clear();
		
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
		
		// methods to work on internal buffer
		void addByte(char);
		void addBuffer(std::string buf, bool clear=false);
		
		// build the complete action
		void build();
		bool isBuilt() const {return built;}
		
		// return the internal buffer of bytes
		std::string getBuffer() const {return buffer;}
		
	private:
		int attack_damage; // damage to be taken
		int mana_reduction; // mana to be reduced
		
		// effects
		bool poisonous, electrifying, burning, strong;
		
		// internal buffer
		std::string buffer;
		
		// is this action ready to be used?
		bool built;
};
