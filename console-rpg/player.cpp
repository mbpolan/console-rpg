/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
 *   kanadakid@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

 #include <iostream>
 #include <fstream>

// player.cpp: declarations for player functions
#include "player.h"

// player class default constructor
player::player() {
	currentHP=100;
	currentMP=10;
	name="Arbba";
	hairOutfit="brown", legsOutfit="blue", torsoOutfit="brown";
	luck=0,power=0,strength=0,defense=0;
	playerVocation=warrior;

	headEq=new item("nothing",head);
	torsoEq=new item("Jacket",torso);
	legEq=new item("Travel Pants",legs);
	bootEq=new item("Boots",boots);

	playerID=0;
	x=0;
	y=0;

};

// player class overloaded constructor
player::player(int fixedHP, int fixedMP, int id) {
	currentHP=fixedHP;
	currentMP=fixedMP;
	name="Arbba";

	luck=0;
	power=0;
	strength=0;
	defense=0;
	hairOutfit="brown", legsOutfit="blue", torsoOutfit="brown";
	playerVocation=warrior;
	
	headEq=new item("nothing",head);
	torsoEq=new item("Jacket",torso);
	legEq=new item("Travel Pants",legs);
	bootEq=new item("Boots",boots);
	
	playerID=id;
	x=0;
	y=0;

};

// player class enhanced constructor
player::player(int hp,int mp,int Luck,int Strength,int Power,int Defense,int id) {
	currentHP=hp;
	currentMP=mp;
	luck=Luck;
	strength=Strength;
	power=Power;
	defense=Defense;

	name="Arbba";
	hairOutfit="brown", legsOutfit="blue", torsoOutfit="brown";
	playerVocation=warrior;

	headEq=new item("nothing",head);
	torsoEq=new item("Jacket",torso);
	legEq=new item("Travel Pants",legs);
	bootEq=new item("Boots",boots);
	
	playerID=id;
	x=0;
	y=0;

};

// player class destructor
player::~player() {
	delete headEq;
	delete torsoEq;
	delete legEq;
	delete bootEq;
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

	name=r_player.getName();
	hairOutfit=r_player.getHair(),torsoOutfit=r_player.getTorso(),legsOutfit=r_player.getLegs();
	playerVocation=r_player.getVoc();

	headEq=r_player.getHeadItem();
	torsoEq=r_player.getTorsoItem();
	legEq=r_player.getLegsItem();
	bootEq=r_player.getBootsItem();

	return *this;
};

// overloaded operator==
bool player::operator==(const player &r_player) {
	if (currentHP==r_player.getHP() && currentMP==r_player.getMP()) {
		// now we test the other various info
		if (luck==r_player.getLuck() && strength==r_player.getStrength() && 
		    power==r_player.getPower() && defense==r_player.getDefense() &&
		    hairOutfit==r_player.getHair() && torsoOutfit==r_player.getTorso() && legsOutfit==r_player.getLegs() &&
		    
		    headEq==r_player.getHeadItem() && torsoEq==r_player.getTorsoItem() &&
		    legEq==r_player.getLegsItem() && bootEq==r_player.getBootsItem() &&
		    name==r_player.getName() && playerVocation==r_player.getVoc())
			return true;
	}
	
	else
		return false;
};

// let the player customize his character
void player::setLook() {

	std::string userVocation;
	
	std::cout << "\nPlease choose a vocation (warrior,mage,archer): ";
	std::cin >> userVocation;
	
	if (userVocation!="warrior" && userVocation!="mage" && userVocation!="archer") {
		std::cout << "\nThis vocation doesn't exist.\nDefault is warrior.\n";
		userVocation="warrior";
	}
	
	if (userVocation=="warrior") { // set warrior class stats
		luck=5;
		strength=10;
		power=15;
		defense=15;
		exp=0;
		level=1;
		std::cout << "\nYou are now a warrior.\n";
		playerVocation=warrior;
	}

	if (userVocation=="mage") { // set mage class stats
		luck=10;
		strength=5;
		power=10;
		defense=5;
		exp=0;
		level=1;
		std::cout << "\nYou are now a mage.\n";
		playerVocation=mage;
	}

	if (userVocation=="archer") { // set archer class stats
		luck=5;
		strength=10;
		power=15;
		defense=10;
		exp=0;
		level=1;
		std::cout << "\nYou are now an archer.\n";
		playerVocation=archer;
	}

	std::cout << "\nWhat is your hair color? ";
	std::cin >> hairOutfit;

	std::cout << "\nWhat is your shirt color? ";
	std::cin >> torsoOutfit;

	std::cout << "\nWhat is your pants color? ";
	std::cin >> legsOutfit;
};

// display player's inventory
void player::displayInventory() {
	std::cout << "\nYour Inventory:\n\n";
	std::cout << "Head: " << headEq->getName() << std::endl;
	std::cout << "Torso: " << torsoEq->getName() << std::endl;
	std::cout << "Legs: " << legEq->getName() << std::endl;
	std::cout << "Feet: " << bootEq->getName() << std::endl;
};

// remove item from inventory
void player::removeInventoryItem(int theType) {
	switch(theType) {
		case 0: headEq=new item("nothing",head);;break;
		case 1: torsoEq=new item("nothing",torso);break;
		case 2: legEq=new item("nothing",legs);break;
		case 3: bootEq=new item("nothing",boots);break;
		default: std::cout << "This item is not equiped!";
	}
};

// add item to inventory
void player::addInventoryItem(TYPE theType,item *thisItem) {
	switch(theType) {
		case head: headEq=(new item(thisItem));break;
		case torso: torsoEq=(new item(thisItem));break;
		case legs: legEq=(new item(thisItem));break;
		case boots: bootEq=(new item(thisItem));break;
		default: std::cout << "This item cannot be equiped!";
	}
};

// iterate through the inventory, look for item
int player::searchInventory(std::string itemName) {
	std::string locator=itemName;
	std::string headItem=headEq->getName();
	std::string torsoItem=torsoEq->getName();
	std::string legsItem=legEq->getName();
	std::string bootsItem=bootEq->getName();
	
	if (locator==headItem)
		return head;
	if (locator==torsoItem)
		return torso;
	if (locator==legsItem)
		return legs;
	if (locator==bootsItem)
		return boots;
	else {
		return npe; // not found
	}
};

// increase the player's current level
void player::increaseLevel(int increase) {
		level+=increase;
		std::cout << "\nYou advanced to level " << level << "!\n";
};

// display player statistics
int player::displayStats() {
	std::cout << "\n\nStats\n";
	std::cout << "HP: " << currentHP << std::endl;
	std::cout << "MP: " << currentMP << std::endl;
	std::cout << "Luck: " << luck << std::endl;
	std::cout << "Strength: " << strength << std::endl;
	std::cout << "Power: " << power << std::endl;
	std::cout << "Defense: " << defense << "\n\n";
};

// saves the current player status to file
int player::savePlayerData(player *Player,int player,int game,bool ignoreTemp) {

	// get the player's coordinates
	int x=Player->x;
	int y=Player->y;

	std::ofstream fout;
	std::ifstream fin;

	char savefile[256];
	char namefile[256];
	char targetDir[256];
	char index[256];
	
	// check which system the client is using. this is nessesary
	// because the file separators in linux and windows are different,
	// which will cause problems if they are not defined specifically ;)
	#ifdef __LINUX__
	sprintf(savefile,"data/game%d/savefile%d.dat",game,player);// the savefile
	sprintf(targetDir,"mkdir data/game%d",game); // command to make a new slot
	sprintf(index,"data/game%d/index.dat",game); // index file
	sprintf(namefile,"data/game%d/name%d.dat",game,player);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(savefile,"data\\game%d\\savefile%d.dat",game,player);// the savefile
	sprintf(targetDir,"mkdir data\\game%d",game); // command to make a new slot
	sprintf(index,"data\\game%d\\index.dat",game); // index file
	sprintf(namefile,"data\\game%d\\name%d.dat",game,player);
	#endif
	
	// if this slot doesn't exist, then make a directory for the savefiles.
	fin.open(savefile);
	
	// if we flag ignoreTemp to be false, then we need to make a temporary
	// directory for savefiles. otherwise we assume to temporary directory exists.
	if (!ignoreTemp) {
		if (!fin) {
			system(targetDir);
		}
	}
	fin.close();
	
	// open our savefile and load the stats in
	// follow each stat by a new line for loading
	fout.open(savefile);
	
	if (!fout) {
		std::cout << "\nUnable to save file!";
		return 0;
	}

	fout.write((char*) &x,sizeof(x));
	fout.write((char*) &y,sizeof(y));
	fout.write((char*) &currentHP,sizeof(currentHP));
	fout.write((char*) &currentMP,sizeof(currentMP));
	
	fout.write((char*) &luck,sizeof(luck));
	fout.write((char*) &strength,sizeof(strength));
	fout.write((char*) &power,sizeof(power));
	fout.write((char*) &defense,sizeof(defense));

	// todo: save eq

	fout.close();
	
	fout.open(namefile);
	if (!fout) {
		std::cout << "\nUnable to save file!";
		return 0;
	}
	
	fout << name;
	fout.close();
	
	saveToIndex(game);
};

// load the savefile and continue the game
int player::loadPlayerData(player *Player,int player,int game) {

	std::fstream fin;
	int x,y;

	// once again, check what the client's system is and use
	// the appropriate file separator.
	#ifdef __LINUX__
	char savefile[256];
	char namefile[256];
	sprintf(savefile,"data/game%d/savefile%d.dat",game,player);
	sprintf(namefile,"data/game%d/name%d.dat",game,player);
	#endif
	
	#ifdef __WINDOWS__
	char savefile[256];
	char namefile[256];
	sprintf(savefile,"data\\game%d\\savefile%d.dat",game,player);
	sprintf(namefile,"data\\game%d\\name%d.dat",game,player);
	#endif
	
	fin.open(savefile);

	if (!fin) {
		std::cout << "\nFailed to load savefile!";
		return 0;
	}

	fin.read((char*) &x,sizeof(x));
	Player->x=x;
	fin.clear();

	fin.read((char*) &y,sizeof(y));
	Player->y=y;
	fin.clear();

	fin.read((char*) &currentHP,sizeof(currentHP));
	fin.clear();
	
	fin.read((char*) &currentMP,sizeof(currentMP));
	fin.clear();

	fin.read((char*) &luck,sizeof(luck));
	fin.clear();

	fin.read((char*) &strength,sizeof(strength));
	fin.clear();

	fin.read((char*) &power,sizeof(power));
	fin.clear();

	fin.read((char*) &defense,sizeof(defense));
	fin.clear();
	 
	fin.close();
	
	fin.open(namefile);
	if (!fin) {
		std::cout << "\nFailed to load namefile!";
		return 0;
	}
	
	fin >> name;
	fin.close();

};

// save to index file
int player::saveToIndex(int game) {

	// currently we only save the amount of players
	// that were playing the game.
	#ifdef __LINUX__
	char index[256];
	sprintf(index,"data/game%d/index.dat",game); // index file
	#endif
	
	#ifdef __WINDOWS__
	char index[256];
	sprintf(index,"data\\game%d\\index.dat",game); // index file
	#endif
	
	std::ofstream fout;
	
	fout.open(index);
	if (!fout) {
		std::cout << "\nUnable to save index file!";
		return 0;
	}
	
	fout << playersOn << std::endl;
	fout.close();
};

// load data from the index file
int player::loadFromIndex(int game) {

	// this is the path to the index file
	#ifdef __LINUX__
	char index[256];
	sprintf(index,"data/game%d/index.dat",game);
	#endif
	
	#ifdef __WINDOWS__
	char index[256];
	sprintf(index,"data\\game%d\\index.dat",game);
	#endif

	std::ifstream fin;
	
	fin.open(index);
	if (!fin) {
		std::cout << "\nUnable to load from index file!";
		return 0;
	}
	
	int playersOnGame;
	fin >> playersOnGame; fin.clear();
	fin.close();
	
	return playersOnGame;
};
	
// delete the temporary directory (99)
int player::removeTemp() {

	// last time we need to check the client's system and
	// use the appropriate file separator.
	char path[256];
	char delCommand[256];
	
	#ifdef __LINUX__
	sprintf(path,"data/game99/savefile1.dat");
	sprintf(delCommand,"rm -rf data/game99");
	#endif
	
	#ifdef __WINDOWS__
	sprintf(path,"data\\game99\\savefile1.dat");
	sprintf(delCommand,"rm -rf data\\game99");
	#endif

	std::ifstream fin;
	
	// first we attempt to load a savefile from the temporary
	// directory. if it fails, then there is no need to remove
	// the directory since it doesn't exist. otherwise, remove it!
	fin.open(path);
	
	if (fin) {
		fin.close();
		system(delCommand);
	}
};
