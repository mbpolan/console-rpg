// map.h: map class and related stuff
#include <iostream>

const int max=30;

class map {
	public:
		map(int,int,int,int);
		virtual ~map();
		
		int getCurrentSpaceX() const {return currentSquareX;}
		int getCurrentSpaceY() const {return currentSquareY;}
		void setCurrentSpaceX(int x) {currentSquareX=x;}
		void setCurrentSpaceY(int y) {currentSquareY=y;}

		int getMapMaxSizeX() const {return MapMaxSizeX;}
		int getMapMaxSizeY() const {return MapMaxSizeY;}
		int getMapMaxSizeNgX() const {return MapMaxSizeNgX;}
		int getMapMaxSizeNgY() const {return MapMaxSizeNgY;}

		void addItemX(item*,int);
		void addItemY(item*,int);
		void removeItemX(int);
		void removeItemY(int);

		bool itemExists(map*,int,int);
		std::string identifyItem(map*);
		TYPE checkItemType(map*);
		int getGroundID() const {return groundID;}
		
		
	private:
		int MapMaxSizeX,MapMaxSizeY,MapMaxSizeNgY,MapMaxSizeNgX;
		int currentSquareX,currentSquareY, groundID;
		int itemSquareX[30],itemSquareY[30];
		int itemSquareNgX[30],itemSquareNgY[30];
		item *itemLineX[max];
		item *itemLineY[max];
		item *itemLineNgX[max];
		item *itemLineNgY[max];
};

