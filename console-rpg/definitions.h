#include <iostream>
using namespace std;

void startGame(movement &);
int menu() {
//	cout << "\nEnter player name: ";
	std::string name;
	movement grid;
//	r_player.setName(name);
	cout << "\nStart a new game? (n,y) ";
	std::string connect;
	cin >> connect;
	if (connect=="y") {
		cout << "\nWelcome to Console RPG! You are now free to move using the letters n, w, e, s.\nType "
	                << "'position' to show your current location on the map [+-15x+-15] or 'quit' to exit. ";
		startGame(grid);
	}
	else {
		cout << "\nQuitting...";
		return 0;
	}
}

void startGame(movement &rhs) {
	while(1) {
		cout << "\nMove: ";
		std::string moverVar;
		cin >> moverVar;
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
			cout << "\nAre you sure you want to quit? (n,y)  ";
			cin >> quitVer;
			if (quitVer=="n")
				continue;
			else
				break;
		}
	}
		
}

