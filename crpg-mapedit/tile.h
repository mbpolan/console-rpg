#ifndef groundtile_h
#define groundtile_h

#include <qtable.h>

class QTable;

class tile: public QTableItem {
       public:
	   tile(const char *tileName,QTable *table, EditType ed=QTableItem::Never);
	   
	   QPixmap getGroundTile() const {return groundTile;}
	   
       private:
	   QPixmap groundTile;
	   
};

#endif
