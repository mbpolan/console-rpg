// crpg.cpp: main file
#include <iostream>
#include "items.cpp"
#include "map.cpp"
#include "player.cpp"
#include "movement.cpp"
#include "definitions.h"

main(int argc, char *argv[]) {
	player *Player=new player(500,200,6,18); // player HP/MP/Height(ft)/age
	std::cout << "\nConsole-RPG 0.1.5\n\n" << std::endl;
	menu(Player); // call menu() and pass Player in
}
