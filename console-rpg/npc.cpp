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
 
#include "npc.h"

// npc class default constructor
npc::npc() {
	name="Arbba";
	posx=0; posy=0;
};

// npc class constructor
npc::npc(int x,int y,std::string _name) {
	name=_name;
	posx=x;
	posy=y;
};

npc::npc(std::string _name,int x,int y,int _hp,int _mp) {
	name=_name;
	posx=x;
	posy=y;
	
	hp=_hp;
	mp=_mp;
};

// npc class destructor
npc::~ npc() {
};

// method for determining where to move
void npc::preformMove(map *karte,bool dest) {
	srand(time(NULL));
	int action; // our action

	// should we preform a random move or a controlled move?
	// no destination; move anywhere...
	if (!dest)
		action=(rand()%7);

	// we have a destination! this npc should think before moving
	else if (dest)
		action=preformThink(karte);

	preformAction(action,MOVE);

	#ifdef DEBUG
	std::cout << "\nNPC moved to x: " << posx << "/y: " << posy << std::endl;
	#endif
	
	return;
};

// method for making an npc "think"
ACTIONS npc::preformThink(map *karte) {
	player *pPlayer;
	int action;

	srand(time(NULL));
	
	std::list<npc*> nearbyNpcs;
	std::list<npc*>::iterator it=karte->npcs.begin();
	int px=this->posx;
	int py=this->posy;
	
	// check for nearby npcs
	while(it!=karte->npcs.end()) {
		if ((*it)) {
			if ((px++)==(*it)->posx)
				nearbyNpcs.push_back((*it));
			if ((px--)==(*it)->posx)
				nearbyNpcs.push_back((*it));
			if ((py++)==(*it)->posy)
				nearbyNpcs.push_back((*it));
			if ((py--)==(*it)->posy)
				nearbyNpcs.push_back((*it));
		}
		
		++it;
	}
	
	// if there are nearby npcs, then move it off the map for now
	// TODO: check if a space is already occupied before moving a blocking npc
	if (!nearbyNpcs.empty()) {
		for (it=nearbyNpcs.begin();it!=nearbyNpcs.end();++it) {
			if ((*it)) {
				(*it)->posx+=karte->getMapMaxSizeX()+1;
				this->posx++;
			}
		}
	}
	
	// no nearby npcs, so do a random move
	else
		action=rand()%4;

	// parse the move and return it
	switch(action) {
		case MOVE_NORTH: return MOVE_NORTH;break;
		case MOVE_SOUTH: return MOVE_SOUTH;break;
		case MOVE_WEST: return MOVE_WEST;break;
		case MOVE_EAST: return MOVE_EAST;break;
/*		case MOVE_NW: return MOVE_NW;break;
		case MOVE_NE: return MOVE_NE;break;
		case MOVE_SW: return MOVE_SW;break;
		case MOVE_SE: return MOVE_SE;break;*/
		default: return DO_NOTHING;break;
	}
};

// npc method for doing a certain action
void npc::preformAction(int action,ACTIONS ACTION) {
	// first we parse what this action is

	// the npc wants to move
	if (ACTION==MOVE) {
		switch(action) {
			case MOVE_NORTH: posx++;break;
			case MOVE_SOUTH: posx--;break;
			case MOVE_WEST: posy--;break;
			case MOVE_EAST: posy++;break;
			case MOVE_NW: posx++; posy--;break;
			case MOVE_NE: posx++; posy++;break;
			case MOVE_SW: posx--; posy--;break;
			case MOVE_SE: posx--; posy++;break;
			default: break;
		}
		return;
	}
};

// put the data into an xmlNodePtr and return it
xmlNodePtr npc::compressToXML() {
	xmlNodePtr ptr;
	std::stringstream ss;
	
	ptr=xmlNewNode(NULL,(const xmlChar*) "npc");
	
	ss << name;
	xmlSetProp(ptr,(const xmlChar*) "name",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << posx;
	xmlSetProp(ptr,(const xmlChar*) "x",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << posy;
	xmlSetProp(ptr,(const xmlChar*) "y",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << hp;
	xmlSetProp(ptr,(const xmlChar*) "hp",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << mp;
	xmlSetProp(ptr,(const xmlChar*) "mp",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	return ptr;
};
