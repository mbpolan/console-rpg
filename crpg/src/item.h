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
// item.h: Item class

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include "object.h"
#include "position.h"

/// Enumerated types of items
enum ITEM_TYPE { ITEM_NON_INT,	// not interactive
		 ITEM_EQ,	// equipment
		 ITEM_FOOD	// recovery item
	       };

/** Class that represents an item.
  * Item provides a fairly large API that allows the programmer to manipulate
  * various aspects of its usage. This class derives from Object, therefore
  * it also inherits all of Object's members. Weapons, plants, etc are all
  * types of items, regardless if there are usage by the player or not. 
  *
  * An item has a series of attributes that the programmer can set. All items
  * are loaded from a file, therefore there is no need to make specific classes
  * for other types of items. However, a Container class is provided since some
  * items can contain others.
  *
  * To check if an item can be used, call isUsable(). Attributes can be set by
  * calling setLuck, setStrength(), etc.
*/
class Item: public Object {
	public:
		/// Default constructor
		Item();
		
		/** Constructor taking four parameters
		  * Creates a new item with certain attributes
		  * \param id The unique ID of the item
		  * \param name The name of the item
		  * \param pos The position of this item
		  * \param use Whether or not this item can be used by the player
		*/
		Item(int id, std::string name, Position pos, bool use); 
		
		/** Constructor taking eight parameters
		  * Creates a new item with certain attributes
		  * \param id The unique ID of the item
		  * \param name The name of this item
		  * \param pos The position of this item
		  * \param use Whether or not this item can be used by the player
		  * \param _luck The item's luck boost
		  * \param def The item's defensive boost
		  * \param pow The item's power boost
		  * \param str The item's strength boost
		*/
		Item(int id, std::string name, Position pos, bool use, int _luck, int def, int pow, int str);
		
		/** Set the ID for this item
		  * \param id The unique ID for this item */
		void setID(int id) { itemID=id; };
		
		/** Get the ID for this item
		  * \return The item's ID */
		int getID() const { return itemID; };
		
		/** Set the name for this item
		  * \param name The name for this item */
		void setName(std::string name) { itemName=name; };
		
		/** Get the name for this item
		  * \return The name of this item */
		std::string getName() const { return itemName; };
		
		/** Set the luck boost for this item
		  * \param _luck The luck boost */
		void setLuck(int _luck) { luck=_luck; };
		
		/** Get the luck boost for this item
		  * \return The luck boost this item provides */
		int getLuck() const { return luck; };
		
		/** Set the defense boost for this item
		  * \param def The defensive boost */
		void setDefense(int def) { defense=def; };
		
		/** Get the defense boost for this item
		  * \return The defensive boost this item provides */
		int getDefense() const { return defense; };
		
		/** Set the power boost for this item
		  * \param pow The power boost */
		void setPower(int pow) { power=pow; };
		
		/** Get the power boost for this item
		  * \return The power boost this item provides */
		int getPower() const { return power; };
		
		/** Set the strength boost for this item
		  * \param str The strength boost */
		void setStrength(int str) { strength=str; };
		
		/** Get the strength boost for this item
		  * \return The strength boost this item provides */
		int getStrength() const { return strength; };
		
		/** Set the item's type
		  * \param itemType The type of item
		*/
		void setType(ITEM_TYPE itemType) { type=itemType; };
		
		/** Get the type of item this is
		  * \return This item's type
		*/
		ITEM_TYPE getType() const { return type; };
		
		/** Set whether or not this item can be used
		  * \param use true if usable, otherwise false
		*/
		void setUsable(bool use) { usable=use; }
		
		/** Check if this item is usable
		  * \return true if usable, otherwise false
		*/
		bool isUsable() const { return usable; }
		
		/** Set whether or not this item is plural
		  * \param pl true if yes, otherwise false
		*/
		void setPlural(bool pl) { plural=pl; }
		
		/** Check if this item is plural or not
		  * \return true if plural, otherwise false
		*/
		bool isPlural() const { return plural; }
		
	protected:
		/// The item's ID
		int itemID;
		
		/// Attributes
		int luck, defense, power, strength;
		
		/// The item's name
		std::string itemName;
		
		/// Whether or not this item can be used
		bool usable;
		
		/// The type of item
		ITEM_TYPE type;
		
		/// Multiple amounts of this item
		bool plural;
};

#endif
