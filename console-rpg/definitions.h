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
#include <fstream>
#include <ctype.h> // for toupper()
#include <stdlib.h> // for atoi()
#include <sstream> // for stringstream

// nessesary headers
#include "items.h"
#include "player.h"
#include "playerlist.h"
#include "movement.h"
#include "utilities.h"
using namespace utilities;
   
#ifdef __LINUX__
typedef unsigned long long __int64;
#define CRPG_CLEAR_SCREEN system("clear") // clear screen macro
#endif

#ifdef __WINDOWS__
#define CRPG_CLEAR_SCREEN system("cls") // clear screen macro
#endif

// maximum map sizes
#define PMAX 50
#define NMAX -50

// are we loading a savefile?
bool load=false;

// set the static number of players to 0
int player::playersOn=0;
int npc::npcsOn=0;

// movement strings
std::string N="n",S="s",W="w",E="e",NW="nw",NE="ne",SW="sw",SE="se";

// forward declarations
class item;
class bag;

// first we place all the function prototypes
// into a generic namespace. this hopefully makes
// it more organized ;)
namespace generic {
  int menu();
  int optionMenu();
  int configurePlayers();
  int loadGame();
  void preGame(movement*,map*,playerList<player*>&,int);
  void startGame(movement*,map*,playerList<player*>&,int,int,int&);
}

// namespace for all methods relating to gameplay customization
namespace options {        
  int redefCtrl();
}

// menu function: display menu and options
int generic::menu() {
  char a_menuChoice[5];
  int menuChoice;

  for(;;) {
    std::cout << "\nConsole-RPG Main Menu\n"
    
    // just for the hell of it ;)
    #ifdef DEBUG
    << " - Debug enabled -\n"
    #endif
    
    << "---------------------" << std::endl;
    std::cout << "(1) Start a new game\n"
    << "(2) Continue playing\n"
    << "(3) Options\n"
    << "(4) Quit\n"
    << "---------------------\n> ";
    std::cin >> a_menuChoice;
    menuChoice=atoi(a_menuChoice);
    std::cin.ignore(); // remove the newline

    switch(menuChoice) {
       case 1: generic::configurePlayers();break;
       case 2: generic::loadGame();break;
       case 3: generic::optionMenu();break;
       default: CRPG_CLEAR_SCREEN; return 0;
    }
  } // for(...)
}

// configurePlayers: (formerly mainMenu) configure all players
int generic::configurePlayers() {
    
    CRPG_CLEAR_SCREEN;

    char ch[5];
    int players; // the amount of players
    std::cout << "\nEnter amount of players (max 10): ";
    std::cin >> ch;
    std::cin.ignore(); // remove the newline

    players=atoi(ch);
      
    if (!(players<=10 && players>0)) {
       std::cout << "\nInvalid player amount!\n";
       return 0;
    }

    // make an array of current players
    //player *list[players];
    playerList<player*> list;
    player::setPlayersOn(players);

    // fill up this array
    for (int i=0;i<players;i++) {
        list[i]=new player(5,0,i); // player HP/MP/id
    }

    movement *grid=new movement; // make a new movement grid
    map *karte=new map(PMAX,PMAX,NMAX,NMAX); // make a new map

    grid->spawnMapItems(karte); // spawn items on map NOW

    char cVar; // confirmation variable

    // loop for as long as there are players
    for (int i=0;i<players;i++) {
    std::string name;
    list[i]=new player;
    
    // now we configure each player's character
    CRPG_CLEAR_SCREEN;

    std::cout << "\n==========================";
    std::cout << "\nPlayer " << i+1 << " Configuration\n";
    std::cout << "\nEnter player name: ";
    std::getline(std::cin,name,'\n');
    
    list[i]->setPlayerID(i+1);
    list[i]->setName(name);
    list[i]->setLook();

    // put this temporary object into the array for good
    karte->players.push_back(list[i]);

    std::cin.ignore();
    std::cout << "==========================\n";
  }

  std::cout << "\nStart a new game? (y,n) ";
  std::cin >> cVar;
  cVar=toupper(cVar);

  if (cVar=='Y') {
    generic::preGame(grid,karte,list,players);
  }
  else {
    std::cout << std::endl;   
    CRPG_CLEAR_SCREEN;
    return 0;
  }

  karte->players.clear();
  karte->npcs.clear();
  
  delete grid; // we are done with the grid map; delete it
  delete karte; // we are done with the world map; delete it
  grid=0;
  karte=0;
}

// function to preform certain actions before start of
// new turn or game.
void generic::preGame(movement *rhs,map *karte,playerList<player*> &r_list,int playerCount) {
  int j=0; // counter variable
  int turns=1; // amount of turns

  for (;;) {
    // reset the counter
    if (j==playerCount)
      j=0;
    
    CRPG_CLEAR_SCREEN;      
      
    #ifdef DEBUG
    std::cout << "Current player: " << j << std::endl;
    #endif
    
    std::cout << "\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*";
    std::cout << "\nWelcome to Console RPG, " << r_list[j]->getName() << std::endl
    << "Type 'help' to display a help menu.";
    std::cout << "\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*";

    generic::startGame(rhs,karte,r_list,j,playerCount,turns); // this is where we actually start
    j++;
    turns++;
  }
}

// optionMenu: function for displaying option menu (finish this later)
int generic::optionMenu() {
  CRPG_CLEAR_SCREEN;
  std::cout << "\nOptions\n";
  std::cout << "-------\n";
  std::cout << "(1) Redefine controls\n"
            << "(2) Return to main\n"
            << "-------\n> ";
            
  std::string ch;
  int command;
  std::cin >> ch;
  
  command=atoi(ch.c_str());
  switch (command) {
         case 1: options::redefCtrl(); break;
         default: break;  
  }
  CRPG_CLEAR_SCREEN;
}

// startGame function: this will start the actual game
void generic::startGame(movement *rhs,map *karte,playerList<player*> &list,int playerNow,int playerCount,int &turns) {

  bool firstTurn=true; // first turn flag
  int moves=10; // moves remaining

  std::cout << "\nTURN: " << turns << std::endl;

  while(1) {
    int count=rhs->getStepCount(); // count the amount of spaces moved

    std::cout << "\nAction: ";

    std::string moverVar;
    std::cin >> moverVar;
    
    // if the player's turn has expired
    if (moves==0) {
      std::cout << "\n----------";
      std::cout << "\nYour turn is now over. Press enter to continue...";
      std::cout << "\n----------\n> ";          
      std::cin.ignore();
      std::cin.get();
      
      karte->creaturesDoAction();
      break;
    }
    
    // for quick movement when debugging ;)
    #ifdef DEBUG
    if (moverVar=="t") {
      int x, y, lyr;
      std::cin >> x >> y >> lyr;
      list[playerNow]->x=x;
      list[playerNow]->y=y;
      list[playerNow]->setLayer(lyr);
    }
    #endif

    // move north
    if (moverVar==N) {
      std::cout << "\n----------";    
      rhs->moveN(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "----------\n";      
      
      moves--;
    }

    // move south
    if (moverVar==S) {
      std::cout << "\n----------";    
      rhs->moveS(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "----------\n";      
      
      moves--;
    }

    // move west
    if (moverVar==W) {
      std::cout << "\n----------";    
      rhs->moveW(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "----------\n";      
      
      moves--;
    }

    // move east
    if (moverVar==E) {
      std::cout << "\n----------";    
      rhs->moveE(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "----------\n";
            
      moves--;
    }

    // move northwest
    if (moverVar==NW) {
      std::cout << "\n----------";    
      rhs->moveNW(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "\n----------\n";      
      
      moves--;
    }

    // move northeast
    if (moverVar==NE) {
      std::cout << "\n----------";    
      rhs->moveNE(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "\n----------\n";      
      
      moves--;
    }

    // move southwest
    if (moverVar==SW) {
      std::cout << "\n----------";    
      rhs->moveSW(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "\n----------\n";      
      
      moves--;
    }

    // move southeast
    if (moverVar==SE) {
      std::cout << "\n----------";    
      rhs->moveSE(list[playerNow],karte);
      rhs->controlTime(count);
      std::cout << "\n----------\n";      
      
      moves--;
    }
    
    // display backpack contents
    if (moverVar=="bp") {
      std::cout << "\n----------";
      std::cout << "\nYour backpack contains:\n";
      list[playerNow]->bp->displayContents();
      std::cout << "----------\n";
    }
    
    // add an item to player's backpack
    if (moverVar=="add") {
      std::cout << "\n----------";
      if (karte->itemExists(list[playerNow]->x, list[playerNow]->y, list[playerNow]->getLayer())) {
      	item *Item=karte->getItem(list[playerNow]->x, list[playerNow]->y, list[playerNow]->getLayer());
	
	std::string s;
	if (Item) {
		std::cout << "\nPut " << Item->getName() << " into your backpack? ";
		std::cin >> s;
		
		if (s[0]=='y' || s[0]=='Y') {
			if (list[playerNow]->bp->addItem(new item(Item->getItemID(), list[playerNow]->getLayer()))) {
				std::cout << "\nItem added.";
				rhs->removeItem(karte, list[playerNow]->x, list[playerNow]->y, list[playerNow]->getLayer());
			}
			
			else
				std::cout << "\nYour backpack is full!";
		}
	} // if (Item)
      } // if (itemExists(...))
      
      std::cout << "\n----------\n";
    }
    
    // remove an item from player's backpack
    if (moverVar=="remove") {
      std::cout << "\n----------";
      std::cout << "\nBackpack contents:\n";
      list[playerNow]->bp->displayContents();
      std::cout << "\nRemove which item (position)? ";
      
      std::string s;
      std::cin >> s;
      int pos=atoi(s.c_str());
      
      item *Item=list[playerNow]->bp->removeItem(pos, true);
      
      // check if this item was dropped correctly
      if (Item) {
        Item->x=list[playerNow]->x;
        Item->y=list[playerNow]->y;

        rhs->placeItem(Item, karte);
      	std::cout << "\nItem dropped.";
      }
      
      // not dropped, so its still in the player's backpack
      else
         std::cout << "\nItem cannot be removed!";

      std::cout << "\n----------\n";
    }

    // display stats
    if (moverVar=="stats") {
      std::cout << "\n----------";
      list[playerNow]->displayStats();
      std::cout << "\n----------\n";
    }

    // display position
    if (moverVar=="pos") {
      std::cout << "\n----------\n";    
      std::cout << "Position: X: " << list[playerNow]->x << " / Y: " << list[playerNow]->y;
      std::cout << "\n----------\n";     
    }

    // look on the ground
    if (moverVar=="look") {
      std::cout << "\n----------";
      rhs->checkTime();
      rhs->look(list[playerNow],karte);
      std::cout << "----------\n";
    }
    
    // talk to an npc or creature on this space
    if (moverVar=="talk") {
      std::cout << "\n----------\n";
      list[playerNow]->sendNpcMsg(karte,rhs);
      std::cout << "\n----------\n";
    }

    // show quick help screen
    if (moverVar=="help") {
      std::cout << "\n----------";    
      std::cout << "\nYou may move around the map using the following directions:\n"
      << "n, w, e, s, nw, ne, sw, se."
      << "\nType 'quit' to exit the game. Further instructions are provided\n"
      << "in the documentation that came with this game.\n"
      << "\nConsole-RPG is licensed under the GNU GPL. Coded by KanadaKid.";
      std::cout << "\n----------";      
    }

    // save the game
    if (moverVar=="save") {
      int slot;
      std::cout << "\n----------";
            
      std::cout << "\nSave to which slot (1-9)? ";
      std::cin >> slot;
      std::cin.ignore();
      
      if (rhs->saveGame(slot, playerCount, karte, list))
      	std::cout << "\nYour game was saved.\n";
      
      else
        std::cout << "\nSlot " << slot << " is already full. Please select another.\n";
      
      std::cout << "\n----------";      
    }

    // display the player's inventory
    if (moverVar=="inv") {
      std::cout << "\n----------";    
      list[playerNow]->displayInventory();
      std::cout << "----------\n";      
    }

    // equip an item on this space
    if (moverVar=="equip") {
      int x=list[playerNow]->x;
      int y=list[playerNow]->y;
      int ly=list[playerNow]->getLayer();
      std::cout << "\n----------";      

      if (karte->itemExists(x, y, ly)) {
        TYPE type=karte->checkItemType(x, y, ly);
        char confirm;
        item *targetItem=karte->getItem(x, y, ly);

	// if the target item is NULL, then disable equipping since
	// it will mostly likely cause a segfault
        if (targetItem!=NULL) {
          std::cout << "\nEquip " << targetItem->getName() << "? ";
          std::cin >> confirm;
          confirm=toupper(confirm);
	  
          if (confirm=='Y') {
            list[playerNow]->addInventoryItem(type,targetItem);
            std::cout << std::endl << targetItem->getName() << " was equipped.\n";

	    karte->removeItem(x, y, ly);
          }
	  
          if (confirm=='N')
            std::cout << std::endl << targetItem->getName() << " was not equipped.\n";
        }
	
	// the item was indeed NULL
        else
          std::cout << "\nThere is no item here that can be equipped.\n";
      }
      
      else
        std::cout << "\nThere is no item here that can be equipped.\n";
	
      std::cout << "----------\n";
    }

    // unequip an item
    if (moverVar=="unequip") {
      std::cout << "\n----------";
          
      std::cout << "\nUnequip which item? ";
      std::string targetItem;
      std::cin.ignore();
      std::getline(std::cin,targetItem,'\n');

      bool equiped=false;
      int itemString=list[playerNow]->searchInventory(targetItem);

      if (itemString>=0 && itemString<=3) {
	item *Item=list[playerNow]->getInventoryItem(itemString);
	if (Item) {
		Item=new item(Item->getItemID(), list[playerNow]->x, list[playerNow]->y, list[playerNow]->getLayer());
		rhs->placeItem(Item, karte);
	}
	
	list[playerNow]->removeInventoryItem(itemString);
	
        std::cout << std::endl << targetItem << " was unequipped.\n";
      }

      if (itemString>3) {
        std::cout << "\nThis item is not equipped!\n";
        equiped=false;
      }

      if (equiped)
        std::cout << "\nYou unequipped the " << targetItem << ".\n";
	
      std::cout << "----------\n";
    }

    // manually end a turn
    if (moverVar=="end") {
      karte->creaturesDoAction(); // move any npcs/monsters
      
      std::cout << "\n----------";
      std::cout << "\nYou ended your turn. Press enter to continue...";
      std::cout << "\n----------\n";
      
      std::cin.ignore();
      std::cin.get();

      break;
    }

    // quit the game
    std::string quitVer;
    if (moverVar=="quit") {
      std::cout << "\n----------";    
      std::cout << "\nAre you sure you want to quit the game? (y,n)  ";
      std::cout << "\n----------\n> ";
      
      std::cin >> quitVer;
      if (quitVer[0]=='n' || quitVer[0]=='N')
        continue;

      else {
        CRPG_CLEAR_SCREEN;
        exit(0);
      }
    } // if (moverVar=="quit")

  } // for (int i=0;i<MAXTURNS;i++)

} // void startGame(...)

// method to load a previously saved game
int generic::loadGame() {
   // ask the user which slot to load from
   int slot;
   std::cout << "\nLoad from which slot (1-9)? ";
   std::cin >> slot; std::cin.ignore();
   
   // allocate memory for the core components of the game.
   playerList<player*> list; // list of players
   movement *grid=new movement; // movement grid
   map *karte=new map(PMAX,PMAX,NMAX,NMAX); // world map
   
   // now we try to load up the saved file
   if (grid->loadGame(slot, karte, list)) {
	int players=karte->players.size();
	load=true;
	generic::preGame(grid, karte, list, players);
   }
   
   else {
	delete grid;
	delete karte;
	grid=0;
	karte=0;
	
	std::cout << "Unable to load file! Press enter to return to the main menu.";
	std::cin.ignore(); std::cin.get();
   }
   
}

/***************************************
 * Start options namespace definitions *
 **************************************/
 
int options::redefCtrl() {
    CRPG_CLEAR_SCREEN;
    std::cout << "\n-----------------";
    std::cout << "\nRedefine Controls\n";
    std::cout << "-----------------\n\n";
    std::string ch;
    
    std::cout << "Move north: ";
    std::cin >> ch; N=ch; 
       
    std::cout << "\nMove south: ";
    std::cin >> ch; 
    if (ch!=N)
       S=ch;
    else
       S="s";
    
    std::cout << "\nMove east: ";
    std::cin >> ch; 
    if (ch!=N && ch!=S)
       E=ch;
    else
       E="e";  
    
    std::cout << "\nMove west: ";
    std::cin >> ch; 
    if (ch!=N && ch!=S && ch!=E)
       W=ch;
    else
       W="w";
    
    std::cout << "\nMove northwest: ";
    std::cin >> ch; 
    if (ch!=N && ch!=S && ch!=W && ch!=E)
       NW=ch;
    else
       NW="nw";
    
    std::cout << "\nMove northest: ";
    std::cin >> ch; 
    if (ch!=N && ch!=S && ch!=W && ch!=E && ch!=NW)
       NE=ch;
    else
       NE="ne";
    
    std::cout << "\nMove southwest: ";
    std::cin >> ch; 
    if (ch!=N && ch!=S && ch!=W && ch!=E && ch!=NW && ch!=NE)
       SW=ch;
    else
       SW="sw";   
    
    std::cout << "\nMove southest: ";
    std::cin >> ch;
    if (ch!=N && ch!=S && ch!=W && ch!=E && ch!=NW && ch!=NE && ch!=SW)
       SE=ch;
    else
       SE="se"; 
    
    std::cout << "\n\nControls redefined! Press enter to return.\n";
    std::cin.get();
    std::cin.ignore();
    return 0;
}

#endif
