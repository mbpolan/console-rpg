#include <qimage.h>
#include <qpixmap.h>

#include "maptable.h"
#include "tile.h"

#include "tiles.dat"

mapTable::mapTable(int row,int col,QWidget *parent,const char *name): QTable(row,col,parent,name) {
    grassTile=QPixmap(grass);
    rows=row;
    cols=col;
    
    for (int i=0;i<col;i++) {
	setColumnWidth(i,32);
    }
    
    for (int i=0;i<row;i++) {
	setRowHeight(i,32);
    }
    
    for (int i=0;i<row;i++) {
	for (int j=0;j<col;j++) {
	    setItem(i,j,(new tile("grass",this)));
	    setPixmap(i,j,grassTile);
	}
    }
	    
    setColumnMovingEnabled(false);
    setRowMovingEnabled(false);	  
    
    this->setTopMargin(0);
    this->setLeftMargin(0);
    
    // if a tile was clicked on the map, update it
    connect(this,SIGNAL(clicked(int,int,int,const QPoint&)),SLOT(updateTile(int,int)));
};

void mapTable::resync(int row,int col) {
    rows=row;
    cols=col;
    
    for (int i=0;i<row;i++)
	setRowHeight(i,32);
    
    for (int i=0;i<col;i++)
	setColumnWidth(i,32);
};

void mapTable::redraw() {
        for (int i=0;i<rows;i++) {
	for (int j=0;j<cols;j++) {
	    setItem(i,j,(new tile("grass",this)));
	    setPixmap(i,j,grassTile);
	}
    }
};

void mapTable::clear() {
    for (int i=0;i<numRows();i++) {
	for (int j=0;j<numCols();j++)
	clearCell(i,j);
    }
}

void mapTable::enableGrid(bool t) {
    if (t) {
	setShowGrid(true);
    }
    
    else
	setShowGrid(false);
};

void mapTable::registerTile(int row,int col) {
    grassTile=QPixmap(grass);
    waterTile=QPixmap(water);
    
    if (row==0 && col==0)
	regTile=grassTile;
    
    if (row==1 && col==0)
	regTile=waterTile;
    
    else 
	regTile=grassTile;
};

void mapTable::updateTile(int row,int col) {
    setPixmap(row,col,regTile);
    updateCell(row,col);
    
    emit tileClicked(row,col);
};
