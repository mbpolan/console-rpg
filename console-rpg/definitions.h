// definitions.h: holds function declarations and definitions
#include <iostream>

void startGame(movement&);
int mainMenu(player&);
void optionMenu();

// menu function: display menu and options
int menu(player &r_player) {
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
			mainMenu(r_player);
			return 0;
		}
		
		if( menuChoice=="2")
			optionMenu();
		
		else
			return 0;
	}
}

// mainMenu: function for displaying the main menu =^/
int mainMenu(player &r_player2) {
	std::cout << "\nEnter player name: ";
	std::string name;
	std::cin >> name;
	movement grid;
	r_player2.setName(name);
	std::cout << "\nStart a new game? (n,y) ";
	std::string connect;
	std::cin >> connect;
	if (connect=="y") {
		std::cout << "\nWelcome to Console RPG, " << r_player2.getName() << "! You are now free to move using"
		     <<" the letters n, w, e, s, nw, ne, sw, and se.\nType 'position' to show your current" 
		     << " location on the map or 'quit' to exit. ";
		startGame(grid); // this is where we actually start
	}
	else {
		std::cout << "\nQuitting...";
		return 0;
	}
}

// optionMenu: (TODO) function for displaying option menu
void optionMenu() {
	std::cout << "\nNo options avaliable at this time.\n";
} 

// startGame function: this will start the movement system
void startGame(movement &rhs) {
	while(1) {
		std::cout << "\nMove: ";
		std::string moverVar;
		std::cin >> moverVar;
		if (moverVar=="n") {
			rhs.moveN();
		}
		if (moverVar=="s") {
			rhs.moveS();
		}
		if (moverVar=="w") {
			rhs.moveW();
		}
		if (moverVar=="e") {
			rhs.moveE();
		}
		if (moverVar=="nw") {
			rhs.moveNW();
		}
		if (moverVar=="ne") {
			rhs.moveNE();
		}
		if (moverVar=="sw") {
			rhs.moveSW();
		}
		if (moverVar=="se") {
			rhs.moveSE();
		}	
		if (moverVar=="position") {
			rhs.getCurrentPosition();
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

