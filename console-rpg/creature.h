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
		
		// visual accessors
		void setHair(std::string hairColor) {hairOutfit=hairColor;}
		void setTorso(std::string torsoColor) {torsoOutfit=torsoColor;}
		void setLegs(std::string legsColor) {legsOutfit=legsColor;}
		
		std::string getHair() const {return hairOutfit;}
		std::string getTorso() const {return torsoOutfit;}
		std::string getLegs() const {return legsOutfit;}
		
	protected:
		std::string name;
		std::string hairOutfit, legsOutfit, torsoOutfit;

};

#endif
