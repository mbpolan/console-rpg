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

#include "player.h"
#include "playerlist.h"
#include "movement.h"

// set the static number of players to 0
int player::playersOn=0;

// first we place all the function prototypes
// into a generic namespace. this hopefully makes
// it more organized ;)
namespace generic {
  int menu();
  int configurePlayers(playerList<player*>&,int);
  void preGame(movement*,map*,playerList<player*>&,int);
  void startGame(movement*,map*,playerList<player*>&,int,int,int&);
  void optionMenu();
}
// menu function: display menu and options
int generic::menu() {
  // takes a reference to player
  char a_menuChoice[5];
  int menuChoice;

  for(;;) {
    std::cout << "\nMain Menu\n"
    << "---------" << std::endl;
    std::cout << "(1) Start a new game.\n"
    << "(2) Continue playing\n"
    << "(3) Options\n"
    << "(4) Quit\n"
    << "---------\n> ";
    std::cin >> a_menuChoice;
    menuChoice=atoi(a_menuChoice);
    std::cin.ignore(); // remove the newline

    // the user wants to start a new game
    if (menuChoice==1) {

      int players; // the amount of players
      std::cout << "\nHow many players in this game? ";
      std::cin >> players;
      std::cin.ignore(); // remove the newline

      // make an array of current players
      //player *list[players];
      playerList<player*> list;
      list[0]->setPlayersOn(players);

      // fill up this array
      for (int i=0;i<players;i++) {
        list[i]=new player(5,0,i); // player HP/MP/id
      }

      generic::configurePlayers(list,players); // pass in the character list

      return 0;
    }

    if (menuChoice==2) {

      // ask the user which slot to load from
      int slot;
      std::cout << "\nLoad from which slot (1-9)? ";
      std::cin >> slot; std::cin.ignore();

      // our stream object
      std::ifstream fin;

      // now we declare some paths based on the client's
      // operating system.
#ifdef __LINUX__
      char index[256];
      sprintf(index,"data/game%d/index.dat",slot); // path to index file
#endif

#ifdef __WINDOWS__
      char index[256];
      sprintf(index,"data\\game%d\\index.dat",slot); // path to index file
#endif

      // now we attempt to open the index file
      player *pPlayer=new player;
      int players;
      players=(pPlayer->loadFromIndex(slot));
      delete pPlayer;

      // allocate memory for the core compenents of the game.
      playerList<player*> list; // list of players
      movement *grid=new movement; // movement grid
      map *karte=new map(30,30,-30,-30); // world map

      // start the loop to fill up array with saved player data
      char path[256];
      for (int i=0;i<players;i++) {
        list[i]=new player;
        player *pPlayer=new player;

        sprintf(path,"data/game%d/savefile%d.dat",slot,i+1);

        fin.open(path);

        if (!fin) {
          std::cout << "\nGame: " << slot;
          std::cout << "\nSavefile " << i << " is either corrupt or not present. Aborting...\n";
          return 0;
        }

        pPlayer->loadPlayerData(karte,i+1,slot);
        pPlayer->loadFromIndex(slot);
        list[i]=pPlayer;

        fin.close();
      }

      generic::preGame(grid,karte,list,players);
    }


    if( menuChoice==3)
      generic::optionMenu(); // display options (todo)

    else
      return 0;
  }
}

// configurePlayers: (formerly mainMenu) configure all players
int generic::configurePlayers(playerList<player*> &r_list,int playerCount) {
  // takes an array of players and count

  movement *grid=new movement; // make a new movement grid
  map *karte=new map(30,30,-30,-30); // make a new map

  grid->spawnMapItems(grid,karte); // spawn items on map NOW

  char cVar; // confirmation variable
  
  // we need to set name and look
  // make a temporary player object
  player *pPlayer=new player;

  // loop for as long as there are players
  for (int i=0;i<playerCount;i++) {
    // now we configure each player's character
    std::cout << "\n==========================";
    std::cout << "\nPlayer " << i+1 << " Configuration\n";
    std::cout << "\nEnter player name: ";
    std::string name;
    std::getline(std::cin,name,'\n');

    pPlayer->setPlayerID(i+1);
    pPlayer->setName(name);
    pPlayer->setLook();

    // put this temporary object into the array for good
    r_list[i]=pPlayer;

    std::cin.ignore();
    std::cout << "==========================\n";
  }
  
  // delete allocated memory for temporary player
  delete pPlayer;

  std::cout << "\nStart a new game? (y,n) ";
  std::cin >> cVar;
  cVar=toupper(cVar);

  if (cVar=='Y') {
    generic::preGame(grid,karte,r_list,playerCount);
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

// function to preform certain actions before start of
// new turn or game.
void generic::preGame(movement *rhs,map *karte,playerList<player*> &r_list,int playerCount) {
  int j=0; // counter variable
  int turns=1; // amount of turns

  for (;;) {
    // reset the counter
    if (j==playerCount)
      j=0;

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
void generic::optionMenu() {
  std::cout << "\nNo options avaliable at this time.\n";
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

  // reset the coordinates for the next player as long as it's
  // still his first turn.
  if (firstTurn) {
    karte->setCurrentSpaceX(0);
    karte->setCurrentSpaceY(0);
  }

  // if it is NOT the first turn
  // 99 is the temporary directory number for saved files
  if (!firstTurn)
    list[playerNow]->loadPlayerData(karte,list[playerNow]->getPlayerID(),99);

  while(moves>0) {
    int count=rhs->getStepCount(); // count the amount of spaces moved

    std::cout << "\nMove: ";

    std::string moverVar;
    std::cin >> moverVar;

    // for debugging purposes only!
#ifdef DEBUG
    if (moverVar=="mod") {
      list[playerNow]->setHP(0);
    }
#endif

    // if this is the final move, then make sure to save the player's
    // stats before passing in the next player
    if (moves==1) {
      moverVar="end";
    }

    if (moverVar=="n") {
      rhs->moveN(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="s") {
      rhs->moveS(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="w") {
      rhs->moveW(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="e") {
      rhs->moveE(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="nw") {
      rhs->moveNW(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="ne") {
      rhs->moveNE(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="sw") {
      rhs->moveSW(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="se") {
      rhs->moveSE(karte);
      rhs->controlTime(count);
      moves--;
    }

    if (moverVar=="stats") {
      list[playerNow]->displayStats();
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
      << "in the documentation that came with this game.\n";
    }

    if (moverVar=="save") {
      int slot;
      std::cout << "\nSave to which slot (1-9)? ";
      std::cin >> slot;
      std::cin.ignore();

      // since the slot doesn't yet exist, we pass in 'false' as the
      // parameter to make the slot directory. loop until every players'
      // stats are saved in the slot.
      for (int i=0;i<playerCount;i++) {
        list[i]->savePlayerData(karte,list[i]->getPlayerID(),slot,false);
      }
      karte->saveMapData(slot);
      std::cout << "\nPlayer and map saved!\n";
    }

    if (moverVar=="inv") {
      list[playerNow]->displayInventory();
    }

    if (moverVar=="equip") {
      int x=karte->getCurrentSpaceX();
      int y=karte->getCurrentSpaceY();

      if (karte->itemExists(karte,x,y)) {
        TYPE type=karte->checkItemType(karte);
        char confirm;
        item *targetItem=karte->identifyItem(karte);

	// if the target item is NULL, then disable equipping since
	// it will mostly likely cause a segfault
        if (targetItem!=NULL) {
          std::cout << "\nEquip " << targetItem->getName() << "? ";
          std::cin >> confirm;
          confirm=toupper(confirm);
	  
          if (confirm=='Y') {
            list[playerNow]->addInventoryItem(type,targetItem);
            rhs->removeItem(karte);
            //std::cout << targetItem->getName(); << " was equipped.\n";
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

      list[playerNow]->savePlayerData(karte,list[playerNow]->getPlayerID(),99,ignore); // save the player's data
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
        exit(0);
      }
    } // if (moverVar=="quit")

  } // for (int i=0;i<MAXTURNS;i++)

} // void startGame(movement *rhs,map *karte,player* r_player,int playerCount)


#endif
