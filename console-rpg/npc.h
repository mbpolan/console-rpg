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
 
#ifndef npc_h
#define npc_h

// npc.h: NPC class declaration for most (if not all) NPC creatures

// needed libraries
#include <iostream>
#include <time.h>
#include <libxml/parser.h>

// needed headers
#include "creature.h"
#include "map.h"
#include "player.h"

class map;

class npc {
	public:
		npc();
		npc(int _layer, int,int,std::string _name); // our constructor
		npc(int _layer, std::string,int,int,int,int); // xml parsed constructor
		~npc();

		// methods for AI and actions
		ACTIONS preformThink(map*);
		void preformMove(map*,bool);
		void preformAction(int,ACTIONS);

		// other methods
		int getID() const {return id;}

		static void setNpcsOn(int npcs) {npcsOn=npcs;}
		static int getNpcsOn() {return npcsOn;}
		
		void setLayer(int l) {layer=l;}
		int getLayer() const {return layer;}
		
		xmlNodePtr compressToXML();
		
		// communication methods
		std::string replyToMsg(std::string);

		// coordinates
		int posx;
		int posy;
		
		std::string name;
		int hp,mp;

	private:
		int id;
		static int npcsOn;
		int layer; // map layer
};

#endif
