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
// object.h: base class for any physical thing in the game 

#ifndef OBJECT_H
#define OBJECT_H

#include "position.h"

/** Base class for all objects
  * This is a base class that any physical thing in the game should
  * derive from. Unless you are making your own object, you shouldn't
  * need to use this class directly.
*/
class Object {
	public:
		/// Default constructor
		/** Creates a new Object at points (0, 0, 0)*/
		Object(): position(0, 0, 0) {};
		
		/// Constructor taking the coordinates of its location
		/** Creates a new Object at the specified points
		  * \param _x The x coordinate
		  * \param _y The y coordinate
		  * \param _z The z coordinate
		*/
		Object(int _x, int _y, int _z): position(_x, _y, _z) {};
		
		/// Destructor
		virtual ~Object() {};
		
		/// Position of this object
		Position position;
};

#endif
