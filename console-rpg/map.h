// map.h: map class and related stuff
#include <iostream>

#include "items.h"

#ifndef map_h
#define map_h

const int max=30; // remove this later

class map {
	public:
		map(int,int,int,int);
		virtual ~map();
		
		// public accessors
		int getCurrentSpaceX() const {return currentSquareX;}
		int getCurrentSpaceY() const {return currentSquareY;}
		void setCurrentSpaceX(int x) {currentSquareX=x;}
		void setCurrentSpaceY(int y) {currentSquareY=y;}
		
		int getMapMaxSizeX() const {return MapMaxSizeX;}
		int getMapMaxSizeY() const {return MapMaxSizeY;}
		int getMapMaxSizeNgX() const {return MapMaxSizeNgX;}
		int getMapMaxSizeNgY() const {return MapMaxSizeNgY;}
		
		// map methods
		void addItemX(item*,int);
		void addItemY(item*,int);
		void removeItemX(int);
		void removeItemY(int);
		
		// misc methods for map
		bool itemExists(map*,int,int);
		std::string identifyItem(map*);
		std::string parseGroundID(int);
		TYPE checkItemType(map*);
		int getGroundID() const {return groundID;}
		int saveMapData();
		int loadMapData();
		
		
	private:
		int MapMaxSizeX,MapMaxSizeY,MapMaxSizeNgY,MapMaxSizeNgX;
		int currentSquareX,currentSquareY, groundID;

		// the item coordinate arrays
		int itemSquareX[max],itemSquareY[max];
		int itemSquareNgX[max],itemSquareNgY[max];

		// the item object arrays
		item *itemLineX[max];
		item *itemLineY[max];
		item *itemLineNgX[max];
		item *itemLineNgY[max];
};

#endif
