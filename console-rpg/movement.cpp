#include "movement.h"

movement::movement(int defaultX=0, int defaultY=0) {
//	groundID=0; // for now, make the ground grass
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
                if (x==karte->getItemSquareX() && y==karte->getItemSquareY())
                        std::cout << itemWarning;
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
	
	if (karte->getCurrentSpaceX()==karte->getItemSquareX() && karte->getCurrentSpaceY()==karte->getItemSquareY())
		std::cout << "\nThere is an item here...";
	else
		std::cout << "\nYou see " << groundType << ".";
	// If there is an item on the ground, then display item instead
	// of ground type. (Do this later)
};

void movement::placeItem(item *thisItem,map *karte) {
	int itemX=(thisItem->getLocationX());
	int itemY=(thisItem->getLocationY());
	karte->setItemSquareX(itemX);
	karte->setItemSquareY(itemY);
};

int movement::getCurrentPosition(map *karte) const {
	int x=karte->getCurrentSpaceX();
	int y=karte->getCurrentSpaceY();
	std::cout << "X: " << x << " Y: " << y << std::endl;
};

