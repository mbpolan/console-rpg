/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
 *   kanadakid@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

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
