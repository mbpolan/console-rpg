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
 
 #include <iostream>
 
 #include "enemy.h"
 
enemy::enemy() {
	x=0;
	y=0;
	layer=0;

	hp=100;
	mp=60;
	name="";
	
	luck=1;
	power=10;
	strength=10;
	defense=10;
};

enemy::enemy(std::string _name, int _spawnX, int _spawnY, int _layer) {
	x=_spawnX;
	y=_spawnY;
	layer=_layer;
	
	hp=100;
	mp=60;
	name=_name;
	
	luck=1;
	power=10;
	strength=10;
	defense=10;
};
