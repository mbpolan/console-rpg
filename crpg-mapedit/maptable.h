#ifndef maptable_h
#define maptable_h

#include <qtable.h>

class mapTable: public QTable {
       Q_OBJECT
    
       public:
	   mapTable(int,int,QWidget *parent=0,const char *name=0);
	   
	   void resync(int,int);
	   void redraw();
	   void clear();
	   
       signals:
	   void tileClicked(int,int);
	   
       public slots:
	   void enableGrid(bool);
	   void registerTile(int,int);
	   void updateTile(int,int);
	   
       private:
	   int rows;
	   int cols;
	   
	   QPixmap grassTile;
	   QPixmap waterTile;
	   QPixmap regTile;
};

#endif
