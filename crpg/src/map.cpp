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
// map.cpp: implementations of the Map class

#include "map.h"

// constructor 
Map::Map(int width, int height): mapWidth(width), mapHeight(height) {
};

// destructor
Map::~Map() {
	// clear out the object list
	for (MapObjectIterator it=objects.begin(); it!=objects.end(); ++it) {
		if ((*it)) {
			delete (*it);
			it=objects.erase(it);
		}
	}
};

// function to clear the entire map of objects
void Map::clear() {
	for (MapObjectIterator it=objects.begin(); it!=objects.end(); ++it) {
		if ((*it)) {
			delete (*it);
			it=objects.erase(it);
		}
	}
};

// function to set the new height of the map
void Map::setHeight(int height) {
	// clear the map first
	clear();
	mapHeight=height;
};

// function to set the new width of the map
void Map::setWidth(int width) {
	// clear the map first
	clear();
	mapWidth=width;
};

// function to return a pointer to an object on the map
Object* Map::getObject(int x, int y, int z) {
	for (MapObjectIterator it=objects.begin(); it!=objects.end(); ++it) {
		if ((*it) && (*it)->getPosition().y==x && (*it)->getPosition().y==y && (*it)->getPosition().z==z)
			return (*it);
	}
	
	// just in case we didn't find the object
	return NULL;
};

// function to place a new object on the map
void Map::placeObject(Object *obj) {
	objects.push_back(obj);
};

// function to remove an object
bool Map::removeObject(int x, int y, int z) {
	// find the first object and remove it
	for (MapObjectIterator it=objects.begin(); it!=objects.end(); ++it) {
		if ((*it) && (*it)->getPosition().x==x && (*it)->getPosition().y==y && (*it)->getPosition().z==z) {
			delete (*it);
			it=objects.erase(it);
			break;
		}
	}
};

