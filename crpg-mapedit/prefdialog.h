#include <qtabdialog.h>

class QGroupBox;
class QCheckBox;
class QTextEdit;
class QLabel;

class prefDialog: public QTabDialog {
       public:
	   prefDialog(QWidget *parent=0,const char* name=0);
	   
       private:
	   QLabel *mapHeaderExp;
	   
	   QGroupBox *globalGB;
	   QGroupBox *mapGB;
	   
	   QCheckBox *dockSidebarCB;
	   QTextEdit *mapHeaderText;
};
