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
 
#ifndef npc_h
#define npc_h

// npc.h: NPC class declaration for most (if not all) NPC creatures

// needed libraries
#include <iostream>
#include <time.h>

// needed headers
#include "creature.h"
#include "map.h"
#include "player.h"

class map;

class npc: public creature {
	public:
		npc();
		npc(int,int,std::string _name); // our constructor
		~npc();

		// methods for npc entity
		int getHP() const {return hp;}
		void setHP(int _hp) {hp=_hp;}

		int getMP() const {return mp;}
		void setMP(int _mp) {mp=_mp;}

		void setName(std::string initialName) {name=initialName;}
		std::string getName() const {return name;}

		void setLuck(int _luck) {luck=_luck;};
		int getLuck() const {return luck;}

		void setPower(int _power) {power=_power;}
		int getPower() const {return power;}

		void setStrength(int _strength) {strength=_strength;}
		int getStrength() const {return strength;}

		void setDefense(int _defense) {defense=_defense;}
		int getDefense() const {return defense;}

		// methods for AI and actions
		ACTIONS preformThink(map*);
		void preformMove(map*,bool);
		void preformAction(int,ACTIONS);

		// other methods
		int getID() const {return id;}

		static void setNpcsOn(int npcs) {npcsOn=npcs;}
		static int getNpcsOn() {return npcsOn;}

		// coordinates
		int posx;
		int posy;

	private:
		int id;
		static int npcsOn;

		std::string name;
		int hp,mp,luck,strength,power,defense;
};

#endif
