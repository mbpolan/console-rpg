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
	posx=0;	posy=0;
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

	// first we check if there are any players nearby and
	// execute actions accordingly.
	std::list<player*>::iterator it;
	for (it=karte->players.begin();it!=karte->players.end();++it) {
		if ((*it)) {
			int x=(*it)->x;
			int y=(*it)->y;

			// player to north
			if ((posx++)==x) {
				action=(rand()%3)-1;
			}

			// player to south
			else if ((posx--)==x) {
				do {
					action=(rand()%3);
				}
				while(action!=MOVE_SOUTH);
			}

			// player to east
			else if ((posy++)==y) {
				do {
					action=(rand()%3);
				}
				while(action!=MOVE_EAST);
			}

			// player to west
			else if ((posy--)==y) {
				do {
					action=(rand()%3);
				}
				while(action!=MOVE_WEST);
			}

			// so there are no nearby players
			else {
				// do a random move for now
				action=(rand()%7);

				// todo: do an action other than move, such as talk
				// to the player(s), etc.
			}

		} // if ((*it))...
	} // for(...)

	// todo: we should also check if there are any npcs nearby =\

	// parse the move and return it
	switch(action) {
		case MOVE_NORTH: return MOVE_NORTH;break;
		case MOVE_SOUTH: return MOVE_SOUTH;break;
		case MOVE_WEST: return MOVE_WEST;break;
		case MOVE_EAST: return MOVE_EAST;break;
		case MOVE_NW: return MOVE_NW;break;
		case MOVE_NE: return MOVE_NE;break;
		case MOVE_SW: return MOVE_SW;break;
		case MOVE_SE: return MOVE_SE;break;
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
