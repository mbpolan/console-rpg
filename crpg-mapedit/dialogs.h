// dialogs.h: various dialog boxes that don't fit into any particular class
#include <qdialog.h>

class QLabel;
class QComboBox;
class QGridLayout;
class QPushButton;

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
