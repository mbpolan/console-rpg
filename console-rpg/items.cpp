// items.cpp: declarations for item functions
#include "items.h"

// item class default constructor
item::item() {
	itemLocationX=new int(0);
	itemLocationY=new int(0);
	itemName=new std::string("NULL");
	itemTYPE=npe;
};

// our item class constructor
item::item(std::string fixedItemName,int spawnX,int spawnY,TYPE thisType) {
	itemLocationX=new int(spawnX);
	itemLocationY=new int(spawnY);
	itemName=new std::string(fixedItemName);
	itemTYPE=thisType;
};

// item class destructor
item::~item() {
	delete itemLocationX;
	delete itemLocationY;
	delete itemName;
	itemName=0;
	itemLocationX=0;
	itemLocationY=0;
};

// set item location on X
void item::setLocationX(int XLOCATION) {
	if (*itemLocationX==XLOCATION)
		*itemLocationX=*itemLocationX;
	else
		*itemLocationX=XLOCATION;
};

// set item location on Y
void item::setLocationY(int YLOCATION) {
	if (*itemLocationY==YLOCATION)
		*itemLocationY=*itemLocationY;
	else
		*itemLocationY=YLOCATION;
};

// check the item's enumerated type
TYPE item::checkType() {
	return itemTYPE;
};

// check if this item can be equipped on head slot
bool item::isHeadItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==head)
		return 1;
	else
		return 0;
};

// check if this item can be equipped on armor slot
bool item::isTorsoItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==torso)
		return 1;
	else
		return 0;
};

// check if this item can be equipped on legs slot
bool item::isLegsItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==legs)
		return 1;
	else
		return 0;
};

// check if this item can be equipped on boots slot
bool item::isBootsItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==boots)
		return 1;
	else
		return 0;
};

