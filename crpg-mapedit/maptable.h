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

#ifndef maptable_h
#define maptable_h

#include <qtable.h>
#include <iostream>
#include <list>
#include <libxml/parser.h>

class QAction;
class fillDialog;
class editNpcDialog;
class mapItem;

// struct to hold registered npc data
struct regNPC {
    QString name;
    int health;
    int mp;
};

class mapTable: public QTable {
       Q_OBJECT
    
       public:
	   mapTable(int,int,QWidget *parent=0,const char *name=0);
	   
	   void resync(int,int);
	   void redraw();
	   void clear();
	   
	   void addItem(int,int,int);
	   void removeItem(int,int,int);
	   void fillSelection(int,int,int,int,int);
	   
	   void placeNpc(int,int);
	   
       signals:
	   void tileClicked(int,int);
	   
       public slots:
	   void enableGrid(bool);
	   void registerTile(int);
	   void registerObj(int);
	   void registerNpc(QString,int,int);
	   void updateTile(int,int);  
	   
	   void setPenTo1();
	   void setPenTo2();
	   void setPenTo3();
	   void setPenTo5();
	   void setNpcPen();
	   
	  void openContextMenu(int,int,const QPoint&);
	  
	  void fillMap();
	  
	  void openEditNpc();
	   
       protected:
	   int rows;
	   int cols;
	   
	   // pens used to draw tiles
	   bool pen1;
	   bool pen2;
	   bool pen3;
	   bool pen5;
	   bool penNpc;
	   
	   // dialogs
	   fillDialog *fill_Dialog;
	   editNpcDialog *eNpc_Dialog;
	   
	   // actions
	   QAction *editNpcAct;
	   QAction *removeItemAct;
	   
	   // tiles
	   int regTileID;
	   QPixmap regTile;
	   
	   // our registered npc to place
	   QString npcName;
	   int npcHealth;
	   int npcMp;
	   
	   // location of last context menu request
	   int cxMenuRow;
	   int cxMenuCol;
};

#endif
