#include <qapplication.h>

#include "mainwindow.h"

int main(int argc,char *argv[]) {
    QApplication app(argc,argv);
    mainWindow *mapMain=new mainWindow;
    app.setMainWidget(mapMain);
    mapMain->show();
    
    return app.exec();
}
