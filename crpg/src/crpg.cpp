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
#include "game.h"
#include "map.h"

// version
const std::string version="0.3.0";

// main
int main(int argc, char *argv[]) {
	// header
	std::cout << "~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n"
		  << "   Console RPG version " << version << "\n"
		  << "~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n\n";
	
	// create a 50x50 map
	Map *map=new Map(50, 50);
	
	// create a new game object
	Game *game=new Game(map);
	
	// start the game
	game->init();
	
	// free memory
	delete game; // game also deletes map
};
