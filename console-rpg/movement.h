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
#include "battlesystem.h"
#include "creature.h"
#include "map.h"
#include "npc.h"
#include "player.h"

enum BLOCK {
	BLOCK_NPC,
	BLOCK_PLAYER,
	BLOCK_MONSTER,
	CLEAR
};

class battleClass;
class enemy;
class map;
class npc;
class player;

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
		void removeItem(map*, int, int, int);
		
		void placeNPC(npc*,map*);
		
		void spawnMapItems(map*);
		int isOccupied(player*,map*);
		int isSpecialTile(player*, map*);

		// get creatures methods
		npc *getNPC(map*, int, int, int);
		player *getPlayer(map*, int, int, int);
		void parseCreature(map*,player*,int);
		void parseSpecialTile(int);
		
		// various actions
		void layerAction(player*, int);

		// time related methods
		void checkTime();
		int controlTime(int);
		int getStepCount() const {return stepCount;}
		
		// battle related methods
		bool startBattle(player*, enemy*, map*, int x, int y, int layer);
		bool endBattle(player*);

	private:
		void initBattle(); // begin the actual battle
	
		std::string itemWarning;
		bool fDay;
		int stepCount;
		
		battleClass *currentBattle;
};

#endif

