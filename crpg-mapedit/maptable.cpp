#include <qapplication.h>
#include <qimage.h>
#include <qaction.h>
#include <qpopupmenu.h>
#include <qpixmap.h>
#include <qeventloop.h>
#include <qcombobox.h>
#include <sstream>

#include "tiles.dat"

#include "dialogs.h"
#include "maptable.h"
#include "tile.h"

mapTable::mapTable(int row,int col,QWidget *parent,const char *name): QTable(row,col,parent,name) {
    pen1=true;
    pen2=false;
    pen3=false;
    pen5=false;
    
    regTileID=0;   
    regTile=tile::parseID(0);
    rows=row;
    cols=col;
    
    removeItemAct=new QAction(tr("Remove items"),tr(""),this);
    removeItemAct->setEnabled(false);
    
    for (int i=0;i<col;i++) {
	setColumnWidth(i,32);
    }
    
    for (int i=0;i<row;i++) {
	setRowHeight(i,32);
    }
    
    for (int i=0;i<row;i++) {
	for (int j=0;j<col;j++)
	    setItem(i,j,(new tile(0,this)));
    }
    
    setColumnMovingEnabled(false);
    setRowMovingEnabled(false);	  
    
    this->setTopMargin(0);
    this->setLeftMargin(0);
    
    // if a tile was clicked on the map, update it
    connect(this,SIGNAL(clicked(int,int,int,const QPoint&)),SLOT(updateTile(int,int)));
};

// resync the rows and columns
void mapTable::resync(int row,int col) {
    rows=row;
    cols=col;
    
    for (int i=0;i<row;i++)
	setRowHeight(i,32);
    
    for (int i=0;i<col;i++)
	setColumnWidth(i,32);
};

// redraw the entire map
void mapTable::redraw() {    
    for (int i=0;i<rows;i++) {
	for (int j=0;j<cols;j++) {
	    setItem(i,j,(new tile(0,this)));
	}
	qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
    }
};

// clear all cells
void mapTable::clear() {
    for (int i=0;i<numRows();i++) {
	for (int j=0;j<numCols();j++)
	    clearCell(i,j);
    }
}

// enable to grid on the map
void mapTable::enableGrid(bool t) {
    if (t) {
	setShowGrid(true);
    }
    
    else
	setShowGrid(false);
};

// set which tile the pen should use
void mapTable::registerTile(int _id) {
    regTileID=_id;
    regTile=tile::parseID(_id);
};

// set which items the pen should use
// TODO: rewrite this to load data from the .dat file
void mapTable::registerObj(int _id) {
    regTileID=_id;
    regTile=tile::parseID(_id);
};

// update a tile on the map
void mapTable::updateTile(int row,int col) {
    // if pen 1x1 is set
    if (pen1) {
	fillSelection(regTileID,row,row+1,col,col+1);
    }
    
    // if pen 2x2 is set
    if (pen2)
	fillSelection(regTileID,row,row+2,col,col+2);
    
    // if pen 3x3 is set
    if (pen3)
	fillSelection(regTileID,row-1,row+2,col-1,col+2);
    
    // if pen 5x5 is set
    if (pen5)
	fillSelection(regTileID,row-2,(row-2)+5,col-2,(col-2)+5);
    
    // broadcast that this tile was clicked
    emit tileClicked(row,col);
};

// method for setting the pen to 1x1
void mapTable::setPenTo1() {
    pen1=true;
    pen2=false;
    pen3=false;
    pen5=false;
};

// method for setting the pen to 2x2
void mapTable::setPenTo2() {
    pen2=true;
    pen1=false;
    pen3=false;
    pen5=false;
};

// method for setting the pen to 3x3
void mapTable::setPenTo3() {
    pen3=true;
    pen1=false;
    pen2=false;
    pen5=false;
};

// method to set the pen to 5x5
void mapTable::setPenTo5() {
    pen5=true;
    pen1=false;
    pen2=false;
    pen3=false;
};

// method to spawn the right-click context menu
void mapTable::contextMenuEvent(QContextMenuEvent *p) {
    QPopupMenu context(this);
    removeItemAct->addTo(&context);
    context.exec(p->globalPos());
};

// method for fillin a range of tiles
void mapTable::fillSelection(int id,int start_row,int end_row,int start_col,int end_col) {
    for (int i=start_row;i<end_row;i++) {
	for (int j=start_col;j<end_col;j++)
	    setItem(i,j,(new tile(id,this)));
	
	qApp->processEvents();
    }
};

// the fill command dialog and actions
void mapTable::fillMap() {
    fill_Dialog=new fillDialog;
    
    fill_Dialog->show();
    fill_Dialog->raise();
    fill_Dialog->setActiveWindow();
    
    if (fill_Dialog->exec()) {
	int item=fill_Dialog->tileCB->currentItem();
	
	for (int i=0;i<numRows();i++) {
	    for (int j=0;j<numCols();j++)
		setItem(i,j,(new tile(item,this)));
	    qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
	}
    }
    
    delete fill_Dialog;
};
