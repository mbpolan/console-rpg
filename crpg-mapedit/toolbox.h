#ifndef toolbox_h
#define toolbox_h

#include <qwidget.h>
#include <qtable.h>

class QTabWidget;
class toolBoxTable;
class toolBoxTableCell;

class toolBox: public QWidget {
       Q_OBJECT
    
       public:
	   toolBox(QWidget *parent=0,const char *name=0);
	   
       signals:
	   void tileChanged(int);
	   void objChanged(int);
	   
       public slots:
	   void broadcastNewTile(int);
	   void broadcastNewObj(int);
	   void highliteCell(int,int);	   
	   
	   
       private:
	   QTabWidget *mainFrame;
	   
	   toolBoxTable *items;
	   toolBoxTable *objects;
	   
	   int irows;
	   int icols;
};

class toolBoxTable: public QTable {
       Q_OBJECT   
    
       public:
	   toolBoxTable(int rows,int cols,QWidget *parent=0,const char *name=0);
	   
	   static void parsePixmap(QPixmap);
};

class toolBoxTableCell: public QTableItem {
       public:
	   toolBoxTableCell(QTable *parent);
};

#endif
