// definitions.h: holds function declarations and definitions
#include <iostream>

void startGame(movement*);
int mainMenu(player&);
void optionMenu();

// menu function: display menu and options
int menu(player &r_player) { // takes a reference to player
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
int mainMenu(player &r_player2) { // takes a reference to player
	movement *grid=new movement;
	std::string cVar;
	std::cout << "\nEnter player name: ";
	std::string name;
	std::cin >> name;
	r_player2.setName(name);
	std::cout << "\nCustomize your character? ";
	std::cin >> cVar;
	if (cVar=="y")
		r_player2.setLook(r_player2);
	else;
	std::cout << "\nStart a new game? (n,y) ";
	std::string connect;
	std::cin >> connect;
	if (connect=="y") {
		std::cout << "\nWelcome to Console RPG, " << r_player2.getName() << std::endl
		     << "Type 'help' to display a help menu.";
		startGame(grid); // this is where we actually start
		delete grid; // we are done with the grid map; delete it
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

void spawnItem(movement *rhs) {
	item *plant=new item("plant",0,0);
	rhs->placeItem(plant,rhs);
}

// startGame function: this will start the movement system
void startGame(movement *rhs) {
	while(1) {
		std::cout << "\nMove: ";
		std::string moverVar;
		std::cin >> moverVar;
		if (moverVar=="n") {
			rhs->moveN();
		}
		if (moverVar=="s") {
			rhs->moveS();
		}
		if (moverVar=="w") {
			rhs->moveW();
		}
		if (moverVar=="e") {
			rhs->moveE();
		}
		if (moverVar=="nw") {
			rhs->moveNW();
		}
		if (moverVar=="ne") {
			rhs->moveNE();
		}
		if (moverVar=="sw") {
			rhs->moveSW();
		}
		if (moverVar=="se") {
			rhs->moveSE();
		}	
		if (moverVar=="position") {
			rhs->getCurrentPosition();
		}
		if (moverVar=="look") {
			rhs->look(rhs);
		}
		if (moverVar=="help") {
			std::cout << "\nYou may move around the map using the following directions:\n"
				<< "n, w, e, s, nw, ne, sw, se."
				<< "\nType 'quit' to exit the game or 'look' to check out\n"
				<< "what is on the ground.";
		}
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


