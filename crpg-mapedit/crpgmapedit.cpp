#include <qapplication.h>

#include "dialogs.h"
#include "mainwindow.h"

int main(int argc,char *argv[]) {
    QApplication app(argc,argv);
    
    initDialog *init_Dialog=new initDialog;
    init_Dialog->show();
    init_Dialog->raise();
    init_Dialog->setActiveWindow();    
    qApp->processEvents();
    
    mainWindow *mapMain=new mainWindow;
    app.setMainWidget(mapMain);
    mapMain->show();
    
    init_Dialog->hide();
    delete init_Dialog;
    
    return app.exec();
}
