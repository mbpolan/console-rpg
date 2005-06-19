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

#include <fstream>
#include <libxml/parser.h>
#include "exception.h"
#include "map.h"

// constructor 
Map::Map(int width, int height): mapWidth(width), mapHeight(height) {
	try {
		loadItemsFromXML("itemdb.xml");
	}
	
	// catch exceptions
	// load error
	catch (const CLoadErrorEx &e) {
		std::cout << "Error loading item database: " << e.what() << std::endl;
		if (e.isFatal())
			exit(1);
	}
	
	// everything else
	catch (...) {
	}
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
		if ((*it) && (*it)->position.y==x && (*it)->position.y==y && (*it)->position.z==z)
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
		if ((*it) && (*it)->position.x==x && (*it)->position.y==y && (*it)->position.z==z) {
			delete (*it);
			it=objects.erase(it);
			break;
		}
	}
};

// function that loads an item database from file
void Map::loadItemsFromXML(std::string file) {
	xmlDocPtr doc=xmlParseFile(file.c_str());
	
	if (doc) {
		xmlNodePtr root, ptr;
		root=xmlDocGetRootElement(doc);
		
		// check the root element
		if (strcmp((const char*) root->name, "item-db")!=0) {
			throw CLoadErrorEx();
		}
		
		ptr=root->children;
		
		// check the ptr node
		if (strcmp((const char*) ptr->name, "items")!=0) {
			throw CLoadErrorEx();
		}
		
		// get a count
		int count=atoi((const char*) xmlGetProp(ptr, (const xmlChar*) "count"));
		
		// load the items
		xmlNodePtr item=ptr->children, attr;
		ItemModel *imodel;
		int counter=0;
		for (int i=0; i<count; i++) {
			std::string name=(std::string) ((const char*) xmlGetProp(item, (const xmlChar*) "name"));
			int id=atoi((const char*) xmlGetProp(item, (const xmlChar*) "id"));
			
			// load attributes
			attr=item->children;
			int pow=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "power"));
			int luck=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "luck"));
			int str=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "luck"));
			int def=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "defense"));
			
			// create a model
			imodel=new ItemModel(name, id, luck, def, pow, str);
			
			// add it to the database
			itemDB[id]=imodel;
			counter+=1;
			
			// next item
			item=item->next;
			
		}
		
		#ifdef DEBUG
		std::cout << "DEBUG: loaded " << counter << " out of " << count << " items.\n";
		#endif
		
		// free the document
		xmlFreeDoc(doc);
	}
	
	else
		throw CLoadErrorEx();
};
