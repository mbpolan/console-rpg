// definitions.h: holds function declarations and definitions
#include <iostream>
#include <fstream>

void startGame(movement*,map*,player*);
int mainMenu(player*);
int savePlayerData(player*);
void optionMenu();

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
	std::string cVar;
	std::cout << "\nEnter player name: ";
	std::string name;
	std::cin >> name;
	r_player2->setName(name);
	std::cout << "\nCustomize your character? (n,y)";
	std::cin >> cVar;
	if (cVar=="y")
		r_player2->setLook(r_player2);
	else;
	std::cout << "\nStart a new game? (n,y) ";
	std::string connect;
	std::cin >> connect;
	if (connect=="y") {
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
	while(1) {
		item *torch=new item("torch",1,1);
		rhs->placeItem(torch,karte);
		std::cout << "\nMove: ";
		
		std::string moverVar;
		std::cin >> moverVar;
		
		if (moverVar=="n") {
			rhs->moveN(karte);
		}
		
		if (moverVar=="s") {
			rhs->moveS(karte);
		}
		
		if (moverVar=="w") {
			rhs->moveW(karte);
		}
		
		if (moverVar=="e") {
			rhs->moveE(karte);
		}
		
		if (moverVar=="nw") {
			rhs->moveNW(karte);
		}
		
		if (moverVar=="ne") {
			rhs->moveNE(karte);
		}
		
		if (moverVar=="sw") {
			rhs->moveSW(karte);
		}
		
		if (moverVar=="se") {
			rhs->moveSE(karte);
		}
		
		if (moverVar=="position") {
			rhs->getCurrentPosition(karte);
		}
		
		if (moverVar=="look") {
			rhs->look(karte);
		}
		
		if (moverVar=="help") {
			std::cout << "\nYou may move around the map using the following directions:\n"
				<< "n, w, e, s, nw, ne, sw, se."
				<< "\nType 'quit' to exit the game or 'look' to check out\n"
				<< "what is on the ground.";
		}
		
		if (moverVar=="save") {
			savePlayerData(r_player);
		}
		
		if (moverVar=="inventory") {
			r_player->displayInventory(r_player);
		}
		
		/* *******************************
		 * Fix addInventoryItem() method *
		 * Remove for now to avoid bugs  *
		 *********************************
		if (moverVar=="equip" {
			r_player->addInventoryItem();
		}; */
		
		/* **********************************
		 * Add removeInventoryItem() method *
		 * after the add~ method is done    *
		 ************************************
		if (moverVar=="remove") {
			std::cout << "\nRemove which item? ";
			std::string targetItem;
			std::cin >> targetItem;
			int itemString=r_player->searchInventory(r_player,targetItem);
			if (itemString<=3)
				r_player->removeInventoryItem(itemString);
			if (itemString>3) {
				std::cout << "This item is not equiped!";
				#define _noEq
			}
			#ifndef _noEq
			std::cout << "\nYou removed the " << targetItem << ".";
			#endif
			#undef _noEq
		} */

		std::string quitVer;
		if (moverVar=="quit") {
			std::cout << "\nAre you sure you want to quit? (n,y)  ";
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
int savePlayerData(player *r_player) {

	std::string playerName(r_player->getName());
	std::string playerHair(r_player->getHair());
	std::string playerTorso(r_player->getTorso());
	std::string playerLegs(r_player->getLegs());
	int playerAge=r_player->getAge();
	int playerHeight=r_player->getHeight();
	
	// End of customization part. Start physical part //
	
	int playerCurrentHP=r_player->getHP();
	int playerCurrentMP=r_player->getMP();
	
	std::ofstream fout;
	fout.open("savefile.dat");
	fout << "[Player]\n";
	// add to stream fout...
	fout << "name = " << playerName << std::endl;
	fout << "hair = " << playerHair << std::endl
	     << "torso = " << playerTorso << std::endl
	     << "legs = " << playerLegs << std::endl
	     << "age = " << playerAge << std::endl
	     << "height = " << playerHeight << std::endl << std::endl;
	     
	fout << "hp = " << playerCurrentHP << std::endl
	     << "mp = " << playerCurrentMP << std::endl
	     << "[/Player]" << std::endl;
	fout.close();
}
