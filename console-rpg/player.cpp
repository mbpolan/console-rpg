// player.cpp: declarations for player functions
#include "player.h"

// player class default constructor
player::player() {
	currentHP=100;
	currentMP=10;
	playerHeight=6;
	playerAge=18;
	playerName="Arbba";
	hair="brown", legs="blue", torso="brown";
	luck=0,power=0,strength=0,defense=0;
	playerVocation=warrior;

	headEq="nothing";
	torsoEq="nothing";
	legEq="nothing";
	bootEq="nothing";

};

// player class overloaded constructor
player::player(int fixedHP, int fixedMP, int fixedHeight, int fixedAge) {
	currentHP=fixedHP;
	currentMP=fixedMP;
	playerHeight=fixedHeight;
	playerAge=fixedAge;
	playerName="Arbba";

	luck=0;
	power=0;
	strength=0;
	defense=0;
	hair="brown",legs="blue",torso="brown";
	playerVocation=warrior;
	
	headEq="nothing";
	torsoEq="Jacket";
	legEq="Travel_Pants";
	bootEq="Boots";
	
};

// player class enhanced constructor
player::player(int hp,int mp,int Luck,int Strength,int Power,int Defense) {
	currentHP=hp;
	currentMP=mp;
	luck=Luck;
	strength=Strength;
	power=Power;
	defense=Defense;

	playerHeight=6,playerAge=18,playerName="Arbba";
	hair="brown",legs="blue",torso="brown";
	playerVocation=warrior;

	headEq="nothing";
	torsoEq="nothing";
        legEq="Travel_Pants";
        bootEq="Boots";
};

// player class destructor
player::~player() {
};

// overloaded operator=
player &player::operator=(const player &r_player) {
	if (this==&r_player)
		return *this;
	currentHP=r_player.getHP();
	currentMP=r_player.getMP();
	luck=r_player.getLuck();
	strength=r_player.getStrength();
	power=r_player.getStrength();
	defense=r_player.getDefense();

	playerHeight=r_player.getHeight(),playerAge=r_player.getAge(),playerName=r_player.getName();
	hair=r_player.getHair(),torso=r_player.getTorso(),legs=r_player.getLegs();
	playerVocation=r_player.getVoc();

	headEq=r_player.getHeadItem();
	torsoEq=r_player.getTorsoItem();
	legEq=r_player.getLegsItem();
	bootEq=r_player.getBootsItem();

	return *this;
};

// let the player customize his character
void player::setLook(player *r_player) {
	std::string userVocation;
	std::string userHair, userBody, userLegs;

	std::cout << "\nPlease choose a vocation (warrior,mage,archer): ";
	std::cin >> userVocation;

	if (userVocation=="warrior") { // set warrior class stats
		r_player->setLuck(5);
		r_player->setStrength(10);
		r_player->setPower(15);
		r_player->setDefense(15);
		r_player->setExp(0);
		r_player->setLevel(1);
		std::cout << "\nYou are now a warrior.\n";
		r_player->setVoc(warrior);
	}

	if (userVocation=="mage") { // set mage class stats
		r_player->setLuck(10);
		r_player->setStrength(5);
		r_player->setPower(10);
		r_player->setDefense(5);
		r_player->setExp(0);
		r_player->setLevel(1);
		std::cout << "\nYou are now a mage.\n";
		r_player->setVoc(mage);
	}

	if (userVocation=="archer") { // set archer class stats
		r_player->setLuck(5);
		r_player->setStrength(10);
		r_player->setPower(15);
		r_player->setDefense(10);
		r_player->setExp(0);
		r_player->setLevel(1);
		std::cout << "\nYou are now an archer.\n";
		r_player->setVoc(archer);
	}

	if (userVocation!="warrior" && userVocation!="mage" && userVocation!="archer") {
		std::cout << "\nThis vocation doesn't exist.\nDefault is warrior.\n";
	}

	std::cout << "\nWhat is your hair color? ";
	std::cin >> userHair;
	r_player->setHair(userHair);
	std::cout << "\nWhat is your shirt color? ";
	std::cin >> userBody;
	r_player->setTorso(userBody);
	std::cout << "\nWhat is your pants color? ";
	std::cin >> userLegs;
	r_player->setLegs(userLegs);
};

// display player's inventory
// BUG: there is a bug here, fix it!
void player::displayInventory() {
	std::cout << "\nYour Inventory:\n\n";
	std::cout << "Head: " << headEq << "\n";
	std::cout << "Torso: " << torsoEq << "\n";
	std::cout << "Legs: " << legEq << "\n";
	std::cout << "Feet: " << bootEq << "\n";
};

// remove item from inventory
void player::removeInventoryItem(int theType) {
	switch(theType) {
		case 0: headEq="nothing";break;
		case 1: torsoEq="nothing";break;
		case 2: legEq="nothing";break;
		case 3: bootEq="nothing";break;
		default: std::cout << "This item is not equiped!";
	}
};

// add item to inventory
void player::addInventoryItem(TYPE theType,std::string name) {
	switch(theType) {
		case 0: headEq=name;break;
		case 1: torsoEq=name;break;
		case 2: legEq=name;break;
		case 3: bootEq=name;break;
		default: std::cout << "This item cannot be equiped!";
	}
};

// iterate through the inventory, look for item
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

// increase the player's current level
void player::increaseLevel() {
		level++;
		std::cout << "\nYou advanced to level " << level << "!\n";
};

// display player statistics
int player::displayStats(player *r_player) {
	std::cout << "\n\nStats\n";
	std::cout << "HP: " << currentHP << std::endl;
	std::cout << "MP: " << currentMP << std::endl;
	std::cout << "Luck: " << luck << std::endl;
	std::cout << "Strength: " << strength << std::endl;
	std::cout << "Power: " << power << std::endl;
	std::cout << "Defense: " << defense << "\n\n";
};
