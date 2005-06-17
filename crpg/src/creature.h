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
// creature.h: base class for all creature-like objects

#ifndef CREATURE_H
#define CREATURE_H 

#include <iostream>
#include "object.h"
#include "position.h"

/** Base class for creatures.
  * The Creature class serves as a base class for all creature-like
  * objects. If you plan on making your own type of creature, then
  * use this class to derive your own from.
  * 
  * If you are looking for more specific classes, consider the Player or
  * NPC classes. Use the Enemy class for monsters that can fight the
  * the user.
*/
class Creature: public Object {
	public:
		/// Default constructor
		/** Creates a new Creature with default values
		*/
		Creature(): Object(0, 0, 0), maxHP(100), hp(100) {};
		
		/// Constructor
		/** Creates a new Creature with a name
		  * \param _name The name of this creature
		  * \param maximumHP The maximum amount of hitpoints
		  * \param initialHP The initial amount of hitpoints
		*/
		Creature(std::string &_name, Position &pos, int maximumHP=100, int initialHP=100): 
			 Object(pos.x, pos.y, pos.z), name(_name), maxHP(maximumHP), hp(initialHP) {};
		
		/// Destructor
		virtual ~Creature() {};
		
		/// Set the amount of hitpoints the creature has <i>now</i>
		/** This function sets the amount of hitpoints that the creature should
		  * have at this point. Note that this is not the maximum hitpoints allowed!
		  * \param hitpoints The amount of hitpoints
		*/
		void setHP(int hitpoints) { hp=hitpoints; };
		
		/// Get the amount of hitpoints this creature has now
		/** Returns the amount of hitpoints this creature has at this point
		  * \return The current hitpoints
		*/
		int getHP() const { return hp; };
		
		/// Set the amount of hitpoints for this creature
		/** \param hitpoints The amount of hitpoints to be the new total
		*/
		void setMaxHP(int hitpoints) { maxHP=hitpoints; };
		
		/// Get the total hitpoints for this creature
		/** Returns the maximum amount of hitpoints for this creature to have
		  * \retun The total amount of max hitpoints
		*/
		int getMaxHP() const { return maxHP; };
		
		/// Set the name of this creature
		/** \param _name The name to give to this creature 
		*/
		void setName(const std::string &_name) { name=_name;} ;
		
		/// Get the name of this creature
		/** Returns the name of this creature
		  * \return This creature's name
		*/
		std::string getName() const { return name; };
		
	protected:
		/// The name for this creature
		std::string name;
		
		/// The current amount of hitpoints
		int hp;
		
		/// The maximum amount of hitpoints
		int maxHP;
};

#endif
