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
	playerName="Arbba";
	hair="brown", legs="blue", torso="brown";
	luck=0,power=0,strength=0,defense=0;
	playerVocation=warrior;

	headEq="nothing";
	torsoEq="Jacket";
	legEq="Travel Pants";
	bootEq="Boots";
	
	playerID=0;

};

// player class overloaded constructor
player::player(int fixedHP, int fixedMP, int id) {
	currentHP=fixedHP;
	currentMP=fixedMP;
	playerName="Arbba";

	luck=0;
	power=0;
	strength=0;
	defense=0;
	hair="brown",legs="blue",torso="brown";
	playerVocation=warrior;
	
	headEq="nothing";
	torsoEq="Jacket";
	legEq="Travel Pants";
	bootEq="Boots";
	
	playerID=id;;
	
};

// player class enhanced constructor
player::player(int hp,int mp,int Luck,int Strength,int Power,int Defense,int id) {
	currentHP=hp;
	currentMP=mp;
	luck=Luck;
	strength=Strength;
	power=Power;
	defense=Defense;

	playerName="Arbba";
	hair="brown",legs="blue",torso="brown";
	playerVocation=warrior;

	headEq="nothing";
	torsoEq="Jacket";
        legEq="Travel Pants";
        bootEq="Boots";
	
	playerID=id;
	
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
	std::cin >> hair;
	
	std::cout << "\nWhat is your shirt color? ";
	std::cin >> torso;

	std::cout << "\nWhat is your pants color? ";
	std::cin >> legs;
};

// display player's inventory
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
int player::savePlayerData(map *karte,int player,int game,bool ignoreTemp) {

	// get the player's coordinates
	int x=karte->getCurrentSpaceX();
	int y=karte->getCurrentSpaceY();
	
	char savefile[256];
	char targetDir[256];
	char index[256];
	char namefile[256];
	
	std::ofstream fout;
	std::ifstream fin;
	
	// check which system the client is using. this is nessesary
	// because the file separators in linux and windows are different,
	// which will cause problems if they are not defined specifically ;)
	#ifdef __LINUX__
	sprintf(savefile,"data/game%d/savefile%d.dat",game,player); // the savefile
	sprintf(targetDir,"mkdir data/game%d",game); // command to make a new slot
	sprintf(index,"data/game%d/index.dat",game); // index file
	sprintf(namefile,"data/game%d/name%d.dat",game,player);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(savefile,"data\\game%d\\savefile%d.dat",game,player); // the savefile
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
	
	//fout.write((char*) &playerName,sizeof(playerName));
	fout.write((char*) &x,sizeof(x));
	fout.write((char*) &y,sizeof(y));
	fout.write((char*) &currentHP,sizeof(currentHP));
	fout.write((char*) &currentMP,sizeof(currentMP));
	
	fout.write((char*) &luck,sizeof(luck));
	fout.write((char*) &strength,sizeof(strength));
	fout.write((char*) &power,sizeof(power));
	fout.write((char*) &defense,sizeof(defense));
	
	fout.close();
	
	fout.open(namefile);
	if (!fout) {
		std::cout << "\nUnable to save file!";
		return 0;
	}
	
	fout << playerName;
	fout.close();
	
	saveToIndex(game);
};

// load the savefile and continue the game
int player::loadPlayerData(map *karte,int player,int game) {
	
	std::fstream fin;
	int x,y;
	char savefile[256];
	char namefile[256];
	
	// once again, check what the client's system is and use
	// the appropriate file separator.
	#ifdef __LINUX__
	sprintf(savefile,"data/game%d/savefile%d.dat",game,player);
	sprintf(namefile,"data/game%d/name%d.dat",game,player);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(savefile,"data\\game%d\\savefile%d.dat",game,player);
	sprintf(namefile,"data\\game%d\\name%d.dat",game,player);
	#endif
	
	fin.open(savefile);

	if (!fin) {
		std::cout << "\nFailed to load savefile!";
		return 0;
	}
	
	/*
	fin.read((char*) &playerName,sizeof(playerName));
	fin.clear();*/
	
	fin.read((char*) &x,sizeof(x));
	karte->setCurrentSpaceX(x);
	fin.clear();

	fin.read((char*) &y,sizeof(y));
	karte->setCurrentSpaceY(y);
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
	
	fin >> playerName;
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

	#ifdef __LINUX__
	char index[256];
	sprintf(index,"data/game%d/index.dat",game); // index file
	#endif
	
	#ifdef __WINDOWS__
	char index[256];
	sprintf(index,"data\\game%d\\index.dat",game); // index file
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
	#ifdef __LINUX__
	char path[]="data/game99/savefile1.dat";
	char delCommand[]="rm -rf data/game99";
	#endif
	
	#ifdef __WINDOWS__
	char path[]="data\\game99\\savefile1.dat";
	char delCommand[]="rmdir /S /Q data\\game99";
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
