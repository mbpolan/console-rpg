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
// game.cpp: implementations of the Game class

#include "game.h"

// main game loop initiator
void Game::init() {
	// see what the user wants to do
	int op=runMenu();
	
	// start a new game
	if (op==GAME_MENU_NEW_GAME)
		startNewGame();
	
	// load a saved game
	else if (op==GAME_MENU_LOAD_GAME)
		loadGame();
	
	// run the options menu
	else if (op==GAME_MENU_OPTIONS)
		runOptionsMenu();
	
	// create an thread to run in the background and process events
	createGameThread();
};

// function that initializes the internal thread
void Game::createGameThread() {
	pthread_t thread;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	pthread_create(&thread, &attr, initThread, this);
};

// function that starts the internal game loop
void Game::initLoop() {
	// the player vector should be full, but let's check to be sure :)
	if (players.empty()) {
		// throw an exception
	}
	
	// cycle through each player keeping the turn count in mind
	std::string buffer;
	for (int t=0; t<turnCount; t++) {
		std::cout << "\n<-> Turn " << t+1 << " <->";
		
		for (int p=0; p<players.size(); p++) {
			std::cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
				  << players[p]->getName() << "'s turn\n"
				  << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
		
			// action loop
			int act=0;
			while(1) {
				std::string action;
				
				// check if we need to break out
				if (act==actionCount)
					break;
				
				// action message
				std::cout << std::endl << players[p]->getName() << "'s Action > ";
			
				std::cin >> action;
				
				// parse the action
				// move north
				if (action=="n") {
					int c=creatureMoveNorth(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
							  << "Moved north\n"
							  << "------------------\n";
						act+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_NORTH));
				}
			
				// move south
				else if (action=="s") {
					int c=creatureMoveSouth(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
							  << "Moved south\n"
							  << "------------------\n";
						act+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_SOUTH));
				}
				
				// move east
				else if (action=="e") {
					int c=creatureMoveEast(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
							  << "Moved east\n"
						  	<< "------------------\n";
						act+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_EAST));
				}
				
				// move west
				else if (action=="w") {
					int c=creatureMoveWest(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
						  	<< "Moved west\n"
							  << "------------------\n";
						act+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_WEST));
				}
				
				// reveal position
				else if (action=="pos") {
					std::cout << "------------------\n"
						  << "Your position: X: " << players[p]->position.x 
						  << " | Y: " << players[p]->position.y 
						  << " | Z: " << players[p]->position.z
						  << "\n------------------\n";
				}
				
				// quit the game
				else if (action=="quit") {
					std::string q;
					std::cout << "------------------\n"
						  << "Are you sure you want to quit the game?\n"
						  << "------------------\n\n> ";
					
					std::cin >> q;
					if (q[0]=='Y' || q[0]=='y') {
						// TODO: exit to main menu
						exit(1);
					}
				}
				
				// end turn early
				else if (action=="end") {
					std::string q;
					std::cout << "------------------\n"
						  << "End your turn?\n"
						  << "------------------\n\n> ";
						 
					std::cin >> q;
					if (q[0]=='Y' || q[0]=='y')
						break;
				}
			
				// appears to be an invalid action...
				else
					std::cout << "Invalid action!\n";
			
				// clear the buffer
				buffer.clear();
			}
		
			// turn is over
			std::cout << "\n---------------------------\n"
				  << players[p]->getName() << "'s turn is over.\n"
				  << "Press any key to continue..."
				  << "\n---------------------------\n\n";
			 
			std::cin.ignore();
			std::cin.get();
		}
	}
};

// function to start the internal thread
void* Game::initThread(void *data) {
	Game *game=(Game*) data;
	
	// event loop
	while(1) {
		// check for events
		if (!game->eventQueue.empty()) {
			Event *e=game->eventQueue.top();
			//std::cout << "Found event: " << e->eventName << std::endl;
			
			// create a thread to handle this
			pthread_t thread;
			pthread_create(&thread, NULL, e->routine, e->eventData);
			
			// remove this event
			game->eventQueue.pop();
		}
	}
};

// function that starts a new game
void Game::startNewGame() {
	std::string buffer;
	
	// ask for the amount of players
	std::cout << "\nEnter amount of players: ";
	std::getline(std::cin, buffer);
	
	playerCount=atoi(buffer.c_str());
	buffer.clear();
	
	// allocate new players
	for (int i=0; i<playerCount; i++) {
		std::cout << "\nEnter name for Player " << i+1 << ": ";
		std::getline(std::cin, buffer);
		
		// add this player
		players.push_back(new Player(buffer, Position(0, 0, 0), PlayerTraits(10, 10, 10, 10), 100, 100, 20, 20));
		
		// clean the buffer
		buffer.clear();
	}
	
	// configure options
	std::cout << "\nEnter amount of turns: ";
	std::cin >> turnCount;
	
	std::cout << "\nEnter amount of actions allowed per turn: ";
	std::cin >> actionCount;
	
	// start the game loop
	initLoop();
};

// TODO: function that loads a saved game
void Game::loadGame() {
};

// TODO: function that runs the options menu
void Game::runOptionsMenu() {
};

// function that runs the main menu
int Game::runMenu() {
	std::string buffer;
	int op;
	
	// loop until we have a valid choice
	while(1) {
		std::cout << "=============================";
		std::cout << "\nSelect an option:"
			  << "\n-----------------------------"
			  << "\n1) Start new game"
			  << "\n2) Load saved game"
			  << "\n3) Options"
			  << "\n4) Quit"
			  << "\n=============================\n\n> ";
		  
		std::getline(std::cin, buffer);
	
		// parse the option
		op=atoi(buffer.c_str());
		
		//clearScreen(); // TODO: clear the screen
		
		// check if it is valid
		if (op > 0 && op < 5)
			break;
		
		// not valid, reprint
		std::cout << std::endl;
		continue;
	}
	
	return op;
};

// function to move a creature north
int Game::creatureMoveNorth(Creature *c) {
	if (c->position.x+1 > gmap->getHeight())
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
	
	c->position.x+=1;
	return GAME_MOVEMENT_OK;
};

// function to move a creature south
int Game::creatureMoveSouth(Creature *c) {
	if (c->position.x-1 < 0)
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
		
	c->position.x-=1;
	return GAME_MOVEMENT_OK;
};

// function to move a creature east
int Game::creatureMoveEast(Creature *c) {
	if (c->position.y+1 > gmap->getWidth())
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
		
	c->position.y+=1;
	return GAME_MOVEMENT_OK;
};

// function to move a creature west
int Game::creatureMoveWest(Creature *c) {
	if (c->position.y-1 < 0)
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
	
	c->position.y-=1;
	return GAME_MOVEMENT_OK;
};

// function that displays an error message if needed about a move
void Game::printMovementMessage(int move_code, Direction dir) {
	switch(move_code) {
		case GAME_MOVEMENT_OUT_OF_BOUNDS: std::cout << "\nYou can't move any further " << dir.getString() << "!\n"; break;
		case GAME_MOVEMENT_BLOCKING_SPACE: std::cout << "\nThat space is blocked!\n"; break;
		default: return;
	}
};
