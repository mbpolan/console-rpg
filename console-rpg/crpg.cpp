// crpg.cpp: main file
#include <iostream>
#include "player.cpp"
#include "movement.cpp"
#include "definitions.h"
using namespace std;

main(int argc, char *argv[]) {
	player Player(500, 200); // player HP/MP
	cout << "\nConsole-RPG 0.1\n\n" << endl;
	menu(Player); // call menu() and pass Player in
}
