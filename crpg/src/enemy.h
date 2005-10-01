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

/// Effects that a monster can issue unto a player
enum MONSTER_EFFECT  { EFFECT_POISON		=	0x00,
		       EFFECT_BURN		=	0x01,
		       EFFECT_ELETROCUTE	=	0X02
		     };

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
		
		/** Set the hit range
		  \param lowest The lowest possible hit
		  \param highest The highest possible hit
		*/
		void setHitRange(int lowest, int highest) { lowestHit=lowest; highestHit=highest; };
		
		/** Get the lowest attack hit for this monster
		  * \returns The lowest hit
		*/
		int getLowestHit() const { return lowestHit; };
		
		/** Get the highest hit for this monster
		  * \returns The highest hit
		*/
		int getHighestHit() const { return highestHit; };
		
		/** Set effect for this monster
		  * \param effect The effect to set
		*/
		void setEffect(MONSTER_EFFECT effect) { monsterEffect=effect; };
		
		/** Get the effect for this monster
		  * \returns The effect this monster issues in battle
		*/
		MONSTER_EFFECT getEffect() const { return monsterEffect; };
		
		/** Sets the general combat level for this monster
		  * \param level The combat level
		*/
		void setCombatLevel(int level) { mLevel=level; };
		
		/** Gets this monster's combat level
		  * \returns The combat level
		*/
		int getCombatLevel() const { return mLevel; };
		
		/** Set the amount of experience points this monster rewards
		  * \param exp The amount of points
		*/
		void setExpReward(int exp) { expGiven=exp; };
		
		/** Gets the amount of experience points this monster rewards
		  * \returns The amount of points
		*/
		int getExpReward() const { return expGiven; };
		
	
	protected:
		/// Lowest possible hit
		int lowestHit;
		
		/// Highest possible hit
		int highestHit;
		
		/// Combat level
		int mLevel;
		
		/// Exp given
		int expGiven;
		
		/// Monster's effect in battle
		MONSTER_EFFECT monsterEffect;
};

#endif
