#include <qapplication.h>
#include <qpopupmenu.h>
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
#include <libxml/parser.h>

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
    
    // create our dialogs
    new_Dialog=new newDialog(this);
    goToCell_Dialog=new goToDialog(this);    
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
    
    menuBar()->insertItem(tr("&File"),file);
    menuBar()->insertItem(tr("&Edit"),edit);
    menuBar()->insertItem(tr("&Options"),options);
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
    new_Dialog->show();
    new_Dialog->raise();
    new_Dialog->setActiveWindow();
	
    connect(new_Dialog,SIGNAL(sizesChanged(int,int)),this,SLOT(handleSizes(int,int)));   
    
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
    mapFilePath=QFileDialog::getOpenFileName("/home","XML files (*.xml)",this,"fileDialog","Open a map file");
    
    if (mapFilePath.isNull())
	return;
    
    xmlDocPtr doc=xmlParseFile((const char*)mapFilePath.ascii());
    
    if (doc) {
	xmlNodePtr root;
	root=xmlDocGetRootElement(doc);
	
	// check to see if this is a console rpg map file
	if (xmlStrcmp(root->name,(const xmlChar*) "crpg-map")!=0) {
	    QMessageBox::warning(this,"Invalid map file",
			              "<p>Invalid map file! Please select another.</p>");
	}
	
	// loadMapData(doc);
	xmlFreeDoc(doc);
    }
};

// slot to save a map
void mainWindow::makeSave() {
    QString savePath=QFileDialog::getSaveFileName("/home/mike","XML files (*.xml)",this,"saveFileDialog","Save current map");
    // saveMapData(savePath);
};

// slot to save a map as...
void mainWindow::makeSaveAs() {
    return;
};

// display dialog for gotocell
void mainWindow::goToCellDialog() {     
    goToCell_Dialog->show();
    goToCell_Dialog->raise();
    goToCell_Dialog->setActiveWindow();
    connect(goToCell_Dialog,SIGNAL(valueChanged(int,int)),this,SLOT(goToCell(int,int)));
};

// our about dialog 
void mainWindow::aboutDialog() {
    QMessageBox::about(this,"About",
		       "<h2>CRPG Map Editor 0.1</h2>"
		      "<p>Written by KanadaKid using the Qt library.</p>"
		      "<p>This map editor is used to edit and make maps"
		      " for Console RPG versions 0.2.0 and higher.</p>"
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
    
    rows=y;
    cols=x;
    
    map->clear();
        
    map->setNumRows(y);
    map->setNumCols(x);
        
    map->resync(y,x);
    map->redraw();
};

// slot for going to a particular cell
void mainWindow::goToCell(int row,int col) {
    if (row > map->numRows() || col > map->numCols()) {
	QMessageBox::warning(this,"Error",
			     "You can only go to a tile on this map!");
    }
    
    map->setCurrentCell(row,col);
};
