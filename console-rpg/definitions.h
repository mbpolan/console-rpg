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

 #ifndef definitions_h
 #define definitions_h
 
// definitions.h: holds function declarations and definitions
#include <iostream>
#include <ctype.h> // for toupper()

#include "player.h"
#include "movement.h"

// our prototypes
// move these into classes later
int mainMenu(player**,int);
void startGame(movement*,map*,player*,int);
void optionMenu();

// menu function: display menu and options
int menu() { // takes a reference to player
	std::string menuChoice;
	for(;;) {
		std::cout << "\nMain Menu\n"
		     << "---------" << std::endl;
		std::cout << "(1) Start a new game.\n"
		     << "(2) Continue playing\n"
		     << "(3) Options\n"
		     << "(4) Quit\n"
		     << "---------\n> ";
		std::cin >> menuChoice;
		std::cin.ignore(); // remove the newline
		
		// the user wants to start a new game
		if (menuChoice=="1") {
		
			int players; // the amount of players
			std::cout << "\nHow many players in this game? ";
			std::cin >> players;
			std::cin.ignore(); // remove the newline
			
			// make an array of current players
			player *playerList[players];
			
			// fill up this array
			for (int i=0;i<players;i++) {
				playerList[i]=new player(5,0,0,0,i); // player HP/MP/Height(ft)/age/id
			}
			
			mainMenu(playerList,players); // pass in the character list
			delete [] playerList; // delete all players
			
			return 0;
		}
		
		if (menuChoice=="2") {
			
			std::cout << "\nLoading from data/ directory...";
			
			int players;
			//player *playerList[players];
			//std::cout << 
		}
			
		
		if( menuChoice=="3")
			optionMenu(); // display options (todo)
		
		else
			return 0;
	}
}

// mainMenu: function for displaying the main menu
int mainMenu(player **r_list,int playerCount) { // takes an array of players and count

	movement *grid=new movement; // make a new movement grid
	map *karte=new map(30,30,-30,-30); // make a new map
	char cVar; // confirmation variable
	
	// loop for as long as there are players
	for (int i=0;i<playerCount;i++) {
		// now we configure each player's character
		std::cout << "\n==========================";
		std::cout << "\nPlayer " << i+1 << " Configuration\n";
		std::cout << "\nEnter player name: ";
		std::string name;
		std::getline(std::cin,name,'\n');
	
		// we need to set name and look
		// make a temporary player object
		player *pPlayer=new player;
		
		pPlayer->setPlayerID(i+1);
		pPlayer->setName(name);
		pPlayer->setLook();
		
		// put this temporary object into the array for good
		r_list[i]=pPlayer;
		
		std::cin.ignore();
		std::cout << "==========================\n";
	}
	
	std::cout << "\nStart a new game? (y,n) ";
	std::cin >> cVar;
	cVar=toupper(cVar);
	
	if (cVar=='Y') {
		int j=0; // counter variable
		 
		for (;;) {
			// reset the counter
			if (j==playerCount)
				j=0;
			
			std::cout << "\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*";
			std::cout << "\nWelcome to Console RPG, " << r_list[j]->getName() << std::endl
			<< "Type 'help' to display a help menu.";
			std::cout << "\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*";
			startGame(grid,karte,r_list[j],playerCount); // this is where we actually start
			j++;
		}
	}
	else {
		std::cout << "\nQuitting...\n";
		return 0;
	}
	
	delete grid; // we are done with the grid map; delete it
	delete karte; // we are done with the world map; delete it
	grid=0;
	karte=0;
}

// optionMenu: function for displaying option menu (finish this later)
void optionMenu() {
	std::cout << "\nNo options avaliable at this time.\n";
}

int turns=0; // amount of turns
// startGame function: this will start the actual game
void startGame(movement *rhs,map *karte,player* r_player,int playerCount) {
	
	bool firstTurn=true; // first turn flag
	
	std::cout << "\nTURN: " << turns << std::endl;
	
	// if amount of turns is greater than the amount of players,
	// then flag firstTurn to false so we can load the player's
	// stats before he starts.
	if (turns>=playerCount)
		firstTurn=false;
	
	// reset the coordinates for the next player as long as it's
	// still his first turn.
	if (firstTurn) {
		karte->setCurrentSpaceX(0);
		karte->setCurrentSpaceY(0);
	}
	
	// if it is NOT the first turn
	// 99 is the temporary directory number for saved files
	if (!firstTurn)
		r_player->loadPlayerData(karte,r_player->getPlayerID(),99);

	while(1) {
		int count=rhs->getStepCount(); // count the amount of spaces moved
		rhs->spawnMapItems(rhs,karte); // spawn items on map NOW
	
		std::cout << "\nMove: ";
		
		std::string moverVar;
		std::cin >> moverVar;
		
		// for debugging purposes only!
		#ifdef DEBUG
		if (moverVar=="mod") {
			r_player->setHP(0);
		}
		#endif
		
		if (moverVar=="n") {
			rhs->moveN(karte);
			rhs->controlTime(count);
		}
		
		if (moverVar=="s") {
			rhs->moveS(karte);
			rhs->controlTime(count);
		}
		
		if (moverVar=="w") {
			rhs->moveW(karte);
			rhs->controlTime(count);
		}
		
		if (moverVar=="e") {
			rhs->moveE(karte);
			rhs->controlTime(count);
		}
		
		if (moverVar=="nw") {
			rhs->moveNW(karte);
			rhs->controlTime(count);
		}
		
		if (moverVar=="ne") {
			rhs->moveNE(karte);
			rhs->controlTime(count);
		}
		
		if (moverVar=="sw") {
			rhs->moveSW(karte);
			rhs->controlTime(count);
		}
		
		if (moverVar=="se") {
			rhs->moveSE(karte);
			rhs->controlTime(count);
		}

		if (moverVar=="stats") {
			r_player->displayStats();
		}
		
		if (moverVar=="pos") {
			rhs->getCurrentPosition(karte);
		}
		
		if (moverVar=="look") {
			rhs->checkTime();
			rhs->look(karte);
		}
		
		if (moverVar=="help") {
			std::cout << "\nYou may move around the map using the following directions:\n"
				<< "n, w, e, s, nw, ne, sw, se."
				<< "\nType 'quit' to exit the game. Further instructions are provided\n"
				<< "In the documentation that came with this game.\n";
		}
		
		if (moverVar=="load")
			r_player->loadPlayerData(karte,r_player->getPlayerID(),1);
		
		
		if (moverVar=="save") {
			int slot;
			std::cout << "\nWhich slot to save to (1-9)? ";
			std::cin >> slot;
			std::cin.ignore();
			
			r_player->savePlayerData(karte,r_player->getPlayerID(),slot);
			karte->saveMapData();
			std::cout << "\nPlayer and map saved!\n";
		}
		
		if (moverVar=="inv") {
			r_player->displayInventory();
		}
		
		if (moverVar=="equip") {
			int x=karte->getCurrentSpaceX();
			int y=karte->getCurrentSpaceY();
			if (karte->itemExists(karte,x,y)) {
				TYPE type=karte->checkItemType(karte);
				char confirm;
				std::string targetItem=karte->identifyItem(karte);
				std::cout << "\nEquip " << targetItem << "? ";
				std::cin >> confirm;
				confirm=toupper(confirm);
				if (confirm=='Y') {
					r_player->addInventoryItem(type,targetItem);
					karte->removeItemX(x); // now remove the item from X
					karte->removeItemY(y); // now remove the item from Y
					std::cout << targetItem << " was equipped.\n";
				}
				if (confirm=='N')
					std::cout << std::endl << targetItem << " was not equipped.\n";
			}
			else
				std::cout << "\nThere is no item here that can be equipped.\n";
		}
		
		if (moverVar=="unequip") {
			std::cout << "\nUnequip which item? ";
			std::string targetItem;
			std::cin.ignore();
			std::getline(std::cin,targetItem,'\n');
			
			bool equiped=false;
			int itemString=r_player->searchInventory(r_player,targetItem);
			if (itemString>=0 && itemString<=3) {
				r_player->removeInventoryItem(itemString);
				std::cout << std::endl << targetItem << " was unequipped.\n";
			}
			if (itemString>3) {
				std::cout << "\nThis item is not equipped!\n";
				equiped=false;
			}
			if (equiped)
				std::cout << "\nYou unequipped the " << targetItem << ".\n";
		}
		
		if (moverVar=="end") {
			turns++; // increment the turns
			r_player->savePlayerData(karte,r_player->getPlayerID(),99); // save the player's data
			break;
		}

		std::string quitVer;
		if (moverVar=="quit") {
			std::cout << "\nAre you sure you want to quit the game? (y,n)  ";
			std::cin >> quitVer;
			if (quitVer=="n")
				continue;
			else {
				r_player->removeTemp(); // remove the temporary directory
				exit(0);
			}
		} // if (moverVar=="quit")
	} // while(1)
		
} // void startGame(movement *rhs,map *karte,player* r_player,int playerCount)

#endif
