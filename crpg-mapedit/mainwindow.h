#ifndef mainwindow_h
#define mainwindow_h

#include <qmainwindow.h>

// nessesary includes
#include "gotodialog.h"
#include "maptable.h"
#include "newdialog.h"
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
	  
      private:
	  // our mapedit body
	  mapTable *map;
	  
	  // needed dialogs
	  goToDialog *goToCell_Dialog;
	  newDialog *new_Dialog;
	  
	  // other components
	  QDockWindow *toolbox;
	  
	  // extras
	  toolBox *itemBox;
	  tileIndicator *position;
	  
	  QPopupMenu *file;
	  QPopupMenu *edit;
	  QPopupMenu *options;
	  QPopupMenu *help;
	  
	  QToolBar *fileToolbar;
	  QToolBar *editToolBar;
	  
	  QAction *newAct;
	  QAction *openAct;
	  QAction *saveAct;
	  QAction *saveAsAct;
	  QAction *closeAct;
	  QAction *aboutAct;
	  QAction *helpAct;
	  QAction *showGridAct;
	  QAction *goToCellAct;
	  
	  // path to our open map file
	  QString mapFilePath;
	  
	  // map sizes
	  int rows,cols;
};
    
#endif
