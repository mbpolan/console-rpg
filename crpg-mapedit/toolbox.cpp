#include <qimage.h>
#include <qpixmap.h>
#include <qpalette.h>
#include <qpainter.h>
#include <qtabwidget.h>

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
    QPixmap bushObj=QPixmap(bush);
    QPixmap rockObj=QPixmap(rock);
    QPixmap sunflowersObj=QPixmap(sunflowers);
    QPixmap fernObj=QPixmap(fern);
    QPixmap herbObj=QPixmap(herb);      
    QPixmap puddleObj=QPixmap(puddle);

    ///////////////////////////////
    // Start tile tab table
    ///////////////////////////////
    items=new toolBoxTable(TILES_DAT_TILE_COUNT,1,this,"item_box");
    
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
    
   objects=new toolBoxTable(TILES_DAT_OBJECT_COUNT,1,this,"objects"); 
    
    objects->setText(0,0,"Bush");
    objects->setPixmap(0,0,bushObj);
    objects->setText(1,0,"Rock");
    objects->setPixmap(1,0,rockObj);
    objects->setText(2,0,"Sunflowers");
    objects->setPixmap(2,0,sunflowersObj);
    objects->setText(3,0,"Fern");
    objects->setPixmap(3,0,fernObj);
    objects->setText(4,0,"Herb");
    objects->setPixmap(4,0,herbObj);   
    objects->setText(5,0,"Puddle");
    objects->setPixmap(5,0,puddleObj);
    
    connect(objects,SIGNAL(clicked(int,int,int,const QPoint&)),this,SLOT(broadcastNewObj(int)));
    
    mainFrame->addTab(objects,"Objects");
    
};

void toolBox::broadcastNewTile(int row) {
    if (row==0)
	emit tileChanged(0);
    if (row==1)
	emit tileChanged(-1);
};

void toolBox::broadcastNewObj(int row) {
    emit objChanged(row+1);
};

void toolBox::highliteCell(int row,int col) {
    return;
};

/////////////////////////////////////////////////////////////////////////
// Start toolBoxTable code definitions...
/////////////////////////////////////////////////////////////////////////

// generic table used in the toolbox
toolBoxTable::toolBoxTable(int rows,int cols,QWidget *parent,const char *name): QTable(rows,cols,parent,name) {
    setTopMargin(0);
    setLeftMargin(0);
    
    for (int i=0;i<rows;i++)
	setRowHeight(i,32);
    
    for (int i=0;i<cols;i++)
	setColumnWidth(i,128);
    
    for (int i=0;i<rows;i++) {
	    for (int j=0;j<cols;j++)
		setItem(i,j,(new toolBoxTableCell(this)));
    }   
};

// the cell in a toolbox entry
toolBoxTableCell::toolBoxTableCell(QTable *parent): QTableItem(parent,QTableItem::Never) {
};
