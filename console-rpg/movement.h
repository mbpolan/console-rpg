// movement.h: holds movement system and map stuff
#include <iostream>

class movement { 
	public:
		movement(int defaultX, int defaultY); // our constructor
		virtual ~movement() {};

		// movement methods
		void moveN();
		void moveS();
		void moveW();
		void moveE();
		void moveNE();
		void moveNW();
		void moveSE();
		void moveSW();

		// other methods
		void look(movement*);
		void placeItem(item*, movement*);

		// public accessors
		signed int getCurrentPosition() const {std::cout << "\nX: " << currentSquareX << ". Y: " << currentSquareY;}
		signed int setItemSquareX(int itemXLocation) {itemSquareX=itemXLocation;}
		signed int setItemSquareY(int itemYLocation) {itemSquareY=itemYLocation;}
		signed int getGroundID() const {return groundID;}
		signed int getMapMaxSizeX() const {return MapMaxSizeX;}
		signed int getMapMaxSizeY() const  {return MapMaxSizeY;}
		
	private:
		signed int MapMaxSizeX, MapMaxSizeY, MapMaxSizeNgX, MapMaxSizeNgY;
		signed int currentSquareX, currentSquareY;
		signed int itemSquareX, itemSquareY, groundID;
};

movement::movement(int defaultX=0, int defaultY=0) {
	currentSquareX=defaultX;
	currentSquareY=defaultY;
	MapMaxSizeX=30, MapMaxSizeY=30, MapMaxSizeNgX=(-30), MapMaxSizeNgY=(-30);
	groundID=0; // for now, make the ground grass
};

void movement::moveN() {
	if (currentSquareX==MapMaxSizeX) {
		std::cout << "\nYou can't move any further north!";
	}
	else {
		currentSquareX++;
		std::cout << "\nMoved North.";
	}
};

void movement::moveS() {
	if (currentSquareX==MapMaxSizeNgX) {
		std::cout << "\nYou can't move any further south!";
	}
	else {
		currentSquareX--;
		std::cout << "\nMoved south.";
	}
};

void movement::moveW() {
	if (currentSquareY==MapMaxSizeNgY) {
		std::cout << "\nYou can't move any further west!";
	}
	else {
		currentSquareY--;
		std::cout << "\nMoved west.";
	}
};

void movement::moveE() {
	if (currentSquareY==MapMaxSizeY)  {
		std::cout << "\nYou can't move any further east!";
	}
	else { 
		currentSquareY++;
		std::cout << "\nMoved east.";
	}
};

void movement::moveNE() {
	if (currentSquareY==MapMaxSizeY || currentSquareX==MapMaxSizeX 
			|| currentSquareY==MapMaxSizeNgY || currentSquareX==MapMaxSizeNgX) {
		std::cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY++;
		currentSquareX++;
		std::cout << "\nMove northeast.";
	}
};

void movement::moveNW() {
	if (currentSquareY==MapMaxSizeY || currentSquareX==MapMaxSizeX
			|| currentSquareY==MapMaxSizeNgY || currentSquareX==MapMaxSizeNgX) {
		std::cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY--;
		currentSquareX++;
		std::cout << "\nMoved northwest.";
	}
};

void movement::moveSE() {
	if (currentSquareY==MapMaxSizeY || currentSquareX==MapMaxSizeNgX 
			|| currentSquareY==MapMaxSizeNgY || currentSquareX==MapMaxSizeNgX) {
		std::cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY++;
		currentSquareX--;
		std::cout << "\nMoved southeast.";
	}
};

void movement::moveSW() {
	if (currentSquareY==MapMaxSizeNgY || currentSquareX==MapMaxSizeNgX 
			|| currentSquareY==MapMaxSizeNgY || currentSquareX==MapMaxSizeNgX) {
		std::cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY--;
		currentSquareX--;
		std::cout << "\nMoved southwest.";
	}
};
	
// look(): look command
void movement::look(movement *gridLocator) {
	std::string groundType; // this is the ground type
	int gID=(gridLocator->getGroundID());
	switch (gID) {
		case 1: groundType="grass"; break;
		case 2: groundType="pavement"; break;
		case 3: groundType="water"; break;
		default: groundType="grass"; break;
	}
	if (currentSquareX==itemSquareX  && currentSquareY==itemSquareY)
		std::cout << "\nThere is an item here...";
	else
		std::cout << "\nYou see " << groundType << ".";
	// If there is an item on the ground, then display item instead
	// of ground type. (Do this later)
};

void movement::placeItem(item *thisItem, movement *rhs) {
	int itemX=(thisItem->getLocationX());
	int itemY=(thisItem->getLocationY());
	rhs->setItemSquareX(itemX);
	rhs->setItemSquareY(itemY);
};

