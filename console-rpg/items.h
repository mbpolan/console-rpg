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

 #ifndef item_h
 #define item_h
 
// items.h: holds item classes and declarations
#include <iostream>
#include <sstream>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <list>

// enumerate the types of items
enum TYPE {head,torso,legs,boots,npe};

class item {
	public:
		item();
		item(item*); // copy constructor
		item(int id, int _layer); // lesser constructor
		item(int id, TYPE, int _layer); // type inclusive constructor
		item(int id, int x, int y, int _layer); // our constructor
		item(int, const char*, const char*, const char*, const char*);
		
		virtual ~item();

		void setItemID(int id) {itemID=id;};
		void setItemName(std::string nameOfItem) {itemName=nameOfItem;}
		
		std::string getName() const {return itemName;}
		void setName(std::string name) {itemName=name;}

		int getItemID() const {return itemID;}
		
		void setLayer(int p) {layer=p;}
		int getLayer() const {return layer;}

		bool isHeadItem();
		bool isTorsoItem();
		bool isLegsItem();
		bool isBootsItem();

		TYPE checkType();
		void invalidateItem();
		
		xmlNodePtr compressToXML();
		void parseItem(int);

		int x,y;
		static int itemCount;

	private:
		int itemID;
		int layer; // used in map layer
		bool isValid;

		std::string itemName;
		TYPE itemTYPE;
};

// a bag type item that holds other items
class bag: public item {
	public:
		bag(int);
		virtual ~bag() {};
		
		item *operator>>(int);
		void operator<<(item*);
		
		bool addItem(item*);
		item* removeItem(int, bool);	
		
		void displayContents();
		
		// list of this bag's items
		std::list<item*> contents;
		
	private:	
		int contentCount; // amount of items now
		int maxSize; // max items
};

#endif
