// movement.h: holds movement system stuff
#include <iostream>
using namespace std;

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
		signed int getCurrentPosition() const {cout << "\nX: " << currentSquareX << ". Y: " << currentSquareY;}
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
		cout << "\nYou can't move any further north!";
	}
	else {
		currentSquareX++;
		cout << "\nMoved North.";
	}
};

void movement::moveS() {
	if (currentSquareX==MapMaxSizeNgX) {
		cout << "\nYou can't move any further south!";
	}
	else {
		currentSquareX--;
		cout << "\nMoved south.";
	}
};

void movement::moveW() {
	if (currentSquareY==MapMaxSizeNgY) {
		cout << "\nYou can't move any further west!";
	}
	else {
		currentSquareY--;
		cout << "\nMoved west.";
	}
};

void movement::moveE() {
	if (currentSquareY==MapMaxSizeY)  {
		cout << "\nYou can't move any further east!";
	}
	else { 
		currentSquareY++;
		cout << "\nMoved east.";
	}
};

void movement::moveNE() {
	if ((currentSquareY==MapMaxSizeY || currentSquareX==MapMaxSizeX)) {
		cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY++;
		currentSquareX++;
		cout << "\nMove north-east.";
	}
};

void movement::moveNW() {
	if (currentSquareY==MapMaxSizeY || currentSquareX==MapMaxSizeX) {
		cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY--;
		currentSquareX++;
		cout << "\nMoved north-west.";
	}
};

void movement::moveSE() {
	if (currentSquareY==MapMaxSizeY || currentSquareX==MapMaxSizeNgX) {
		cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY++;
		currentSquareX--;
		cout << "\nMoved south-east.";
	}
};

void movement::moveSW() {
	if (currentSquareY==MapMaxSizeNgY || currentSquareX==MapMaxSizeNgX) {
		cout << "\nYou can't move any further!";
	}
	else {
		currentSquareY--;
		currentSquareX--;
		cout << "\nMoved south-west.";
	}
};

