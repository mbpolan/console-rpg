#ifndef maptable_h
#define maptable_h

#include <qtable.h>
#include <iostream>
#include <list>
#include <libxml/parser.h>

class QAction;
class fillDialog;
class mapItem;

class mapTable: public QTable {
       Q_OBJECT
    
       public:
	   mapTable(int,int,QWidget *parent=0,const char *name=0);
	   
	   void resync(int,int);
	   void redraw();
	   void clear();
	   
	   int size() const {return items.size();}
	   
	   void addItem(int,int,int);
	   void removeItem(int,int);
	   void fillSelection(int,int,int,int,int);
	   
	   // list of items
	   std::list<mapItem*> items;
	   
       signals:
	   void tileClicked(int,int);
	   
       public slots:
	   void enableGrid(bool);
	   void registerTile(int);
	   void registerObj(int);
	   void updateTile(int,int);  
	   
	   void setPenTo1();
	   void setPenTo2();
	   void setPenTo3();
	   void setPenTo5();
	   
	  void contextMenuEvent(QContextMenuEvent*);
	  
	  void fillMap();
	   
       protected:
	   int rows;
	   int cols;
	   
	   // pens used to draw tiles
	   bool pen1;
	   bool pen2;
	   bool pen3;
	   bool pen5;
	   
	   // dialogs
	   fillDialog *fill_Dialog;
	   
	   // actions
	   QAction *removeItemAct;
	   
	   // tiles
	   int regTileID;
	   QPixmap regTile;
};

// items used in maplist
class mapItem {
       public:
	   mapItem(int,int,int);
	   
	   xmlNodePtr compressToXML();
	   int getID() const {return id;}
	   
	   int x,y;
	   
       private:
	   int id;
};

#endif
