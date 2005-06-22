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
// itemmodel.h: the ItemModel class

#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <iostream>

/** Model that represents an item.
  * ItemModel is a class that stores information about a certain item including
  * its ID, name, and attributes. If you wish to store information about an
  * item, and don't plan on using that item directly, then you should use this
  * class instead of Item.
*/
class ItemModel {
	public:
		/** Constructor
		  * \param _name The item's name
		  * \param id The item's unique ID
		  * \param luck The item's luck boost
		  * \param def The item's defensive boost
		  * \param pow The item's power boost
		  * \param str The item's strength boost
		*/
		ItemModel(std::string _name, int id, int luck, int def, int pow, int str, bool _usable):
			name(_name), luckBoost(luck), defenseBoost(def), powerBoost(pow), strBoost(str), usable(_usable) {};
			
		/** Get the name of this item
		  * \return The name of this item */
		std::string getName() const { return name; };
		
		/** Get the ID of this item
		  * \return The ID number for this item */
		int getID() const { return id; };
		
		/** Get the luck boost for this item
		  * \return The luck boost this item provides */
		int getLuck() const { return luckBoost; };
		
		/** Get the defense boost for this item
		  * \return The defensive boost this item provides */
		int getDefense() const { return defenseBoost; };
		
		/** Get the power boost for this item
		  * \return The power boost this item provides */
		int getPower() const { return powerBoost; };
		
		/** Get the strength boost for this item
		  * \return The strength boost this item provides */
		int getStrength() const { return strBoost; };
		
		/** Check if this item is usable or not
		  * \return true if usable, false otherwise */
		bool isUsable() const { return usable; };  
		
	private:
		/// Name of this model
		std::string name;
		
		/// Attribute boosters
		int luckBoost, defenseBoost, powerBoost, strBoost;
		
		/// ID of this item
		int id;
		
		/// Usable item
		bool usable;
};

#endif
