#include <qpushbutton.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <ctype.h>

#include "newdialog.h"

newDialog::newDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setSizeGripEnabled(false);
    setModal(true);
    setCaption("New map");
    
    grid=new QGridLayout(this,4,3);
    
    title=new QLabel("Make a new map.",this,"title");
    title->setFont(QFont("Times",14,QFont::Bold));
    
    sizeX=new QLabel("X Size",this);
    sizeY=new QLabel("Y Size",this);
    
    sizeEditX=new QLineEdit(this,"sizeEditX");
    sizeEditY=new QLineEdit(this,"sizeEditY");
    
    okButton=new QPushButton("&OK",this);
    cancelButton=new QPushButton("&Cancel",this);
    
    connect(okButton,SIGNAL(clicked()),this,SLOT(broadcastSizes()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    
    // syntax is rows then columns
    grid->addWidget(title,0,0);
    grid->addWidget(sizeX,1,0);
    grid->addWidget(sizeY,2,0);
    
    grid->addWidget(sizeEditX,1,1);
    grid->addWidget(sizeEditY,2,1);
    grid->addWidget(okButton,1,2);
    grid->addWidget(cancelButton,2,2);
};

void newDialog::broadcastSizes() {
    QString sx=sizeEditX->text();
    QString sy=sizeEditY->text();
    
    if ((!sx.isEmpty()) && (!sy.isEmpty())) {
	int x=atoi(sx.ascii());
	int y=atoi(sy.ascii());
	emit sizesChanged(x,y);
    }
    
    this->accept();
};
