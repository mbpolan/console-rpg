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
 
 #include "creature.h"
 
 class enemy: public creature {
 	public:
		enemy();
		enemy(std::string, int, int, int);
		
		virtual int getHP() const {return hp;}
		virtual void setHP(int _hp) {hp=_hp;}

		virtual int getMP() const {return mp;}
		virtual void setMP(int _mp) {mp=_mp;}

		virtual void setName(std::string _n) {name=_n;}
		virtual std::string getName() const {return name;}

		virtual void setLuck(int _l) {luck=_l;}
		virtual int getLuck() const {return luck;}

		virtual void setPower(int _p) {power=_p;}
		virtual int getPower() const {return power;}

		virtual void setStrength(int _s) {strength=_s;}
		virtual int getStrength() const {return strength;}
		
		virtual void setDefense(int _d) {defense=_d;}
		virtual int getDefense() const {return defense;}
		
		void setLayer(int _layer) {layer=_layer;}
		int getLayer() const {return layer;}
		
		int x, y;
		
	private:
		int hp, mp;
		std::string name;
		
		int luck, power, strength, defense;
		int layer;
};
