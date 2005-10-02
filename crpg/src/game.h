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
// game.h: the Game class

#ifndef GAME_H
#define GAME_H

#include <iostream> 
#include <queue>
#include <vector>
#include "event.h"
#include "eventprocessor.h"
#include "map.h"
#include "player.h"
#include "position.h"

/// Struct that stores critical Game class data
struct GameData {
	/// Amount of turns total
	int turnCount;
	
	/// The current turn
	int currentTurn;
	
	/// Amount of actions total
	int actionCount;
	
	/// The current action for active player
	int currentAction;
	
	/// Amount of players
	int playerCount;
	
	/// The active player that saved the game last
	int currentPlayer;
	
	/// The amount of timeTicks that passed
	int timeTicks;
	
	/// Time of day
	bool day;
};

/** Class that controls all aspects of the game.
  * This is an important class that pretty much serves as the "core" of
  * Console RPG. All events, such as battles, are handled through this
  * class. To start the main loop, call the function init().
*/
class Game {
	public:
		/** Constructor
		  * \param map An instance of a Map class to be used in the game
		*/
		Game(Map *map);
		
		/// Destructor
		virtual ~Game() {};
		
		/** Function that prepares and starts the game */
		void init();
		
		/** Get a pointer to the stored map
		  * \return A pointer to this map
		*/
		Map* map() const { return gmap; };
		
		/** Set the amount of time ticks
		  * \param ticks The amount of ticks
		*/
		void setTimeTicks(int ticks) { gdata.timeTicks=ticks; };
		
		/** Get the amount of time ticks
		  * \return Time ticks
		*/
		int getTimeTicks() const { return gdata.timeTicks; };
		
		/// Lock the Game mutex
		void lock() { LockMutex(mutex); };
		
		/// Unlock the Game mutex
		void unlock() { UnlockMutex(mutex); };
		
		/** Function that adds an event to the internal EventProcessor's queue
		  * \param e The event to be added to the event queue
		*/
		void appendEvent(Event *e) { ep.appendEvent(e); };
		
		/** Function to change the time of day */
		void changeDay() { gdata.day=gdata.day ? false : true; };
		
		/// Function that saves a game to file
		void saveGame(std::string path);
		
		/// Function that loads a game
		void loadGame(std::string path);
		
	protected:
		/// Game map
		Map *gmap;
		
		/// Event processor
		EventProcessor ep;
		
		/// Function that starts the internal thread
		void createGameThread();
		
		/// Function that initializes the main game loop
		void initLoop();
		
		/// Function that starts a new game
		void startNewGame();
		
		/// Function that presents the options menu
		void runOptionsMenu();
		
		/// Function that runs the menu
		int runMenu();
		
		/// Action functions
		int creatureMoveNorth(Creature*);
		int creatureMoveSouth(Creature*);
		int creatureMoveEast(Creature*);
		int creatureMoveWest(Creature*);
		int creatureMoveNorthwest(Creature*);
		int creatureMoveNortheast(Creature*);
		int creatureMoveSouthwest(Creature*);
		int creatureMoveSoutheast(Creature*);
		void creatureAddItem(Creature*);
		void creatureDisplayInventory(Creature*);
		void creatureDisplayStats(Creature*);
		void creatureEquipItem(Creature*);
		void creatureRemoveItem(Creature*);
		void creatureUnequipItem(Creature*);
		void creatureLook(Creature*);
		void creatureInitBattle(Creature*, Enemy*);
		void checkMovement(Creature*);
		void beginBattleSequence(Player*, Enemy*);
		void endBattleSequence(Player*, Enemy*);
		void printMovementMessage(int move_code, const Direction dir);
		
		/// Game data struct
		struct GameData gdata;
		
		/// Vector of players
		std::vector<Player*> players;
		
		/// Mutex
		TMutex mutex;
};

#endif
