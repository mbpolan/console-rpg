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

#include <algorithm>
#include <time.h>

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

// remove a directory
int utilities::removeDir(const char *dir) {
	// last time we need to check the client's system and
	// use the appropriate command
	char delCommand[256];
	
	#ifdef __LINUX__
	sprintf(delCommand,"rm -rf %s",dir);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(delCommand,"rmdir /Q /S %s",dir);
	#endif

	system(delCommand);
};

// produce a random number based on a given range (low to high)
int utilities::random_range(int low, int high) {
    srand(static_cast<unsigned> (time(0)));
    
    if(low>high) {
        std::swap(low,high);
    }
    
    int range=high-low+1;
    return low+int(range*rand()/(RAND_MAX+1.0));
};
