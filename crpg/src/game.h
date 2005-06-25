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

// define's for menu
#define GAME_MENU_NEW_GAME	1
#define GAME_MENU_LOAD_GAME	2
#define GAME_MENU_OPTIONS	3

// different types of situations that could result from movement
#define GAME_MOVEMENT_OUT_OF_BOUNDS	0
#define GAME_MOVEMENT_OK		1
#define GAME_MOVEMENT_BLOCKING_SPACE	2

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
		Game(Map *map): gmap(map), ep(), timeTicks(0), day(true) { MutexInit(mutex); };
		
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
		void setTimeTicks(int ticks) { timeTicks=ticks; };
		
		/** Get the amount of time ticks
		  * \return Time ticks
		*/
		int getTimeTicks() const { return timeTicks; };
		
		/// Lock the Game mutex
		void lock() { LockMutex(mutex); };
		
		/// Unlock the Game mutex
		void unlock() { UnlockMutex(mutex); };
		
		/** Function that adds an event to the internal EventProcessor's queue
		  * \param e The event to be added to the event queue
		*/
		void appendEvent(Event *e) { ep.appendEvent(e); };
		
		/** Function to change the time of day */
		void changeDay() { day=day ? false : true; };
		
	protected:
		/// Game map
		Map *gmap;
		
		/// Event processor
		EventProcessor ep;
		
		/// Function that starts the internal thread
		void createGameThread();
		
		/// Function that initializes the main game loop
		void initLoop();
		
		// Function that initializes the main thread
		static void* initThread(void *data);
		
		/// Function that starts a new game
		void startNewGame();
		
		/// Function that loads a game
		void loadGame();
		
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
		void creatureLook(Creature*);
		void printMovementMessage(int move_code, const Direction dir);
		
		/// Amount of actions before the turn ends
		int actionCount;
		
		/// Amount of players
		int playerCount;
		
		/// Amount of turns maximum before the game ends
		int turnCount;
		
		/// Time ticks
		int timeTicks;
		
		/// Time of day
		bool day;
		
		/// Vector of players
		std::vector<Player*> players;
		
		/// Mutex
		TMutex mutex;
};

#endif
