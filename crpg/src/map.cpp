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
#include "enemy.h"
#include "exception.h"
#include "map.h"

// constructor 
Map::Map(int width, int height, int loadMethod, std::string path): mapWidth(width), mapHeight(height) {
	MutexInit(mutex);

	try {
		if (loadMethod==MAP_LOAD_METHOD_XML)
			loadItemsFromXML(path);
		
		else if (loadMethod==MAP_LOAD_METHOD_BINARY)
			loadItemsFromBinary(path);
	}
	
	// catch exceptions
	// load error
	catch (const CLoadErrorEx &e) {
		std::cout << "Error loading item database: " << e.what() << std::endl;
		std::cin.get();
		if (e.isFatal())
			exit(1);
	}
	
	// everything else
	catch (...) {
	}
	
	// spawn items
	spawnMapItems(3000);
	
	// spawn enemies
	spawnEnemies(50);
};

// destructor
Map::~Map() {
	// clear out the object list
	for (MapObjectIterator it=items.begin(); it!=items.end(); ++it) {
		if ((*it)) {
			delete (*it);
			it=items.erase(it);
		}
	}
	
	// clear out the enemy list
	for (MapEnemyIterator it=enemies.begin(); it!=enemies.end(); ++it) {
		if ((*it)) {
			delete (*it);
			it=enemies.erase(it);
		}
	}
};

// function to clear the entire map of items
void Map::clear() {
	for (MapObjectIterator it=items.begin(); it!=items.end(); ++it) {
		if ((*it)) {
			delete (*it);
			it=items.erase(it);
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
Item* Map::getItem(Position pos) {
	MapObjectIterator it=items.begin();
	 
	 while(it!=items.end()) {
		if ((*it) && (*it)->position.x==pos.x && (*it)->position.y==pos.y && (*it)->position.z==pos.z)
			return (*it);
		
		else
			++it;
	}
	
	// just in case we didn't find the object
	return NULL;
};

// function to place a new object on the map
void Map::placeItem(Item *item) {
	items.push_back(item);
};

// function to remove an object
bool Map::removeItem(Position pos) {
	// find the first object and remove it
	MapObjectIterator it=items.begin();
	
	while(it!=items.end()) {
		if ((*it) && (*it)->position.x==pos.x && (*it)->position.y==pos.y && (*it)->position.z==pos.z)
			it=items.erase(it);
		
		else
			++it;
	}
	
	return true;
};

// function to return a pointer to an enemy on the map
Enemy* Map::getEnemy(Position pos) {
	MapEnemyIterator it=enemies.begin();
	 
	 while(it!=enemies.end()) {
		if ((*it) && (*it)->position.x==pos.x && (*it)->position.y==pos.y && (*it)->position.z==pos.z)
			return (*it);
		
		else
			++it;
	}
	
	return NULL;
};

// function to place a new enemy on the map
void Map::placeEnemy(Enemy *enemy) {
	enemies.push_back(enemy);
};

// function to remove an enemy
bool Map::removeEnemy(Position pos) {
	// find the first enemy and remove it
	MapEnemyIterator it=enemies.begin();
	 
	 while(it!=enemies.end()) {
		if ((*it) && (*it)->position.x==pos.x && (*it)->position.y==pos.y && (*it)->position.z==pos.z)
			it=enemies.erase(it);
		
		else
			++it;
	}
	
	return true;
};

// function that loads an item database from file
void Map::loadItemsFromXML(std::string file) {
	#ifdef DEBUG
	std::cout << "Loading items from XML...\n";
	#endif
	
	xmlDocPtr doc=xmlParseFile(file.c_str());
	
	if (doc) {
		xmlNodePtr root, ptr;
		root=xmlDocGetRootElement(doc);
		
		// check the root element
		if (strcmp((const char*) root->name, "items-db")!=0) {
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
			bool usable=atoi((const char*) xmlGetProp(item, (const xmlChar*) "usable"));
			bool plural=atoi((const char*) xmlGetProp(item, (const xmlChar*) "plural"));
			
			// load attributes
			attr=item->children;
			int pow=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "power"));
			int luck=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "luck"));
			int str=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "luck"));
			int def=atoi((const char*) xmlGetProp(attr, (const xmlChar*) "defense"));
			
			// create a model
			imodel=new ItemModel(name, id, luck, def, pow, str, plural, usable);
			
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
}

// function to load items from a binary file
void Map::loadItemsFromBinary(std::string file) {
	#ifdef DEBUG
	std::cout << "Loading items from binary file...\n";
	#endif
	
	FILE *f=fopen(file.c_str(), "r");
	if (f) {
		// first 4 bytes are the header
		if (!(fgetc(f)=='C' && fgetc(f)=='R' && 
		     (fgetc(f)=='P' && fgetc(f)=='G'))) {
		     	std::cout << "This is not a CRPG item database file!\n";
			throw CLoadErrorEx();
		}
		
		// count of items
		int count=fgetc(f), counter=0;
		for (int i=0; i<count; i++) {
			// id
			int id=fgetc(f);
			
			// name
			int length=fgetc(f);
			std::string name;
			for (int j=0; j<length; j++)
				name+=(char) fgetc(f);
			
			// usable
			bool usable=fgetc(f);
			
			// plural
			bool plural=fgetc(f);
			
			// attributes
			int def=fgetc(f);
			int luck=fgetc(f);
			int pow=fgetc(f);
			int str=fgetc(f);
			
			// end byte
			fgetc(f);
			
			// place the new item into the database
			itemDB[id]=new ItemModel(name, id, luck, def, pow, str, plural, usable);
			counter+=1;
		}
		
		#ifdef DEBUG
		std::cout << "DEBUG: Loaded " << counter << " out of " << count << " items.\n";
		#endif
		
		return;
	}
	
	else
		throw CLoadErrorEx();
};

// function to create a new item
Item* Map::createItem(Map *map, int id, Position pos) {
	Item *item=new Item;
	
	// get attributes from database
	std::string name;
	int luck, def, pow, str, _id;
	bool found=false, plural, use;
	for (MapItemIterator it=map->itemDB.begin(); it!=map->itemDB.end(); ++it) {
		if ((*it).second && ((*it).second)->getID()==id) {
			_id=((*it).second)->getID();
			name=((*it).second)->getName();
			luck=((*it).second)->getLuck();
			def=((*it).second)->getDefense();
			pow=((*it).second)->getPower();
			str=((*it).second)->getStrength();
			use=((*it).second)->isUsable();
			plural=((*it).second)->isPlural();
			found=true;
			
			break;
		}
	}
	
	// check if we found a match
	if (found) {
		item->setID(_id);
		item->setName(name);
		item->setLuck(luck);
		item->setDefense(def);
		item->setPower(pow);
		item->setStrength(str);
		item->setPlural(plural);
		item->setUsable(use);
		item->position=pos;
		
		return item;
	}
	
	else {
		delete item;
		return NULL;
	}
};

// function to spawn some items on the map
void Map::spawnMapItems(int amount) {
	srand(static_cast<unsigned> (time(NULL)));
	
	for (int i=0; i<amount; i++) {
		int x=rand()%mapWidth;
		int y=rand()%mapHeight;
		//int z=rand()%5; // TODO: implement layers
		int z=0;
		int id=(rand()%5)+1; // FIXME: these id's should not be hard coded!
		
		if (!this->getItem(Position(x, y, z)) && x!=0 && y!=0) {
			// place this item
			placeItem(Map::createItem(this, id, Position(x, y, z)) ? Map::createItem(this, id, Position(x, y, z)) : new Item);
		}
		
		#ifdef DEBUG
		std::cout << "DEBUG: Placed item (id: " << id << ") at Position(" << x << ", " << y << ", " << z << ")";
		if (Map::createItem(this, id, Position(x, y, z)))
			std::cout << " - Valid";
		
		else
			std::cout << " - Invalid";
		
		std::cout << std::endl;
		#endif
		// sword and shield debug items
		placeItem(Map::createItem(this, 100, Position(1, 1, 0)));
		placeItem(Map::createItem(this, 110, Position(1, 2, 0)));
		
		// test food
		Item *t=new Item(5000, "Cake", Position(15, 15, 0), true);
		t->setPower(5);
		t->setStrength(3);
		placeItem(t);
		//#endif
	}
};

// function to spawn some enemies on the map
void Map::spawnEnemies(int amount) {
	srand(static_cast<unsigned> (time(NULL)));
	
	for (int i=0; i<amount; i++) {
		int x=rand()%mapWidth;
		int y=rand()%mapHeight;
		int z=0;
		
		// place this enemy
		placeEnemy(new Enemy("Enemy", 100, 100, Position(x, y, z)));
		
	}
	
	// test enemy
	placeEnemy(new Enemy("Cat", 100, 100, Position(10, 10, 0)));
};
