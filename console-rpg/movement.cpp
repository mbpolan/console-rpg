// movement.h: definitions for movement class
#include "movement.h"

movement::movement() {
	fDay=true; // make it day by default
	stepCount=0;
	itemWarning="\nThere is an item here.";
};

void movement::moveN(map *karte) {
	if (karte->getCurrentSpaceX()==karte->getMapMaxSizeX()) {
		std::cout << "\nYou can't move any further north!";
	}
	else {
		int x=karte->getCurrentSpaceX();
		int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceX(++x);
		std::cout << "\nMoved North.";
	}
};

void movement::moveS(map *karte) {
	if (karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further south!";
	}
	else {
		int x=karte->getCurrentSpaceX();
		int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceX(--x);
		std::cout << "\nMoved south.";
	}
};

void movement::moveW(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY()) {
		std::cout << "\nYou can't move any further west!";
	}
	else {
		int y=karte->getCurrentSpaceY();
		int x=karte->getCurrentSpaceX();
		karte->setCurrentSpaceY(--y);
		std::cout << "\nMoved west.";
	}
};

void movement::moveE(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY())  {
		std::cout << "\nYou can't move any further east!";
	}
	else { 
		int y=karte->getCurrentSpaceY();
		int x=karte->getCurrentSpaceX();
		karte->setCurrentSpaceY(++y);
		std::cout << "\nMoved east.";
	}
};

void movement::moveNE(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX() 
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}
	else {
                int x=karte->getCurrentSpaceX();
                int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(++y);
		karte->setCurrentSpaceX(++x);
		std::cout << "\nMove northeast.";
	}
};

void movement::moveNW(map *karte) {
	if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX()
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
        }
	else {
                int x=karte->getCurrentSpaceX();
                int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(--y);
		karte->setCurrentSpaceX(++x);
		std::cout << "\nMoved northwest.";
	}
};

void movement::moveSE(map *karte) {
        if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX()
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
                std::cout << "\nYou can't move any further!";
	}
	else {
                int x=karte->getCurrentSpaceX();
                int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(++y);
		karte->setCurrentSpaceX(--x);
		std::cout << "\nMoved southeast.";
	}
};

void movement::moveSW(map *karte) {
        if (karte->getCurrentSpaceY()==karte->getMapMaxSizeY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeX()
       || karte->getCurrentSpaceY()==karte->getMapMaxSizeNgY() || karte->getCurrentSpaceX()==karte->getMapMaxSizeNgX()) {
		std::cout << "\nYou can't move any further!";
	}
	else {
		int x=karte->getCurrentSpaceX();
		int y=karte->getCurrentSpaceY();
		karte->setCurrentSpaceY(--y);
		karte->setCurrentSpaceX(--x);
		std::cout << "\nMoved southwest.";
	}
};
	
// look(): look command
void movement::look(map *karte) {
	std::string groundType; // this is the ground type
	int gID=(karte->getGroundID());
	
	switch (gID) {
		case 1: groundType="grass"; break;
		case 2: groundType="pavement"; break;
		case 3: groundType="water"; break;
		default: groundType="grass"; break;
	}
	
	if (karte->itemExists(karte,karte->getCurrentSpaceX(),karte->getCurrentSpaceY())) {
		std::string theName=karte->identifyItem(karte);
		std::cout << "\nYou see a " << theName << ".\n";
	}
	else
		std::cout << "\nYou see " << groundType << ".";
	// If there is an item on the ground, then display item instead
	// of ground type. (Do this later)
};

void movement::placeItem(item *thisItem,map *karte) {
	int itemX=(thisItem->getLocationX());
	int itemY=(thisItem->getLocationY());
	karte->addItemX(thisItem,itemX);
	karte->addItemY(thisItem,itemY);
};

void movement::removeItem(item *thisItem,map *karte) {
	int itemX=(thisItem->getLocationX());
	int itemY=(thisItem->getLocationY());
	karte->removeItemX(itemX);
	karte->removeItemY(itemY);
};

int movement::getCurrentPosition(map *karte) const {
	int x=karte->getCurrentSpaceX();
	int y=karte->getCurrentSpaceY();
	std::cout << "X: " << x << " Y: " << y << std::endl;
};

void movement::spawnMapItems(movement *rhs,map *karte) {
	item *plant0=new item("fern",1,2,npe);
	rhs->placeItem(plant0,karte);

	item *rock0=new item("rock",-1,-1,npe);
	rhs->placeItem(rock0,karte);

	item *plant1=new item("herb",-2,3,npe);
	rhs->placeItem(plant1,karte);

	item *plant2=new item("bush",-10,5,npe);
	rhs->placeItem(plant2,karte);

	item *plant3=new item("sunflowers",20,5,npe);
	rhs->placeItem(plant3,karte);

	item *equip=new item("Leather_Armor",4,6,torso);
	rhs->placeItem(equip,karte);
};

int movement::controlTime(int steps) {
	if (steps==500) { // toggle day/night now
		if (!fDay) { // if it is night
			std::cout << "\nIt is now day time.\n";
			stepCount=0;
			fDay=true;
			return 0;
		}
		if (fDay) { // if it is day
			std::cout << "\nIt is now night.\n";
			stepCount=0;
			fDay=false;
			return 0;
		}
	}

	if (steps!=500) // leave it at the current time
		stepCount++; // increment player steps
};

void movement::checkTime() {
	if (fDay)
		std::cout << "\nIt is day time.\n";
	if (!fDay)
		std::cout << "\nIt is night time.\n";
};

