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

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

// nessesary includes
#include "map.h"

// map class constructor
map::map(int X,int Y,int NgY,int NgX) {
	MapMaxSizeX=X;
	MapMaxSizeY=Y;
	MapMaxSizeNgY=NgY;
	MapMaxSizeNgX=NgX;
	groundID=0;

	players.clear();
	npcs.clear();
	items.clear();
};

// map class destructor
map::~map() {};

// add item to map
void map::addItem(item *thisItem) {
	items.push_back(thisItem);
};

// remove item from map
void map::removeItem(int x,int y) {
	item *thisItem=getItem(x,y);
	std::list<item*>::iterator it=items.begin();

	while (it!=items.end()) {
		if ((*it)) {
			if ((*it)->x==x && (*it)->y==y) {
				it = items.erase(it);
				delete (*it);
			}
		else
			++it;
		}
	}

	delete thisItem;
};

// check to see if the item exists on this space
bool map::itemExists(int currentX,int currentY) {
	std::list<item*>::iterator it;

	for (it=items.begin();it!=items.end();++it) {
		if ((*it)) {
			if ((*it)->x==currentX && (*it)->y==currentY)
				return true;
		}
	}

	return false;
};

// get the item based on coordinates
item* map::getItem(int currentX,int currentY) {
	std::list<item*>::iterator it;

	for (it=items.begin();it!=items.end();++it) {
		if ((*it)) {
			if ((*it)->x==currentX && (*it)->y==currentY)
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
TYPE map::checkItemType(int currentX,int currentY) {
	std::list<item*>::iterator it;

	for (it=items.begin();it!=items.end();++it) {
		if ((*it)) {
			if ((*it)->x==currentX && (*it)->y==currentY)
				return (*it)->checkType();
		}
	}
};

// save the current map data to file
int map::saveMapData(int game) {
	std::stringstream path,ss;
	
	#ifdef __LINUX__
	path << "data/game" << game << "/crpgmap.xml";
	#endif

	#ifdef __WINDOWS__
	path << "data\\game" << game << "\\crpgmap.xml";
	#endif

	xmlDocPtr doc; // our document
	xmlNodePtr root,ptr;
	
	doc=xmlNewDoc((const xmlChar*) "1.0");
	
	doc->children=xmlNewDocNode(doc,NULL,(const xmlChar*) "crpg-map",NULL);
	
	root=doc->children;
	
	// save the items
	ptr=xmlNewChild(doc->children,NULL,(const xmlChar*) "items",NULL);
	
	ss << items.size();
	xmlSetProp(ptr,(const xmlChar*) "count",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	std::list<item*>::iterator iit;
	for (iit=items.begin();iit!=items.end();++iit) {
		if ((*iit))
			xmlAddChild(ptr,(*iit)->compressToXML());
	}
	
	// save the npcs
	ptr=xmlNewChild(doc->children,NULL,(const xmlChar*) "npcs",NULL);
	
	ss << npcs.size();
	xmlSetProp(ptr,(const xmlChar*) "count",(const xmlChar*) ss.str().c_str());
	
	std::list<npc*>::iterator nit;
	for (nit=npcs.begin();nit!=npcs.end();++nit) {
		if ((*nit))
			xmlAddChild(ptr,(*nit)->compressToXML());
	}

	xmlKeepBlanksDefault(1);
	
	// save our new map...
	xmlSaveFile(path.str().c_str(),doc);
	xmlFreeDoc(doc);
};

// load saved map data from file
int map::loadMapData(int game) {
	std::ifstream fin;
	
	char path[256];
	
	#ifdef __LINUX__
	sprintf(path,"data/game%d/crpgmap.xml",game);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(path,"data\\game%d\\crpgmap.xml",game);
	#endif
	
	xmlDocPtr doc=xmlParseFile(path);
	std::list<item*> itemsId;
	
	if (doc) {
		xmlNodePtr root,ptr,Items,Npcs;
		root=xmlDocGetRootElement(doc);
		
		if (xmlStrcmp(root->name,(const xmlChar*) "crpg-map")) {
			xmlFreeDoc(doc);
			return 0;
		}
		
		ptr=root->children;
		
		if (ptr) {
			// first load in the items
			int itemCount=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "count"));
			xmlNodePtr items=ptr->children;
			
			for (int i=0;i<itemCount;i++) {
				int t=atoi((const char*) xmlGetProp(items,(xmlChar*) "id"));
				if (t>0) {
					const char* x=(const char*) xmlGetProp((xmlNodePtr) items,(xmlChar*) "x");
					const char* y=(const char*) xmlGetProp((xmlNodePtr) items,(xmlChar*) "y");
					const char* valid=(const char*) xmlGetProp((xmlNodePtr) items,(xmlChar*) "valid");
				
					this->items.push_back(new item(t,x,y,valid));
				}
					
				items=items->next;
			}
			
			ptr=ptr->next;
		
			// now load in the npcs
			int npcCount=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "count"));
			xmlNodePtr npcs=ptr->children;
			
			for (int i=0;i<npcCount;i++) {
				std::string npcName=item::atos((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "name"));
				int X=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "x"));
				int Y=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "y"));
				int HP=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "hp"));
				int MP=atoi((const char*) xmlGetProp((xmlNodePtr) npcs,(xmlChar*) "mp"));
			
				this->npcs.push_back(new npc(npcName,X,Y,HP,MP));
				
				npcs=npcs->next;
			}

		}
		
		xmlFreeDoc(doc);
		
		return 1;
	}
	
	std::cout << "\nUnable to load map.xml in savefile " << game << "!\n";
	return 0;
};

// map method for removing players from the list
void map::removeFromList(player *rhs) {
	std::list<player*>::iterator it;

	for (it=players.begin();it!=players.end();++it) {
		if ((*it)) {
			std::string name=(*it)->getName();

			if (name==rhs->getName())
				players.pop_front();
		}
	} // for(...)
};

// map method for removing npcs from the list
void map::removeFromList(npc *rhs) {
	std::list<npc*>::iterator it;

	for (it=npcs.begin();it!=npcs.end();++it) {
		if ((*it)) {
			int id=(*it)->getID();

			if (id==rhs->getID())
				npcs.pop_front();
		}
	} // for(...)
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
