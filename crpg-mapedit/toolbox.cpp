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
    
    
    mainFrame->setMinimumSize(WIDTH,HEIGHT);

    items=new QTable(TILES_DAT_TILE_COUNT,1,this,"item_box");
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++)
	items->setRowHeight(i,32);
    
    for (int i=0;i<1;i++)
	items->setColumnWidth(i,128);
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++) {
	for (int j=0;j<1;j++)
	    items->setItem(i,j,(new tile("mapTile",items)));
    }
    
    connect(items,SIGNAL(clicked(int,int,int,const QPoint&)),SLOT(highliteCell(int,int)));
    connect(items,SIGNAL(clicked(int,int,int,const QPoint&)),this,SLOT(broadcastNewTile(int,int)));
    
    QPixmap grassTile=QPixmap(grass);
    QPixmap waterTile=QPixmap(water);
    
    items->setText(0,0,"Grass");
    items->setPixmap(0,0,grassTile);
    items->setText(1,0,"Water");
    items->setPixmap(1,0,waterTile);
    
    items->setShowGrid(true);
    items->setTopMargin(0);
    items->setLeftMargin(0);
    
    mainFrame->addTab(items,"Tiles");
    
};

void toolBox::broadcastNewTile(int row,int col) {
    emit tileChanged(row,col);
};

void toolBox::highliteCell(int row,int col) {
};
