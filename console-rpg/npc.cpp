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
	posx=0;
	posy=0;
};

// npc class constructor
npc::npc(int x,int y,std::string _name) {
	name=_name;
	posx=x;
	posy=y;
};

// npc class destructor
npc::~ npc() {
};

// method for determining where to move
void npc::preformMove() {
	srand(time(NULL));
	
	int action=(rand()%7);
	
	switch(action) {
		case MOVE_NORTH: posx++;break;
		case MOVE_SOUTH: posx--;break;
		case MOVE_WEST: posy--;break;
		case MOVE_EAST: posy++;break;
		case MOVE_NW: posx++; posy--;break;
		case MOVE_NE: posx++; posy++;break;
		case MOVE_SW: posx--; posy--;break;
		case MOVE_SE: posx--; posy++;break;
		default: posx++;break;
	}
	
	#ifdef DEBUG
	std::cout << "\nNPC moved to x: " << posx << "/y: " << posy << std::endl;
	#endif
	
	return;
};
