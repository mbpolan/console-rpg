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

// items.cpp: declarations for item functions
#include "items.h"

// item class default constructor
item::item() {
	itemLocationX=0;
	itemLocationY=0;
	itemName="NULL";
	itemTYPE=npe;
};

// our item class constructor
item::item(std::string fixedItemName,int spawnX,int spawnY,TYPE thisType) {
	itemLocationX=spawnX;
	itemLocationY=spawnY;
	itemName=fixedItemName;
	itemTYPE=thisType;
};

// item class destructor
item::~item() {
};

// set item location on X
void item::setLocationX(int XLOCATION) {
	itemLocationX=XLOCATION;
};

// set item location on Y
void item::setLocationY(int YLOCATION) {
	itemLocationY=YLOCATION;
};

// check the item's enumerated type
TYPE item::checkType() {
	return itemTYPE;
};

// check if this item can be equipped on head slot
bool item::isHeadItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==head)
		return 1;
	else
		return 0;
};

// check if this item can be equipped on armor slot
bool item::isTorsoItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==torso)
		return 1;
	else
		return 0;
};

// check if this item can be equipped on legs slot
bool item::isLegsItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==legs)
		return 1;
	else
		return 0;
};

// check if this item can be equipped on boots slot
bool item::isBootsItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==boots)
		return 1;
	else
		return 0;
};

