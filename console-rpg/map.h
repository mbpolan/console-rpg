#include <iostream>

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

		int getItemSquareX() const {return itemSquareX;}
		int getItemSquareY() const {return itemSquareY;}
		void setItemSquareX(int x) {itemSquareX=x;}
		void setItemSquareY(int y) {itemSquareY=y;}

		int getGroundID() const {return groundID;}
		
	private:
		int MapMaxSizeX,MapMaxSizeY,MapMaxSizeNgY,MapMaxSizeNgX;
		int currentSquareX,currentSquareY;
		int itemSquareX,itemSquareY,groundID;
};


