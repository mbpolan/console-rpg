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

// map.cpp: declarations for map functions
#include <iostream>
#include <fstream>
#include <sstream>
#include <libxml/parser.h>

// nessesary includes
#include "map.h"
#include "utilities.h"
using namespace utilities;

// map class constructor
map::map(int X,int Y,int x,int y) {
	MapMaxSizeX=X;
	MapMaxSizeY=Y;
	groundID=0;

	players.clear();
	npcs.clear();
	items.clear();
	spItems.clear();
};

// map class destructor
map::~map() {};

// add item to map
void map::addItem(item *thisItem) {
	items.push_back(thisItem);
};

// remove item from map
void map::removeItem(int x, int y, int _layer) {
	item *thisItem=getItem(x, y, _layer);
	std::list<item*>::iterator it=items.begin();

	while (it!=items.end()) {
		if ((*it)) {
			if ((*it)->x==x && (*it)->y==y && (*it)->getLayer()==_layer) {
				it = items.erase(it);
				delete (*it);
			}
		else
			++it;
		}
	}

	delete thisItem;
};

// remove an enemy
void map::removeEnemy(enemy *e) {
	std::list<enemy*>::iterator it=enemies.begin();
	
	while(it!=enemies.end()) {
		if ((*it)) {
			if ((*it)->x==e->x && (*it)->y==e->y && (*it)->getLayer()==e->getLayer() && (*it)->getName()==e->getName()) {
				it=enemies.erase(it);
				delete (*it);
			}
		}
		
		else
			++it;
	}
	
	delete e;
};

// remove an npc
void map::removeNpc(npc *n) {
	std::list<npc*>::iterator it=npcs.begin();
	
	while(it!=npcs.end()) {
		if ((*it)) {
			if ((*it)->posx==n->posx && (*it)->posy==n->posy && (*it)->getLayer()==n->getLayer() && (*it)->name==n->name) {
				it=npcs.erase(it);
				delete (*it);
			}
		}
		
		else
			++it;
	}
	
	delete n;
};

// remove a player
void map::removePlayer(player *p) {
	std::list<player*>::iterator it=players.begin();
	
	while(it!=players.end()) {
		if ((*it)) {
			if ((*it)->x==p->x && (*it)->y==p->y && (*it)->getLayer()==p->getLayer() && (*it)->getName()==p->getName()) {
				it=players.erase(it);
				delete (*it);
			}
		}
		
		else
			++it;
	}
	
	delete p;
}

// check to see if the item exists on this space
bool map::itemExists(int currentX, int currentY, int _layer) {
	std::list<item*>::iterator it;

	for (it=items.begin();it!=items.end();++it) {
		if ((*it)) {
			if ((*it)->x==currentX && (*it)->y==currentY && (*it)->getLayer()==_layer)
				return true;
		}
	}

	return false;
};

// get the item based on coordinates
item* map::getItem(int currentX, int currentY, int _layer) {
	std::list<item*>::iterator it;

	for (it=items.begin();it!=items.end();++it) {
		if ((*it)) {
			if ((*it)->x==currentX && (*it)->y==currentY && (*it)->getLayer()==_layer)
				return (*it);
		}
	}
};

// parse the ground id and return a std::string
std::string map::parseGroundID(int id) {
	std::string groundType;
	switch (id) {
		case 1: groundType="grass"; break;
		case 2: groundType="pavement"; break;
		case 3: groundType="water"; break;
		case 4: groundType="dirt"; break;
		default: groundType="grass"; break;
	}

	return groundType;
};

// check the type of item (head,torso,leg,boot,npe)
TYPE map::checkItemType(int currentX,int currentY, int _layer) {
	std::list<item*>::iterator it;

	for (it=items.begin();it!=items.end();++it) {
		if ((*it)) {
			if ((*it)->x==currentX && (*it)->y==currentY && (*it)->getLayer()==_layer)
				return (*it)->checkType();
		}
	}
};

// save the current map data to an xmlNodePtr
xmlNodePtr map::saveMapData() {
	std::stringstream path,ss;
	xmlNodePtr root,ptr;
	
	root=xmlNewNode(NULL,(const xmlChar*) "crpg-map");
	
	// save the items
	ptr=xmlNewChild(root,NULL,(const xmlChar*) "items",NULL);
	
	ss << items.size();
	xmlSetProp(ptr,(const xmlChar*) "count",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	std::list<item*>::iterator iit;
	for (iit=items.begin();iit!=items.end();++iit) {
		if ((*iit))
			xmlAddChild(ptr,(*iit)->compressToXML());
	}
	
	// save our special tiles
	ptr=xmlNewChild(root, NULL, (const xmlChar*) "spItems", NULL);
	
	ss << spItems.size();
	xmlSetProp(ptr, (const xmlChar*) "count", (const xmlChar*) ss.str().c_str());
	ss.str("");
	
	for (iit=spItems.begin();iit!=spItems.end();++iit) {
		if ((*iit))
			xmlAddChild(ptr, (*iit)->compressToXML());
	}
	
	// save the npcs
	ptr=xmlNewChild(root,NULL,(const xmlChar*) "npcs",NULL);
	
	ss << npcs.size();
	xmlSetProp(ptr,(const xmlChar*) "count",(const xmlChar*) ss.str().c_str());
	
	std::list<npc*>::iterator nit;
	for (nit=npcs.begin();nit!=npcs.end();++nit) {
		if ((*nit))
			xmlAddChild(ptr,(*nit)->compressToXML());
	}
	
	return root;
};

// load saved map data from file
bool map::loadMapData(xmlNodePtr p) {
	std::list<item*> itemsId;
	
	xmlNodePtr ptr, Items,Npcs;
	
	if (p) {
		if (xmlStrcmp(p->name,(const xmlChar*) "crpg-map")) {
			return false;
		}
		ptr=p->children;
		
		
		// first load in the items
		int itemCount=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "count"));
		xmlNodePtr items=ptr->children;
			
		for (int i=0;i<itemCount;i++) {
			int t=atoi((const char*) xmlGetProp(items,(xmlChar*) "id"));
			if (t>0) {
				const char* x=(const char*) xmlGetProp((xmlNodePtr) items,(xmlChar*) "x");
				const char* y=(const char*) xmlGetProp((xmlNodePtr) items,(xmlChar*) "y");
				const char* _layer=(const char*) xmlGetProp((xmlNodePtr) items, (xmlChar*) "layer");
				const char* valid=(const char*) xmlGetProp((xmlNodePtr) items,(xmlChar*) "valid");
			
				this->items.push_back(new item(t , x, y, valid, _layer));
			}
				
			items=items->next;
		}
		
		ptr=ptr->next;
		
		// second, load in all special tiles, etc.
		int spItemCount=atoi((const char*) xmlGetProp(ptr, (xmlChar*) "count"));
		xmlNodePtr spItems=ptr->children;
		
		for (int i=0;i<spItemCount;i++) {
			int t=atoi((const char*) xmlGetProp((xmlNodePtr) spItems, (xmlChar*) "id"));
			const char* x=(const char*) xmlGetProp((xmlNodePtr) spItems,(xmlChar*) "x");
			const char* y=(const char*) xmlGetProp((xmlNodePtr) spItems,(xmlChar*) "y");
			const char* _layer=(const char*) xmlGetProp((xmlNodePtr) spItems, (xmlChar*) "layer");
			const char* valid=(const char*) xmlGetProp((xmlNodePtr) spItems,(xmlChar*) "valid");
			
			this->spItems.push_back(new item(t , x, y, valid, _layer));
			
			spItems=spItems->next;
		}
		
		ptr=ptr->next;
		
		// now load in the npcs
		int npcCount=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "count"));
		xmlNodePtr npcs=ptr->children;
		
		for (int i=0;i<npcCount;i++) {
			std::string npcName=atos((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "name"));
			int X=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "x"));
			int Y=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "y"));
			int HP=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "hp"));
			int MP=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "mp"));
			int _layer=atoi((const char*) xmlGetProp((xmlNodePtr) npcs, (xmlChar*) "layer"));
		
			this->npcs.push_back(new npc(_layer, npcName,X,Y,HP,MP));
			
			npcs=npcs->next;
		}
		
		return true;
	}
	
	return false;
};

// map method for making creatures do certain actions
void map::creaturesDoAction() {
	std::list<npc*>::iterator it;

	// first we start with npcs
	for (it=npcs.begin();it!=npcs.end();++it) {
		if ((*it)) {
			// just make the npcs move for now
			(*it)->preformMove(this,false);
		}
	}
};
