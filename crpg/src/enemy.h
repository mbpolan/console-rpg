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
// enemy.h: the Enemy class 

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "creature.h"
#include "position.h"

/** Creature that is attackable by players.
  * The Enemy class is a derived Creature that can be attacked and battled
  * by the user.
*/
class Enemy: public Creature {
	public:
		/** Constructor
		  * \param name The name of this Enemy
		  * \param hpNow Initial hitpoints
		  * \param hpMax Maximum hitpoints
		  * \param pos The position of this object
		*/
		Enemy(std::string name, int hpNow, int hpMax, Position pos);
		
		/// Destructor
		virtual ~Enemy();
};

#endif
