// items.cpp: declarations for item functions
#include "items.h"

item::item(std::string fixedItemName, int spawnX, int spawnY) {
	itemLocationX=new int(spawnX);
	itemLocationY=new int(spawnY);
	itemName=new std::string(fixedItemName);
};

item::~item() {
	delete itemLocationX;
	delete itemLocationY;
	delete itemName;
	itemLocationX=0;
	itemLocationY=0;
	itemName=0;
};

void item::setLocationX(int XLOCATION) {
	if (*itemLocationX==XLOCATION)
		*itemLocationX=*itemLocationX;
	else
		*itemLocationX=XLOCATION;
};

void item::setLocationY(int YLOCATION) {
	if (*itemLocationY==YLOCATION)
		*itemLocationY=*itemLocationY;
	else
		*itemLocationY=YLOCATION;
};

TYPE item::checkType() {
	return itemType;
};

bool item::isHeadItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==head)
		return 1;
	else
		return 0;
};

bool item::isTorsoItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==torso)
		return 1;
	else
		return 0;
};

bool item::isLegsItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==legs)
		return 1;
	else
		return 0;
};

bool item::isBootsItem(item *thisItem) {
	TYPE result=thisItem->checkType();
	if (result==boots)
		return 1;
	else
		return 0;
};
