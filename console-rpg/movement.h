// movement.h: holds movement system stuff
#include <iostream>

class movement {
	public:
		movement(int defaultX, int defaultY); // our constructor
		~movement() {};

		// movement methods
		void moveN();
		void moveS();
		void moveW();
		void moveE();
		void moveNE();
		void moveNW();
		void moveSE();
		void moveSW();

		// public accessors
		signed int getCurrentPosition() const {std::cout << "\nX: " << currentSquareX << ". Y: " << currentSquareY;}
		signed int getMapMaxSizeX() const {return MapMaxSizeX;}
		signed int getMapMaxSizeY() const  {return MapMaxSizeY;}
		
	private:
		signed int MapMaxSizeX, MapMaxSizeY, MapMaxSizeNgX, MapMaxSizeNgY;
		signed int currentSquareX, currentSquareY;
};

movement::movement(int defaultX=0, int defaultY=0) {
	currentSquareX=defaultX;
	currentSquareY=defaultY;
	MapMaxSizeX=15, MapMaxSizeY=15, MapMaxSizeNgX=(-15), MapMaxSizeNgY=(-15);
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
		std::cout << "\nMove north-east.";
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
		std::cout << "\nMoved north-west.";
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
		std::cout << "\nMoved south-east.";
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
		std::cout << "\nMoved south-west.";
	}
};

