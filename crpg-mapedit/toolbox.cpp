#include <qtable.h>
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

    QPixmap grassTile=QPixmap(grass);
    QPixmap waterTile=QPixmap(water);
    
    mainFrame->setMinimumSize(WIDTH,HEIGHT);

    ///////////////////////////////
    // Start tile tab table
    ///////////////////////////////
    items=new QTable(TILES_DAT_TILE_COUNT,1,this,"item_box");
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++)
	items->setRowHeight(i,32);
    
    items->setColumnWidth(0,128);
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++) {
	for (int j=0;j<1;j++)
	    items->setItem(i,j,(new tile("mapTile",items)));
    }
    
    connect(items,SIGNAL(clicked(int,int,int,const QPoint&)),SLOT(highliteCell(int,int)));
    connect(items,SIGNAL(clicked(int,int,int,const QPoint&)),this,SLOT(broadcastNewTile(int,int)));
    
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
    
    objects->setColumnWidth(0,128);
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++) {
	for (int j=0;j<1;j++)
	    objects->setItem(i,j,(new tile("mapTile",items)));
    }    
    
   QPixmap bushObj=QPixmap(bush);
   QPixmap rockObj=QPixmap(rock);
   QPixmap fernObj=QPixmap(fern);
   QPixmap herbObj=QPixmap(herb);        
    
    objects->setText(0,0,"Bush");
    objects->setPixmap(0,0,bushObj);
    objects->setText(1,0,"Rock");
    objects->setPixmap(1,0,rockObj);
    objects->setText(2,0,"Fern");
    objects->setPixmap(2,0,fernObj);
    objects->setText(3,0,"Herb");
    objects->setPixmap(3,0,herbObj);
    
    connect(objects,SIGNAL(clicked(int,int,int,const QPoint&)),this,SLOT(broadcastNewObj(int,int)));
    
    mainFrame->addTab(objects,"Objects");
    
};

void toolBox::broadcastNewTile(int row,int col) {
    emit tileChanged(row,col);
};

void toolBox::broadcastNewObj(int row,int col) {
    emit objChanged(row,col);
};

void toolBox::highliteCell(int row,int col) {
};
