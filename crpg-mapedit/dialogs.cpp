/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
 *   kanadakid@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <ctype.h>

#include "dialogs.h"
#include "tile.h"
#include "tiles.dat"

// newDialog constructor
newDialog::newDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setSizeGripEnabled(false);
    setModal(true);
    setCaption("New map");    
    
    grid=new QGridLayout(this,4,3);
    grid->setMargin(5);
    grid->setResizeMode(QLayout::Fixed);        
    
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
    grid->addMultiCellWidget(title,0,0,0,2);
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
    grid->setMargin(5);
    grid->setResizeMode(QLayout::Fixed);        
    
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
    grid->setMargin(5);
    grid->setResizeMode(QLayout::Fixed);        
    
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

// init dialog constructor
initDialog::initDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Loading...");
    grid=new QGridLayout(this,1,1);
    grid->setMargin(5);
    grid->setResizeMode(QLayout::Fixed);
    
    msg=new QLabel("Loading map editor... Please wait.",this);
    msg->setFont(QFont("Times",16,QFont::Bold));
    grid->addWidget(msg,0,0);
};

// gen dialog constructor
genDialog::genDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Generating map");    
    setModal(true);
    
    grid=new QGridLayout(this,1,1);
    grid->setMargin(5);
    grid->setResizeMode(QLayout::Fixed);    
    
    msg=new QLabel("Generating map",this);
    msg->setFont(QFont("Times",16,QFont::Normal));
    grid->addWidget(msg,0,0);
};

// dialog displayed when making a new npc
makeNpcDialog::makeNpcDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Make NPC");
    grid=new QGridLayout(this,6,2);
    grid->setMargin(5);
    grid->setResizeMode(QLayout::Fixed);    
    
    intro=new QLabel("Make an NPC first by supplying a name and health.\n" 
		     "Click OK to place it on the map."
		     "\n-----------------------------------------------------------------------------------------",this);
    
    nameLab=new QLabel("NPC Name",this);
    healthLab=new QLabel("NPC Health",this);
    mpLab=new QLabel("NPC Magic Points",this);
    
    nameEdit=new QLineEdit(this);
    healthEdit=new QLineEdit(this);
    mpEdit=new QLineEdit(this);
    
    okButton=new QPushButton("OK",this);
    cancelButton=new QPushButton("Cancel",this);
    cancelButton->setMaximumSize(okButton->width(),okButton->height());
    
    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    
    // add our intro label from col 0 to 1
    grid->addMultiCellWidget(intro,0,0,0,1);
    grid->setRowSpacing(1,5);
    
    // add name labels
    grid->addWidget(nameLab,2,0);
    grid->addWidget(healthLab,3,0);   
    grid->addWidget(mpLab,4,0);
    
    // add line edits
    grid->addWidget(nameEdit,2,1);
    grid->addWidget(healthEdit,3,1);
    grid->addWidget(mpEdit,4,1);
    
    // finally, add our buttons
    grid->addWidget(okButton,5,0);
    grid->addWidget(cancelButton,5,1);
};

editNpcDialog::editNpcDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Edit NPC");
    grid=new QGridLayout(this,5,2);
    grid->setMargin(5);
    grid->setResizeMode(QLayout::Fixed);
    
    // set some spacing
    grid->setSpacing(5);
    
    intro=new QLabel("Edit this NPC.",this);
    nameLab=new QLabel("NPC Name",this);
    healthLab=new QLabel("NPC Health",this);
    mpLab=new QLabel("NPC Magic Points",this);
    
    nameEdit=new QLineEdit(this);
    healthEdit=new QLineEdit(this);
    mpEdit=new QLineEdit(this);
    
    okButton=new QPushButton("OK",this);
    cancelButton=new QPushButton("Cancel",this);
    
    connect(okButton,SIGNAL(clicked()),SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),SLOT(reject()));
    
    // add our new widgets
    grid->addMultiCellWidget(intro,0,0,0,1);
    grid->setRowSpacing(0,10);
    grid->addWidget(nameLab,1,0);
    grid->addWidget(healthLab,2,0);
    grid->addWidget(mpLab,3,0);
    
    grid->addWidget(nameEdit,1,1);
    grid->addWidget(healthEdit,2,1);
    grid->addWidget(mpEdit,3,1);
    
    grid->setRowSpacing(4,40);
    grid->addWidget(okButton,4,0);
    grid->addWidget(cancelButton,4,1);    
};
