#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qtextedit.h>
#include <qlabel.h>

#include "prefdialog.h"

prefDialog::prefDialog(QWidget *parent,const char *name): QTabDialog(parent,name) {
    globalGB=new QGroupBox(1,Qt::Vertical,"General",this,"globalGB");
    
    dockSidebarCB=new QCheckBox("Keep the sidebar docked",globalGB,"dockSidebar");
    dockSidebarCB->setChecked(true);
    
    this->addTab(globalGB,"Global");
    
    mapGB=new QGroupBox(2,Qt::Horizontal,"Map Header",this,"mapGB");
    
    mapHeaderExp=new QLabel("This is the text that will be displayed at the top of the map XML document.",mapGB);
    mapGB->addSpace(1);
    
    mapHeaderText=new QTextEdit(mapGB,"mapHeaderText");
    mapHeaderText->setMinimumHeight(200);
    
    this->addTab(mapGB,"Map");
    
    setOkButton("OK");
    setApplyButton("Apply");
    setCancelButton("Cancel");
    
    connect(this,SIGNAL(applyButtonPressed()),this,SLOT(accept())); // todo
    connect(this,SIGNAL(cancelButtonPressed()),this,SLOT(reject()));
};
