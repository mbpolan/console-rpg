#include <qlabel.h>
#include <qfont.h>
#include <sstream>

#include "tileindicator.h"

tileIndicator::tileIndicator(QWidget *parent,const char *name): QWidget(parent,name) {
    setMinimumSize(75,2);
    std::stringstream ss;
    ss << "X: " << 0 << " | Y: " << 0;
    
    pos=new QLabel(ss.str().c_str(),this,"tileX");
    pos->setFont(QFont("Times",12,QFont::Normal));
    pos->setAlignment(Qt::AlignTop);
};

void tileIndicator::update(int row,int col) {
    std::stringstream ss;
    ss << "X: " << col << " | Y: " << row;
    
    pos->setText(ss.str().c_str());
};
