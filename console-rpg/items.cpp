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

