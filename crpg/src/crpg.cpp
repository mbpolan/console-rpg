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
// crpg.cpp: main file

#include <iostream>
#include "definitions.h"
#include "exception.h"
#include "game.h"
#include "map.h"
#include "parser.h"
#include "utilities.h"
using namespace Utilities;

// main
int main(int argc, char *argv[]) {
	// header
	std::cout << "~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n"
		  << "   Console RPG version " << version << "\n"
		  << "~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n\n";
	
	// create a lua parser
	std::string path, method;
	try {
		Parser p("crpg.cfg");
		
		method=p.getStringValue("itemdb_type");
		path=p.getStringValue("itemdb_path");
	}
	
	// catch exceptions
	catch (const CLoadErrorEx &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
		exit(1);
	}
	
	// check the method
	int loadMethod=mtoi(method);
	if (loadMethod < 0 || loadMethod > 1) {
		std::cout << "Invalid item database load method!\n";
		exit(1);
	}
	
	// create a 50x50 map
	Map *map=new Map(50, 50, loadMethod, path);
	
	// create a new game object
	Game *game=new Game(map);
	
	// start the game
	game->init();
	
	// free memory
	delete game; // game also deletes map
};
