// items.h: holds item class and declarations
#include <iostream>

class item {
	public:
		item(std::string fixedItemName, int spawnX, int spawnY); // our constructor
		~item();

		void setLocationX(int);
		void setLocationY(int);
		void setItemID(int);
		void setItemName(std::string nameOfItem) {*itemName=nameOfItem;}
		
		int getLocationX() const {return *itemLocationX;}
		int getLocationY() const {return *itemLocationY;}
		std::string getItemName() const {return *itemName;}
		int getItemID() const {return *itemID;}

	private:
		int *itemLocationX;
		int *itemLocationY;
		int *itemID;
		std::string *itemName;
};


