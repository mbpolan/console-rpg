#ifndef maptable_h
#define maptable_h

#include <qtable.h>

class QAction;

class mapTable: public QTable {
       Q_OBJECT
    
       public:
	   mapTable(int,int,QWidget *parent=0,const char *name=0);
	   
	   void resync(int,int);
	   void redraw();
	   void clear();
	   
	   void removeItem(int,int);
	   
       signals:
	   void tileClicked(int,int);
	   
       public slots:
	   void enableGrid(bool);
	   void registerTile(int,int);
	   void registerObj(int,int);
	   void updateTile(int,int);  
	   
	   void setPenTo1();
	   void setPenTo2();
	   void setPenTo3();
	   void setPenTo5();
	   
	  void contextMenuEvent(QContextMenuEvent*);
	   
       protected:
	   int rows;
	   int cols;
	   
	   // pens used to draw tiles
	   bool pen1;
	   bool pen2;
	   bool pen3;
	   bool pen5;
	   
	   // actions
	   QAction *removeItemAct;
	   
	   // tiles
	   QPixmap regTile;
};

#endif