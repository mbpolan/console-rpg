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

#include "utilities.h"

// convert a char array to an std::string
std::string utilities::atos(const char* cstring) {
	std::stringstream ss;
	
	for (int i=0;i<strlen(cstring);i++) {
		ss << cstring[i];
	}
	
	return ss.str();
};

// convert a vocation to an int
int utilities::vtoi(VOCATION myvoc) {
	int voc;
	
	switch(myvoc) {
		case WARRIOR: voc=0;break;
		case MAGE: voc=1;break;
		case ARCHER: voc=2;break;
		default: voc=0;break;
	}
	
	return voc;
};

// convert an int to a player vocation
VOCATION utilities::itov(int voc) {
	VOCATION myvoc;
	
	switch(voc) {
		case 0: myvoc=WARRIOR;break;
		case 1: myvoc=MAGE;break;
		case 2: myvoc=ARCHER;break;
		default: myvoc=WARRIOR;break;
	}
	
	return myvoc;
};

// delete the temporary directory (99)
int utilities::removeTemp() {
	// last time we need to check the client's system and
	// use the appropriate file separator.
	char path[256];
	char delCommand[256];
	
	#ifdef __LINUX__
	sprintf(path,"data/game99/savefile1.dat");
	sprintf(delCommand,"rm -rf data/game99");
	#endif
	
	#ifdef __WINDOWS__
	sprintf(path,"data\\game99\\savefile1.dat");
	sprintf(delCommand,"rm -rf data\\game99");
	#endif

	std::ifstream fin;
	
	// first we attempt to load a savefile from the temporary
	// directory. if it fails, then there is no need to remove
	// the directory since it doesn't exist. otherwise, remove it!
	fin.open(path);
	
	if (fin) {
		fin.close();
		system(delCommand);
	}
};
