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

enum TYPE {head,torso,legs,boots,npe};

class item {
	public:
		item();
		item(std::string,TYPE); // lesser constructor
		item(std::string,int,int,TYPE); // our constructor
		virtual ~item();

		void setLocationX(int);
		void setLocationY(int);
		void setItemID(int);
		void setItemName(std::string nameOfItem) {itemName=nameOfItem;}
		
		std::string getName() const {return itemName;}
		void setName(std::string name) {itemName=name;}
		
		int getLocationX() const {return itemLocationX;}
		int getLocationY() const {return itemLocationY;}
		int getItemID() const {return itemID;}
		
		bool isHeadItem(item*);
		bool isTorsoItem(item*);
		bool isLegsItem(item*);
		bool isBootsItem(item*);
		
		TYPE checkType();

	private:
		int itemLocationX, itemLocationY, itemID;
		std::string itemName;
		TYPE itemTYPE;
};

#endif
