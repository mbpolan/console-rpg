// player.cpp: declarations for player functions
#include "player.h"

player::player(int fixedHP, int fixedMP, int fixedHeight, int fixedAge) {
	currentHP=new int(fixedHP);
	currentMP=new int(fixedMP);
	playerHeight=new int(fixedHeight);
	playerAge=new int(fixedAge);
	playerName=new std::string;
	playerName=new std::string("Arbba");
	hair="brown", legs="blue", torso="brown";
	
	headEq="helmet";
	torsoEq="nothing";
	legEq="nothing";
	bootEq="nothing";
	
};

player::~player() {
	delete currentHP;
	delete currentMP;
	delete playerName;
	delete playerHeight;
	delete playerAge;
	currentHP=0;
	currentMP=0;
	playerName=0;
	playerHeight=0;
	playerAge=0;
};

void player::setLook(player *r_player) {
	std::string userHair, userBody, userLegs;
	std::cout << "\nWhat is your hair color? ";
	std::cin >> userHair;
	r_player->setHair(userHair);
	std::cout << "\nWhat is your shirt color? ";
	std::cin >> userBody;
	r_player->setTorso(userBody);
	std::cout << "\nFinally, what is your pants color? ";
	std::cin >> userLegs;
	r_player->setLegs(userLegs);
};

std::string player::displayInventory(player *r_player) {
	std::cout << "\nYour Inventory:\n\n";
	std::cout << "Head: " << r_player->getHeadItem() << ".\n";
	std::cout << "Torso: " << r_player->getTorsoItem() << ".\n";
	std::cout << "Legs: " << r_player->getLegsItem() << ".\n";
	std::cout << "Feet: " << r_player->getBootsItem() << ".\n";
};

void player::removeInventoryItem(int theType) {
	switch(theType) {
		case 0: headEq="nothing";break;
		case 1: torsoEq="nothing";break;
		case 2: legEq="nothing";break;
		case 3: bootEq="nothing";break;
		default: std::cout << "This item is not equiped!";
	}
};

/************************* 
 *this needs to be FIXED!*
 *************************
void player::addInventoryItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	switch(result) {
		case 0: headEq=thisItem->getName();break;
		case 1: torsoEq=thisItem->getName();break;
		case 2: legEq=thisItem->getName();break;
		case 3: bootEq=thisItem->getName();break;
		default: std::cout << "This item cannot be equiped!";
	}
};*/

int player::searchInventory(player *r_player,std::string itemName) {
	std::string locator=itemName;
	std::string headItem=r_player->getHeadItem();
	std::string torsoItem=r_player->getTorsoItem();
	std::string legsItem=r_player->getLegsItem();
	std::string bootsItem=r_player->getBootsItem();
	
	if (locator==headItem)
		return 0;
	if (locator==torsoItem)
		return 1;
	if (locator==legsItem)
		return 2;
	if (locator==bootsItem)
		return 3;
	else {
		return 4; // not found
	}
};
