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

#ifndef dialogs_h
#define dialogs_h

// dialogs.h: various dialog boxes that don't fit into any particular class
#include <qdialog.h>

class QLabel;
class QComboBox;
class QGridLayout;
class QPushButton;
class QLineEdit;

// dialog for generating a new map
class newDialog: public QDialog {
      Q_OBJECT
    
       public:
	   newDialog(QWidget *parent=0,const char *name=0);
	   
	   QLineEdit *sizeEditX;
	   QLineEdit *sizeEditY;
	   
       private:
	   QGridLayout *grid;
	   
	   QPushButton *okButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *sizeX;
	   QLabel *sizeY;
};

// dialog for going to a tile on the map
class goToDialog: public QDialog {
       Q_OBJECT
    
       public:
	   goToDialog(QWidget *parent=0,const char *name=0);
	   
	   QLineEdit *lineRow;
	   QLineEdit *lineCol;
	   
       private:	   
	   QGridLayout *grid;
	   
	   QPushButton *goButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *trow;
	   QLabel *tcol;
};

// the fill command dialog
class fillDialog: public QDialog {
       public:
	   fillDialog(QWidget *parent=0,const char *name=0);
	   
   	   QComboBox *tileCB;
	   
       private:   
	   QGridLayout *grid;
	   
	   QPushButton *okButton;
	   QPushButton *cancelButton;
	   
	   QLabel *title;
	   QLabel *fillExp;
};

// dialog displayed when loading map editor
class initDialog: public QDialog {
       public:
	   initDialog(QWidget *parent=0,const char *name=0);
	   
       private:
	   QGridLayout *grid;	   
	   
	   QLabel *msg;
};

// dialog displayed when making a new map
class genDialog: public QDialog {
       public:
	   genDialog(QWidget *parent=0,const char *name=0);
	   
       private:
	   QGridLayout *grid;
	   
	   QLabel *msg;
};

// dialog used to make an npc on the map
class makeNpcDialog: public QDialog {
       public:
	   makeNpcDialog(QWidget *parent=0,const char *name=0);
	   
	   QLineEdit *nameEdit;
	   QLineEdit *healthEdit;
	   QLineEdit *mpEdit;	   
	   
       private:
	   QGridLayout *grid;
	   
	   QLabel *title;
	   QLabel *intro;
	   QLabel *nameLab;
	   QLabel *healthLab;
	   QLabel *mpLab;	   
	   
	   QPushButton *okButton;
	   QPushButton *cancelButton;
};
	   
class editNpcDialog: public QDialog {
       public:
	   editNpcDialog(QWidget *parent=0,const char *name=0);
	   
	   QLineEdit *nameEdit;
	   QLineEdit *healthEdit;
	   QLineEdit *mpEdit;
	   
       private:
	   QGridLayout *grid;
	   
	   QLabel *intro;
	   QLabel *nameLab;
	   QLabel *healthLab;
	   QLabel *mpLab;
	   
	   QPushButton *okButton;
	   QPushButton *cancelButton;
};

#endif
