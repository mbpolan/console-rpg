#include <iostream>
using namespace std;

class movement {
	public:
		movement(int defaultX, int defaultY);
		~movement() {};
		void moveN();
		void moveS();
		void moveW();
		void moveE();
		signed int getCurrentPosition() const {cout << "\nX: " << currentSquareX << ". Y: " << currentSquareY;}
		signed int getMapMaxSizeX() const {return MapMaxSizeX;}
		signed int getMapMaxSizeY() const  {return MapMaxSizeY;}
	private:
		signed int MapMaxSizeX, MapMaxSizeY, MapMaxSizeNgX, MapMaxSizeNgY;
		signed int currentSquareX, currentSquareY;
};

//movement::movement(): MapMaxSizeX(15), MapMaxSizeY(15), MapMaxSizeNgY(-15), MapMaxSizeNgX(-15) {};

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
