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
#include <qpopupmenu.h>
#include <qlineedit.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtoolbar.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qmessagebox.h>
#include <qstatusbar.h>
#include <qfiledialog.h>
#include <qdockwindow.h>
#include <qdialog.h>
#include <qeventloop.h>
#include <qprogressdialog.h>
#include <qcheckbox.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sstream>
#include <fstream>

#include "icons/filenew.xpm"
#include "icons/fileopen.xpm"
#include "icons/filesave.xpm"
#include "icons/filesaveas.xpm"
#include "icons/quit.xpm"
#include "icons/pen1.xpm"
#include "icons/pen2.xpm"
#include "icons/pen3.xpm"

#include "mainwindow.h"
#include "tile.h"

mainWindow::mainWindow(QWidget *parent,const char *name): QMainWindow(parent,name) {
    setCaption("Console RPG Map Editor 0.1 ~ Coded by KanadaKid");
    setMinimumSize(800,600);
    firstSave=true;
    
    // now we make the actual map editor tables...
    map=new mapTable(50,50,this,"map");
    this->setCentralWidget(map);
    
    // make the mainwindow components
    makeActions();
    makeMenus();
    makeToolbars();
    
    // make our toolbox dock window
    makeToolbox();
    
    // make some connections
    connect(map,SIGNAL(tileClicked(int,int)),position,SLOT(update(int,int)));
    
    // dialogs
    pref_Dialog=new prefDialog(this);    
};

// make the actions used by menus, toolbars, etc.
void mainWindow::makeActions() {
    QPixmap icon_fileopen=QPixmap(fileopen);
    QPixmap icon_filenew=QPixmap(filenew);
    QPixmap icon_filesave=QPixmap(filesave);
    QPixmap icon_filesave_as=QPixmap(filesaveas);
    QPixmap icon_quit=QPixmap(quit);
    
    newAct=new QAction(tr("&New"),tr("Ctrl+N"),this);
    newAct->setIconSet(icon_filenew);
    newAct->setStatusTip("Make a new map");
    connect(newAct,SIGNAL(activated()),this,SLOT(makeNew()));
    
    openAct=new QAction(tr("&Open"),tr("Ctrl+O"),this);
    openAct->setIconSet(icon_fileopen);    
    openAct->setStatusTip("Open a map file");
    connect(openAct,SIGNAL(activated()),this,SLOT(makeOpen()));
    
    saveAct=new QAction(tr("&Save"),tr("Ctrl+S"),this);
    saveAct->setIconSet(icon_filesave);    
    saveAct->setStatusTip("Save your current map");
    connect(saveAct,SIGNAL(activated()),this,SLOT(makeSave()));
    
    saveAsAct=new QAction(tr("Save As"),tr(""),this);
    saveAsAct->setStatusTip("Save your map as another file");
    saveAsAct->setIconSet(icon_filesave_as);
    connect(saveAsAct,SIGNAL(activated()),this,SLOT(makeSaveAs()));
    
    closeAct=new QAction(tr("&Quit"),tr("Ctrl+Q"),this);
    closeAct->setIconSet(icon_quit);
    closeAct->setStatusTip("Quit the map editor");
    connect(closeAct,SIGNAL(activated()),qApp,SLOT(quit()));
    
    aboutAct=new QAction(tr("About"),tr(""),this);
    aboutAct->setStatusTip("About this map editor");
    connect(aboutAct,SIGNAL(activated()),this,SLOT(aboutDialog()));
    
    helpAct=new QAction(tr("&Help"),tr("F1"),this);
    helpAct->setStatusTip("View help topics");
    connect(helpAct,SIGNAL(activated()),this,SLOT(helpDialog()));
    
    showGridAct=new QAction(tr("Show Grid"),tr("Ctrl+G"),this);
    showGridAct->setToggleAction(true);
    showGridAct->setOn(map->showGrid());
    showGridAct->setStatusTip("Show or hide the grid");
    connect(showGridAct,SIGNAL(toggled(bool)),map,SLOT(enableGrid(bool)));
    
    goToCellAct=new QAction(tr("Go to Tile"),tr("Alt+G"),this);
    goToCellAct->setStatusTip("Go to a tile on the map");
    connect(goToCellAct,SIGNAL(activated()),this,SLOT(goToCellDialog()));
    
    QPixmap icon_pen1=QPixmap(pen1);
    QPixmap icon_pen2=QPixmap(pen2);
    QPixmap icon_pen3=QPixmap(pen3);    
    
    setPen1Act=new QAction(tr("Pen 1x1"),tr(""),this);
    setPen1Act->setStatusTip("Set the pen to 1x1 tile");
    setPen1Act->setIconSet(icon_pen1);
    connect(setPen1Act,SIGNAL(activated()),map,SLOT(setPenTo1()));
    
    setPen2Act=new QAction(tr("Pen 2x2"),tr(""),this);
    setPen2Act->setStatusTip("Set the pen to 2x2 tile");
    setPen2Act->setIconSet(icon_pen2);
    connect(setPen2Act,SIGNAL(activated()),map,SLOT(setPenTo2()));    
    
    setPen3Act=new QAction(tr("Pen 3x3"),tr(""),this);
    setPen3Act->setStatusTip("Set the pen to 3x3 tile");
    setPen3Act->setIconSet(icon_pen3);
    connect(setPen3Act,SIGNAL(activated()),map,SLOT(setPenTo3()));    
    
    setPen5Act=new QAction(tr("Pen 5x5"),tr(""),this);
    setPen5Act->setStatusTip("Set the pen to 5x5 tile");
    connect(setPen5Act,SIGNAL(activated()),map,SLOT(setPenTo5()));
    
    prefAct=new QAction(tr("Preferences"),tr(""),this);
    prefAct->setStatusTip("Edit preferences");
    connect(prefAct,SIGNAL(activated()),this,SLOT(openPrefDialog()));
    
    fillAct=new QAction(tr("Fill"),tr(""),this);
    fillAct->setStatusTip("Fill the map with one tile or object");
    connect(fillAct,SIGNAL(activated()),map,SLOT(fillMap()));
    
    makeNpcAct=new QAction(tr("Make NPC"),tr("Alt+N"),this);
    makeNpcAct->setStatusTip("Make a new NPC");
    connect(makeNpcAct,SIGNAL(activated()),this,SLOT(makeNpc()));
};

// create our menus
void mainWindow::makeMenus() {
    file=new QPopupMenu(this);
    newAct->addTo(file);
    openAct->addTo(file);
    saveAct->addTo(file);
    saveAsAct->addTo(file);
    file->insertSeparator();
    closeAct->addTo(file);
    
    edit=new QPopupMenu(this);
    goToCellAct->addTo(edit);
    fillAct->addTo(edit);
    
    edit->insertSeparator();
    prefAct->addTo(edit);
    
    options=new QPopupMenu(this);
    penOps=new QPopupMenu(options);
    
    options->insertItem(tr("&Pen"),penOps);
    setPen1Act->addTo(penOps);
    setPen2Act->addTo(penOps);    
    setPen3Act->addTo(penOps); 
    setPen5Act->addTo(penOps);
    
    options->insertSeparator();
    showGridAct->addTo(options);
    
    help=new QPopupMenu(this);
    helpAct->addTo(help);
    aboutAct->addTo(help);
    
    npc=new QPopupMenu(this);
    makeNpcAct->addTo(npc);
    
    menuBar()->insertItem(tr("&File"),file);
    menuBar()->insertItem(tr("&Edit"),edit);
    menuBar()->insertItem(tr("&Options"),options);
    menuBar()->insertItem(tr("&NPC"),npc);
    menuBar()->insertItem(tr("&Help"),help);
    
    // our tile indicator on the status bar
    position=new tileIndicator;
    
    // build a status bar and put an inital message into it
    statusBar()->message("Welcome to Console RPG Map Editor");
    statusBar()->addWidget(position,0,true);
};

// create our toolbars
void mainWindow::makeToolbars() {
    fileToolbar=new QToolBar(tr("File"),this);
    newAct->addTo(fileToolbar);
    openAct->addTo(fileToolbar);
    saveAct->addTo(fileToolbar);
    
    drawToolbar=new QToolBar(tr("Draw"),this);
    setPen1Act->addTo(drawToolbar);
    setPen2Act->addTo(drawToolbar);
    setPen3Act->addTo(drawToolbar);
};

// slot to make a new map
void mainWindow::makeNew() {
    new_Dialog=new newDialog(this);
    
    new_Dialog->show();
    new_Dialog->raise();
    new_Dialog->setActiveWindow();
    
    if (new_Dialog->exec()) {
	QString sx=new_Dialog->sizeEditX->text();
	QString sy=new_Dialog->sizeEditY->text();
	
	if (sx.isNull() || sy.isNull()) {
	    QMessageBox::warning(this,"Error",
				 "You must enter a size in rows and columns (x/y)!");
	    return;
	}
	
	handleSizes(atoi(sx.ascii()),atoi(sy.ascii()));
    }
    
    delete new_Dialog;
    
};

// create our tile toolbox
void mainWindow::makeToolbox() {
    toolbox=new QDockWindow(this,"toolbox");
    toolbox->setCaption("Toolbox");
    
    //    toolbox->setHorizontallyStretchable(false);
    toolbox->setMovingEnabled(false);
    moveDockWindow(toolbox,Qt::Left);
    
    itemBox=new toolBox(toolbox,"itemToolBox");
    toolbox->setWidget(itemBox);
    
    connect(itemBox,SIGNAL(tileChanged(int)),map,SLOT(registerTile(int)));
    connect(itemBox,SIGNAL(objChanged(int)),map,SLOT(registerObj(int)));
};

// slot to open a map file
void mainWindow::makeOpen() {
    mapFilePath=QFileDialog::getOpenFileName(0,"XML files (*.xml)",this,"fileDialog","Open a map file");
    
    if (mapFilePath.isNull())
	return;
    
    xmlDocPtr doc=xmlParseFile((const char*)mapFilePath.ascii());
    
    if (doc) {
	xmlNodePtr root, ptr, items, npcs;
	root=xmlDocGetRootElement(doc);
	
	// check to see if this is a console rpg map file
	if (xmlStrcmp(root->name,(const xmlChar*) "crpg-map")!=0) {
	    QMessageBox::warning(this,"Invalid map file",
				 "<p>Invalid map file! Please select another.</p>");
	    return;
	}
	
	ptr=root->children;
	if (ptr) {
	    map->clear();
	    
	    int itemCount=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "count"));	
	    items=ptr->children;
	    
	    QProgressDialog progress("Loading map...",0,itemCount,this,"saveMapDialog",true);
	    progress.setMinimumDuration(0);	
	    
	    for (int i=0;i<itemCount;i++) {
		progress.setProgress(i);
		int _id=atoi((const char*) xmlGetProp(items,(xmlChar*) "id"));
		
		int x=atoi((const char*) xmlGetProp(items,(xmlChar*) "x"));
		int y=atoi((const char*) xmlGetProp(items,(xmlChar*) "y"));
		    
		map->setItem(y,x,(new tile(_id,map)));
		
		items=items->next;
		
		qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
	    }
	    
	    ptr=ptr->next;
	        
	    // now we load in the npcs
	    int npcCount=atoi((const char*) xmlGetProp(ptr,(xmlChar*) "count"));
	    npcs=ptr->children;
	    
	    // renew the progress bar dialog
	    progress.setProgress(0,npcCount);
	    for (int i=0;i<npcCount;i++) {
		progress.setProgress(i);
		
		const char *_name=(const char*) xmlGetProp(npcs,(xmlChar*) "name");
		int _x=atoi((const char*) xmlGetProp(npcs,(xmlChar*) "x"));
		int _y=atoi((const char*) xmlGetProp(npcs,(xmlChar*) "y"));
		
		int _hp=atoi((const char*) xmlGetProp(npcs,(xmlChar*) "hp"));
		int _mp=atoi((const char*) xmlGetProp(npcs,(xmlChar*) "mp"));
		
		map->setItem(_y,_x,new tile(0,true,_name,_hp,map));
		
		npcs=npcs->next;
	    }
	} // if (ptr)...
	
	xmlFreeDoc(doc);
	return;
    }
    
    QMessageBox::critical(this,"Error","Unable to load map file from XML!");
};

// slot to save a map
void mainWindow::makeSave() {   
    if (firstSave) {
	savePath=QFileDialog::getSaveFileName(0,"XML files (*.xml)",this,"saveFileDialog","Save current map");
	savePath+=".xml";
    }
    
    std::ifstream fin;
    fin.open(savePath.ascii());
    
    if (fin && firstSave) {
	int confirm=QMessageBox::warning(this,"File exists!",
			     "This file already exists! Are you sure you want to overwrite it?",QMessageBox::Yes,QMessageBox::No);
	
	if (confirm==QMessageBox::No)
	    return;
    }
    fin.close();
    
    std::stringstream ss;
    if (savePath!=".xml") {
	firstSave=false;
	
	// save info in xml format
	xmlDocPtr doc;
	xmlNodePtr root,nodePtr,ptr;
	
	// add header along with xml version
	doc=xmlNewDoc((const xmlChar*) "1.0");
	
	root=xmlNewDocNode(doc,0,(const xmlChar*) "crpg-map",0);
	
	// if the user has added  a custom header
	if (!mapHeaderInfo.isNull()) {
	    ptr=xmlNewDocComment(doc,(const xmlChar*) mapHeaderInfo.ascii());
	    xmlDocSetRootElement(doc,ptr);
	}
	
	xmlDocSetRootElement(doc,root);
	
	nodePtr=xmlNewChild(root,0,(const xmlChar*) "items",0);
	
	QTableItem *Item;
	int itemCount=0;
	
	// get a count of items on the map
	for(int i=0;i<map->numRows();i++) {
	    for (int j=0;j<map->numCols();j++) {
		Item=map->item(i,j);
		
		if (Item)
		    itemCount+=1;
	    }
	}
		
	ss << itemCount;
	xmlSetProp(nodePtr,(const xmlChar*) "count",(const xmlChar*) ss.str().c_str()); // item count
	ss.str("");
	
	QProgressDialog progress("Saving map items",0,map->numRows(),this,"saveMapDialog",true);
	progress.setMinimumDuration(0);
	
	// save our item to an xmlNodePtr and add it
	for(int i=0;i<map->numRows();i++) {
	    for (int j=0;j<map->numCols();j++) {
		progress.setProgress(i);
		Item=map->item(i,j);
		
		if (Item) {
		        ptr=xmlNewNode(0,(const xmlChar*) "item");
		    
		        ss << ((tile*) Item)->getID();
                                        xmlSetProp(ptr,(const xmlChar*) "id",(const xmlChar*) ss.str().c_str());
                                        ss.str("");
    
		        ss << j;
		        xmlSetProp(ptr,(const xmlChar*) "x",(const xmlChar*) ss.str().c_str());
                                        ss.str("");
    
		        ss << i;
		        xmlSetProp(ptr,(const xmlChar*) "y",(const xmlChar*) ss.str().c_str());
		        ss.str("");
    
		        xmlSetProp(ptr,(const xmlChar*) "valid",(const xmlChar*) "1");
		        ss.str("");
			
		        xmlAddChild(nodePtr,ptr);
		    }
	    }
	    qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
	}
	
	// get a count on npcs
	int npcCount=0;
	for (int i=0;i<map->numRows();i++) {
	    for (int j=0;j<map->numCols();j++) {
		Item=map->item(i,j);
		
		if (((tile*) Item)->hasNpc())
		    npcCount+=1;
	    }
	}
	
	ss << npcCount;
	nodePtr=xmlNewChild(root,0,(const xmlChar*) "npcs",0);
	xmlSetProp(nodePtr,(const xmlChar*) "count",(const xmlChar*) ss.str().c_str());
	ss.str("");
	
	// progress.setLabel(new QLabel("Saving NPCs",0));
	progress.setProgress(0,map->numRows());
	
	// now save each npc to the map
	for (int i=0;i<map->numRows();i++) {
	    for (int j=0;j<map->numCols();j++) {
		progress.setProgress(i);
		Item=map->item(i,j);
		
		if (Item && ((tile*) Item)->hasNpc()) {
		    ptr=xmlNewNode(0,(const xmlChar*) "npc");
		    
		    ss << ((tile*) Item)->Npc.name.ascii();
		    xmlSetProp(ptr,(const xmlChar*) "name",(const xmlChar*) ss.str().c_str());
		    ss.str("");
		    
		    ss << i;
		    xmlSetProp(ptr,(const xmlChar*) "x",(const xmlChar*) ss.str().c_str());
		    ss.str("");
		    
		    ss << j;
		    xmlSetProp(ptr,(const xmlChar*) "y",(const xmlChar*) ss.str().c_str());
		    ss.str("");
		    
		    ss << ((tile*) Item)->Npc.health;
		    xmlSetProp(ptr,(const xmlChar*) "hp",(const xmlChar*) ss.str().c_str());
		    ss.str("");
		    
		    xmlSetProp(ptr,(const xmlChar*) "mp",(const xmlChar*) "0");
		    
		    xmlAddChild(nodePtr,ptr);
		}
		
	    qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);		
	    }
	}
	
	xmlKeepBlanksDefault(1);
	xmlSaveFile(savePath.ascii(),doc);
	
	xmlFreeDoc(doc);
    }
};

// slot to save a map as...
void mainWindow::makeSaveAs() {
    firstSave=true;
    makeSave();
};

// display dialog for gotocell
void mainWindow::goToCellDialog() {   
    goToCell_Dialog=new goToDialog(this);    
    
    goToCell_Dialog->show();
    goToCell_Dialog->raise();
    goToCell_Dialog->setActiveWindow();
    
    if (goToCell_Dialog->exec()) {
	QString row=goToCell_Dialog->lineRow->text();
	QString col=goToCell_Dialog->lineCol->text();
	
	if (row.isEmpty() || col.isEmpty()) {
	    QMessageBox::warning(this,"Error",
				 "You must enter a valid pair of coordinates!");
	    return;
	}
	
	goToCell(atoi(row.ascii()),atoi(col.ascii()));
    }
    
    delete goToCell_Dialog;
};

// our about dialog 
void mainWindow::aboutDialog() {
    QMessageBox::about(this,"About",
		       "<h2>CRPG Map Editor 0.1</h2>"
		       "<p>Written by KanadaKid using the Qt 3 library.</p>"
		       "<p>Licensed under the GNU GPL license.</p>"
		       "<p>This map editor is used to edit and make maps"
		       " for Console RPG versions 0.2.5 and higher.</p>"
		       "<p> Email: kanadakid@gmail.com</p>");
};

// our help dialog
void mainWindow::helpDialog() {
    QMessageBox::information(this,"Help",
			     "Need help? Go see a doctor. ;)");
};

// slot to handle map resizing
void mainWindow::handleSizes(int x,int y) {
    if (x>50 || y>50) {
	QMessageBox::warning(this,"Error",
			     "Map is too big! The maximum size is 50/50.");
	return;
    }
    
    int choice=QMessageBox::warning(this,"Proceed?",
				    "Generating the map may take awhile depending on your system. "
				    "Are you sure you want to continue?",QMessageBox::Yes,QMessageBox::No,QMessageBox::NoButton);
    
    if (choice==QMessageBox::No)
	return;
    
    gen_Dialog=new genDialog(this);
    gen_Dialog->show();
    gen_Dialog->raise();
    gen_Dialog->setActiveWindow();    
    
    qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
    
    rows=y;
    cols=x;
    
    map->setNumRows(rows);
    map->setNumCols(cols);
    
    map->clear();
    
    map->resync(y,x);
    map->redraw();
    
    delete gen_Dialog;
};

// slot for going to a particular cell
void mainWindow::goToCell(int row,int col) {
    if (row > map->numRows() || col > map->numCols()) {
	QMessageBox::warning(this,"Error",
			     "You can only go to a tile on this map!");
	return;
    }
    
    map->setCurrentCell(row,col);
};

// open the preferences dialog
void mainWindow::openPrefDialog() {
    pref_Dialog->show();
    pref_Dialog->raise();
    pref_Dialog->setActiveWindow();
    
    connect(pref_Dialog,SIGNAL(dockSidebarChecked(bool)),itemBox,SLOT(dockSidebar(bool)));
    connect(pref_Dialog,SIGNAL(dockSidebarChecked(bool)),this,SLOT(sendDock(bool)));
    connect(pref_Dialog,SIGNAL(mapHeader(QString)),this,SLOT(updateMapHeader(QString)));
};

// slot to make a new npc
void mainWindow::makeNpc() {
    mNpc_Dialog=new makeNpcDialog(this);
    mNpc_Dialog->show();
    mNpc_Dialog->raise();
    mNpc_Dialog->setActiveWindow();
    
    if (mNpc_Dialog->exec()) {
	QString Name=mNpc_Dialog->nameEdit->text();
	int Health=atoi(mNpc_Dialog->healthEdit->text().ascii());
	
	map->registerNpc(Name,Health);
	map->setNpcPen();
    }
    
    delete mNpc_Dialog;
};
