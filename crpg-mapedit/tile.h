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

#ifndef tile_h
#define tile_h

#include <qtable.h>
#include <iostream>

#include "maptable.h"

class QTable;

class tile: public QTableItem {
       public:
	   tile(int,QTable *table, EditType ed=QTableItem::Never);
	   tile(int, bool, QString, int, int, QTable *table, EditType ed=QTableItem::Never);

	   int getID() const {return id;}
	   void setID(int _id) {id=_id;}
	   void setItem(bool t) {isItem=t;}
	   
	   static QPixmap parseID(int);
	   static std::string parseIDToName(int);
	   void setPic(int); // set the pixmap	
	   
	   void setNpc(bool t);
	   bool hasNpc() {return isNpc;}
	   
	   virtual int rtti() const {return 1001;}
	   
	   // npc
	   regNPC Npc;
	   
       private:
	   bool isNpc; // is an npc here?
	   bool isItem; // is an item here?
	   int id; // item id
};

#endif
