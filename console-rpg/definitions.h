// definitions.h: holds function declarations and definitions
#include <iostream>
#include <fstream>
#include <ctype.h> // for toupper()

#include "player.h"
#include "movement.h"

// our prototypes
// move these into classes later
int mainMenu(player*);
int savePlayerData(player*,map*);
int loadPlayerData(player*,map*);
void startGame(movement*,map*,player*);
void optionMenu();
void spawnMapItems(movement*,map*);

// menu function: display menu and options
int menu(player *r_player) { // takes a reference to player
	std::string menuChoice;
	for(;;) {
		std::cout << "\nMain Menu\n"
		     << "---------" << std::endl;
		std::cout << "(1) Start a new game.\n"
		     << "(2) Options\n"
		     << "(3) Quit\n"
		     << "---------\n> ";
		std::cin >> menuChoice;
		
		if (menuChoice=="1") {
			mainMenu(r_player); // pass in the character
			return 0;
		}
		
		if( menuChoice=="2")
			optionMenu();
		
		else
			return 0;
	}
}

// mainMenu: function for displaying the main menu
int mainMenu(player *r_player2) { // takes a reference to player
	movement *grid=new movement;
	map *karte=new map(30,30,-30,-30);
	char cVar;
	
	std::cout << "\nEnter player name: ";
	std::string name;
	std::cin >> name;
	
	r_player2->setName(name);
	std::cout << "\nCustomize your character? (y,n) ";
	std::cin >> cVar;
	cVar=toupper(cVar);
	if (cVar=='Y')
		r_player2->setLook(r_player2);
	else;
	std::cout << "\nStart a new game? (y,n) ";
	char connect;
	std::cin >> connect;
	connect=toupper(connect);
	if (connect=='Y') {
		std::cout << "\nWelcome to Console RPG, " << r_player2->getName() << std::endl
		     << "Type 'help' to display a help menu.";
		startGame(grid,karte,r_player2); // this is where we actually start
		delete grid; // we are done with the grid map; delete it
		delete karte; // we are done with the world map; delete it
		grid=0;
	}
	else {
		std::cout << "\nQuitting...";
		return 0;
	}
}

// optionMenu: function for displaying option menu (finish this later)
void optionMenu() {
	std::cout << "\nNo options avaliable at this time.\n";
}

// startGame function: this will start the actual game
void startGame(movement *rhs,map *karte,player *r_player) {
	for(;;) {
		
		int count=rhs->getStepCount(); // count the amount of spaces moved
		rhs->spawnMapItems(rhs,karte); // spawn items on map NOW
	
		std::cout << "\nMove: ";
		
		std::string moverVar;
		std::cin >> moverVar;
		
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
			r_player->displayStats(r_player);
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
		
		if (moverVar=="save") {
			savePlayerData(r_player,karte);
		}

		if (moverVar=="load") {
			loadPlayerData(r_player,karte);
			std::cout << "\nLoading NOW!\n";
		}
		
		/* ********************************************** *
		 * Displaying the inventory results in a loop bug *
		 * Fix it before making equipment spawnable!      *
		 * ********************************************** *
		if (moverVar=="inv") {
			r_player->displayInventory(r_player);
		}
		* ******************** *
		* End bug segment code *
		* ******************** */
		
		if (moverVar=="equip") {
			if (karte->itemExists(karte,karte->getCurrentSpaceX(),karte->getCurrentSpaceY())) {
				TYPE type=karte->checkItemType(karte);
				char confirm;
				std::string targetItem=karte->identifyItem(karte);
				std::cout << "\nEquip " << targetItem << "? ";
				std::cin >> confirm;
				confirm=toupper(confirm);
				if (confirm=='Y') {
					r_player->addInventoryItem(type,targetItem);
					karte->removeItemX(karte->getCurrentSpaceX()); // now remove the item from X
					karte->removeItemY(karte->getCurrentSpaceY()); // now remove the item from Y
					std::cout << targetItem << " was equiped.\n";
				}
				if (confirm=='N')
					std::cout << std::endl << targetItem << " was not equiped.\n";
			}
			else
				std::cout << "\nThere is no item here that can be equipped.\n";
		}
		
		if (moverVar=="unequip") {
			std::cout << "\nRemove which item? ";
			std::string targetItem;
			std::cin >> targetItem;
			
			bool equiped=false;
			int itemString=r_player->searchInventory(r_player,targetItem);
			if (itemString>=0 && itemString<=3) {
				r_player->removeInventoryItem(itemString);
				std::cout << std::endl << itemString << " was unequiped.\n";
			}
			if (itemString>3) {
				std::cout << "\nThis item is not equiped!\n";
				equiped=false;
			}
			if (equiped)
				std::cout << "\nYou removed the " << targetItem << ".\n";
		}

		std::string quitVer;
		if (moverVar=="quit") {
			std::cout << "\nAre you sure you want to quit? (y,n)  ";
			std::cin >> quitVer;
			if (quitVer=="n")
				continue;
			else
				break;
		}
	}
		
}

// savePlayerData: saves the current player status to file
// (Todo: encrypt the save file so the user can't edit it)
int savePlayerData(player *r_player, map *karte) {

	std::string playerName(r_player->getName());
	
	// do these later //
//	std::string playerHair(r_player->getHair());
//	std::string playerTorso(r_player->getTorso());
//	std::string playerLegs(r_player->getLegs());
//	int playerAge=r_player->getAge();
//	int playerHeight=r_player->getHeight();
	
	// End of customization part. Start physical part //
	
	int playerCurrentHP=r_player->getHP();
	int playerCurrentMP=r_player->getMP();
	int luck=r_player->getLuck();
	int strength=r_player->getStrength();
	int power=r_player->getPower();
	int defense=r_player->getDefense();

	// get the player's coordinates
	int x=karte->getCurrentSpaceX();
	int y=karte->getCurrentSpaceY();
	
	std::ofstream fout;
	
	// open our savefile and load the stats in
	// follow each stat by a new line for loading
	fout.open("data/savefile.dat");
	
	if (!fout) {
		std::cout << "\nUnable to save file!";
		return 0;
	}
	
	fout << playerName << std::endl;
	fout << x << std::endl;
	fout << y << std::endl;
	fout << playerCurrentHP << std::endl;
	fout << playerCurrentMP << std::endl;
	fout << luck << std::endl;
	fout << strength << std::endl;
	fout << power << std::endl;
	fout << defense << std::endl;
	fout.close();
}

// loadPlayerData: load the savefile and continue the game
int loadPlayerData(player *r_player, map *karte) {
	std::fstream fin;
	std::string name;
	int hp,mp,luck,strength,power,defense;
	int x,y;
	
	fin.open("data/savefile.dat");

	if (!fin) {
		std::cout << "\nFailed to load savefile!";
		return 0;
	}
	
	
	fin >> name;
	r_player->setName(name);
	fin.clear();

	fin >> x;
	karte->setCurrentSpaceX(x);
	fin.clear();

	fin >> y;
	karte->setCurrentSpaceY(y);
	fin.clear();
	
	fin >> hp;
	r_player->setHP(hp);
	fin.clear();
	
	fin >> mp;
	r_player->setMP(mp);
	fin.clear();

	fin >> luck; r_player->setLuck(luck);
	fin.clear();

	fin >> strength; r_player->setStrength(strength);
	fin.clear();

	fin >> power; r_player->setPower(power);
	fin.clear();

	fin >> defense; r_player->setDefense(defense);
	fin.clear(); fin.close();
}

