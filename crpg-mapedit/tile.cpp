#include <qimage.h>
#include <qpixmap.h>
#include <string.h>

#include "tile.h"

tile::tile(const char *tileName,QTable *table,EditType ed): QTableItem(table,ed) {
    isItem=false;
    id=-1;
};
