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
#include "battlesystem.h"
#include "creature.h"
#include "enemy.h"
#include "items.h"
#include "map.h"
#include "movement.h"
#include "npc.h"

enum VOCATION {WARRIOR,MAGE,ARCHER};

class battleAction;
class map;
class movement;

class player: public creature {
	public:
		player();
		player(int hp,int mp,int id); // new player constructor
		player(int hp,int mp,int Luck,int Strength,int Power,int Defense,int id); // enhanced constructor
		virtual ~player();

		// overloaded operators
		player &operator=(const player&);
		bool operator==(const player&);
		
		// player specific definitions
		int getHP() const {return currentHP;}
		void setHP(int hp) {currentHP=hp;}
	
		int getMP() const {return currentMP;}
		void setMP(int mp) {currentMP=mp;}
		
		void setName(std::string initialName) {name=initialName;}
		std::string getName() const {return name;}
		
		void setLuck(int _luck) {luck=_luck;};
		int getLuck() const {return luck;}
		
		void setPower(int _power) {power=_power;}
		int getPower() const {return power;}
		
		void setStrength(int _strength) {strength=_strength;}
		int getStrength() const {return strength;}
		
		void setDefense(int _defense) {defense=_defense;}
		int getDefense() const {return defense;}
		
		void setVoc(VOCATION _vocation) {playerVocation=_vocation;}
		VOCATION getVoc() const {return playerVocation;}
		
		// level related stat accessors
		void setLevel(int _level) {level=_level;}
		int getLevel() const {return level;}
		void setExp(int _exp) {exp=_exp;}
		int getExp() const {return exp;}
		
		void increaseExp(int _exp) {exp+=_exp;} 
		void increaseLevel(int);
		
		// for saving the data to a savefile
		int savePlayerData(int,int,bool);
		int loadPlayerData(int,int);
		
		int saveToIndex(int);
		static int loadFromIndex(int,int&);
		int removeTemp();
		
		// item actions
		void setHeadItem(item*);
		void setTorsoItem(item*);
		void setLegsItem(item*);
		void setBootsItem(item*);
		item* getHeadItem() const {return headEq;}
		item* getTorsoItem() const {return torsoEq;}
		item* getLegsItem() const {return legEq;}
		item* getBootsItem() const {return bootEq;}
		
		// inventory actions
		void removeInventoryItem(int);
		void addInventoryItem(TYPE,item*);
		int searchInventory(std::string);

		// to display player's stats
		void displayInventory();
		int displayStats();
		
		// visual accessors
		void setHair(std::string hairColor) {hairOutfit=hairColor;}
		void setTorso(std::string torsoColor) {torsoOutfit=torsoColor;}
		void setLegs(std::string legsColor) {legsOutfit=legsColor;}
		std::string getHair() const {return hairOutfit;}
		std::string getTorso() const {return torsoOutfit;}
		std::string getLegs() const {return legsOutfit;}
		
		// misc methods
		void setPlayerID(int id) {playerID=id;}
		int getPlayerID() const {return playerID;}
		
		static void setPlayersOn(int players) {playersOn=players;}
		static int getPlayersOn() {return playersOn;}
		
		void setLook();
		void setLayer(int _layer) {layer=_layer;}
		int getLayer() const {return layer;}
		
		// communication methods
		void sendNpcMsg(map*,movement*);
		
		// battle methods
		void receiveAttack(battleAction*);
		bool attemptRunFromBattle(enemy*);
		bool inBattle, inDefense;

		int x,y;
		
		// player's backpack
		bag *bp;

	private:
		std::string name;
		std::string hairOutfit, legsOutfit, torsoOutfit;
		
		static int playersOn; // count of all the players on the game
		
		// stats and id
		int playerID;
		int currentHP,currentMP,luck,strength,power,defense,level,exp;
		int layer; // map layer
		
		// equipment
		item *headEq;
		item* torsoEq;
		item *legEq;
		item *bootEq;
		
		// vocation
		VOCATION playerVocation;
};

#endif

