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

#include "player.h"
#include "playerlist.h"
#include "movement.h"
   
#ifdef __LINUX__
typedef unsigned long long __int64;
#define CRPG_CLEAR_SCREEN system("clear") // clear screen macro
#endif

#ifdef __WINDOWS__
#define CRPG_CLEAR_SCREEN system("cls") // clear screen macro
#endif

// maximum map sizes
#define PMAX 30
#define NMAX -30

// are we loading a savefile?
bool load=false;

// set the static number of players to 0
int player::playersOn=0;
int npc::npcsOn=0;

// movement strings
std::string N="n",S="s",W="w",E="e",NW="nw",NE="ne",SW="sw",SE="se";

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
      
    #ifdef DEBUG
    std::cout << "current player: " << j << std::endl;
    #endif

 //   CRPG_CLEAR_SCREEN;
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
  std::cout << "-------\n\n";
  std::cout << "(1) Redefine controls\n"
            << "(2) Return to main\n"
            << "-------\n\n> ";
            
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

  // if amount of turns is greater than the amount of players,
  // then flag firstTurn to false so we can load the player's
  // stats before he starts.
  if (turns>playerCount)
    firstTurn=false;

  // if it is NOT the first turn, we load the player's file
  // 99 is the temporary directory number for saved files
  //if (!firstTurn)
  //  list[playerNow]->loadPlayerData(list[playerNow]->getPlayerID(),99);

  while(moves>0) {
    int count=rhs->getStepCount(); // count the amount of spaces moved

    std::cout << "\nAction: ";

    std::string moverVar;
    std::cin >> moverVar;

    // if this is the final move, then make sure to save the player's
    // stats before passing in the next player
    if (moves==1) {
      moverVar="end";
    }

    if (moverVar==N) {
      rhs->moveN(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar==S) {
      rhs->moveS(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar==W) {
      rhs->moveW(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar==E) {
      rhs->moveE(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar==NW) {
      rhs->moveNW(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar==NE) {
      rhs->moveNE(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar==SW) {
      rhs->moveSW(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar==SE) {
      rhs->moveSE(list[playerNow],karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="stats") {
      list[playerNow]->displayStats();
    }

    if (moverVar=="pos") {
      rhs->getCurrentPosition(list[playerNow]);
    }

    if (moverVar=="look") {
      rhs->checkTime();
      rhs->look(list[playerNow],karte);
    }

    if (moverVar=="help") {
      std::cout << "\nYou may move around the map using the following directions:\n"
      << "n, w, e, s, nw, ne, sw, se."
      << "\nType 'quit' to exit the game. Further instructions are provided\n"
      << "in the documentation that came with this game.\n"
      << "\nConsole-RPG is licensed under the GNU GPL. Coded by KanadaKid.";
    }

    if (moverVar=="save") {
      int slot;
      std::cout << "\nSave to which slot (1-9)? ";
      std::cin >> slot;
      std::cin.ignore();
      
      std::stringstream ss;
      
      #ifdef __LINUX__
      ss << "data/game" << slot << "/";
      #endif
      
      #ifdef __WINDOWS__
      ss << "data\\game" << slot << "\\";
      #endif
      
      bool exists=false;
      std::ifstream fin;
      fin.open(ss.str().c_str());
      
      if (fin) {
        std::cout << "\nSlot " << slot << " is already full. Please select another.\n";
        break;
      }
      
      // only if the slot is not occupied
      if (!fin) {
        for (int i=0;i<playerCount;i++) {
          // to avoid the "directory already exists" error  
          if (i>0)
             exists=true;
             
          list[i]->savePlayerData(list[i]->getPlayerID(),slot,exists);
        }
	
        karte->saveMapData(slot);
        std::cout << "\nPlayer and map saved!\n";
      }
      
      else
        std::cout << "\nSlot " << slot << " is already full. Please select another.\n";
      
      fin.close();
    }

    if (moverVar=="inv") {
      list[playerNow]->displayInventory();
    }

    if (moverVar=="equip") {
      int x=list[playerNow]->x;
      int y=list[playerNow]->y;

      if (karte->itemExists(x,y)) {
        TYPE type=karte->checkItemType(x,y);
        char confirm;
        item *targetItem=karte->getItem(x,y);

	// if the target item is NULL, then disable equipping since
	// it will mostly likely cause a segfault
        if (targetItem!=NULL) {
          std::cout << "\nEquip " << targetItem->getName() << "? ";
          std::cin >> confirm;
          confirm=toupper(confirm);
	  
          if (confirm=='Y') {
            list[playerNow]->addInventoryItem(type,targetItem);
            std::cout << std::endl << targetItem->getName() << " was equipped.\n";

	    karte->removeItem(x,y);
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
    }

    if (moverVar=="unequip") {
      std::cout << "\nUnequip which item? ";
      std::string targetItem;
      std::cin.ignore();
      std::getline(std::cin,targetItem,'\n');

      bool equiped=false;
      int itemString=list[playerNow]->searchInventory(targetItem);

      if (itemString>=0 && itemString<=3) {
        list[playerNow]->removeInventoryItem(itemString);
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
      bool ignore=false; // should we ignore making a temp directory?

      // after the first player ends his turn, then the temp directory is made.
      // since it's already there, we ignore remaking it based upon the player's
      // id. any id's above 1 are NOT the first players.
      if (list[playerNow]->getPlayerID()>1)
        ignore=true;

      list[playerNow]->savePlayerData(list[playerNow]->getPlayerID(),99,ignore); // save the player's data
      karte->creaturesDoAction(); // move any npcs/monsters

      break;
    }

    std::string quitVer;
    if (moverVar=="quit") {
      std::cout << "\nAre you sure you want to quit the game? (y,n)  ";
      std::cin >> quitVer;
      if (quitVer=="n")
        continue;

      else {
        list[playerNow]->removeTemp(); // remove the temporary directory
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

   // our stream object
   std::ifstream fin;

   // now we declare some paths based on the client's
   // operating system.
   #ifdef __LINUX__
   std::stringstream index;
   char path[256];
   index << "data/game" << slot << "/index.dat"; // path to index file
   #endif

   #ifdef __WINDOWS__
   char path[256];
   std::stringstream index;
   index << "data\\game" << slot << "\\index.dat"; // path to index file
   #endif

   // now we attempt to open the index file
   int players;
   player::loadFromIndex(slot,players);

   // allocate memory for the core compenents of the game.
   playerList<player*> list; // list of players
   movement *grid=new movement; // movement grid
   map *karte=new map(PMAX,PMAX,NMAX,NMAX); // world map
   
//   grid->spawnMapItems(karte);

   int success=karte->loadMapData(slot);
   if (success==0)
   	return 0;

   // start the loop to fill up array with saved player data
   for (int i=0;i<players;i++) {
       list[i]=new player;

	   #ifdef __LINUX__
	   sprintf(path,"data/game%d/savefile%d.xml",slot,i+1);
	   #endif

	   #ifdef __WINDOWS__
	   sprintf(path,"data\\game%d\\savefile%d.xml",slot,i+1);	
	   #endif

       fin.open(path);

           #ifdef DEBUG
	   std::cout << "\nLoading from " << path << "...\n";
	   #endif

       if (!fin) {
          std::cout << "\nGame: " << slot;
          std::cout << "\nSavefile " << i << " is either corrupt or not present. Aborting...\n";
          return 0;
       }

       if (list[i]->loadPlayerData(i+1,slot))
          karte->players.push_back(list[i]);
	  
       else {
          std::cout << "\nUnable to load player data!\n";
	  return 0;
       }
       
       fin.close();
   }
   
   load=true;
   generic::preGame(grid,karte,list,players);
   
   // free up the memory allocated for these objects
   delete grid; 
   delete karte;
   
   grid=0;
   karte=0;
}

/***************************************
 * Start options namespace definitions *
 **************************************/
 
int options::redefCtrl() {
    CRPG_CLEAR_SCREEN;
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
