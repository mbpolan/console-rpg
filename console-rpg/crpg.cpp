#include <iostream>
#include "player.cpp"
#include "movement.cpp"
#include "definitions.h"
using namespace std;

main(int argc, char *argv[]) {
	player Player(500, 200);
	movement grid;
	cout << "Console RPG 0.1...\n\n" << endl;
	menu();
}
