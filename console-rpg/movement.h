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
 
#ifndef movement_h
#define movement_h

// movement.h: holds movement system and map stuff
#include "creature.h"
#include "map.h"

enum BLOCK {
	BLOCK_NPC,
	BLOCK_PLAYER,
	BLOCK_MONSTER,
	CLEAR
};

class movement { 
	public:
		movement(); // our constructor
		virtual ~movement() {};

		// movement methods
		void moveN(player*,map*);
		void moveS(player*,map*);
		void moveW(player*,map*);
		void moveE(player*,map*);
		void moveNE(player*,map*);
		void moveNW(player*,map*);
		void moveSE(player*,map*);
		void moveSW(player*,map*);

		// other methods
		void look(player*,map*);
		void placeItem(item*,map*);
		void removeItem(map*,int,int);
		
		void placeNPC(npc*,map*);
		
		void spawnMapItems(map*);
		int isOccupied(player*,map*);

		// get creatures methods
		npc *getNPC(map*,int,int);
		player *getPlayer(map*,int,int);
		void parseCreature(map*,player*,int);

		// time related methods
		void checkTime();
		int controlTime(int);
		int getStepCount() const {return stepCount;}

	private:
		std::string itemWarning;
		bool fDay;
		int stepCount;
};

#endif

