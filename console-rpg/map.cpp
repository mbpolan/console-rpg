// map.cpp: declarations for map functions
#include <iostream>
#include "map.h"

map::map(int X,int Y,int NgY,int NgX) {
	MapMaxSizeX=X;
	MapMaxSizeY=Y;
	MapMaxSizeNgY=NgY;
	MapMaxSizeNgX=NgX;
	currentSquareX=0,currentSquareY=0;
	groundID=0;
};

void map::setItemSquareX(int x) {
	itemSquareX.push_back(x);
};

void map::setItemSquareY(int y) {
	itemSquareY.push_back(y);
};

int map::getItemSquareX() {
	std::list<int>::iterator itemItX;
	for (itemItX=itemSquareX.begin();itemItX!=itemSquareX.end();++itemItX) {
		return *itemItX;
	}
};

int map::getItemSquareY() {
	std::list<int>::iterator itemItY;
	for (itemItY=itemSquareY.begin();itemItY!=itemSquareY.end();++itemItY) {
		return *itemItY;
	}
};

map::~map() {};
