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
	   
	   QLineEdit *sizeEditX;
	   QLineEdit *sizeEditY;
	   
       private:
	   QGridLayout *grid;
	   
	   QPushButton *okButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *sizeX;
	   QLabel *sizeY;
};

#endif
