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

 #ifndef creature_h
 #define creature_h
 
// creature.h: holds the ADT creature class

// enumerated actions the creature can preform
enum ACTIONS {
	MOVE_NORTH,
	MOVE_SOUTH,
	MOVE_WEST,
	MOVE_EAST,
	MOVE_NW,
	MOVE_NE,
	MOVE_SW,
	MOVE_SE,
	TALK,
	DROP_ITEM,

	MOVE, // this is generic
	DO_NOTHING // stand still
};

class creature {
	public:
		virtual ~creature() {};

		virtual int getHP() const =0;
		virtual void setHP(int) =0;

		virtual int getMP() const =0;
		virtual void setMP(int) =0;

		virtual void setName(std::string) =0;
		virtual std::string getName() const =0;

		virtual void setLuck(int) =0;
		virtual int getLuck() const =0;

		virtual void setPower(int) =0;
		virtual int getPower() const =0;

		virtual void setStrength(int) =0;
		virtual int getStrength() const =0;
		
		virtual void setDefense(int) =0;
		virtual int getDefense() const =0;
	
	protected:
		bool isBurned, isPoisoned, isElectrified;
};

#endif
