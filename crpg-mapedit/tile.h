#ifndef tile_h
#define tile_h

#include <qtable.h>

class QTable;

class tile: public QTableItem {
       public:
	   tile(const char *tileName,QTable *table, EditType ed=QTableItem::Never);
	   
	   QPixmap getGroundTile() const {return groundTile;}
	   void setID(int _id) {id=_id;}
	   void setItem(bool t) {isItem=t;}
	   
       private:
	   QPixmap groundTile;
	   bool isItem;
	   int id;
	   
};

#endif
