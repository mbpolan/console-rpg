#include <qimage.h>
#include <qpixmap.h>
#include <string.h>

#include "tile.h"

//#include "tiles/grass.xpm"

tile::tile(const char *tileName,QTable *table,EditType ed): 
	QTableItem(table,ed) {
    
/*    if (strcmp(tileName,"grass")==0)
	groundTile=QPixmap(grass);
    
    else
	groundTile=QPixmap(grass);*/
};
