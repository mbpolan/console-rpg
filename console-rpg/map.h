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

// our maximum map size
#define max 50

class item;
class player;
class npc;

class map {
	public:
		map() {};
		map(int,int,int,int);
		virtual ~map();
		
		// public accessors
		int getMapMaxSizeX() const {return MapMaxSizeX;}
		int getMapMaxSizeY() const {return MapMaxSizeY;}
		
		// map methods
		void addItem(item*);
		void removeItem(int, int, int);

		// misc methods for map
		bool itemExists(int, int, int);

		item* getItem(int, int, int);
		std::string parseGroundID(int);
		TYPE checkItemType(int, int, int);

		int getGroundID() const {return groundID;}
		int saveMapData(int);
		int loadMapData(int);

		void removeFromList(player*);
		void removeFromList(npc*);

		void creaturesDoAction();

		// list of players on the map
		std::list<player*> players;

		// list of npcs on the map
		std::list<npc*> npcs;

		// list of all items on the map
		std::list<item*> items;
		
		// list of all special items/tiles on map
		std::list<item*> spItems;
		
	private:
		int MapMaxSizeX,MapMaxSizeY;
		int currentSquareX,currentSquareY,groundID;
};

#endif
