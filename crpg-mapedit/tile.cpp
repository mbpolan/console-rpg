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

#include <qimage.h>
#include <qpixmap.h>
#include <string.h>

#include "tiles.dat"
#include "tile.h"

// tile constructor
tile::tile(int _id,QTable *table,EditType ed): QTableItem(table,ed) {
    isItem=false;
    isNpc=false;
    id=_id;
    setPixmap(parseID(id));
    
    // locate the mouse
//    setMouseTracking(true);
};

// npc constructor
tile::tile(int _id, bool NPC, QString _name, int _health, int _mp, QTable *table, EditType ed): QTableItem(table,ed) {
    isItem=false;
    isNpc=NPC;
    id=_id;
    
    // locate the mouse
 //   setMouseTracking(true);
    
    if (NPC) {
	setPixmap(parseID(-100));
	this->Npc.name=_name;
	this->Npc.health=_health;
	this->Npc.mp=_mp;
	
    }
    
    if (!NPC)
	setPixmap(parseID(0));
};

// parse the id of the item and return the appropriate pixmap
QPixmap tile::parseID(int id) {
    QPixmap pic;
    
    switch(id) {
       case -0x64: pic=QPixmap(npc); break;
       case -0x01: pic=QPixmap(water); break;	
	   
       case 0: pic=QPixmap(grass); break;
	   
       case 0x01: pic=QPixmap(bush); break;
       case 0x02: pic=QPixmap(rock); break;
       case 0x03: pic=QPixmap(sunflowers); break;	   
       case 0x04: pic=QPixmap(fern); break;
       case 0x05: pic=QPixmap(herb); break;
       case 0x06: pic=QPixmap(puddle); break;
       }
    
    return pic;
};

// parse the id and return this tile's name
std::string tile::parseIDToName(int id) {
    std::string name;
    
    switch(id) {
       case -0x64: name="NPC"; break;
       case	 -0x01: name="water"; break;
		
       case 0x00: name="grass"; break;
       
       case 0x01: name="bush"; break;
       case 0x02: name="rock"; break;
       case 0x03: name="sunflowers"; break;
       case 0x04: name="fern"; break;
       case 0x05: name="herb"; break;
       case 0x06: name="puddle"; break;	   
    }
    
    return name;
};

// method to set the pixmap
void tile::setPic(int _id) {
    id=_id;
    setPixmap(tile::parseID(_id));
};

// method for setting this tile to npcs
void tile::setNpc(bool t) {
    if (t) {
	isNpc=true;
	
	// set an npc pixmap image
	setPixmap(tile::parseID(-100));
    }
};
