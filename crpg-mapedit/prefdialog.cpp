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

#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qtextedit.h>
#include <qlabel.h>

#include "prefdialog.h"

// prefDialog constructor
prefDialog::prefDialog(QWidget *parent,const char *name): QTabDialog(parent,name) {
    setCaption("Preferences");
    globalGB=new QGroupBox(1,Qt::Vertical,"General",this,"globalGB");
    
    dockSidebarCB=new QCheckBox("Keep the sidebar undocked",globalGB,"dockSidebar");
    dockSidebarCB->setChecked(false);
    
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
    
    connect(this,SIGNAL(applyButtonPressed()),this,SLOT(broadcastPrefs()));
    connect(this,SIGNAL(cancelButtonPressed()),this,SLOT(reject()));
};

// emit a signal to global app when prefs change
void prefDialog::broadcastPrefs() {
    emit dockSidebarChecked(dockSidebarCB->isChecked());
    emit mapHeader(mapHeaderText->text());
};
