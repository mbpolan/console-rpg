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
// map.h: the Map class

#ifndef MAP_H
#define MAP_H

#include <list>
#include <map>
#include "definitions.h"
#include "enemy.h"
#include "item.h"
#include "itemmodel.h"
#include "object.h"
#include "threads.h"
using namespace Threads;

/// Map Object iterator
typedef std::list<Item*>::iterator MapObjectIterator;

/// Map Enemy iterator
typedef std::list<Enemy*>::iterator MapEnemyIterator;

/// Map ItemModel iterator
typedef std::map<int, ItemModel*>::iterator MapItemIterator;

/** A class that contains data about the map.
  * This class controls and stores information about the various aspects
  * of the world map. Any objects are stored in a list and can be manipulated
  * by calling certain Map functions.
  *
  * An instance of the Map can be found in the Game class.
*/
class Map {
	public:
		/// Constructor
		/** Creates a new blank map that is <i>width</i> tiles wide and
		  * <i>height</i> tiles high.
		  * \param width The width in tiles
		  * \param height The height in tiles
		  * \param loadMethod The method used to load the item database
		  * \param path Path to the item database file
		*/
		Map(int width, int height, int loadMethod, std::string path);
		
		/// Destructor
		virtual ~Map();
		
		/// List of item database
		std::map<int, ItemModel*> itemDB;
		
		/// Clear the entire map of any objects
		void clear();
		
		/// Sets the new height of the map
		/** Changes the height of the map to be <i>height</i> tiles.
		  * Warning: the entire map will be cleared and then remade with
		  * the new height measurements.
		  * \param height The new height of the map in tiles
		*/
		void setHeight(int height);
		
		/** Get the height of the map
		  * \return The height of this map in tiles
		*/
		int getHeight() const { return mapHeight; };
		
		/// Sets the new width of the map
		/** Changes the width of the map to be <i>width</i> tiles.
		  * Warning: the entire map will be cleared and then remade with
		  * the new width measurements.
		  * \param width The new width of the map in tiles
		*/
		void setWidth(int width);
		
		/** Get the width of the map
		  * \return The width of this map in tiles
		*/
		int getWidth() const { return mapWidth; };
		
		/** Get a pointer to an item on the map
		  * \param pos The target position
		  * \return The requested object, or NULL if not found
		*/
		Item* getItem(Position pos);
		
		/** Place an item on the map
		  * Note: The item's coordinates should already be changed to the
		  * ones that it should be on.
		  * \param item The target item
		*/
		void placeItem(Item *item);
		
		/** Remove an item from the map
		  * \param pos The item's position
		  * \return true if the item was removed, otherwise false if not
		*/
		bool removeItem(Position pos);
		
		/** Get a pointer to an Enemy object on the map
		  * \param pos The target position
		  * \return The requested Enemy object, NULL if not found
		*/
		Enemy* getEnemy(Position pos);
		
		/** Place an Enemy on the map
		  * \param enemy The Enemy to place
		*/
		void placeEnemy(Enemy *enemy);
		
		/** Remove an Enemy from the map
		  * \param pos The target position
		  * \return true if removed, false otherwise
		*/
		bool removeEnemy(Position pos);
		
		/** Load an item database from XML file
		  * \param file The path to the target file
		*/
		void loadItemsFromXML(std::string file);
		
		/** Load an item database from binary file
		  * \param file The path to the target file
		*/
		void loadItemsFromBinary(std::string file);
		
		/** Creates a new item
		  * Attempts to create an item based on ID, loading attributes
		  * from the loaded database.
		  * \return A pointer to a new Item
		*/
		static Item* createItem(Map*, int id, Position pos);
		
		/// List of all items on the map
		std::list<Item*> items;
		
		/// List of all enemies on the map
		std::list<Enemy*> enemies;
		
		/// Lock the Map mutex
		void lock() { LockMutex(mutex); };
		
		/// Unlock the Map mutex
		void unlock() { UnlockMutex(mutex); };
		
	protected:
		/// Spawn initial items on map
		void spawnMapItems(int amount);
		
		/// Spawn initial enemies on map
		void spawnEnemies(int amount);
		
		/// Width of the map
		int mapWidth;
		
		/// Height of the map
		int mapHeight;
		
		/// Mutex
		TMutex mutex;
};

#endif
