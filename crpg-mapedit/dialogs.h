#ifndef dialogs_h
#define dialogs_h

// dialogs.h: various dialog boxes that don't fit into any particular class
#include <qdialog.h>

class QLabel;
class QComboBox;
class QGridLayout;
class QPushButton;
class QLineEdit;

// dialog for generating a new map
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

// dialog for going to a tile on the map
class goToDialog: public QDialog {
       Q_OBJECT
    
       public:
	   goToDialog(QWidget *parent=0,const char *name=0);
	   
	   QLineEdit *lineRow;
	   QLineEdit *lineCol;
	   
       private:	   
	   QGridLayout *grid;
	   
	   QPushButton *goButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *trow;
	   QLabel *tcol;
};

// the fill command dialog
class fillDialog: public QDialog {
       public:
	   fillDialog(QWidget *parent=0,const char *name=0);
	   
   	   QComboBox *tileCB;
	   
       private:   
	   QGridLayout *grid;
	   
	   QPushButton *okButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *fillExp;
};

// dialog displayed when loading map editor
class initDialog: public QDialog {
       public:
	   initDialog(QWidget *parent=0,const char *name=0);
	   
       private:
	   QLabel *msg;
};

#endif
