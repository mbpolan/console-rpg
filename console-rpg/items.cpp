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

int item::itemCount=0;

// item class default constructor
item::item() {
	x=0;
	y=0;
	itemName="NULL";
	itemTYPE=npe;
};

// copy constructor
item::item(item *rhs) {
	x=rhs->x;
	y=rhs->y;

	itemName=rhs->getName();
	itemTYPE=rhs->checkType();
};

// lesser item constructor
item::item(int id) {
	parseItem(id);
	itemID=id;
};

// type inclusive constructor
item::item(int id,TYPE type) {
	parseItem(id);
	itemID=id;
	itemTYPE=type;
};

// our item class constructor
item::item(int id,int spawnX,int spawnY) {
	parseItem(id);
	x=spawnX;
	y=spawnY;
	
	itemID=id;
};

item::item(int id,const char* cx,const char* cy,const char* valid) {
	parseItem(id);
	
	x=atoi(cx);
	y=atoi(cy);
	
	if (strcmp(valid,"1"))
		isValid=true;
	else
		isValid=false;
		
	itemID=id;
};	

// item class destructor
item::~item() {
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

// method for making items unusable
void item::invalidateItem(item *thisItem) {
	isValid=false;
};

xmlNodePtr item::compressToXML() {
	std::stringstream ss;
	xmlNodePtr ptr;
	
	ptr=xmlNewNode(NULL,(const xmlChar*) "item");
	
	ss << itemID;
	xmlSetProp(ptr,(const xmlChar*) "id",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << x;
	xmlSetProp(ptr,(const xmlChar*) "x",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << y;
	xmlSetProp(ptr,(const xmlChar*) "y",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	if (isValid)
		ss << 1;
	else
		ss << 0;
	
	xmlSetProp(ptr,(const xmlChar*) "valid",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	return ptr;
};

void item::parseItem(int id) {
	switch(id) {
		// generic
		case 0: itemName="nothing"; itemTYPE=npe; break;
		// inanimate objects
		case 1: itemName="a bush"; itemTYPE=npe; break;
		case 2: itemName="a rock"; itemTYPE=npe; break;
		case 3: itemName="sunflowers"; itemTYPE=npe; break;
		case 4: itemName="a fern"; itemTYPE=npe; break;
		case 5: itemName="an herb"; itemTYPE=npe; break;
		case 6: itemName=""; itemTYPE=npe; break;
		
		// equipment
		// armors
		case 100: itemName="Jacket"; itemTYPE=torso; break;
		case 101: itemName="Leather Armor"; itemTYPE=torso; break;
		case 102: itemName="Chain Mail"; itemTYPE=torso; break;
		case 103: itemName="Full Chain Armor"; itemTYPE=torso; break;
		case 104: itemName="Steel Mail"; itemTYPE=torso; break;
		case 105: itemName="Full Steel Armor"; itemTYPE=torso; break;
		
		// legs
		case 114: itemName="Leather Legs"; itemTYPE=legs; break;
		case 115: itemName="Chain Legs"; itemTYPE=legs; break;
		case 116: itemName="Light Steel Legs"; itemTYPE=legs; break;
		case 117: itemName="Heavy Steel Legs"; itemTYPE=legs; break;
		case 118: itemName="Fighter Legs"; itemTYPE=legs; break;
		case 119: itemName="Noble Legs"; itemTYPE=legs; break;
		case 120: itemName="Warrior Legs"; itemTYPE=legs; break;
		
		// boots
		case 130: itemName="Boots"; itemTYPE=boots; break;
		case 131: itemName="War Boots"; itemTYPE=boots; break;
		case 132: itemName="Ares Boots"; itemTYPE=boots; break;
		
		// helmets
		case 140: itemName="Leather Cap"; itemTYPE=head; break;
		case 141: itemName="Chain Helmet"; itemTYPE=head; break;
		case 142: itemName="Light Steel Helmet"; itemTYPE=head; break;
		case 143: itemName="Heavy Steel Helmet"; itemTYPE=head; break;
		case 144: itemName="Fighter Helmet"; itemTYPE=head; break;
		case 145: itemName="Noble Helmet"; itemTYPE=head; break;
		case 146: itemName="Warrior Helmet"; itemTYPE=head; break;
		
		default: itemName=""; itemTYPE=npe; break;
	}
};

std::string item::atos(const char* cstring) {
	std::stringstream ss;
	
	for (int i=0;i<strlen(cstring);i++) {
		ss << cstring[i];
	}
	
	return ss.str();
};
