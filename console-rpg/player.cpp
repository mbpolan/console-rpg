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
 #include <libxml/xmlmemory.h>
 #include <libxml/parser.h>

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

	headEq=new item(0,head);
	torsoEq=new item(100,torso);
	legEq=new item(114,legs);
	bootEq=new item(130,boots);

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
	
	headEq=new item(0,head);
	torsoEq=new item(100,torso);
	legEq=new item(114,legs);
	bootEq=new item(130,boots);
	
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

	headEq=new item(0,head);
	torsoEq=new item(100,torso);
	legEq=new item(114,legs);
	bootEq=new item(130,boots);
	
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
		case 0: headEq=new item(0,head);;break;
		case 1: torsoEq=new item(0,torso);break;
		case 2: legEq=new item(0,legs);break;
		case 3: bootEq=new item(0,boots);break;
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
int player::savePlayerData(int player,int game,bool ignoreTemp) {
	std::ofstream fout;
	std::ifstream fin;

	char savefile[256];
	char namefile[256];
	char targetDir[256];
	char index[256];
	
	// check which system the client is using
	#ifdef __LINUX__
	sprintf(savefile,"data/game%d/savefile%d.xml",game,player);// the savefile
	sprintf(targetDir,"mkdir data/game%d",game); // command to make a new slot
	sprintf(index,"data/game%d/index.dat",game); // index file
	#endif
	
	#ifdef __WINDOWS__
	sprintf(savefile,"data\\game%d\\savefile%d.xml",game,player);// the savefile
	sprintf(targetDir,"mkdir data\\game%d",game); // command to make a new slot
	sprintf(index,"data\\game%d\\index.dat",game); // index file
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
	
	xmlDocPtr doc;
	xmlNodePtr root,ptr;
	std::stringstream ss;
	
	doc=xmlNewDoc((const xmlChar*) "1.0");
	doc->children=xmlNewDocNode(doc,NULL,(const xmlChar*) "player",NULL);
	root=doc->children;
	
	// save some info such as location, etc.
	xmlNodePtr info=xmlNewNode(NULL,(const xmlChar*) "info");
	
	ss << name;
	xmlSetProp(info,(const xmlChar*) "name",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << x;
	xmlSetProp(info,(const xmlChar*) "x",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << y;
	xmlSetProp(info,(const xmlChar*) "y",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	xmlAddChild(doc->children,info);
	
	////////////////////////
	// save character entity
	////////////////////////
	xmlNodePtr ent=xmlNewNode(NULL,(const xmlChar*) "entity");
	
	ss << hairOutfit;
	xmlSetProp(ent,(const xmlChar*) "hair",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << torsoOutfit;
	xmlSetProp(ent,(const xmlChar*) "torso",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << legsOutfit;
	xmlSetProp(ent,(const xmlChar*) "legs",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << currentHP;
	xmlSetProp(ent,(const xmlChar*) "hp",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << currentMP;
	xmlSetProp(ent,(const xmlChar*) "mp",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << luck;
	xmlSetProp(ent,(const xmlChar*) "luck",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << strength;
	xmlSetProp(ent,(const xmlChar*) "strength",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << power;
	xmlSetProp(ent,(const xmlChar*) "power",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << defense;
	xmlSetProp(ent,(const xmlChar*) "defense",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << level;
	xmlSetProp(ent,(const xmlChar*) "level",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << exp;
	xmlSetProp(ent,(const xmlChar*) "exp",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	xmlAddChild(doc->children,ent);
	
	///////////////////
	// Save player's EQ
	///////////////////
	xmlNodePtr eq=xmlNewNode(NULL,(const xmlChar*) "eq");
	
	ss << headEq->getItemID();
	xmlSetProp(eq,(const xmlChar*) "head",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << torsoEq->getItemID();
	xmlSetProp(eq,(const xmlChar*) "torso",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << legEq->getItemID();
	xmlSetProp(eq,(const xmlChar*) "legs",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << bootEq->getItemID();
	xmlSetProp(eq,(const xmlChar*) "boots",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	xmlAddChild(doc->children,eq);
	

	xmlKeepBlanksDefault(1);
	
	// save the player file
	xmlSaveFile(savefile,doc);
	xmlFreeDoc(doc);
	
	// make an index file
	saveToIndex(game);
};

// load the savefile and continue the game
int player::loadPlayerData(int player,int game) {
	std::fstream fin;
	
	char savefile[256];
	char namefile[256];

	// once again, check what the client's system is and use
	// the appropriate file separator.
	#ifdef __LINUX__
	sprintf(savefile,"data/game%d/savefile%d.xml",game,player);
	#endif
	
	#ifdef __WINDOWS__
	sprintf(savefile,"data\\game%d\\savefile%d.xml",game,player);
	#endif
	
	xmlDocPtr doc=xmlParseFile(savefile);
	
	if (doc) {
		xmlNodePtr root,ptr,temp;
		root=xmlDocGetRootElement(doc);
	
		if (xmlStrcmp(root->name,(const xmlChar*) "player")) {
			xmlFreeDoc(doc);
			return 0;
		}
		
		ptr=root->children;
		char _name[256];
		
		// load the basic info
		this->name=item::atos((const char*) xmlGetProp(ptr,(xmlChar*) "name"));
		this->x=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "x"));
		this->y=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "y"));
		
		ptr=ptr->next;
		
		// get the entity of the player
		this->hairOutfit=item::atos((const char*) xmlGetProp(ptr,(xmlChar*) "hair"));
		this->torsoOutfit=item::atos((const char*) xmlGetProp(ptr,(xmlChar*) "torso"));
		this->legsOutfit=item::atos((const char*) xmlGetProp(ptr,(xmlChar*) "legs"));
		
		this->currentHP=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "hp"));
		this->currentMP=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "mp"));
		this->luck=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "luck"));
		this->strength=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "strength"));
		
		this->power=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "power"));
		this->defense=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "defense"));
		this->level=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "level"));
		this->exp=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "exp"));
		
		ptr=ptr->next;
		
		// load the player's equipment
		//int hid=atoi((const char*)xmlGetProp(ptr,(xmlChar*) "head"));
		headEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "head")));
		torsoEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "torso")));
		legEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "legs")));
		bootEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "boots")));
		
		xmlFreeDoc(doc);
		return 1;
	}
	
	return 0;
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
int player::loadFromIndex(int game,int &playersOnGame) {

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
	
	fin >> playersOnGame; fin.clear();
	fin.close();
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
