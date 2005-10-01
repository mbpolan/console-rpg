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

#include "definitions.h"
#include "event.h"
#include "events.h"
#include "exception.h"
#include "game.h"
#include "timer.h"
#include "utilities.h"
using namespace Utilities;

// constructor
Game::Game(Map *map): gmap(map), ep(), gdata() {
	// initialize members of struct GameData
	gdata.actionCount=0;
	gdata.currentAction=0;
	gdata.currentPlayer=0;
	gdata.currentTurn=0;
	gdata.day=true;
	gdata.playerCount=0;
	gdata.timeTicks=0;
	gdata.turnCount=0;
	
	// create the mutex
	MutexInit(mutex);
};

// function to save the game to file
void Game::saveGame(std::string path) {
	FILE *f=fopen(path.c_str(), "w");
	if (f) {
		this->lock();
		
		// version of Console RPG
		fputc(version.size(), f);
		for (int i=0; i<version.size(); i++)
			fputc(version[i], f);
		
		// game attributes
		fputc(gdata.turnCount, f);
		fputc(gdata.currentTurn, f);
		fputc(gdata.actionCount, f);
		fputc(gdata.currentAction, f);
		fputc(gdata.playerCount, f);
		fputc(gdata.currentPlayer, f);
		fputc(gdata.timeTicks, f);
		fputc(gdata.day, f);
		
		// save players first
		Player *p;
		std::cout << "Saving players...";
		for (int i=0; i<players.size(); i++) {
			if (players[i]) {
				p=players[i];
				// name
				fputc(p->getName().size(), f);
				for (int j=0; j<p->getName().size(); j++)
					fputc(p->getName()[j], f);
				
				// position
				fputc(p->position.x, f);
				fputc(p->position.y, f);
				fputc(p->position.z, f);
				
				// current hp
				fputc(p->getHP(), f);
				
				// max hp
				fputc(p->getMaxHP(), f);
				
				// current mp
				fputc(p->getMP(), f);
				
				// max mp
				fputc(p->getMaxMP(), f);
				
				// attributes
				PlayerTraits tr=p->getTraits();
				fputc(tr.defense, f);
				fputc(tr.luck, f);
				fputc(tr.power, f);
				fputc(tr.strength, f);
				
				// vocation
				fputc(p->getVocation(), f);
				
				// save equipment by id
				for (int j=0; j<6; j++)
					fputc(p->isEquipped(j) ? p->itemAt(j)->getID() : 0x00, f);
				
				// save backpack by id
				fputc(p->bp->size(), f);
				for (int j=0; j<p->bp->size(); j++)
					fputc(p->bp->getItemByPos(j)->getID(), f);
				
				fputc(0x00, f);
			}
		}
		std::cout << " done\nSaving map...";
		
		// map data
		gmap->lock();
		
		// dimensions
		fputc(gmap->getWidth(), f);
		fputc(gmap->getHeight(), f);
		
		// save item vector
		// count
		fputc(gmap->items.size(), f);
		
		Item *item;
		for (MapObjectIterator it=gmap->items.begin(); it!=gmap->items.end(); ++it) {
			if ((*it)) {
				item=(*it);
				
				// id and location
				fputc(item->getID(), f);
				fputc(item->position.x, f);
				fputc(item->position.y, f);
				fputc(item->position.z, f);
			}
		}
		std::cout << " done\n";
		
		gmap->unlock();
		this->unlock();
		
		// close the file
		fclose(f);
		std::cout << "Your game was saved.\n";
		return;
	}
};

// function to load a saved game
void Game::loadGame(std::string path) {
	std::string buffer;
	FILE *f=fopen(path.c_str(), "r");
	if (f) {
		// version
		std::string sver;
		int count=fgetc(f);
		for (int i=0; i<count; i++)
			sver+=(char) fgetc(f);
		
		// check the version before going on
		if (sver!=version) {
			std::cout << "The version of the savefile (" << sver << ") doesn't match that of this release of Console RPG "
				  << "(" << version << ").\n";
			return;
		}
	
		gdata.turnCount=fgetc(f);
		gdata.currentTurn=fgetc(f);
		gdata.actionCount=fgetc(f);
		gdata.currentAction=fgetc(f);
		gdata.playerCount=fgetc(f);
		gdata.currentPlayer=fgetc(f);
		gdata.timeTicks=fgetc(f);
		gdata.day=fgetc(f);
		
		// load players
		std::cout << "Loading players...";
		
		count=gdata.playerCount;
		Player *p;
		for (int i=0; i<count; i++) {
			p=new Player;
			
			// size of name
			int length=fgetc(f);
			for (int j=0; j<length; j++)
				buffer+=(char) fgetc(f);
			
			// set the name
			p->setName(buffer);
			buffer.clear();
			
			// position
			int x=fgetc(f);
			int y=fgetc(f);
			int z=fgetc(f);
			p->position=Position(x, y, z);
			
			// hp/maxhp/mp/maxmp
			p->setHP(fgetc(f));
			p->setMaxHP(fgetc(f));
			p->setMP(fgetc(f));
			p->setMaxMP(fgetc(f));
			
			// attributes
			int def=fgetc(f);
			int luck=fgetc(f);
			int pow=fgetc(f);
			int str=fgetc(f);
			PlayerTraits tr(luck, str, pow, def);
			p->setTraits(tr);
			
			// vocation
			p->setVocation(itov(fgetc(f)));
			
			// equipment
			for (int j=0; j<6; j++) {
				int id=fgetc(f);
				if (id!=0x00) {
					if (Map::createItem(gmap, id, Position(0xFFFF, 0xFFFF, 0x00)))
						p->equip(j, Map::createItem(gmap, id, Position(0xFFFF, 0xFFFF, 0x00)));
				}
			}
			
			// backpack
			length=fgetc(f);
			for (int j=0; j<length; j++) {
				int id=fgetc(f);
				if (Map::createItem(gmap, id, Position(0xFFFF, 0xFFFF, 0x00)))
					p->bp->addItem(Map::createItem(gmap, id, Position(0xFFFF, 0xFFFF, 0x00)));
			}
			
			// end byte
			fgetc(f);
			
			// store the player
			players.push_back(p);
		}
		std::cout << "done\nLoading map...";
		
		// map data
		gmap->setWidth(fgetc(f));
		gmap->setHeight(fgetc(f));
		
		// items
		count=fgetc(f);
		for (int i=0; i<count; i++) {
			Position pos(0, 0, 0);
			
			// item stuff
			int id=fgetc(f);
			pos.x=fgetc(f);
			pos.y=fgetc(f);
			pos.z=fgetc(f);
			
			// add the item to the list
			if (Map::createItem(gmap, id, pos))
				gmap->items.push_back(Map::createItem(gmap, id, pos));
		}
		
		// clean up
		fclose(f);
		std::cout << "done\n";
		
		// add some initial event functions
		ep.appendEvent(Event::create("TIME_CONTROL_EVENT", &Events::controlTime, this, 1));
		ep.appendEvent(Event::create("SPAWN_MANAGE_EVENT", &Events::spawnManage, this, 5));
		
		// start the loop
		initLoop();
		return;
	}
	
	std::cout << "Error: unable to open savefile (" << path << ")!\n";
};

// main game loop initiator
void Game::init() {
	// see what the user wants to do
	int op=runMenu();
	
	// start a new game
	if (op==GAME_MENU_NEW_GAME)
		startNewGame();
	
	// load a saved game
	else if (op==GAME_MENU_LOAD_GAME)
		loadGame("savefile.crpgsf");
	
	// run the options menu
	else if (op==GAME_MENU_OPTIONS)
		runOptionsMenu();
};

// function that starts the internal game loop
void Game::initLoop() {
	// the player vector should be full, but let's check to be sure :)
	if (players.empty()) {
		// throw an exception
		throw CNoPlayersEx();
	}
	CRPG_CLEAR_SCREEN;
	
	// cycle through each player keeping the turn count in mind
	std::string buffer;
	for (int t=gdata.currentTurn; t<gdata.turnCount; t++) {
		std::cout << "\n<-> Turn " << (t==0 ? t+1 : t) << " <->";
		gdata.currentTurn+=1;
		
		for (int p=gdata.currentPlayer; p<players.size(); p++) {
			std::cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
				  << players[p]->getName() << "'s turn\n"
				  << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
		
			// action loop
			gdata.currentPlayer=p;
			while(1) {
				std::string action;
				
				// check if we need to break out
				if (gdata.currentAction==gdata.actionCount)
					break;
				
				// action message
				std::cout << std::endl << players[p]->getName() << "'s Action [" << gdata.currentAction+1 << "] > ";
			
				std::cin >> action;
				
				// parse the action
				// move north
				if (action=="n") {
					int c=creatureMoveNorth(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
							  << "Moved north\n"
							  << "------------------\n";
						gdata.currentAction+=1;
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
						gdata.currentAction+=1;
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
						gdata.currentAction+=1;
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
						gdata.currentAction+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_WEST));
				}
				
				// move northwest
				else if (action=="nw") {
					int c=creatureMoveNorthwest(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
						  	<< "Moved northwest\n"
							  << "------------------\n";
						gdata.currentAction+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_NORTHWEST));
				}
				
				// move northeast
				else if (action=="ne") {
					int c=creatureMoveNortheast(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
						  	<< "Moved northeast\n"
							  << "------------------\n";
						gdata.currentAction+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_NORTHEAST));
				}
				
				// move southwest
				else if (action=="sw") {
					int c=creatureMoveSouthwest(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
						  	<< "Moved southwest\n"
							  << "------------------\n";
						gdata.currentAction+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_SOUTHWEST));
				}
				
				// move southeast
				else if (action=="se") {
					int c=creatureMoveSoutheast(players[p]);
					if (c==GAME_MOVEMENT_OK) {
						std::cout << "------------------\n"
						  	<< "Moved southeast\n"
							  << "------------------\n";
						gdata.currentAction+=1;
					}
					
					else
						printMovementMessage(c, Direction(DIRECTION_SOUTHEAST));
				}
				
				// reveal position
				else if (action=="pos") {
					std::cout << "------------------\n"
						  << "Your position: X: " << players[p]->position.x 
						  << " | Y: " << players[p]->position.y 
						  << " | Z: " << players[p]->position.z
						  << "\n------------------\n";
				}
				
				// look on the ground
				else if (action=="look") {
					std::cout << "------------------\n";
					creatureLook(players[p]);
					std::cout << "------------------\n";
				}
				
				// check the time
				else if (action=="time") {
					std::cout << "------------------\n";
					std::cout << "It is";
					if (gdata.day)
						std::cout << " daytime ";
					
					else
						std::cout << " nighttime ";
					
					std::cout << "now.\n";
					std::cout << "------------------\n";
				}
				
				// look at inventory
				else if (action=="inv") {
					std::cout << "------------------\n";
					creatureDisplayInventory(players[p]);
					std::cout << "------------------\n";
				}
				
				// equip an item
				else if (action=="equip") {
					std::cout << "------------------\n";
					creatureEquipItem(players[p]);
					std::cout << "------------------\n";
				}
				
				// unequip an item
				else if (action=="unequip") {
					std::cout << "------------------\n";
					creatureUnequipItem(players[p]);
					std::cout << "------------------\n";
				}
				
				// save game
				else if (action=="save") {
					std::cout << "------------------\n";
					this->saveGame("savefile.crpgsf");
					std::cout << "------------------\n";
				}
				
				// display stats
				else if (action=="stats") {
					std::cout << "------------------\n";
					creatureDisplayStats(players[p]);
					std::cout << "------------------\n";
				}
				
				// display contents of backpack
				else if (action=="bp") {
					std::cout << "------------------\n";
					players[p]->bp->displayContents();
					std::cout << "------------------\n";
				}
				
				// add an item to backpack
				else if (action=="add") {
					std::cout << "------------------\n";
					creatureAddItem(players[p]);
					std::cout << "------------------\n";
				}
				
				// remove an item from backpack
				else if (action=="remove") {
					std::cout << "------------------\n";
					creatureRemoveItem(players[p]);
					std::cout << "------------------\n";
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
			
			// update current player data
			if (p+1 >= gdata.playerCount)
				gdata.currentPlayer=0;
			
			else if (p+1 < gdata.playerCount)
				gdata.currentPlayer+=1;
			
			// reset action count
			gdata.currentAction=0;
			
			// clear the screen
			CRPG_CLEAR_SCREEN;
		}
	}
};

// function that starts a new game
void Game::startNewGame() {
	CRPG_CLEAR_SCREEN;
	std::string buffer;
	
	// add some initial event functions
	ep.appendEvent(Event::create("TIME_CONTROL_EVENT", &Events::controlTime, this, 1));
	ep.appendEvent(Event::create("SPAWN_MANAGE_EVENT", &Events::spawnManage, this, 5));
	
	// lock the user until he enters a valid amount of players
	while(1) {
		// ask for the amount of players
		std::cout << "\nEnter amount of players: ";
		std::getline(std::cin, buffer);
	
		gdata.playerCount=atoi(buffer.c_str());
		buffer.clear();
		
		if (gdata.playerCount > 0)
			break;
		
		else
			std::cout << "\nYou must enter at least 1 player!";
	}
	
	// allocate new players
	for (int i=0; i<gdata.playerCount; i++) {
		CRPG_CLEAR_SCREEN;
		std::cout << "\n---------------------------------------\n"
			  << "Player 1 Configuration"
			  << "\n---------------------------------------";
		
		std::cout << "\nEnter name for Player " << i+1 << ": ";
		std::getline(std::cin, buffer);
		std::string name=buffer;
		
		// clean the buffer
		buffer.clear();
		
		// ask for vocation
		int voc=0;
		while(1) {
			std::cout << "\nSelect vocation:\n~~~~~~~~~~~\n1) Knight\n2) Paladin\n3) Mage\n~~~~~~~~~~~\n> ";
			std::getline(std::cin, buffer);
			
			// parse the vocation
			voc=atoi(buffer.c_str());
			
			if (voc<=0 || voc > 3) {
				std::cout << "Invalid vocation.\n";
				continue;
			}
			
			else
				break;
		}
		
		// create a player with specific attributes that relate to the vocation
		switch(voc) {
			case VOCATION_KNIGHT: {
				players.push_back(new Player(name, Position(0, 0, 0), PlayerTraits(10, 15, 15, 20), 150, 150, 5, 5));
				players[i]->setVocation(VOCATION_KNIGHT);
			}
			break;
			
			case VOCATION_PALADIN: {
				players.push_back(new Player(name, Position(0, 0, 0), PlayerTraits(10, 15, 25, 10), 130, 130, 10, 10));
				players[i]->setVocation(VOCATION_PALADIN);
			}
			break;
			
			case VOCATION_MAGE: {
				players.push_back(new Player(name, Position(0, 0, 0), PlayerTraits(10, 5, 10, 5), 100, 100, 100, 100));
				players[i]->setVocation(VOCATION_MAGE);
			}
			break;
		}
		
		// done with this player
		std::cout << "\n//////////////////////////\n"
			  << "Player " << name << " (" << capFirst(vocToString(players[i]->getVocation())) << ") created.\n"
			  << "Press any key to continue player configuration."
			  << "\n//////////////////////////\n> ";
		
		std::getline(std::cin, buffer);
	}
	
	CRPG_CLEAR_SCREEN;
	
	// configure options
	std::cout << "\n---------------------------------------\n"
		  << "Global Game Configuration"
		  << "\n---------------------------------------";
		  
	std::cout << "\nEnter amount of turns: ";
	std::cin >> gdata.turnCount;
	
	std::cout << "\nEnter amount of actions allowed per turn: ";
	std::cin >> gdata.actionCount;
	
	// start the game loop
	initLoop();
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
		
		CRPG_CLEAR_SCREEN;
		
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

// function to move a creature northwest
int Game::creatureMoveNorthwest(Creature *c) {
	if (c->position.y-1 < 0 || c->position.x > gmap->getHeight())
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
	
	c->position.y-=1;
	c->position.x+=1;
	return GAME_MOVEMENT_OK;
};

// function to move a creature northeast
int Game::creatureMoveNortheast(Creature *c) {
	if (c->position.y+1 > gmap->getWidth() || c->position.x+1 > gmap->getHeight())
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
	
	c->position.y+=1;
	c->position.x+=1;
	return GAME_MOVEMENT_OK;
};

// function to move a creature southwest
int Game::creatureMoveSouthwest(Creature *c) {
	if (c->position.y-1 < 0 || c->position.x-1 < 0)
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
	
	c->position.y-=1;
	c->position.x-=1;
	return GAME_MOVEMENT_OK;
};

// function to move a creature southeast
int Game::creatureMoveSoutheast(Creature *c) {
	if (c->position.y+1 > gmap->getWidth() || c->position.x-1 < 0)
		return GAME_MOVEMENT_OUT_OF_BOUNDS;
	
	c->position.y+=1;
	c->position.x-=1;
	return GAME_MOVEMENT_OK;
};

// function to add an item to a player's backpack
void Game::creatureAddItem(Creature *c) {
	Player *p=dynamic_cast<Player*> (c);
	if (p) {
		if (gmap->getItem(p->position)) {
			Item *item=gmap->getItem(p->position);
			if (item->isUsable()) {
				if (p->bp->canAddItem()) {
					p->bp->addItem(item);
					gmap->removeItem(p->position);
					std::cout << "You added " << item->getName() << " to your backpack.\n";
				}
				
				else if (!p->bp->canAddItem())
					std::cout << "You can't add anymore items into your backpack.\n";
				
				return;
			}
			
			std::cout << "You can't add this item to your backpack.\n";
		}
		
		else
			std::cout << "There are no items here that you can add to your backpack\n";
		
		return;
	}
};

// function to remove an item from a player's backpack
void Game::creatureRemoveItem(Creature *c) {
	Player *p=dynamic_cast<Player*> (c);
	if (p) {
		int slot;
		p->bp->displayContents();
		
		// if the backpack is empty, then return
		if (p->bp->empty())
			return;
		
		// lock the user until we get a valid slot or he aborts
		while(1) {
			std::cout << "Slot to remove (0 to abort): ";
			std::cin >> slot;
			
			// check if we want to abort this function
			if (slot==0)
				return;
			
			// verify the slot
			else if (slot < 1 || slot > p->bp->size()) {
				std::cout << "Invalid slot.\n";
				continue;
			}
			
			else
				break;
		}
		
		// sync the slot with the backpack's contents
		slot-=1;
		
		// remove the target item
		Item *item=p->bp->getItemByPos(slot);
		p->bp->removeItemByPos(slot);
		
		// change the items' position
		item->position=p->position;
		
		// put it back on the map
		gmap->placeItem(item);
		
		std::cout << "You removed " << item->getName() << std::endl;
	}
};

// function to show a creature's inventory
void Game::creatureDisplayInventory(Creature *c) {
	Player *p=dynamic_cast<Player*> (c);
	if (p) {
		std::cout << p->getName() << "'s Inventory"
			  << "\n~~~~~~~~~~~~~~~~~~\n";
		// head equipment
		std::cout << "1) Head (";
		if (p->isEquipped(PLAYER_SLOT_HEAD))
			std::cout << p->itemAt(PLAYER_SLOT_HEAD)->getName();
		 
		else
			std::cout << "empty";
		std::cout << ")\n";
		
		// torso equipment
		std::cout << "2) Torso ("; 
		if (p->isEquipped(PLAYER_SLOT_TORSO))
			std::cout << p->itemAt(PLAYER_SLOT_TORSO)->getName();
		 
		else
			std::cout << "empty";
		std::cout << ")\n";
		
		// left hand equipment
		std::cout << "3) Left Hand (";
		if (p->isEquipped(PLAYER_SLOT_LEFT_ARM))
			std::cout << p->itemAt(PLAYER_SLOT_LEFT_ARM)->getName();
		 
		else
			std::cout << "empty"; 
		std::cout << ")\n";
		
		// right hand equipment
		std::cout << "4) Right Hand (";
		if (p->isEquipped(PLAYER_SLOT_RIGHT_ARM))
			std::cout << p->itemAt(PLAYER_SLOT_RIGHT_ARM)->getName();
		 
		else 
			std::cout << "empty";
		std::cout << ")\n";
		
		// leg equipment
		std::cout << "5) Legs (";
		if (p->isEquipped(PLAYER_SLOT_LEGS))
			std::cout << p->itemAt(PLAYER_SLOT_LEGS)->getName();
		 
		else
			std::cout << "empty";
		std::cout << ")\n";
					
		// boot equipment
		std::cout << "6) Boots (";
		if (p->isEquipped(PLAYER_SLOT_BOOTS))
			std::cout << p->itemAt(PLAYER_SLOT_BOOTS)->getName();
		
		else 
			std::cout << "empty";
		std::cout << ")\n";
		
		std::cout << "~~~~~~~~~~~~~~~~~~\n";
	}
};

// function to display stats
void Game::creatureDisplayStats(Creature *c) {
	Player *p=dynamic_cast<Player*> (c);
	if (p) {
		PlayerTraits tr=p->getTraits();
		std::cout << p->getName() << "'s Stats\n~~~~~~~~~~~~~~~\n";
		std::cout << "HP: " << p->getHP() << "/" << p->getMaxHP() << std::endl
			  << "MP: " << p->getMP() << "/" << p->getMaxMP() << std::endl
			  << "Defense: " << tr.defense << " (" << (tr.defenseBoost < 0 ? "-" : "+") << tr.defenseBoost << ")\n"
			  << "Luck: " << tr.luck << " (" << (tr.luckBoost < 0 ? "-" : "+") << tr.luckBoost << ")\n"
			  << "Power: " << tr.power  << " (" << (tr.powerBoost < 0 ? "-" : "+") << tr.powerBoost << ")\n"
			  << "Strength: " << tr.strength << " (" << (tr.strengthBoost < 0 ? "-" : "+") << tr.strengthBoost << ")\n"
			  << "\nVocation: " << capFirst(vocToString(p->getVocation())) << std::endl;
		std::cout << "~~~~~~~~~~~~~~~\n";
	}
};

// function that handles a creature equipping an item
void Game::creatureEquipItem(Creature *c) {
	std::string buffer;
	Player *p=dynamic_cast<Player*> (c);
	if (p) {
		// check if this item exists
		if (gmap->getItem(c->position)) {
			Item *item=dynamic_cast<Item*> (gmap->getItem(c->position));
			if (item && item->isUsable()) {
				// ask which slot to equip to
				int act=0;
				while(1) {
					creatureDisplayInventory(p);
					
					std::cout << "Equip to slot (0 to abort): > ";
					// get the user's choice
					std::cin.ignore();
					std::getline(std::cin, buffer);
					
					act=atoi(buffer.c_str());
					buffer.clear();
					
					if (act<0 || act>6) {
						std::cout << "\nInvalid slot.\n";
						continue;
					}
					
					else if (act==0) {
						std::cout << "\nNothing was equipped.\n";
						return;
					}
					
					else
						break;
				}
				
				// sync this up with the equipment array
				act-=1;
				
				// check if there are any equipped items at this slot
				Item *fcon;
				bool unequip=false;
				if (p->isEquipped(act)) {
					fcon=p->unequip(act);
					unequip=true;
				}
				
				// equip to slot
				p->equip(act, item);
				
				// remove this item off the ground
				gmap->removeItem(p->position);
				
				// place old item on ground
				if (unequip) {
					// modify position
					fcon->position=c->position;
					gmap->placeItem(fcon);
					
					// confirmation messages
					std::cout << "\nYou unequipped " << fcon->getName() << " and ";
					std::cout << "you equipped " << item->getName() << ".\n";
				}
				
				else
					std::cout << "\nYou equipped " << item->getName() << ".\n";
				
				return;
			}
			
			// not equipable
			std::cout << "This item can't be equipped.\n";
			return;
		}
		
		// no item
		std::cout << "There is no item here that can be equipped.\n";
		return;
	}
};

// function to unequip an item
void Game::creatureUnequipItem(Creature *c) {
	std::string buffer;
	Player *p=dynamic_cast<Player*> (c);
	if (p) {
		// show the inventory first
		creatureDisplayInventory(p);
		std::cin.ignore();
		
		// lock the user until a valid choice is made
		int slot=0;
		while(1) {
			std::cout << "Unequip from slot (0 to abort): > ";
			std::getline(std::cin, buffer);
			
			// get the slot number
			slot=atoi(buffer.c_str());
			slot-=1;
			buffer.clear();
			
			// abort the unequip
			if (slot==-1) {
				std::cout << "\nNothing was unequipped.\n";
				return;
			}
			
			// make sure this slot is valid
			else if (!p->isEquipped(slot) || slot<0 || slot>6) {
				std::cout << "\nInvalid or empty slot.\n";
				continue;
			}
			
			// everything seems ok
			else
				break;
		}
		
		// unequip and get the item
		Item *fcon=p->unequip(slot);
		fcon->position=p->position;
		
		// place this item on the ground
		gmap->placeItem(fcon);
		
		// confirmation message
		std::cout << "\nYou unequipped " << fcon->getName() << ".\n";
	}
};

// function that allows a creature to check the ground for items
void Game::creatureLook(Creature *c) {
	// check if an object is even here
	if (gmap->getItem(c->position)) {
		// is this an item?
		Item *item=gmap->getItem(c->position);
		if (item) {
			std::cout << "You see ";
			
			// make sure to use proper grammar
			// (my english teacher would be strict as hell about this ;P)
			if (!item->isPlural()) {
				if (hasVowel(item->getName()))
					std::cout << "an ";
			
				else
					std::cout << "a ";
			}
			 
			std::cout << item->getName() << "." << std::endl;
		}
		
		/*
		// check for other players
		Player *p=dynamic_cast<Player*> (gmap->getObject(c->position.x, c->position.y, c->position.z));
		if (p)
			std::cout << "You see " << p->getName() << "." << std::endl;*/
	}
	
	// print the ground type
	std::cout << "You see grass." << std::endl; // TODO: different ground tiles
};

// function that displays an error message if needed about a move
void Game::printMovementMessage(int move_code, Direction dir) {
	switch(move_code) {
		case GAME_MOVEMENT_OUT_OF_BOUNDS: std::cout << "\nYou can't move any further " << dir.getString() << "!\n"; break;
		case GAME_MOVEMENT_BLOCKING_SPACE: std::cout << "\nThat space is blocked!\n"; break;
		default: return;
	}
};
