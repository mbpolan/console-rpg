// items.h: holds item class and declarations
#include <iostream>

enum TYPE {head,torso,legs,boots};

class item {
	public:
		item(std::string fixedItemName, int spawnX, int spawnY); // our constructor
		virtual ~item();

		void setLocationX(int);
		void setLocationY(int);
		void setItemID(int);
		void setItemName(std::string nameOfItem) {*itemName=nameOfItem;}
		
		int getLocationX() const {return *itemLocationX;}
		int getLocationY() const {return *itemLocationY;}
		std::string getName() const {return *itemName;}
		int getItemID() const {return *itemID;}
		
		bool isHeadItem(item*);
		bool isTorsoItem(item*);
		bool isLegsItem(item*);
		bool isBootsItem(item*);
		
		TYPE checkType();

	private:
		int *itemLocationX;
		int *itemLocationY;
		int *itemID;
		std::string *itemName;
		TYPE itemType;
};


