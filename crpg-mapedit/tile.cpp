#include <qimage.h>
#include <qpixmap.h>
#include <string.h>

#include "tiles.dat"

#include "tile.h"

tile::tile(int _id,QTable *table,EditType ed): QTableItem(table,ed) {
    isItem=false;
    id=_id;
    setPixmap(parseID(id));
};

// parse the id of the item and return the appropriate pixmap
QPixmap tile::parseID(int id) {
    QPixmap pic;
    
    switch(id) {
       case 0: pic=QPixmap(grass);break;
       case (-1): pic=QPixmap(water);break;
	   
       case 0x01: pic=QPixmap(bush);break;
       case 0x02: pic=QPixmap(rock);break;
       case 0x03: pic=QPixmap(sunflowers);break;	   
       case 0x04: pic=QPixmap(fern);break;
       case 0x05: pic=QPixmap(herb);break;
       case 0x06: pic=QPixmap(puddle);break;
       }
    
    return pic;
};

void tile::setPic(int _id) {
    id=_id;
    setPixmap(tile::parseID(_id));
};
