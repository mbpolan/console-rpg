#include <iostream>
#include "player.cpp"
#include "movement.cpp"
using namespace std;

main(int argc, char *argv[]) {
	player Player(500, 200);
	movement grid;
	cout << "Console RPG 0.1...\n\n" << endl;
	cout << "Start a new game? (n,y)  ";
	std::string connect;
	cin >> connect;
	if (connect == "y") {
		cout << "\nWelcome to Console RPG! You are now free to move using the letters n, w, e, s.\nType "
			<< "'position' to show your current location on the map [+-15x+-15] or 'quit' to exit. ";
		while(1) {
		cout << "\nMove: ";
		std::string moverVar;
		cin >> moverVar;
		if (moverVar=="n") {
			grid.moveN();
		}
		if (moverVar=="s") {
			grid.moveS();
		}
		if (moverVar=="w") {
			grid.moveW();
		}
		if (moverVar=="e") {
			grid.moveE();
		}
		if (moverVar=="position") {
			grid.getCurrentPosition();
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
	if (connect=="n") {
		cout << "\nQuitting...";
		return 0;
		}
	}
}
