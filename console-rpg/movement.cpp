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

// movement.h: definitions for movement class
#include <iostream>

#include "movement.h"
#include "utilities.h"
using namespace utilities;

// movement class default constructor
movement::movement() {
	fDay=true; // make it day by default
	stepCount=0;
	itemWarning="\nThere is an item here.";
};

// move north
void movement::moveN(player *Player,map *karte) {
	if (Player->x==0) {
		std::cout << "\nYou can't move any further north!\n";
		return;
	}

	Player->x-=1;
	std::cout << "\nMoved north.\n";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move south
void movement::moveS(player *Player,map *karte) {
	if (Player->x==karte->getMapMaxSizeX()) {
		std::cout << "\nYou can't move any further south!\n";
		return;
	}

	Player->x+=1;
	std::cout << "\nMoved south.\n";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move west
void movement::moveW(player *Player,map *karte) {
	if (Player->y==0) {
		std::cout << "\nYou can't move any further west!\n";
		return;
	}

	Player->y-=1;
	std::cout << "\nMoved west.\n";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move east
void movement::moveE(player *Player,map *karte) {
	if (Player->y==karte->getMapMaxSizeY())  {
		std::cout << "\nYou can't move any further east!\n";
		return;
	}

	Player->y+=1;
	std::cout << "\nMoved east.\n";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move northeast
void movement::moveNE(player *Player,map *karte) {
/*        if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}

	Player->y+=1;
	Player->x+=1;
	std::cout << "\nMoved northeast.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);*/

};

// move northwest
void movement::moveNW(player *Player,map *karte) {
/*        if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
        }

	Player->y-=1;
	Player->x+=1;
	std::cout << "\nMoved northwest.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);*/
};

// move southeast
void movement::moveSE(player *Player,map *karte) {
 /*       if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
	}

	Player->y+=1;
	Player->x-=1;
	std::cout << "\nMoved southeast.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);*/
};

// move southwest
void movement::moveSW(player *Player,map *karte) {
/*        if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}

	Player->y-=1;
	Player->x-=1;
	std::cout << "\nMoved southwest.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);*/
};
	
// look(): look command
void movement::look(player *Player,map *karte) {
	std::string groundType; // this is the ground type
	
	int gID=(karte->getGroundID());
	groundType=karte->parseGroundID(gID); // parse the id
	bool Npc=false;
	
	std::list<npc*>::iterator nit;
	for (nit=karte->npcs.begin();nit!=karte->npcs.end();++nit) {
		if ((*nit)) {
			if ((*nit)->posx==Player->x && (*nit)->posy==Player->y) {
				std::cout << std::endl << (*nit)->name << " is standing here.";
				Npc=true;
			}
		}
	} // for (...)

	if (karte->itemExists(Player->x,Player->y)) {
		item* theName=karte->getItem(Player->x,Player->y);

		if (theName)
			std::cout << "\nYou see " << theName->getName() << ".\n";
			
		if (theName && Npc)
			std::cout << "\nYou see " << theName->getName() << " on the ground.\n";
			
		return;
	}

	else
		std::cout << "\nYou see " << groundType << ".\n";
};

// place item on the map
void movement::placeItem(item *thisItem,map *karte) {
	item::itemCount+=1;
	karte->addItem(thisItem);

	// shows what this function is doing when called
	#ifdef DEBUG
		if (karte->itemExists(thisItem->x,thisItem->y)) {
			if (x!=0 && y!=0)
				std::cout << "\nItem added at " << itemX << "," << itemY << std::endl;
		}
		
		else if (!karte->itemExists(thisItem->x,thisItem->y)) {
			if (x!=0 && y!=0)
				std::cout << "\nFailed to add item at " << itemX << "," << itemY << std::endl;
		}
	#endif
};

// remove the item from the map
void movement::removeItem(map *karte,int x,int y) {
	karte->removeItem(x,y);
	item::itemCount-=1;

	// shows what this function is doing when called
	#ifdef DEBUG
//		item *thisItem=karte->getItem(x,y);
		if (karte->itemExists(x,y)) {
			if (x!=0 && y!=0)
				std::cout << "\nFailed to remove item at " << x << "," << y << std::endl;
		}
		
		else if (!karte->itemExists(x,y)) {
			if (x!=0 && y!=0)
				std::cout << "\nItem removed at " << x << "," << y << std::endl;
		}

//		delete thisItem;
	#endif
};

// method to add npc creatures to the map
void movement::placeNPC(npc *thisNPC,map *karte) {
	karte->npcs.push_back(thisNPC);
	int npcs=npc::getNpcsOn();
	
	npc::setNpcsOn(npcs+=1);
};

// spawn some initial map items/creatures
void movement::spawnMapItems(map *karte) {

	srand(static_cast<unsigned> (time(0)));
	
	for (int i=0;i<((karte->getMapMaxSizeX()*2)*4)*2;i++) {
		int x=(rand()%100);
		int y=(rand()%100);
		int id=(rand()%5)+1;
		
		// syntax for new item is id,x,y
		placeItem(new item(id,x,y),karte);
	}

	// syntax for new npcs is x,y,name
	placeNPC(new npc(26,26,"Mike"),karte);
};

// toggle between night and day, or increase step count if none
int movement::controlTime(int steps) {
	if (steps==500) { // toggle day/night now
		if (!fDay) { // if it is night
			std::cout << "\nIt is now day time.\n";
			stepCount=0;
			fDay=true;
			return 0;
		}
		if (fDay) { // if it is day
			std::cout << "\nIt is now night.\n";
			stepCount=0;
			fDay=false;
			return 0;
		}
	}

	if (steps!=500) // leave it at the current time
		stepCount++; // increment player steps
};

// fetch the current time
void movement::checkTime() {
	if (fDay)
		std::cout << "\nIt is day time.";
	if (!fDay)
		std::cout << "\nIt is night time.";
};

int movement::isOccupied(player *Player,map *karte) {
	std::list<player*>::iterator playerIt;
	std::list<npc*>::iterator npcIt;

	for (playerIt=karte->players.begin();playerIt!=karte->players.end();++playerIt) {
		if ((*playerIt!=Player)) {
			int x=(*playerIt)->x;
			int y=(*playerIt)->y;

			if (x==Player->x && y==Player->y)
				return BLOCK_PLAYER;
		}
	}

	for (npcIt=karte->npcs.begin();npcIt!=karte->npcs.end();++npcIt) {
		if ((*npcIt)) {
			int x=(*npcIt)->posx;
			int y=(*npcIt)->posy;

			if (x==Player->x && y==Player->y)
				return BLOCK_NPC;
		}
	}

	return CLEAR;
};

// get an NPC based on coordinates
npc* movement::getNPC(map *karte,int x,int y) {
	std::list<npc*>::iterator it;

	for (it=karte->npcs.begin();it!=karte->npcs.end();++it) {
		if ((*it)) {
			int nx=(*it)->posx;
			int ny=(*it)->posy;

			if (x==nx && y==ny)
				return (*it);
		}
	}
};

// get a player based on coordinates
player* movement::getPlayer(map *karte,int x,int y) {
	std::list<player*>::iterator it;

	for (it=karte->players.begin();it!=karte->players.end();++it) {
		if ((*it)) {
			int nx=(*it)->x;
			int ny=(*it)->y;

			if (x==nx && y==ny)
				return (*it);
		}
	}
};

// parse the creature and do some actions appropriately
void movement::parseCreature(map *karte,player *Player,int block) {
	if (block!=CLEAR) {
		if (block==BLOCK_NPC) {
			npc *myNpc=getNPC(karte,Player->x,Player->y);
			if (myNpc)
				std::cout << "(!) ~ You encounter " << myNpc->name << " (NPC) ~ (!)\n";
		}

		else if (block==BLOCK_PLAYER) {
			player *myPlayer=getPlayer(karte,Player->x,Player->y);
			if (myPlayer)
				std::cout << "(!) ~ You encounter " << myPlayer->getName() << " (Player) ~ (!)\n";
		}
	}
};
