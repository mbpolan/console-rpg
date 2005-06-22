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
#include "item.h"
#include "itemmodel.h"
#include "object.h"

/// Map Object iterator
typedef std::list<Object*>::iterator MapObjectIterator;

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
		*/
		Map(int width, int height);
		
		/// Destructor
		virtual ~Map();
		
		/// Map of item database
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
		
		/// Get a pointer to an object on the map
		/** \param x The x coordinate
		  * \param y The y coordinate
		  * \param z The z coordinate
		  * \return The requested object, or NULL if not found
		*/
		Object* getObject(int x, int y, int z);
		
		/** Place an object on the map
		  * Note: The object's coordinates should already be changed to the
		  * ones that it should be on.
		  * \param obj The target object
		*/
		void placeObject(Object *obj);
		
		/** Remove an object from the map
		  * \param x The x coordinate
		  * \param y The y coordinate
		  * \param z The z coordinate
		  * \return true if the object was removed, otherwise false if not
		*/
		bool removeObject(int x, int y, int z);
		
		/** Load an item database from XML file
		  * \param file The path to the target file
		  * \return true if the database was loaded, false otherwise
		*/
		void loadItemsFromXML(std::string file);
		
		/** Creates a new item
		  * Attempts to create an item based on ID, loading attributes
		  * from the loaded database.
		  * \return A pointer to a new Item
		*/
		static Item* createItem(Map*, int id, Position pos);
		
	protected:
		/// Spawn initial items on map
		void spawnMapItems(int amount);
		
		/// List of all objects on the map
		std::list<Object*> objects;
		
		/// Width of the map
		int mapWidth;
		
		/// Height of the map
		int mapHeight;
};

#endif
