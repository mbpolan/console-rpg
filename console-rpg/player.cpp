#include "player.h"

void player::setLook(player &r_player) {
	std::string userHair, userBody, userLegs;
	std::cout << "\nWhat is your hair color? ";
	std::cin >> userHair;
	r_player.setHair(userHair);
	std::cout << "\nWhat is your shirt color? ";
	std::cin >> userBody;
	r_player.setTorso(userBody);
	std::cout << "\nFinally, what is your pants color? ";
	std::cin >> userLegs;
	r_player.setLegs(userLegs);
};
