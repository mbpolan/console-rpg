/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
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
 
#ifndef movement_h
#define movement_t

// movement.h: holds movement system and map stuff
#include "map.h"

class movement { 
	public:
		movement(); // our constructor
		virtual ~movement() {};

		// movement methods
		void moveN(map*);
		void moveS(map*);
		void moveW(map*);
		void moveE(map*);
		void moveNE(map*);
		void moveNW(map*);
		void moveSE(map*);
		void moveSW(map*);

		// other methods
		void look(map*);
		void placeItem(item*,map*);
		void removeItem(item*,map*);
		void spawnMapItems(movement*,map*);

		// public accessors
		signed int getCurrentPosition(map*) const;

		// time related methods
		void checkTime();
		int controlTime(int);
		int getStepCount() const {return stepCount;}
		
	private:
		std::string itemWarning;
		bool fDay;
		int stepCount;
};

#endif

