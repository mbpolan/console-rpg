#ifndef tile_h
#define tile_h

#include <qtable.h>
#include <iostream>

class QTable;

class tile: public QTableItem {
       public:
	   tile(int,QTable *table, EditType ed=QTableItem::Never);

	   int getID() const {return id;}
	   void setID(int _id) {id=_id;}
	   void setItem(bool t) {isItem=t;}
	   
	   static QPixmap parseID(int);
	   static std::string parseIDToName(int);
	   void setPic(int); // set the pixmap	
	   
	   virtual int rtti() const {return 1001;}
	   
       private:
	   bool isItem; // is an item here?
	   int id; // item id
	   
};

#endif
