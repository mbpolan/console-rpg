// map.h: map class and related stuff
#include <iostream>
#include <list>

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

		int getItemSquareX();
		int getItemSquareY();
		void setItemSquareX(int x);
		void setItemSquareY(int y);

		int getGroundID() const {return groundID;}
		
	private:
		int MapMaxSizeX,MapMaxSizeY,MapMaxSizeNgY,MapMaxSizeNgX;
		int currentSquareX,currentSquareY;
		int /*itemSquareX,itemSquareY,*/groundID;
		std::list<int> itemSquareX;
		std::list<int> itemSquareY;
};


