#ifndef tileindicator_h
#define tileindicator_h

#include <qwidget.h>

class QLabel;

class tileIndicator: public QWidget {
       Q_OBJECT
     
       public:
	   tileIndicator(QWidget *parent=0,const char *name=0);
	   
       public slots:
	   void update(int,int);
	   
       private:
	   QLabel *pos;
};

#endif
