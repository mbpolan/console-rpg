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
 
// items.h: holds item class and declarations
#include <iostream>
#include <sstream>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

// enumerate the types of items
enum TYPE {head,torso,legs,boots,npe};

class item {
	public:
		item();
		item(item*); // copy constructor
		item(int id); // lesser constructor
		item(int id,TYPE); // type inclusive constructor
		item(int id,int x,int y); // our constructor
		item(int,const char*,const char*,const char*);
		
		virtual ~item();

		void setItemID(int id) {itemID=id;};
		void setItemName(std::string nameOfItem) {itemName=nameOfItem;}
		
		std::string getName() const {return itemName;}
		void setName(std::string name) {itemName=name;}

		int getItemID() const {return itemID;}

		bool isHeadItem(item*);
		bool isTorsoItem(item*);
		bool isLegsItem(item*);
		bool isBootsItem(item*);

		TYPE checkType();
		void invalidateItem(item*);
		
		xmlNodePtr compressToXML();
		void parseItem(int);
		
		static std::string atos(const char*);

		int x,y;
		static int itemCount;

	private:
		int itemID;
		bool isValid;

		std::string itemName;
		TYPE itemTYPE;
};

#endif
