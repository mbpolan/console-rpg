#ifndef newDialog_h
#define newDialog_h

#include <qdialog.h>

class QLabel;
class QLineEdit;
class QPushButton;
class QGridLayout;

class newDialog: public QDialog {
      Q_OBJECT
    
       public:
	   newDialog(QWidget *parent=0,const char *name=0);
	  
       signals:
	   void sizesChanged(int,int);
	   
       public slots:
	   void broadcastSizes();
	   
       private:
	   QGridLayout *grid;
	   
	   QPushButton *okButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *sizeX;
	   QLabel *sizeY;
	   
	   QLineEdit *sizeEditX;
	   QLineEdit *sizeEditY;
};

#endif
