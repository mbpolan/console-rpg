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
void movement::moveN(map *karte) {
	if (karte->getCurrentSpaceX()==karte->getMapMaxSizeX()) {
		std::cout << "\nYou can't move any further north!";
	}
	else {
		int x=karte->getCurrentSpaceX();
		int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceX(++x);
		std::cout << "\nMoved north.";
	}
};

// move south
void movement::moveS(map *karte) {
	if (karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further south!";
	}
	else {
		int x=karte->getCurrentSpaceX();
		int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceX(--x);
		std::cout << "\nMoved south.";
	}
};

// move west
void movement::moveW(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY()) {
		std::cout << "\nYou can't move any further west!";
	}
	else {
		int y=karte->getCurrentSpaceY();
		int x=karte->getCurrentSpaceX();
		karte->setCurrentSpaceY(--y);
		std::cout << "\nMoved west.";
	}
};

// move east
void movement::moveE(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY())  {
		std::cout << "\nYou can't move any further east!";
	}
	else { 
		int y=karte->getCurrentSpaceY();
		int x=karte->getCurrentSpaceX();
		karte->setCurrentSpaceY(++y);
		std::cout << "\nMoved east.";
	}
};

// move northeast
void movement::moveNE(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX() 
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}
	else {
                int x=karte->getCurrentSpaceX();
                int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(++y);
		karte->setCurrentSpaceX(++x);
		std::cout << "\nMove northeast.";
	}
};

// move northwest
void movement::moveNW(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX()
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
        }
	else {
                int x=karte->getCurrentSpaceX();
                int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(--y);
		karte->setCurrentSpaceX(++x);
		std::cout << "\nMoved northwest.";
	}
};

// move southeast
void movement::moveSE(map *karte) {
        if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX()
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
	}
	else {
                int x=karte->getCurrentSpaceX();
                int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(++y);
		karte->setCurrentSpaceX(--x);
		std::cout << "\nMoved southeast.";
	}
};

// move southwest
void movement::moveSW(map *karte) {
        if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX()
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}
	else {
		int x=karte->getCurrentSpaceX();
		int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(--y);
		karte->setCurrentSpaceX(--x);
		std::cout << "\nMoved southwest.";
	}
};
	
// look(): look command
void movement::look(map *karte) {
	std::string groundType; // this is the ground type
	
	int gID=(karte->getGroundID());
	groundType=karte->parseGroundID(gID); // parse the id
	
	if (karte->itemExists(karte,karte->getCurrentSpaceX(),karte->getCurrentSpaceY())) {
		item* theName=karte->identifyItem(karte);
		
		if (theName!=NULL)
			std::cout << "\nYou see " << theName->getName() << ".\n";
		
		else
			std::cout << "\nYou see " << groundType << ".";
	}
	else
		std::cout << "\nYou see " << groundType << ".";
	// If there is an item on the ground, then display item instead
	// of ground type. (Do this later)
};

// place item on the map
void movement::placeItem(item *thisItem,map *karte) {
	int itemX=(thisItem->getLocationX());
	int itemY=(thisItem->getLocationY());
	
	karte->addItemX(thisItem,itemX);
	karte->addItemY(thisItem,itemY);
	
	// shows what this function is doing when called
	#ifdef DEBUG
		int x=karte->getCurrentSpaceX();
		int y=karte->getCurrentSpaceY();
		
		if (karte->itemExists(karte,x,y)) {
			if (x!=0 && y!=0)
				std::cout << "\nItem added at " << x << "," << y << std::endl;
		}
		
		else if (!karte->itemExists(karte,x,y)) {
			if (x!=0 && y!=0)
				std::cout << "\nFailed to add item at " << x << "," << y << std::endl;
		}
	#endif
};

// remove the item from the map
void movement::removeItem(map *karte) {
	int x=karte->getCurrentSpaceX();
	int y=karte->getCurrentSpaceY();
	
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
int movement::getCurrentPosition(map *karte) const {
	int x=karte->getCurrentSpaceX();
	int y=karte->getCurrentSpaceY();
	std::cout << "X: " << x << " Y: " << y << std::endl;
};

// spawn some initial map items
void movement::spawnMapItems(movement *rhs,map *karte) {

	// syntax for new item is name,x,y,type.
	// then call placeItem to put these on the map.
	item *plant0=new item("fern",1,2,npe);
	rhs->placeItem(plant0,karte);

	item *rock0=new item("rock",-1,-1,npe);
	rhs->placeItem(rock0,karte);

	item *plant1=new item("herb",-2,3,npe);
	rhs->placeItem(plant1,karte);

	item *plant2=new item("bush",-10,5,npe);
	rhs->placeItem(plant2,karte);

	item *plant3=new item("sunflowers",20,5,npe);
	rhs->placeItem(plant3,karte);

	item *equip=new item("Leather Armor",4,6,torso);
	rhs->placeItem(equip,karte);
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
		std::cout << "\nIt is day time.\n";
	if (!fDay)
		std::cout << "\nIt is night time.\n";
};

