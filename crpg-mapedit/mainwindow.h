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
	  
      private:
	  // our mapedit body
	  mapTable *map;
	  
	  // other components
	  QDockWindow *toolbox;
	  
	  // needed dialogs
	  goToDialog *goToCell_Dialog;
	  newDialog *new_Dialog;
	  prefDialog *pref_Dialog;
	  
	  // extras
	  toolBox *itemBox;
	  tileIndicator *position;
	  
	  QPopupMenu *file;
	  QPopupMenu *edit;
	  QPopupMenu *options;
	  QPopupMenu *help;
	  QPopupMenu *penOps;
	  
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
	  
	  // path to our open map file
	  QString mapFilePath;
	  
	  // map sizes
	  int rows,cols;
      };

#endif
