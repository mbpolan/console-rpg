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
// container.h: the Container class

#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <list>
#include "item.h"

// Convenience iterator for Container's item list
typedef std::list<Item*>::iterator ContainerIterator;

/** A storage class that contains other Items.
  * Container is a container class that can store Items. Each Container
  * can have a limit of Items, and that parameter is passed to the constructor. You
  * can add Items by calling addItem() or by using the overloaded insertion operator.
  * Both of the above methods abide by the Container's item limit. 
  *
  * You can remove an item by calling removeItemByPos(), which requires a position of
  * the item you wish to remove. To remove large quantities of items, call removeItemsByID(),
  * which removes every item in the Container that has a matching ID to the one specified in
  * the parameter. Note that the above functions don't call delete on the items you are removing;
  * it is your responsibility to free memory occupied by the Items. However, the destructor will
  * take care of freeing the memory allocated to its contents.
*/
class Container: public Item {
	public:
		/** Constructor
		  * \param max The maximum amount of items this Container can hold
		*/
		Container(int max): maxItems(max) {};
		
		/// Destructor
		virtual ~Container();
		
		/// Overloaded operator << for addition of items
		void operator<<(Item*);
		
		/** Add an item to the Container
		  * \param item The Item to add
		*/
		void addItem(Item* item);
		
		/** Get an Item by its position
		  * \param pos The target item's position
		*/
		Item* getItemByPos(int pos);
		
		/** Remove an item by its position
		  * \param pos The target item's position
		*/
		void removeItemByPos(int pos);
		
		/** Remove all items with the matching ID's
		  * \param id The ID number of the item(s) to remove
		*/
		void removeItemsByID(int id);
		
		/** Check if the Container is holding an item with the specified ID
		  * \param id The target Item's ID
		*/
		bool hasItem(int id);
		
		/// Get the size of the contents list
		int size() const { return items.size(); };
		
		/// Get the maximum size of this container
		int getItemLimit() const { return maxItems; };
		
		/// Set the maximum size for this container
		void setItemLimit(int limit) { maxItems=limit; };
		
		/// Check if another item can be added
		bool canAddItem() const;
		
		/// Check if the container is empty
		bool empty() const { return items.empty(); };
		
		/// Display the Container's contents in a numbered list
		void displayContents();
		
		
	protected:
		// The maximum amount of items this Container can carry
		int maxItems;
		
		/// The Container's contents
		std::list<Item*> items;
};

#endif
