/***************************************************************************
 *   Copyright (C) 2005 by KanadaKid                                       *
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
// wizard.h: Wizard class

#ifndef WIZARD_H
#define WIZARD_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/table.h>
#include <gtkmm/window.h>
#include "numericentry.h"

// wizard for adding new items
class Wizard: public Gtk::Window {
	public:
		// constructor
		Wizard();
		
		// destructor
		virtual ~Wizard() {};
		
		// signals
		sigc::signal<void> signalSaveItemRequest() { return sig_saveItemRequest; };
		
		// public widgets
		Gtk::Entry *nameEntry;
		NumericEntry *idEntry;
		NumericEntry *luckEntry;
		NumericEntry *defEntry;
		NumericEntry *powEntry;
		NumericEntry *strEntry;
		Gtk::ComboBoxText *usableCB;
		
	private:
		// signal handlers
		void saveItem();
		
		// containers
		Gtk::ButtonBox *buttonBox;
		Gtk::Frame *frame;
		Gtk::ScrolledWindow *sWindow;
		Gtk::Table *table;
		Gtk::VBox *vb;
		
		// wizards
		Gtk::Label *titleLabel;
		Gtk::Label *nameLabel;
		Gtk::Label *idLabel;
		Gtk::Label *luckLabel;
		Gtk::Label *defLabel;
		Gtk::Label *powLabel;
		Gtk::Label *strLabel;
		Gtk::Label *usableLabel;
		
		Gtk::Button *okButton;
		Gtk::Button *cancelButton;
		
		// signals
		sigc::signal<void> sig_saveItemRequest;
};

#endif
