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

#include <qapplication.h>
#include <qimage.h>
#include <qaction.h>
#include <qpopupmenu.h>
#include <qprogressdialog.h>
#include <qpixmap.h>
#include <qeventloop.h>
#include <qcombobox.h>
#include <qlineedit.h>
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
    penNpc=false;
    
    regTileID=0;   
    regTile=tile::parseID(0);
    rows=row;
    cols=col;
    
    editNpcAct=new QAction(tr("Edit NPC"),tr(""),this);
    editNpcAct->setEnabled(false);
    connect(editNpcAct,SIGNAL(activated()),SLOT(openEditNpc()));
    
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
    connect(this,SIGNAL(contextMenuRequested(int,int,const QPoint&)),SLOT(openContextMenu(int,int,const QPoint&)));
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

void mapTable::registerNpc(QString _name,int _health,int _mp) {
    npcName=_name;
    npcHealth=_health;
    npcMp=_mp;
};

// update a tile on the map
void mapTable::updateTile(int row,int col) {
    // if we are placing an npc
    if (penNpc) {
	placeNpc(row,col);
    }
    
    // if pen 1x1 is set
    if (pen1)
	fillSelection(regTileID,row,row+1,col,col+1);
    
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
    
    // reset the pen
    if (penNpc)
	setPenTo1();
};

// method for setting the pen to 1x1
void mapTable::setPenTo1() {
    pen1=true;
    pen2=false;
    pen3=false;
    pen5=false;
    penNpc=false;    
};

// method for setting the pen to 2x2
void mapTable::setPenTo2() {
    pen2=true;
    pen1=false;
    pen3=false;
    pen5=false;
    penNpc=false;    
};

// method for setting the pen to 3x3
void mapTable::setPenTo3() {
    pen3=true;
    pen1=false;
    pen2=false;
    pen5=false;
    penNpc=false;    
};

// method to set the pen to 5x5
void mapTable::setPenTo5() {
    pen5=true;
    pen1=false;
    pen2=false;
    pen3=false;
    penNpc=false;    
};

void mapTable::setNpcPen() {
    penNpc=true;    
    pen1=false;
    pen2=false;
    pen3=false;
    pen5=false;
};

// method to spawn the right-click context menu
void mapTable::openContextMenu(int row,int col,const QPoint &p) {
    QPopupMenu context(this);
    editNpcAct->addTo(&context);
    removeItemAct->addTo(&context);
    
    // check if an npc is here. if yes, then enable editNpcAct
    QTableItem *Tile=item(row,col);
    if (Tile && ((tile*) Tile)->hasNpc())
	editNpcAct->setEnabled(true);
    else
	editNpcAct->setEnabled(false);
    
    cxMenuRow=row;
    cxMenuCol=col;
    
    context.exec(p);
};

// method for fillin a range of tiles
void mapTable::fillSelection(int id,int start_row,int end_row,int start_col,int end_col) {
    for (int i=start_row;i<end_row;i++) {
	for (int j=start_col;j<end_col;j++)
	    setItem(i,j,(new tile(id,this)));
	
	qApp->processEvents();
    }
};

// method for placing npcs
void mapTable::placeNpc(int row,int col) {
    setItem(row,col,(new tile(0,true,npcName,npcHealth,npcMp,this)));
};

// the fill command dialog and actions
void mapTable::fillMap() {
    fill_Dialog=new fillDialog;
    
    fill_Dialog->show();
    fill_Dialog->raise();
    fill_Dialog->setActiveWindow();
    
    if (fill_Dialog->exec()) {
	int item=fill_Dialog->tileCB->currentItem();
	
	QProgressDialog progress("Filling map...",0,numRows(),this,"fillMapDialog",true);
	progress.setMinimumDuration(0);
	
	for (int i=0;i<numRows();i++) {
	    for (int j=0;j<numCols();j++) {
		progress.setProgress(i);
		setItem(i,j,(new tile(item,this)));
	    }
	    
	    qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
	}
    }
    
    delete fill_Dialog;
};

// slot to open the npc dialog and modify an npc
void mapTable::openEditNpc() {
    eNpc_Dialog=new editNpcDialog(this);
    std::stringstream ss;
    
    // get the target tile
    QTableItem *Tile=item(cxMenuRow,cxMenuCol);
    if (Tile) {
	// current npc data
	QString tileNpcName=((tile*) Tile)->Npc.name;
	int tileNpcHealthInt=((tile*) Tile)->Npc.health;
	int tileNpcMpInt=((tile*) Tile)->Npc.mp;
	
	ss << tileNpcHealthInt;
	QString tileNpcHealth=ss.str();
	ss.str("");
	
	ss << tileNpcMpInt;
	QString tileNpcMp=ss.str().c_str();
	ss.str("");	
    
	// send npc data to the dialog and update the fields
	eNpc_Dialog->nameEdit->setText(tileNpcName);
	eNpc_Dialog->healthEdit->setText(tileNpcHealth);
	eNpc_Dialog->mpEdit->setText(tileNpcMp);
    
	// show our dialog
	eNpc_Dialog->show();
	eNpc_Dialog->raise();
	eNpc_Dialog->setActiveWindow();
    
	if (eNpc_Dialog->exec()) {
	    // get the user's modifications
	    tileNpcName=eNpc_Dialog->nameEdit->text();
	    tileNpcHealthInt=atoi(eNpc_Dialog->healthEdit->text().ascii());
	    tileNpcMpInt=atoi(eNpc_Dialog->mpEdit->text().ascii());
	    
	    // and update the npc
	    ((tile*) Tile)->Npc.name=tileNpcName;
	    ((tile*) Tile)->Npc.health=tileNpcHealthInt;
	    ((tile*) Tile)->Npc.mp=tileNpcMpInt;
	}
    }
};
