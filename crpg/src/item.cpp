/***************************************************************************
 *   Copyright (C) 2005 by KanadaKid                                       *
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
// item.cpp: implementations of Item class

#include "item.h"

// default constructor
Item::Item(): Object(0, 0, 0), itemID(0), luck(0), defense(0), power(0), strength(0), itemName("NULL_ITEM"), usable(false) {
};

// constructor taking three parameters
Item::Item(int id, std::string name, Position pos, bool use): 
	Object(pos.x, pos.y, pos.z), itemID(id), luck(0), defense(0), power(0), strength(0), itemName(name), usable(use) {
};

// constructor taking eight parameters
Item::Item(int id, std::string name, Position pos, bool use, int _luck, int def, int pow, int str):
	Object(pos.x, pos.y, pos.z), itemID(id), luck(_luck), defense(def), power(pow), strength(str) {
};
