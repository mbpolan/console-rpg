#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <ctype.h>

#include "tiles.dat"

#include "dialogs.h"
#include "tile.h"

// newDialog constructor
newDialog::newDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setSizeGripEnabled(false);
    setModal(true);
    setCaption("New map");    
    
    grid=new QGridLayout(this,4,3);
    
    title=new QLabel("Make a new map.",this,"title");
    title->setFont(QFont("Times",14,QFont::Bold));
    
    sizeX=new QLabel("X Size",this);
    sizeY=new QLabel("Y Size",this);
    
    sizeEditX=new QLineEdit(this,"sizeEditX");
    sizeEditY=new QLineEdit(this,"sizeEditY");
    
    okButton=new QPushButton("&OK",this);
    cancelButton=new QPushButton("&Cancel",this);
    
    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    
    // syntax is rows then columns
    grid->addWidget(title,0,0);
    grid->addWidget(sizeX,1,0);
    grid->addWidget(sizeY,2,0);
    
    grid->addWidget(sizeEditX,1,1);
    grid->addWidget(sizeEditY,2,1);
    grid->addWidget(okButton,1,2);
    grid->addWidget(cancelButton,2,2);
};

// goToDialog constructor
goToDialog::goToDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Go to Tile");
    
    grid=new QGridLayout(this,3,3);
    
    goButton=new QPushButton("&Go",this,"goButton");
    cancelButton=new QPushButton("&Cancel",this,"cancelButton");
    
    title=new QLabel("Go to Tile",this,"title");
    title->setFont(QFont("Times",14,QFont::Bold));
    
    trow=new QLabel("Position on X",this,"trow");
    tcol=new QLabel("Position on Y",this,"tcol");
    
    lineRow=new QLineEdit(this,"lineRow");
    lineCol=new QLineEdit(this,"lineCol");
    
    grid->addMultiCellWidget(title,0,0,0,2);
    grid->addWidget(trow,1,0);
    grid->addWidget(tcol,2,0);
    
    grid->addWidget(lineRow,1,1);
    grid->addWidget(lineCol,2,1);
    grid->addWidget(goButton,1,2);
    grid->addWidget(cancelButton,2,2);
    
    connect(goButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
};

// fill dialog constructor
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

initDialog::initDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Loading...");
    setMinimumSize(230,20);
    
    msg=new QLabel("Loading map editor... Please wait.",this);
    msg->setFont(QFont("Times",16,QFont::Bold));
    msg->setMinimumSize(230,20);
};
