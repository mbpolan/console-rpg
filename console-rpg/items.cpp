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
#include <fstream>

#include "items.h"

int item::itemCount=0;

// item class default constructor
item::item() {
	x=0;
	y=0;
	itemName="NULL";
	itemTYPE=npe;
	layer=0;
};

// copy constructor
item::item(item *rhs) {
	x=rhs->x;
	y=rhs->y;

	itemName=rhs->getName();
	itemTYPE=rhs->checkType();
	
	itemID=rhs->getItemID();
	layer=rhs->getLayer();
};

// lesser item constructor
item::item(int id, int _layer) {
	x=0;
	y=0;
	layer=_layer;

	parseItem(id);
	itemID=id;
};

// type inclusive constructor
item::item(int id,TYPE type, int _layer) {
	parseItem(id);
	itemID=id;
	itemTYPE=type;
	layer=_layer;
};

// our item class constructor
item::item(int id,int spawnX,int spawnY, int _layer) {
	parseItem(id);
	x=spawnX;
	y=spawnY;
	layer=_layer;
	
	itemID=id;
};

item::item(int id,const char* cx,const char* cy,const char* valid, const char *lyr) {
	parseItem(id);
	
	x=atoi(cx);
	y=atoi(cy);
	layer=atoi(lyr);
	
	if (strcmp(valid, "1")==0)
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
bool item::isHeadItem() {
	if (itemTYPE==head)
		return true;
	else
		return false;
};

// check if this item can be equipped on armor slot
bool item::isTorsoItem() {
	if (itemTYPE==torso)
		return true;
	else
		return false;
};

// check if this item can be equipped on legs slot
bool item::isLegsItem() {
	if (itemTYPE==legs)
		return true;
	else
		return false;
};

// check if this item can be equipped on boots slot
bool item::isBootsItem() {
	if (itemTYPE==boots)
		return true;
	else
		return false;
};

// method for making items unusable
void item::invalidateItem() {
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
	
	ss << layer;
	xmlSetProp(ptr,(const xmlChar*) "layer",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	if (isValid)
		ss << 1;
	else
		ss << 0;
	
	xmlSetProp(ptr,(const xmlChar*) "valid",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	return ptr;
};

// parse the id and set some variables
void item::parseItem(int id) {
  // map related item
	if (id >= 0x00 && id < 0x64) {
		switch(id) {
			// generic
      default:
			case 0x00: itemName="nothing"; itemTYPE=npe; break;
		
			// inanimate objects
			case 0x01: itemName="a bush"; itemTYPE=npe; break;
			case 0x02: itemName="a rock"; itemTYPE=npe; break;
			case 0x03: itemName="sunflowers"; itemTYPE=npe; break;
			case 0x04: itemName="a fern"; itemTYPE=npe; break;
			case 0x05: itemName="an herb"; itemTYPE=npe; break;
			case 0x06: itemName="a puddle"; itemTYPE=npe; break;
		}
	}

  // this is an item
  else if (id >= 0x64) {
/*    // known item
    if (karte->itemDb.getObject(id))
      return;
      //this=items[id];*/
  }

  // unknown item
  else {
    itemName="";
    itemTYPE=npe;
  }
};

/********************************************************************
 * Start bag item definitions...
 *******************************************************************/

// bag constructor taking an int
bag::bag(int items) {
	contentCount=0;
	maxSize=items;
	
	contents.clear();
};

// overloaded operator>> for extraction of items (get item)
item* bag::operator>>(int pos) {
	removeItem(pos, true);
};

// overloaded operator<< for insertion of new item
void bag::operator<<(item *Item) {
	addItem(Item);
};

// method for adding items to the bag
bool bag::addItem(item *Item) {
	if (contentCount<=maxSize) {
		contentCount+=1;
		
		contents.push_back(Item);
		
		return true;
	}
	
	// out of space?
	return false;
};

// method for removing/getting items
item* bag::removeItem(int pos, bool get) {
	std::list<item*>::iterator it=contents.begin();
	
	int i=0; // determine position with this
	while(it!=contents.end()) {
		i+=1; // next pos
	
		if ((*it) && i==pos) {
			item ret=(*it);
		
			contents.erase(it);
			delete (*it);
			
			contentCount-=1;
			
			// if we want to get this item, return it
			if (get)
				return (new item(ret));
			
			// return NULL;
			else
				return NULL;
		}
		
		else
			++it;
	}
};

// method for displaying this bag's contents
void bag::displayContents() {
	std::list<item*>::iterator it;
	
	int i=0;
	for (it=contents.begin();it!=contents.end();++it) {
		if ((*it)) {
			i++;
			std::cout << i << ": " << (*it)->getName() << std::endl;
		}
	}
};
