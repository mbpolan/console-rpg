#include <qtabdialog.h>

class QGroupBox;
class QCheckBox;
class QTextEdit;
class QLabel;

class prefDialog: public QTabDialog {
       Q_OBJECT
    
       public:
	   prefDialog(QWidget *parent=0,const char* name=0);
	   
	   QCheckBox *dockSidebarCB;
	   QTextEdit *mapHeaderText;
	   
       signals:
	   void dockSidebarChecked(bool);
	   void mapHeader(QString);
	   
       public slots:
	   void broadcastPrefs();
	   
       private:
	   QLabel *mapHeaderExp;
	   
	   QGroupBox *globalGB;
	   QGroupBox *mapGB;
};
