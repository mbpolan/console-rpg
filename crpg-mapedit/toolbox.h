#ifndef toolbox_h
#define toolbox_h

#include <qwidget.h>

class QTabWidget;
class QTable;

class toolBox: public QWidget {
       Q_OBJECT
    
       public:
	   toolBox(QWidget *parent=0,const char *name=0);
	   
       signals:
	   void tileChanged(int);
	   void objChanged(int);
	   
       public slots:
	   void broadcastNewTile(int);
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
