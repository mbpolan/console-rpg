#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qfont.h>
#include <qmessagebox.h>
#include <ctype.h>

#include "gotodialog.h"

goToDialog::goToDialog(QWidget *parent,const char *name): QDialog(parent,name) {
    setCaption("Go to Tile");
    
    grid=new QGridLayout(this,3,3);
    
    goButton=new QPushButton("&Go",this,"goButton");
    cancelButton=new QPushButton("&Cancel",this,"cancelButton");
    
    title=new QLabel("Go to Tile",this,"title");
    title->setFont(QFont("Times",14,QFont::Bold));
    
    trow=new QLabel("Position on X",this,"trow");
    tcol=new QLabel("Position on Y",this,"tcol");
    
    lineRow=new QLineEdit(this,"lineRow");
    lineCol=new QLineEdit(this,"lineCol");
    
    grid->addMultiCellWidget(title,0,0,0,2);
    grid->addWidget(trow,1,0);
    grid->addWidget(tcol,2,0);
    
    grid->addWidget(lineRow,1,1);
    grid->addWidget(lineCol,2,1);
    grid->addWidget(goButton,1,2);
    grid->addWidget(cancelButton,2,2);
    
    connect(goButton,SIGNAL(clicked()),this,SLOT(broadcastTiles()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
};

void goToDialog::broadcastTiles() {
    int col=atoi(lineRow->text().ascii());
    int row=atoi(lineCol->text().ascii());
    
    if (row==NULL || col==NULL) {
	QMessageBox::warning(this,"Error",
			     "You must enter a pair of coordinates!");
    }
    
    if (row>=0 && col>=0)
	emit valueChanged(row,col);
};
