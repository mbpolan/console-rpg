#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qpushbutton.h>

#include "tiles.dat"

#include "dialogs.h"
#include "tile.h"

fillDialog::fillDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Fill");
    grid=new QGridLayout(this,3,2,2);
    
    title=new QLabel("Fill map",this,"title");
    title->setFont(QFont("Times",14,QFont::Bold));
    
    fillExp=new QLabel("Fill map with",this,"fillExp");
    
    tileCB=new QComboBox(false,this,"tileCB");
    
    for (int i=0;i<TILES_DAT_TILE_COUNT;i++)
	tileCB->insertItem(tile::parseIDToName(i));
    
    for (int i=2;i<TILES_DAT_OBJECT_COUNT+1;i++)
	tileCB->insertItem(tile::parseIDToName(i));
    
    okButton=new QPushButton("Fill",this);
    cancelButton=new QPushButton("Cancel",this);
    
    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    
    grid->addMultiCellWidget(title,0,0,0,2);
    grid->addWidget(fillExp,1,0);
    grid->addWidget(tileCB,1,1);
    
    grid->addWidget(okButton,2,0);
    grid->addWidget(cancelButton,2,1);
};
