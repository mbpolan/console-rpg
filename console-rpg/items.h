// items.h: holds item class and declarations
#include <iostream>

class item {
	public:
		item(std::string fixedItemName, int spawnX, int spawnY); // our constructor
		~item();

		void setLocationX(int*);
		void setLocationY(int*);
		void setItemID(int*);
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

item::item(std::string fixedItemName, int spawnX, int spawnY) {
	itemLocationX=new int(spawnX);
	itemLocationY=new int(spawnY);
	itemName=new std::string(fixedItemName);
};

item::~item() {
	delete itemLocationX;
	delete itemLocationY;
	delete itemName;
	itemLocationX=0;
	itemLocationY=0;
	itemName=0;
};

void item::setLocationX(int *XLOCATION) {
	if (*XLOCATION==*itemLocationX)
		*itemLocationX==*itemLocationX;
	else
		*itemLocationX==*XLOCATION;
};

void item::setLocationY(int *YLOCATION) {
	if (*YLOCATION==*itemLocationY)
		*itemLocationY==*itemLocationY;
	else
		*itemLocationY==*YLOCATION;
};

