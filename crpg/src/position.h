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
// position.h: Position class and friends

#ifndef POSITION_H
#define POSITION_H

#include <iostream>

// directional define's
#define DIRECTION_NORTH	0
#define DIRECTION_SOUTH	1
#define DIRECTION_WEST	2
#define DIRECTION_EAST	3

/** Class that stores direction.
  * This class simply stores an integral direction and provides a function,
  * getString(), to parse a string from the direction.
*/
class Direction {
	public:
		/// Constructor
		/** \param dir The integral direction
		*/
		Direction(int dir): direction(dir) {};
		
		/// Returns a string parsed from the integral direction
		/** \return An std::string with the direction
		*/
		std::string getString() const {
			switch(direction) {
				case DIRECTION_NORTH: return std::string("north");
				case DIRECTION_SOUTH: return std::string("south");
				case DIRECTION_WEST: return std::string("west");
				case DIRECTION_EAST: return std::string("east");
			}
		};
		
	private:
		/// The direction of type int
		int direction;
};

/** Class containing the position of an object.
  * The Position class simply holds 3 integral members which represent
  * the location of an object on the coordinate plane.
*/
class Position {
	public:
		/// Constructor
		/** \param _x The x coordinate
		  * \param _y The y coordinate
		  * \param _z The z coordinate
		*/
		Position(int _x, int _y, int _z):
			x(_x), y(_y), z(_z) {};
		
		/// Coordinates
		int x, y, z;
};

#endif
