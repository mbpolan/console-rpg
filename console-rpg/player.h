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
 
#ifndef player_h
#define player_h

// player.h: holds player class and member data
#include "creature.h"
#include "items.h"
#include "map.h"

enum vocation {warrior,mage,archer};

class player: public creature {
	public:
		player();
		player(int hp,int mp,int id); // new player constructor
		player(int hp,int mp,int Luck,int Strength,int Power,int Defense,int id); // enhanced constructor
		virtual ~player();

		// overloaded operators
		player &operator=(const player&);
		
		// player specific definitions
		int getHP() const {return currentHP;}
		void setHP(int hp) {currentHP=hp;}
	
		int getMP() const {return currentMP;}
		void setMP(int mp) {currentMP=mp;}
		
		void setName(std::string initialName) {playerName=initialName;}
		std::string getName() const {return playerName;}
		
		void setLuck(int _luck) {luck=_luck;};
		int getLuck() const {return luck;}
		
		void setPower(int _power) {power=_power;}
		int getPower() const {return power;}
		
		void setStrength(int _strength) {strength=_strength;}
		int getStrength() const {return strength;}
		
		void setDefense(int _defense) {defense=_defense;}
		int getDefense() const {return defense;}
		
		void setHeight(int height) {playerHeight=height;}
		int getHeight() const {return playerHeight;}
		
		void setAge(int age) {playerAge=age;}
		int getAge() const {return playerAge;}
				
		void setVoc(vocation _vocation) {playerVocation=_vocation;}
		vocation getVoc() const {return playerVocation;}
		
		// level related stat accessors
		void setLevel(int _level) {level=_level;}
		int getLevel() const {return level;}
		void setExp(int _exp) {exp=_exp;}
		int getExp() const {return exp;}
		
		void increaseExp(int _exp) {exp+=_exp;} 
		void increaseLevel();
		
		// visual accessors
		void setLook();
		void setHair(std::string hairColor) {hair=hairColor;}
		void setTorso(std::string torsoColor) {torso=torsoColor;}
		void setLegs(std::string legsColor) {legs=legsColor;}
		std::string getHair() const {return hair;}
		std::string getTorso() const {return torso;}
		std::string getLegs() const {return legs;}
		
		// for saving the data to a savefile
		int savePlayerData(map*,int,int,bool);
		int loadPlayerData(map*,int,int);
		int saveToIndex(int);
		int loadFromIndex(int);
		int removeTemp();
		
		// item actions
		void setHeadItem(item*);
		void setTorsoItem(item*);
		void setLegsItem(item*);
		void setBootsItem(item*);
		std::string getHeadItem() const {return headEq;}
		std::string getTorsoItem() const {return torsoEq;}
		std::string getLegsItem() const {return legEq;}
		std::string getBootsItem() const {return bootEq;}
		
		// inventory actions
		void removeInventoryItem(int);
		void addInventoryItem(TYPE,std::string);
		int searchInventory(player*,std::string);

		// to display player's stats
		void displayInventory();
		int displayStats();
		
		// misc methods
		void setPlayerID(int id) {playerID=id;}
		int getPlayerID() const {return playerID;}
		void setPlayersOn(int players) {playersOn=players;}
		int getPlayersOn() {return playersOn;}
		
	private:
		static int playersOn; // count of all the players on the game
		
		int playerID;
		int currentHP,currentMP,luck,strength,power,defense,level,exp;
		int playerHeight,playerAge;
		std::string playerName;
		std::string hair, legs, torso;
		std::string headEq,torsoEq,legEq,bootEq;
		vocation playerVocation;
};

#endif

