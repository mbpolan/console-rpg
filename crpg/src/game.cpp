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
	
	//
	else if (op==GAME_MENU_LOAD_GAME)
		loadGame();
	
	else if (op==GAME_MENU_OPTIONS)
		runOptionsMenu();
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
		std::cout << "<-> Turn " << t+1 << " <->" << std::endl;
		
		for (int p=0; p<players.size(); p++) {
			std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
				  << players[p]->getName() << "'s turn\n"
				  << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
			std::cin.ignore();
		
			// action loop
			int act=0;
			while(1) {
				std::string action;
				
				// check if we need to break out
				if (act==actionCount)
					break;
				
				// action message
				std::cout << std::endl << players[p]->getName() << " Action > ";
			
				std::cin >> action;
				
				// parse the action
				// move north
				if (action=="n") {
					creatureMoveNorth(players[p]);
					std::cout << "------------------\n"
						  << "Moved north\n"
						  << "------------------\n";
					act+=1;
				}
			
				// move south
				else if (action=="s") {
					creatureMoveSouth(players[p]);
					std::cout << "------------------\n"
						  << "Moved south\n"
						  << "------------------\n";
					act+=1;
				}
				
				// move east
				else if (action=="e") {
					creatureMoveEast(players[p]);
					std::cout << "------------------\n"
						  << "Moved east\n"
						  << "------------------\n";
					act+=1;
				}
				
				// move west
				else if (action=="w") {
					creatureMoveWest(players[p]);
					std::cout << "------------------\n"
						  << "Moved west\n"
						  << "------------------\n";
					act+=1;
				}
				
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
				
				else if (action=="end") {
					std::string q;
					std::cout << "------------------\n"
						  << "End your turn?\n"
						  << "------------------\n\n> ";
						 
					std::cin >> q;
					if (q[0]=='Y' || q[0]=='y')
						break;
				}
			
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
void Game::creatureMoveNorth(Creature *c) {
	c->getPosition().x+=1;
};

// function to move a creature south
void Game::creatureMoveSouth(Creature *c) {
	c->getPosition().x-=1;
};

// function to move a creature east
void Game::creatureMoveEast(Creature *c) {
	c->getPosition().y-=1;
};

// function to move a creature west
void Game::creatureMoveWest(Creature *c) {
	c->getPosition().y+=1;
};
