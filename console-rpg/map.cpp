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

map::~map() {};
