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
 #include <libxml/parser.h>

// player.cpp: declarations for player functions
#include "player.h"
#include "utilities.h"
using namespace utilities;

// player class default constructor
player::player() {
	currentHP=100;
	currentMP=10;
	name="Arbba";
	hairOutfit="brown", legsOutfit="blue", torsoOutfit="brown";
	luck=0,power=0,strength=0,defense=0;
	playerVocation=WARRIOR;

	headEq=new item(0,head);
	torsoEq=new item(100,torso);
	legEq=new item(114,legs);
	bootEq=new item(130,boots);
	bp=new bag(8);

	playerID=0;
	x=25;
	y=25;
	layer=0;
	
	isPoisoned=false;
	isBurned=false;
	isElectrified=false;
	inBattle=false;
	inDefense=false;

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
	playerVocation=WARRIOR;
	
	headEq=new item(0,head);
	torsoEq=new item(100,torso);
	legEq=new item(114,legs);
	bootEq=new item(130,boots);
	bp=new bag(8);
	
	playerID=id;
	x=25;
	y=25;
	layer=0;
	
	isPoisoned=false;
	isBurned=false;
	isElectrified=false;
	inBattle=false;
	inDefense=false;

};

// player class enhanced constructor
player::player(int hp,int mp,int Luck,int Strength,int Power,int Defense,int id) {
	luck=Luck;
	strength=Strength;
	power=Power;
	defense=Defense;

	name="Arbba";
	hairOutfit="brown", legsOutfit="blue", torsoOutfit="brown";
	playerVocation=WARRIOR;

	headEq=new item(0,head);
	torsoEq=new item(100,torso);
	legEq=new item(114,legs);
	bootEq=new item(130,boots);
	bp=new bag(8);
	
	x=25;
	y=25;
	layer=0;
	
	isPoisoned=false;
	isBurned=false;
	isElectrified=false;
	inBattle=false;
	inDefense=false;

};

// player class destructor
player::~player() {
	delete headEq;
	delete torsoEq;
	delete legEq;
	delete bootEq;
	delete bp;
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
		playerVocation=WARRIOR;
	}

	if (userVocation=="mage") { // set mage class stats
		luck=10;
		strength=5;
		power=10;
		defense=5;
		exp=0;
		level=1;
		std::cout << "\nYou are now a mage.\n";
		playerVocation=MAGE;
	}

	if (userVocation=="archer") { // set archer class stats
		luck=5;
		strength=10;
		power=15;
		defense=10;
		exp=0;
		level=1;
		std::cout << "\nYou are now an archer.\n";
		playerVocation=ARCHER;
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
	std::cout << "Other: Backpack" << std::endl;
};

// remove item from inventory
void player::removeInventoryItem(int theType) {
	switch(theType) {
		case 0: delete headEq; headEq=new item(0,head);break;
		case 1: delete torsoEq; torsoEq=new item(0,torso);break;
		case 2: delete  legEq; legEq=new item(0,legs);break;
		case 3: delete bootEq; bootEq=new item(0,boots);break;
		default: std::cout << "This item is not equiped!";
	}
};

// add item to inventory
void player::addInventoryItem(TYPE theType,item *thisItem) {
	switch(theType) {
		case head: headEq=thisItem; break;
		case torso: torsoEq=thisItem; break;
		case legs: legEq=thisItem; break;
		case boots: bootEq=thisItem; break;
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

// return a pointer to an item in the inventory
item* player::getInventoryItem(int pos) {
	#ifdef DEBUG
	std::cout << "Getting inventory item at pos: " << pos << std::endl;
	#endif
	
	switch(pos) {
		case INV_HEAD: return headEq; break;
		case INV_TORSO: return torsoEq; break;
		case INV_LEGS: return legEq; break;
		case INV_BOOTS: return bootEq; break;
		default: return NULL; break;
	}
};

// increase the player's current level
void player::increaseLevel(int increase) {
		level+=increase;
		std::cout << "\nYou advanced to level " << level << "!\n";
};

// display player statistics
int player::displayStats() {
	std::cout << "\nStats\n";
	std::cout << "HP: " << currentHP << std::endl;
	std::cout << "MP: " << currentMP << std::endl;
	std::cout << "Luck: " << luck << std::endl;
	std::cout << "Strength: " << strength << std::endl;
	std::cout << "Power: " << power << std::endl;
	std::cout << "Defense: " << defense;
};

// saves the current player stats
xmlNodePtr player::savePlayerData() {
/*	std::ofstream fout;
	std::ifstream fin;
	
	// if this slot doesn't exist, then make a directory for the savefiles.
	fin.open(savefile);
	
	if (!ignoreTemp) {
		if (!fin) {
			system(targetDir);
		}
	}
	
	fin.close();*/
	
	xmlNodePtr root;
	std::stringstream ss, ss2;
	
	root=xmlNewNode(NULL, (const xmlChar*) "player");
	
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
	
	ss << layer;
	xmlSetProp(info, (const xmlChar*) "layer", (const xmlChar*) ss.str().c_str());
	ss.str("");
	
	ss << utilities::vtoi(playerVocation);
	xmlSetProp(info,(const xmlChar*) "vocation",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	xmlAddChild(root,info);
	
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
	
	xmlAddChild(root,ent);
	
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
	
	xmlNodePtr bpNode=xmlNewNode(0, (const xmlChar*) "backpack");
	xmlNodePtr bpItem;
	
	std::list<item*>::iterator it;
	int i=0;
	
	// save the contents of the player's backpack
	for (it=((bag*) bp)->contents.begin();it!=((bag*) bp)->contents.end();it++) {
		if ((*it)) {
			i++;
			
			bpItem=xmlNewNode(0, (const xmlChar*) "slot");
			
			ss << (*it)->getItemID();
			xmlSetProp(bpItem, (const xmlChar*) "item", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			xmlAddChild(bpNode, bpItem);
		}
	}
	
	ss << i;
	xmlSetProp(bpNode, (const xmlChar*) "contents", (const xmlChar*) ss.str().c_str());
	ss.str("");
	
	// add backpack node to equipment node
	xmlAddChild(eq, bpNode);
	xmlAddChild(root,eq);
	
	// return the newly made xmlNodePtr
	return root;
};

// load the savefile and continue the game
bool player::loadPlayerData(xmlNodePtr p) {
	xmlNodePtr ptr;
	
	if (strcmp("player", (const char*) p->name)==0) {
		ptr=p->children;
		
		// load the basic info
		this->name=(std::string) ((const char*) xmlGetProp(ptr,(xmlChar*) "name"));
		this->x=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "x"));
		this->y=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "y"));
		this->layer=atoi((const char*) xmlGetProp(ptr, (xmlChar*) "layer"));
		this->playerVocation=itov((int) xmlGetProp(ptr,(xmlChar*) "vocation"));
		
		ptr=ptr->next;
		
		// get the entity of the player
		this->hairOutfit=atos((const char*) xmlGetProp(ptr,(xmlChar*) "hair"));
		this->torsoOutfit=atos((const char*) xmlGetProp(ptr,(xmlChar*) "torso"));
		this->legsOutfit=atos((const char*) xmlGetProp(ptr,(xmlChar*) "legs"));
		
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
		headEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "head")), 0x64);
		torsoEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "torso")), 0x64);
		legEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "legs")), 0x64);
		bootEq=new item(atoi((const char*) xmlGetProp(ptr,(xmlChar*) "boots")), 0x64);
	
		xmlNodePtr temp=ptr->children;
		
		// load in the player's backpack contents
		int bpCount=atoi((const char*) xmlGetProp(temp, (xmlChar*) "contents"));
		xmlNodePtr bpItemNode=temp->children;;
		
		while(bpItemNode) {
			int bpItemId=atoi((const char*) xmlGetProp(bpItemNode, (xmlChar*) "item"));
		
			bp->addItem(new item(bpItemId, 0x64));
		
			bpItemNode=bpItemNode->next;
		}
		
		return true;
	}
	
	return false;
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

// send a message to an npc on the map
void player::sendNpcMsg(map *karte,movement *rhs) {
	std::string msg;
	
	std::cout << "Enter message: ";
	std::cin >> msg;
	
	npc *myNpc=rhs->getNPC(karte, x, y, layer);
	if (myNpc) {
		msg=myNpc->replyToMsg(msg);
		
		if (msg!=(std::string) "NULL")
			std::cout << std::endl << myNpc->name << " says: " << msg;
			
		else
			std::cout << std::endl << myNpc->name << " says: ???";
		
		return;
	}
	
	std::cout << "\nThere is no one here to talk to.";
};

// TODO: method to receive an attack
void player::receiveAttack(battleAction *act) {
	return;
};

// method to attempt to run from a battle
bool player::attemptRunFromBattle(enemy *e) {
	if (e->strong())
		return false;
	
	else {
		int rand=utilities::random_range(0, e->getStrength());
		if (rand < e->getStrength()/2)
			return true;
		
		else
			return false;
	}
};
