// items.h: holds item class and declarations
#include <iostream>

#ifndef _nItems
#define _nItems

enum TYPE {head,torso,legs,boots,npe};

class item {
	public:
		item();
		item(std::string,int,int,TYPE); // our constructor
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
		TYPE itemTYPE;
};

#endif

