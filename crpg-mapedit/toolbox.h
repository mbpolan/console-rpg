#ifndef toolbox_h
#define toolbox_h

#include <qwidget.h>

class QTable;
class QTabWidget;

class toolBox: public QWidget {
       Q_OBJECT
    
       public:
	   toolBox(QWidget *parent=0,const char *name=0);
	   
       signals:
	   void tileChanged(int,int);
	   void objChanged(int,int);
	   
       public slots:
	   void broadcastNewTile(int,int);
	   void broadcastNewObj(int,int);
	   void highliteCell(int,int);	   
	   
	   
       private:
	   QTabWidget *mainFrame;
	   
	   QTable *items;
	   QTable *objects;
	   
	   int irows;
	   int icols;
};

#endif
