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
 
#ifndef map_h
#define map_h

// map.h: map class and related stuff
#include <list>

#include "items.h"
#include "npc.h"
#include "player.h"

// our maximum map size (+/-)
#define max 30

class player;
class npc;

class map {
	public:
		map(int,int,int,int);
		virtual ~map();
		
		// public accessors
		int getMapMaxSizeX() const {return MapMaxSizeX;}
		int getMapMaxSizeY() const {return MapMaxSizeY;}
		int getMapMaxSizeNgX() const {return MapMaxSizeNgX;}
		int getMapMaxSizeNgY() const {return MapMaxSizeNgY;}
		
		// map methods
		void addItemX(item*,int);
		void addItemY(item*,int);
		void removeItemX(int);
		void removeItemY(int);

		// misc methods for map
		bool itemExists(int,int);

		item* identifyItem(int,int);
		std::string parseGroundID(int);
		TYPE checkItemType(int,int);

		int getGroundID() const {return groundID;}
		int saveMapData(int);
		int loadMapData(int);

		void removeFromList(player*);
		void removeFromList(npc*);
		
		// list of players on the map
		std::list<player*> players;

		// list of npcs on the map
		std::list<npc*> npcs;
		
	private:
		int MapMaxSizeX,MapMaxSizeY,MapMaxSizeNgY,MapMaxSizeNgX;
		int currentSquareX,currentSquareY,groundID;

		// the item coordinate arrays
		int itemSquareX[max],itemSquareY[max];
		int itemSquareNgX[max],itemSquareNgY[max];

		// the item object arrays
		item *itemLineX[max];
		item *itemLineY[max];
		item *itemLineNgX[max];
		item *itemLineNgY[max];
};

#endif
