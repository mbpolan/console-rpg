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
// wizard.cpp: implementations of Wizard class

#include "wizard.h"

// constructor
Wizard::Wizard(bool editor): Gtk::Window(), originalItem("") {
	set_title("Item Wizard");
	set_modal(true);
	set_border_width(4);
	
	// create the vbox
	vb=new Gtk::VBox;
	vb->set_spacing(2);
	
	// create the scrolled window
	sWindow=new Gtk::ScrolledWindow;
	
	// create the frame
	frame=new Gtk::Frame;
	
	// create the main table
	table=new Gtk::Table(8, 2, false);
	table->set_spacings(3);
	
	// create labels
	if (!editor)
		titleLabel=new Gtk::Label("You can use the Item Wizard to make a new item. Simply fill in the\n"
					  "fields below and click OK. Your item will be added to the database.");
	
	else
		titleLabel=new Gtk::Label("You can edit the chosen item below by changing the values stored in the\n"
					  "entries. Click OK once you are done to save the changes.");
	
	nameLabel=new Gtk::Label("Name");
	idLabel=new Gtk::Label("ID");
	usableLabel=new Gtk::Label("Usable");
	pluralLabel=new Gtk::Label("Plural");
	luckLabel=new Gtk::Label("Luck");
	defLabel=new Gtk::Label("Defense");
	powLabel=new Gtk::Label("Power");
	strLabel=new Gtk::Label("Strength");
	
	// create entries
	nameEntry=new Gtk::Entry;
	nameEntry->signal_insert_text().connect(sigc::mem_fun(*this, &Wizard::validateInsertText));
	nameEntry->signal_delete_text().connect(sigc::mem_fun(*this, &Wizard::validateDeleteText));
	
	idEntry=new NumericEntry;
	idEntry->sigTextInserted().connect(sigc::mem_fun(*this, &Wizard::validate));
	idEntry->sigTextDeleted().connect(sigc::mem_fun(*this, &Wizard::validate));
	
	luckEntry=new NumericEntry;
	luckEntry->sigTextInserted().connect(sigc::mem_fun(*this, &Wizard::validate));
	luckEntry->sigTextDeleted().connect(sigc::mem_fun(*this, &Wizard::validate));
	
	defEntry=new NumericEntry;
	defEntry->sigTextInserted().connect(sigc::mem_fun(*this, &Wizard::validate));
	defEntry->sigTextDeleted().connect(sigc::mem_fun(*this, &Wizard::validate));
	
	powEntry=new NumericEntry;
	powEntry->sigTextInserted().connect(sigc::mem_fun(*this, &Wizard::validate));
	powEntry->sigTextDeleted().connect(sigc::mem_fun(*this, &Wizard::validate));
	
	strEntry=new NumericEntry;
	strEntry->sigTextInserted().connect(sigc::mem_fun(*this, &Wizard::validate));
	strEntry->sigTextDeleted().connect(sigc::mem_fun(*this, &Wizard::validate));
	
	// the usable combo box
	usableCB=new Gtk::ComboBoxText();
	usableCB->append_text("Yes");
	usableCB->append_text("No");
	usableCB->set_active(0);
	
	// plural combobox 
	pluralCB=new Gtk::ComboBoxText();
	pluralCB->append_text("Yes");
	pluralCB->append_text("No");
	pluralCB->set_active(0);
	
	// buttons
	buttonBox=new Gtk::HButtonBox;
	okButton=new Gtk::Button("OK");
	okButton->set_sensitive(false);
	okButton->signal_clicked().connect(sigc::mem_fun(*this, &Wizard::saveItem));
	
	cancelButton=new Gtk::Button("Cancel");
	cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &Wizard::hide));
	
	// attach widgets
	// labels
	table->attach(*manage(nameLabel), 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(idLabel), 0, 1, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(usableLabel), 0, 1, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(pluralLabel), 0, 1, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(luckLabel), 0, 1, 4, 5, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(defLabel), 0, 1, 5, 6, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(powLabel), 0, 1, 6, 7, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(strLabel), 0, 1, 7, 8, Gtk::SHRINK, Gtk::SHRINK);
	
	// entries
	table->attach(*manage(nameEntry), 1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(idEntry), 1, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(usableCB), 1, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(pluralCB), 1, 2, 3, 4, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(luckEntry), 1, 2, 4, 5, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(defEntry), 1, 2, 5, 6, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(powEntry), 1, 2, 6, 7, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(strEntry), 1, 2, 7, 8, Gtk::SHRINK, Gtk::SHRINK);
	
	// add into parent containers
	sWindow->add(*manage(table));
	frame->add(*manage(sWindow));
	frame->set_size_request(373, 170);
	
	// buttons box
	buttonBox->pack_start(*manage(okButton));
	buttonBox->pack_start(*manage(cancelButton));
	
	// pack widgets
	vb->pack_start(*manage(titleLabel));
	vb->pack_start(*manage(frame));
	vb->pack_start(*manage(buttonBox));
	
	// vb to main container
	add(*manage(vb));
	
	// show widgets
	show_all_children();
};

// function to emit a save signal
void Wizard::saveItem() {
	sigSaveItemRequest().emit();
	hide();
};

// function to check if all required info was filled in
void Wizard::validate() {
	if (!nameEntry->get_text().empty() && !idEntry->get_text().empty() && !luckEntry->get_text().empty() &&
	    !defEntry->get_text().empty() && !powEntry->get_text().empty() && !strEntry->get_text().empty())
		okButton->set_sensitive();
	
	else
		okButton->set_sensitive(false);
};

void Wizard::validateInsertText(const Glib::ustring&, int*) {
	validate();
};

void Wizard::validateDeleteText(int, int) {
	validate();
};
