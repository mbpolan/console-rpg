#include <qimage.h>
#include <qpixmap.h>
#include <qpalette.h>
#include <qpainter.h>
#include <qtabwidget.h>
#include <qtable.h>
#include <qdockwindow.h>

#include "tiles.dat"

#include "toolbox.h"
#include "tile.h"

const int HEIGHT=530;
const int WIDTH=135;

toolBox::toolBox(QWidget *parent,const char *name): QWidget(parent,name) {        
    setMinimumSize(WIDTH,HEIGHT);
    mainFrame=new QTabWidget(this);
    
    mainFrame->setMinimumSize(WIDTH,HEIGHT);
    
    QPixmap grassTile=QPixmap(grass);
    QPixmap waterTile=QPixmap(water);

    ///////////////////////////////
    // Start tile tab table
    ///////////////////////////////
    items=new QTable(TILES_DAT_TILE_COUNT,1,this,"item_box");
    
    items->setTopMargin(0);
    items->setLeftMargin(0);
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++)
	items->setRowHeight(i,32);
    
    items->setColumnWidth(1,128);
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++) {
	    for (int j=0;j<1;j++)
		items->setItem(i,j,(new tile(0,items)));
    }      
    
    connect(items,SIGNAL(clicked(int,int,int,const QPoint&)),SLOT(highliteCell(int,int)));
    connect(items,SIGNAL(clicked(int,int,int,const QPoint&)),this,SLOT(broadcastNewTile(int)));
    
    items->setText(0,0,"Grass");
    items->setPixmap(0,0,grassTile);
    items->setText(1,0,"Water");
    items->setPixmap(1,0,waterTile);
    
    items->setShowGrid(true);
    items->setTopMargin(0);
    items->setLeftMargin(0);
    
    mainFrame->addTab(items,"Tiles");
    
    ///////////////////////////////
    // Start object tab table
    ///////////////////////////////
    
   objects=new QTable(TILES_DAT_OBJECT_COUNT,1,this,"objects"); 
   
    objects->setTopMargin(0);
    objects->setLeftMargin(0);
    
    for (int i=0;i<TILES_DAT_OBJECT_COUNT;i++)
	objects->setRowHeight(i,32);
    
    objects->setColumnWidth(1,128);
    
    for (int i=0;i<TILES_DAT_OBJECT_COUNT;i++) {
	for (int j=0;j<1;j++) {		
		objects->setItem(i,j,(new tile(i+1,objects)));
		objects->setText(i,j,tile::parseIDToName(i+1).c_str());
	}
    }     
    
    connect(objects,SIGNAL(clicked(int,int,int,const QPoint&)),this,SLOT(broadcastNewObj(int,int)));
    
    mainFrame->addTab(objects,"Objects");
    
};

// broadcast a signal when a tile was clicked
void toolBox::broadcastNewTile(int row) {
    if (row==0)
	emit tileChanged(0);
    if (row==1)
	emit tileChanged(-1);
};

// broadcast a signal when an object was clicked
void toolBox::broadcastNewObj(int row,int col) {
    QTableItem *Tile=objects->item(row,col);
 
    int _id;
    if (Tile && Tile->rtti()==1001)
	_id=((tile*) (Tile))->getID();
    
    emit objChanged(_id);
};

// slot to highlight a cell (TODO)
void toolBox::highliteCell(int row,int col) {
    return;
};

// slot to control toolbox docking
void toolBox::dockSidebar(bool t) {
    ((QDockWindow*) parent())->setMovingEnabled(t);
};
