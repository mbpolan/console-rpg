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

// movement class default constructor
movement::movement() {
	fDay=true; // make it day by default
	stepCount=0;
	itemWarning="\nThere is an item here.";
};

// move north
void movement::moveN(player *Player,map *karte) {
	if (Player->x==karte->getMapMaxSizeX()) {
		std::cout << "\nYou can't move any further north!\n";
		return;
	}

	Player->x+=1;
	std::cout << "\nMoved north.\n";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move south
void movement::moveS(player *Player,map *karte) {
	if (Player->x==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further south!\n";
	}

	Player->x-=1;
	std::cout << "\nMoved south.\n";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move west
void movement::moveW(player *Player,map *karte) {
	if (Player->y==karte->getMapMaxSizeNgY()) {
		std::cout << "\nYou can't move any further west!\n";
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
	}

	Player->y+=1;
	std::cout << "\nMoved east.\n";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move northeast
void movement::moveNE(player *Player,map *karte) {
        if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}

	Player->y+=1;
	Player->x+=1;
	std::cout << "\nMoved northeast.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);

};

// move northwest
void movement::moveNW(player *Player,map *karte) {
        if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
        }

	Player->y-=1;
	Player->x+=1;
	std::cout << "\nMoved northwest.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move southeast
void movement::moveSE(player *Player,map *karte) {
        if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
	}

	Player->y+=1;
	Player->x-=1;
	std::cout << "\nMoved southeast.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};

// move southwest
void movement::moveSW(player *Player,map *karte) {
        if (Player->y==karte->getMapMaxSizeY() || Player->x==karte->getMapMaxSizeX()
        || Player->y==karte->getMapMaxSizeNgY() || Player->x==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}

	Player->y-=1;
	Player->x-=1;
	std::cout << "\nMoved southwest.";

	int block=isOccupied(Player,karte);

	parseCreature(karte,Player,block);
};
	
// look(): look command
void movement::look(player *Player,map *karte) {
	std::string groundType; // this is the ground type
	
	int gID=(karte->getGroundID());
	groundType=karte->parseGroundID(gID); // parse the id

	if (karte->itemExists(Player->x,Player->y)) {
		item* theName=karte->identifyItem(Player->x,Player->y);

		if (theName)
			std::cout << "You see " << theName->getName() << ".\n";

		else
			std::cout << "You see " << groundType << ".\n";
	}

	else
		std::cout << "\nYou see " << groundType << ".\n";
};

// place item on the map
void movement::placeItem(item *thisItem,map *karte) {
	int itemX=(thisItem->getLocationX());
	int itemY=(thisItem->getLocationY());
	
	karte->addItemX(thisItem,itemX);
	karte->addItemY(thisItem,itemY);
	
	// shows what this function is doing when called
	#ifdef DEBUG
		if (karte->itemExists(karte,itemX,itemY)) {
			if (x!=0 && y!=0)
				std::cout << "\nItem added at " << itemX << "," << itemY << std::endl;
		}
		
		else if (!karte->itemExists(karte,itemX,itemY)) {
			if (x!=0 && y!=0)
				std::cout << "\nFailed to add item at " << itemX << "," << itemY << std::endl;
		}
	#endif
};

// remove the item from the map
void movement::removeItem(map *karte,int x,int y) {
	karte->removeItemX(x);
	karte->removeItemY(y);

	// shows what this function is doing when called
	#ifdef DEBUG		
		if (karte->itemExists(karte,x,y)) {
			if (x!=0 && y!=0)
				std::cout << "\nFailed to remove item at " << x << "," << y << std::endl;
		}
		
		else if (!karte->itemExists(karte,x,y)) {
			if (x!=0 && y!=0)
				std::cout << "\nItem removed at " << x << "," << y << std::endl;
		}
	#endif
};

// fetch the player's current position on X/Y
int movement::getCurrentPosition(player *Player) const {
	std::cout << "X: " << Player->x << " Y: " << Player->y << std::endl;
};

// spawn some initial map items/creatures
void movement::spawnMapItems(movement *rhs,map *karte) {

	// syntax for new item is name,x,y,type.
	// then call placeItem to put these on the map.
	rhs->placeItem(new item("fern",1,2,npe),karte);
	rhs->placeItem(new item("rock",-1,-1,npe),karte);
	rhs->placeItem(new item("herb",-2,3,npe),karte);
	rhs->placeItem(new item("bush",-10,5,npe),karte);
	rhs->placeItem(new item("sunflowers",20,5,npe),karte);
	rhs->placeItem(new item("Leather Armor",4,6,torso),karte);

	// syntax for new npcs is x,y,name
	karte->npcs.push_back(new npc(2,3,"Mike"));
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
				std::cout << "(!) ~ You encounter " << myNpc->getName() << " (NPC) ~ (!)\n";
		}

		else if (block==BLOCK_PLAYER) {
			player *myPlayer=getPlayer(karte,Player->x,Player->y);
			if (myPlayer)
				std::cout << "(!) ~ You encounter " << myPlayer->getName() << " (Player) ~ (!)\n";
		}
	}
};
