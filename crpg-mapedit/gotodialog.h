#ifndef gotodialog_h
#define gotodialog_h

#include <qdialog.h>

class QPushButton;
class QLabel;
class QGridLayout;
class QLineEdit;

class goToDialog: public QDialog {
       Q_OBJECT
    
       public:
	   goToDialog(QWidget *parent=0,const char *name=0);
	   
       signals:
	   void valueChanged(int,int);
	   
       public slots:
	   void broadcastTiles();
	   
       private:
	   QGridLayout *grid;
	   
	   QPushButton *goButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *trow;
	   QLabel *tcol;
	   
	   QLineEdit *lineRow;
	   QLineEdit *lineCol;
};

#endif