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

	for (int i=0;i<max;i++) {
		itemSquareX[i]=0;
		itemSquareY[i]=0;
		itemSquareNgX[i]=0;
		itemSquareNgY[i]=0;
		
		itemLineX[i]=NULL;
		itemLineNgX[i]=NULL;
		itemLineY[i]=NULL;
		itemLineNgY[i]=NULL;
	}
	
	npcs.clear();
};

// map class destructor
map::~map() {};

// add item to map on X
void map::addItemX(item	*thisItem,int spawnX) {
	if (spawnX<0) {
		itemSquareNgX[(spawnX+1)*(-1)]=spawnX;
		itemLineNgX[(spawnX+1)*(-1)]=thisItem;
	}
	if (spawnX>0) {
		itemSquareX[spawnX-1]=spawnX;
		itemLineX[spawnX-1]=thisItem;
	}
};

// add item to map on Y
void map::addItemY(item *thisItem,int spawnY) {
	if (spawnY<0) {
		itemSquareNgY[(spawnY+1)*(-1)]=spawnY;
		itemLineNgY[(spawnY+1)*(-1)]=thisItem;
	}
	if (spawnY>0) {
		itemSquareY[spawnY-1]=spawnY;
		itemLineY[spawnY-1]=thisItem;
	}
};

// remove item from map on X
void map::removeItemX(int spawnX) {
	if (spawnX<0) {
		itemSquareNgX[(spawnX+1)*(-1)]=0;
		itemLineNgX[(spawnX+1)*(-1)]=0;
	}
	if (spawnX>0) {
		itemSquareX[spawnX-1]=0;
		itemLineX[spawnX-1]=0;
	}
};

// remove item from map on Y
void map::removeItemY(int spawnY) {
	if (spawnY<0) {
		itemSquareNgY[(spawnY+1)*(-1)]=0;
		itemLineNgY[(spawnY+1)*(-1)]=0;
	}
	if (spawnY>0) {
		itemSquareY[spawnY-1]=0;
		itemLineY[spawnY-1]=0;
	}
};

// check to see if the item exists on this space
bool map::itemExists(int currentX,int currentY) {
	if (currentX==0 && currentY==0)
		return false;

	if (currentX==0 || currentY==0)
		return false;
	
	if (currentX<0 && currentY<0) { // if both X & Y are <0
		if (itemSquareNgX[(currentX+1)*(-1)]==currentX && itemSquareNgY[(currentY+1)*(-1)]==currentY)
			return true;
		else
			return false;
	}
	if (currentX>0 && currentY>0) { // if both X & Y are >0
	        if (itemSquareX[currentX-1]==currentX && itemSquareY[currentY-1]==currentY)
		        return true;
		else
		 	return false;
	}
	if (currentX<0 && currentY>0) { // if X<0 BUT Y>0
	        if (itemSquareNgX[(currentX+1)*(-1)]==currentX && itemSquareY[currentY-1]==currentY)
	                return true;
	        else
	                return false;
	}
	if (currentX>0 && currentY<0) { // if X>0 BUT Y<0
                if (itemSquareX[currentX-1]==currentX && itemSquareNgY[(currentY+1)*(-1)]==currentY)
	                return true;
	        else
	                return false;
	}
};

// get the item's name, similar to itemExists()
item* map::identifyItem(int currentX,int currentY) {
	if (currentX<0 && currentY>0) { // if X<0 BUT Y>0
		if ((itemLineNgX[(currentX+1)*(-1)]->getName())==(itemLineY[currentY-1]->getName()))
			return itemLineNgX[(currentX+1)*(-1)];
	}
	
	if (currentX>0 && currentY<0) { // if X>0 BUT Y<0
		if ((itemLineX[currentX-1]->getName())==(itemLineNgY[(currentY+1)*(-1)]->getName()))
			return itemLineX[currentX-1];
	}

	if (currentX<0 && currentY<0) { // both <0
		if ((itemLineNgX[(currentX+1)*(-1)]->getName())==(itemLineNgY[(currentY+1)*(-1)]->getName()))
			return itemLineNgX[(currentX+1)*(-1)];
	}
	
	if (currentX>0 && currentY>0) { // both >0
		if ((itemLineX[currentX-1]->getName())==(itemLineY[currentY-1]->getName()))
			return itemLineY[currentY-1];
	}

	if (currentX==currentY) {
		std::string xName,yName;
		if (currentX>0 && currentY>0) {
			xName=itemLineX[currentX-1]->getName();
			yName=itemLineY[currentY-1]->getName();
			if (xName==yName)
				return itemLineX[currentX-1];
			if (xName!=yName) {
				return NULL;
			}
		}
		if (currentX<0 && currentY<0) {
			xName=itemLineNgX[(currentX+1)*(-1)]->getName();
			yName=itemLineNgY[(currentY+1)*(-1)]->getName();
			if (xName==yName)
				return itemLineNgX[(currentX+1)*(-1)];
			if (xName!=yName) {
				return NULL;
			}
		}
		
	} // end of -if (currentX==currentY)- block
			
	else
		return NULL;
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
	if (currentX<0 && currentY>0) { // if X<0 BUT Y>0
		if ((itemLineNgX[(currentX+1)*(-1)]->checkType())==(itemLineY[currentY-1]->checkType()))
			return itemLineNgX[(currentX+1)*(-1)]->checkType();
	}
	
	if (currentX>0 && currentY<0) { // if X>0 BUT Y<0
		if ((itemLineX[currentX-1]->checkType())==(itemLineNgY[(currentY+1)*(-1)]->checkType()))
			return itemLineX[currentX-1]->checkType();
	}

	if (currentX<0 && currentY<0) { // both <0
		if ((itemLineNgX[(currentX+1)*(-1)]->checkType())==(itemLineNgY[(currentY+1)*(-1)]->checkType()))
			return itemLineNgX[(currentY+1)*(-1)]->checkType();
	}
	
	if (currentX>0 && currentY>0) { // both >0
		if ((itemLineX[currentX-1]->checkType())==(itemLineY[currentY-1]->checkType()))
			return itemLineX[currentX-1]->checkType();
	}

	if (currentX==currentY) {
		TYPE xType,yType;
		if (currentX>0 && currentY>0) {
			xType=itemLineX[currentX-1]->checkType();
			yType=itemLineY[currentY-1]->checkType();
			if (xType==yType)
				return xType;
			if (xType!=yType)
				return npe;
		}
		
		if (currentX<0 && currentY<0) {
			xType=itemLineNgX[(currentX+1)*(-1)]->checkType();
			yType=itemLineNgY[(currentY+1)*(-1)]->checkType();
			if (xType==yType)
				return xType;
			if (xType!=yType)
				return npe;
		}
	}
	
	else
		return npe;
};

// save the current map data to file
// todo: merge the map.dat file into savefile.dat
int map::saveMapData(int game) {
	std::ofstream fout;
	
	std::stringstream path;
	
	#ifdef __LINUX__
	path << "data/game" << game << "/map.dat";
	#endif
	
	#ifdef __WINDOWS__
	path << "data\\game" << game << "\\map.dat";
	#endif
	
	fout.open(path.str().c_str()); // open a new map file
	
	if (!fout) {
		std::cout << "\nFailed to save map data!\n";
		return 0;
	}
	
	// now we save the item squares to file
	// format is: number <space> number <space>...
	for (int i=0;i<max;i++)
		fout << itemSquareX[i] << " ";
	fout << std::endl;
	
	for (int i=0;i<max;i++)
		fout << itemSquareNgX[i] << " ";
	fout << std::endl;
	
	for (int i=0;i<max;i++)
		fout << itemSquareY[i] << " "; 
	fout << std::endl;

	for (int i=0;i<max;i++)
		fout << itemSquareNgY[i] << " "; 
	fout << std::endl << std::endl;
	
	// now we save the item object arrays to the same file
	for (int i=0;i<max;i++) {
		fout.write((char*) &itemLineX[i],sizeof(itemLineX[i]));
		fout << " ";
	}
	fout << std::endl;
	
	for (int i=0;i<max;i++) {
		fout.write((char*) &itemLineNgX[i],sizeof(itemLineNgX[i]));
		fout << " ";
	}
	fout << std::endl;
	
	for (int i=0;i<max;i++) {
		fout.write((char*) &itemLineY[i],sizeof(itemLineY[i]));
		fout << " ";
	}
	fout << std::endl;
	
	for (int i=0;i<max;i++) {
		fout.write((char*) &itemLineNgY[i],sizeof(itemLineNgY[i]));
		fout << " ";
	}
	fout << std::endl;
	
	fout.close();
};

// load saved map data from file
int map::loadMapData(int game) {
	std::ifstream fin;
	char path[256];
	
	#ifdef __LINUX__
	sprintf(path,"data/game%d/map.dat",game);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(path,"data\\game%d\\map.dat",game);
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
		fin.ignore(256,' ');
	}
	fin.clear();

	for (int i=0;i<max;i++) {
		fin >> itemSquareNgX[i];
		fin.ignore(256,' ');
	}
	fin.clear();

	for (int i=0;i<max;i++) {
		fin >> itemSquareY[i];
		fin.ignore(256,' ');
	}
	fin.clear();

	for (int i=0;i<max;i++) {
		fin >> itemSquareNgY[i];
		fin.ignore(256,' ');
	}
	fin.clear(); fin.clear();
	
	// load the last 4 lines of the file into itemLine
	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineX[i],sizeof(itemLineX[i]));
		fin.ignore(256,' ');
	}	
	fin.clear();
	
	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineNgX,sizeof(itemLineNgX[i]));
		fin.ignore(256,' ');
	}
	fin.clear();
	
	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineY[i],sizeof(itemLineY[i]));
		fin.ignore(256,' ');
	}
	fin.clear();
	
	for (int i=0;i<max;i++) {
		fin.read((char*) &itemLineNgY[i],sizeof(itemLineNgY[i]));
		fin.ignore(256,' ');
	}
	fin.clear();

	fin.close();
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
