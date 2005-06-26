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
// player.h: the Player class

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "creature.h"
#include "item.h"
#include "position.h"

/// Vocations for players
enum VOCATION { VOCATION_KNIGHT=0x01, VOCATION_PALADIN=0x02, VOCATION_MAGE=0x03 };

/** Class that holds some player attributes and traits.
  * An instance of this class is used as a member of the Player class for
  * storage of traits and skill levels.
*/
class PlayerTraits {
	public:
		/** Constructor
		  * \param _luck The amount of luck to allocate to the player
		  * \param _strength The strength skill level
		  * \param _power The power skill level
		  * \param _defense The defense skill level
		*/
		PlayerTraits(int _luck, int _strength, int _power, int _defense):
			     luck(_luck), strength(_strength), power(_power), defense(_defense) {};
		
		/// Skill levels
		int luck, strength, power, defense;
};

/** Class that represents a human player.
  * Any creature that can be controlled by the user should be an instance
  * of this class. The Player class is unique in the sense that it has
  * its own set of traits that the user can have.
*/
class Player: public Creature {
	public:
		/// Default constructor
		/** Creates a player with default settings and no name */
		Player();
		
		/// Constructor taking name, position, and hitpoint parameters
		/** Creates a player with the provided parameters
		  * \param _name The name of the player
		  * \param pos The position of the player
		  * \param hp The maximum hitpoints
		  * \param hpNow Current amount of hitpoints
		*/
		Player(std::string _name, Position pos, PlayerTraits ptraits, int hp, int hpNow, int mp, int mpNow);
		
		/// Destructor
		virtual ~Player();
		
		/** Set the maximum magic points
		  * \param mp The amount of magic points
		*/
		void setMaxMP(int mp) { maxMagicPts=mp; };
		
		/** Get the maximum amount of magic points
		  * \return The maximum allowed magic points for this player
		*/
		int getMaxMP() const { return maxMagicPts; };
		
		/** Set the traits for this player
		  * \param ptraits The trait set that this player will have
		*/
		void setTraits(PlayerTraits &ptraits) { traits=ptraits; }
		
		/** Get this player's traits
		  * \return The trait set for this player
		*/
		PlayerTraits getTraits() const { return traits; };
		
		/** Set this player's vocation
		  * \param voc The vocation for this player
		*/
		void setVocation(VOCATION voc) { VOC=voc; };
		
		/** Get this player's vocation
		  * \return This player's vocation
		*/
		VOCATION getVocation() const { return VOC; };
		
				/** Equip an item onto a specific slot
		  * \param slot The target slot
		  * \param item The item to equip
		  * \return The item previously equipped on the target slot, NULL if none
		*/ 
		Item* equip(int slot, Item *item);
		
		/** Unequip an item at a specific slot
		  * \param slot The target slot
		  * \return The item previously equipped on the target slot, NULL if none
		*/
		Item* unequip(int slot);
		
		/** Check if a slot is already occupied
		  * \param slot The target slot
		  * \return true if the slot is occupied, false otherwise
		*/
		bool isEquipped(int slot);
		
		/** Get a pointer to the item stored at this slot
		  * \param slot The target slot
		  * \return A pointer to the requested item
		*/
		Item *itemAt(int slot) { return equipment[slot]; };
		
	protected:
		/// Magic points
		int maxMagicPts;
		int magicPts;
		
		/// Traits for this player
		PlayerTraits traits;
		
		/// Player vocation
		VOCATION VOC;
		
		/// Equipment
		Item *equipment[6];
};

#endif
