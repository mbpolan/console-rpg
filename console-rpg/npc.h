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

// enumerated actions the NPC can preform
enum ACTIONS {
	MOVE_NORTH,
	MOVE_SOUTH,
	MOVE_WEST,
	MOVE_EAST,
	MOVE_NW,
	MOVE_NE,
	MOVE_SW,
	MOVE_SE,
	TALK,
	DROP_ITEM,

	MOVE, // this is generic
	DO_NOTHING // stand still
};

class map;

class npc: public creature {
	public:
		npc();
		npc(int,int,std::string _name); // our constructor
		~npc();

		ACTIONS preformThink(map*);
		void preformMove(map*,bool);
		void preformAction(int,ACTIONS);

	private:
		int posx, posy;
		std::string name;
};

#endif
