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
// todo: merge the map.dat file into savefile.dat
int map::saveMapData(int game) {
/*	std::ofstream fout;

	std::stringstream path,obj;

	#ifdef __LINUX__
	path << "data/game" << game << "/map.crpgmap";
	obj << "data/game" << game << "/obj.crpgmap";
	#endif

	#ifdef __WINDOWS__
	path << "data\\game" << game << "\\map.crpgmap";
	obj << "data\\game" << game << "\\obj.crpgmap";
	#endif
	
	fout.open(path.str().c_str()); // open a new map file
	
	if (!fout) {
		std::cout << "\nFailed to save map data!\n";
		return 0;
	}
	
	// now we save the item squares to file
	for (int i=0;i<max;i++)
		fout << itemSquareX[i] << std::endl;

	for (int i=0;i<max;i++)
		fout << itemSquareNgX[i] << std::endl;

	for (int i=0;i<max;i++)
		fout << itemSquareY[i] << std::endl;

	for (int i=0;i<max;i++)
		fout << itemSquareNgY[i] << std::endl;

	fout.close();

	fout.open(obj.str().c_str());
	if (!fout) {
		std::cout << "\nFailed to save map data!\n";
		return 0;
	}

	// now we save the item object arrays to the same file
	for (int i=0;i<max;i++) {
		fout.write((char*) &(*itemLineX[i]),sizeof(itemLineX[i]));
		fout << std::endl;
	}

	for (int i=0;i<max;i++) {
		fout.write((char*) &(*itemLineNgX[i]),sizeof(itemLineNgX[i]));
		fout << std::endl;
	}
	
	for (int i=0;i<max;i++) {
		fout.write((char*) &(*itemLineY[i]),sizeof(itemLineY[i]));
		fout << std::endl;
	}
	
	for (int i=0;i<max;i++) {
		fout.write((char*) &(*itemLineNgY[i]),sizeof(itemLineNgY[i]));
		fout << std::endl;
	}
	fout.close();

	// save the player/npc lists
	std::list<player*>::iterator pit;
	std::list<npc*>::iterator nit;

	for (pit=players.begin();pit!=players.end();++pit) {
		fout.write((char*) &(*pit),sizeof(player));
		fout << " ";
	}
	fout << std::endl << std::endl;

	for (nit=npcs.begin();nit!=npcs.end();++nit) {
		fout.write((char*) &(*nit),sizeof(npc));
		fout << " ";
	}*/
};

// load saved map data from file
int map::loadMapData(int game) {
/*	std::ifstream fin;
	char path[256];
	char obj[256];
	
	#ifdef __LINUX__
	sprintf(path,"data/game%d/map.crpgmap",game);
	sprintf(obj,"data/game%d/obj.crpgmap",game);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(path,"data\\game%d\\map.crpgmap",game);
	sprintf(obj,"data\\game%d\\obj.crpgmap",game);
	#endif
	
	fin.open(path); // try to load a map file

	if (!fin) {
		std::cout << "\nFailed to load map data!\n";
		return 0;
	}
	
	for (int i=0;i<max;i++) {
		itemSquareX[i]=0;
		itemSquareNgX[i]=0;
		itemSquareY[i]=0;
		itemSquareNgY[i]=0;
		
		itemLineX[i]=NULL;
		itemLineNgX[i]=NULL;
		itemLineY[i]=NULL;
		itemLineNgY[i]=NULL;
	}
	
	// load the first 4 lines of the file into itemSquare
	for (int i=0;i<max;i++) {
		fin >> itemSquareX[i];
		fin.clear();
	}

	for (int i=0;i<max;i++) {
		fin >> itemSquareNgX[i];
		fin.clear();
	}

	for (int i=0;i<max;i++) {
		fin >> itemSquareY[i];
		fin.clear();
	}

	for (int i=0;i<max;i++) {
		fin >> itemSquareNgY[i];
		fin.clear();
	}
	fin.close();

	fin.open(obj);
	if (!fin) {
		std::cout << "\nFailed to load map data!\n";
		return 0;
	}

	// load the last 4 lines of the file into itemLine
	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineX[i],sizeof(itemLineX[i]));
		fin.clear();
	}

	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineNgX[i],sizeof(itemLineNgX[i]));
		fin.clear();
	}

	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineY[i],sizeof(itemLineY[i]));
		fin.clear();
	}

	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineNgY[i],sizeof(itemLineNgY[i]));
		fin.clear();
	}

	// load the player/npc lists
	std::list<player*>::iterator pit;
	std::list<npc*>::iterator nit;

//	player *pPlayer;
//	npc *pNpc;

	for (int i=0;i<player::getPlayersOn();i++) {
		fin.read((char*) &pPlayer,sizeof(player));
		players.push_back(pPlayer);

		fin.ignore(256,' ');
	}
	fin.clear(); fin.clear();

	for (int i=0;i<npc::getNpcsOn();i++) {
		fin.read((char*) &pNpc,sizeof(npc));
		npcs.push_back(pNpc);

		fin.ignore(256,' ');
	}

//	delete pPlayer;
//	delete pNpc;

	fin.close();*/
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
