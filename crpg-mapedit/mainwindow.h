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

#ifndef mainwindow_h
#define mainwindow_h

#include <qmainwindow.h>

// nessesary includes
#include "dialogs.h"
#include "maptable.h"
#include "prefdialog.h"
#include "tileindicator.h"
#include "toolbox.h"

// forward declare some classes
class QAction;
class QPopupMenu;
class QToolBar;
class QDockWindow;
class QTable;

// the main window of the map editor
class mainWindow: public QMainWindow {
    Q_OBJECT
    
      public:
	  mainWindow(QWidget *parent=0,const char *name=0); // our constructor
	  
	  // some public members
	  void makeActions();
	  void makeMenus();
	  void makeToolbars();
	  void makeToolbox();
	  	
	  // other components
	  QDockWindow *toolbox;	  
	  
      signals:
	  // none for now
	  
	  // our public slots
      public slots:
	  void makeNew();
	  void makeOpen();
	  void makeSave();
	  void makeSaveAs();
	  
	  void aboutDialog();
	  void helpDialog();
	  void goToCellDialog();
	  
	  void handleSizes(int,int);
	  void goToCell(int,int);
	  void openPrefDialog();
	  
	  void updateMapHeader(QString text) {mapHeaderInfo=text;}  // update the map's header
	  void sendDock(bool t) {if (!t) moveDockWindow(toolbox,Qt::Left);}
	  
	  void makeNpc();
	  
	  tileIndicator *position;
	  
      private:
	  // our mapedit body
	  mapTable *map;
	  
	  // needed dialogs
	  goToDialog *goToCell_Dialog;
	  newDialog *new_Dialog;
	  prefDialog *pref_Dialog;
	  genDialog *gen_Dialog;
	  
	  makeNpcDialog *mNpc_Dialog; // make an npc
	  
	  // extras
	  toolBox *itemBox;
	  
	  QPopupMenu *file;
	  QPopupMenu *edit;
	  QPopupMenu *options;
	  QPopupMenu *help;
	  QPopupMenu *penOps;
	  QPopupMenu *npc;
	  
	  QToolBar *fileToolbar;
	  QToolBar *editToolbar;
	  QToolBar *drawToolbar;
	  
	  QAction *newAct;
	  QAction *openAct;
	  QAction *saveAct;
	  QAction *saveAsAct;
	  QAction *closeAct;
	  
	  QAction *aboutAct;
	  QAction *helpAct;
	  QAction *showGridAct;
	  QAction *goToCellAct;
	  
	  QAction *setPen1Act;
	  QAction *setPen2Act;
	  QAction *setPen3Act;
	  QAction *setPen5Act;
	  
	  QAction *prefAct;
	  QAction *fillAct;
	  
	  QAction *makeNpcAct;
	  
	  // path to our open map file
	  QString mapFilePath;
	  
	  // map sizes
	  int rows,cols;
	  
	  // save dialog related variables
	  bool firstSave;
	  QString savePath;
	  
	  QString mapHeaderInfo; // the text at the top of the map file
      };

#endif
