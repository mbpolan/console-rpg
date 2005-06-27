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
// mainwindow.cpp: implementations of MainWindow class

#include <iostream>
#include <gtkmm/cellrenderertoggle.h>
#include <gtkmm/dialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <libxml/parser.h>
#include <sstream>
#include "mainwindow.h"

// constructor
MainWindow::MainWindow(): Gtk::Window() {
	set_title("Console RPG Item Maker"); 
	
	// create the menu bars
	actionGroup=Gtk::ActionGroup::create();
	
	// add menus and action
	actionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW, "_New", "Create a new database"),
			 sigc::mem_fun(*this, &MainWindow::newDatabase));
			 
	actionGroup->add(Gtk::Action::create("FileOpenXML", "_XML"),
			 sigc::mem_fun(*this, &MainWindow::openDatabaseXML));
			
	actionGroup->add(Gtk::Action::create("FileSaveXML", "_XML"),
			 sigc::mem_fun(*this, &MainWindow::saveDatabaseXML));
			
	actionGroup->add(Gtk::Action::create("FileOpenBin", "_Binary"),
			 sigc::mem_fun(*this, &MainWindow::openDatabaseBin));
		
	actionGroup->add(Gtk::Action::create("FileSaveBin", "_Binary"),
			 sigc::mem_fun(*this, &MainWindow::saveDatabaseBin));
			
	actionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT, "_Quit", "Quit CRPG Item Maker"),
			 sigc::mem_fun(*this, &MainWindow::hide));
			 
	actionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::HELP, "_About", "About CRPG Item Maker"),
			 sigc::mem_fun(*this, &MainWindow::aboutThis));
			
	actionGroup->add(Gtk::Action::create("FileMenu", "File"));
	actionGroup->add(Gtk::Action::create("FileMenuOpen", Gtk::Stock::OPEN, "Open", "Open a database"));
	actionGroup->add(Gtk::Action::create("FileMenuSave", Gtk::Stock::SAVE, "Save", "Save this database"));
	actionGroup->add(Gtk::Action::create("HelpMenu", "Help"));
	
	// create the ui manager
	uiManager=Gtk::UIManager::create();
	uiManager->insert_action_group(actionGroup);
	
	// create the ui string
	try {
		Glib::ustring buffer=
		"<ui>"
		"	<menubar name='MainMenuBar'>"
		"		<menu action='FileMenu'>"
		"			<menuitem action='FileNew'/>"
		"			<menu action='FileMenuOpen'>"
		"				<menuitem action='FileOpenBin'/>"
		"				<menuitem action='FileOpenXML'/>"
		"			</menu>"
		"			<menu action='FileMenuSave'>"
		"				<menuitem action='FileSaveBin'/>"
		"				<menuitem action='FileSaveXML'/>"
		"			</menu>"
		"			<menuitem action='FileQuit'/>"
		"		</menu>"
		"		<menu action='HelpMenu'>"
		"			<menuitem action='HelpAbout'/>"
		"		</menu>"
		"	</menubar>"
		"</ui>";
		
		// add the string
		uiManager->add_ui_from_string(buffer);
	}
	
	// catch exceptions
	catch (const Glib::Error &e) {
		std::cout << "Unable to make menus: " << e.what() << std::endl;
		exit(1);
	}
	
	// create a menubar widget
	Gtk::VBox *vb=new Gtk::VBox;
	Gtk::Widget *mBar=uiManager->get_widget("/MainMenuBar");
	if (mBar)
		 vb->pack_start(*manage(mBar), Gtk::PACK_SHRINK);
		
	// create main table
	table=new Gtk::Table(4, 3, false);
	table->set_spacings(2);
	
	// create the label
	titleLabel=new Gtk::Label;
	titleLabel->set_markup("<b>Console RPG Item Maker</b>");
	
	// create buttons
	addItemButton=new Gtk::Button("Add Item");
	addItemButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::startItemWizard));
	
	rmItemButton=new Gtk::Button("Remove Item");
	rmItemButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::startRmItemWizard));
	
	editItemButton=new Gtk::Button("Edit Item");
	editItemButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::startEditItemWizard));
	
	// create the tree view
	sWindow=new Gtk::ScrolledWindow;
	lstore=Gtk::ListStore::create(colRec);
	tview=new Gtk::TreeView(lstore);
	
	// append columns
	tview->append_column_editable("Name", colRec.name);
	tview->append_column("ID", colRec.id);
	tview->append_column_editable("Usable", colRec.usable);
	tview->append_column_editable("Plural", colRec.plural);
	tview->append_column("Luck", colRec.luck);
	tview->append_column("Defense", colRec.defense);
	tview->append_column("Power", colRec.power);
	tview->append_column("Strength", colRec.strength);
	
	// resizable columns
	for (int i=0; i<7; i++)
		tview->get_column(i)->set_resizable(true);
	
	// make sure rows are reorderable
	tview->set_reorderable(true);
	
	sWindow->add(*manage(tview));
	sWindow->set_size_request(400, 290);
	
	// attach widgets
	table->attach(*manage(vb), 0, 3, 0, 1/*, Gtk::SHRINK*/);
	table->attach(*manage(titleLabel), 0, 3, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(addItemButton), 0, 1, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(rmItemButton), 1, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(editItemButton), 2, 3, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(sWindow), 0, 3, 3, 4);
	
	add(*manage(table));
	
	show_all_children();
};

// destructor
MainWindow::~MainWindow() {
	// clean the queue
	for (std::list<Gtk::Widget*>::iterator it=destroyQueue.begin(); it!=destroyQueue.end(); ++it) {
		if ((*it)) {
			delete (*it);
			it=destroyQueue.erase(it);
		}
	}
};

void MainWindow::newDatabase() {
	// check if there are any rows
	if (!lstore->children().empty()) {
		Gtk::MessageDialog mw(*this, "Would you like to save your current item database?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
		int id=mw.run();
		
		// should we save?
		if (id==(-8))
			saveDatabaseXML();
	}
	
	// make a new database
	lstore->clear();
};

void MainWindow::openDatabaseXML() {
	// open an xml doc
	Gtk::FileChooserDialog fcd(*this, "Open");
	fcd.add_button("Open", 0x00);
	fcd.add_button("Cancel", 0x01);
	
	if (fcd.run()==0x00) {
		xmlDocPtr doc=xmlParseFile(fcd.get_filename().c_str());
		
		// check if this doc was opened
		if (doc) {
			xmlNodePtr root, ptr;
			root=xmlDocGetRootElement(doc);
			
			// check the root node
			if (strcmp((const char*) root->name, "items-db")!=0) {
				Gtk::MessageDialog md(*this, "Bad document root node!", true);
				md.run();
				
				return;
			}
			
			ptr=root->children;
			
			// get a count of items
			int count=atoi((const char*) xmlGetProp(ptr, (const xmlChar*) "count"));
			
			// load each item
			xmlNodePtr item=ptr->children, attr;
			Gtk::TreeModel::Row row;
			for (int i=0; i<count; i++) {
				// get item attributes
				std::string name=(std::string) (const char*) xmlGetProp(item, (const xmlChar*) "name");
				std::string id=(std::string) (const char*) xmlGetProp(item, (const xmlChar*) "id");
				std::string usable=(std::string) (const char*) xmlGetProp(item, (const xmlChar*) "usable");
				std::string plural=(std::string) (const char*) xmlGetProp(item, (const xmlChar*) "plural");
				
				// load skill attributes
				attr=item->children;
				
				std::string luck=(std::string) (const char*) xmlGetProp(attr, (const xmlChar*) "luck");
				std::string def=(std::string ) (const char*) xmlGetProp(attr, (const xmlChar*) "defense");
				std::string pow=(std::string) (const char*) xmlGetProp(attr, (const xmlChar*) "power");
				std::string str=(std::string) (const char*) xmlGetProp(attr, (const xmlChar*) "strength");
				
				// add a row to the list
				row=*(lstore->append());
				row[colRec.name]=name;
				row[colRec.id]=id;
				row[colRec.usable]=usable=="1" ? true : false;
				row[colRec.plural]=plural=="1" ? true : false;
				row[colRec.luck]=luck;
				row[colRec.defense]=def;
				row[colRec.power]=pow;
				row[colRec.strength]=str;
				
				// next item
				item=item->next;
			}
			
			xmlFreeDoc(doc);
			
			// display a message
			Gtk::MessageDialog fmd(*this, "Database loaded successfully.", true);
			fmd.run();
			
			return;
		}
		
		Gtk::MessageDialog fmd(*this, "Unable to load document.", true);
	}
};

void MainWindow::saveDatabaseXML() {
	// save in XML format
	xmlDocPtr doc=xmlNewDoc((const xmlChar*) "1.0");
	xmlNodePtr root, ptr;
	std::stringstream ss;
	
	// new doc node
	doc->children=xmlNewDocNode(doc, NULL, (const xmlChar*) "items-db", NULL);
	
	root=doc->children;
	ptr=xmlNewChild(root, NULL, (const xmlChar*) "items", NULL);
	
	// save the amount of items
	int count=lstore->children().size();
	ss << count;
	
	xmlSetProp(ptr, (const xmlChar*) "count", (const xmlChar*) ss.str().c_str());
	ss.str("");
	
	// save each item
	xmlNodePtr item, attr;
	for (Gtk::TreeModel::iterator it=lstore->children().begin(); it!=lstore->children().end(); ++it) {
		if ((*it)) {
			item=xmlNewChild(ptr, NULL, (const xmlChar*) "item", NULL);
			
			// set general attributes
			ss << (*it)[colRec.name];
			xmlSetProp(item, (const xmlChar*) "name", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			ss << (*it)[colRec.id];
			xmlSetProp(item, (const xmlChar*) "id", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			ss << (*it)[colRec.usable];
			xmlSetProp(item, (const xmlChar*) "usable", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			ss << (*it)[colRec.plural];
			xmlSetProp(item, (const xmlChar*) "plural", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			// set skill attributes
			attr=xmlNewChild(item, NULL, (const xmlChar*) "attributes", NULL);
			
			// luck boost
			ss << (*it)[colRec.luck];
			xmlSetProp(attr, (const xmlChar*) "luck", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			// defense boost
			ss << (*it)[colRec.defense];
			xmlSetProp(attr, (const xmlChar*) "defense", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			// power boost
			ss << (*it)[colRec.power];
			xmlSetProp(attr, (const xmlChar*) "power", (const xmlChar*) ss.str().c_str());
			ss.str("");
			
			// strength boost
			ss << (*it)[colRec.strength];
			xmlSetProp(attr, (const xmlChar*) "strength", (const xmlChar*) ss.str().c_str());
			ss.str("");
		}
	}
	
	// wrap up
	xmlKeepBlanksDefault(1);
	
	// get the save path
	Gtk::FileChooserDialog fcd(*this, "Save", Gtk::FILE_CHOOSER_ACTION_SAVE);
	fcd.add_button("Save", 0x00);
	fcd.add_button("Cancel", 0x01);
	
	if (fcd.run()==0x00) {
		// get the path
		Glib::ustring path=fcd.get_filename();
	
		// save this database
		xmlSaveFile(path.c_str(), doc);
		xmlFreeDoc(doc);
	
		// present a message dialog
		Gtk::MessageDialog md(*this, "Your database was saved successfully.", true);
		md.run();
	}
};

// open a binary database file
void MainWindow::openDatabaseBin() {
	Gtk::FileChooserDialog fcd(*this, "Open");
	fcd.add_button("Open", 0x00);
	fcd.add_button("Cancel", 0x01);
	
	if (fcd.run()==0x00) {
		FILE *f=fopen(fcd.get_filename().c_str(), "r");
		std::stringstream ss;
		if (f) {
			// first 4 bytes are the header
			if (!(fgetc(f)=='C' && fgetc(f)=='R' &&
			      fgetc(f)=='P' && fgetc(f)=='G')) {
			      	Gtk::MessageDialog md(*this, "This is not a CRPG item database file!", true);
				md.run();
				return;
			}
			
			// get a count
			int count=fgetc(f);
			Gtk::TreeModel::Row row;
			for (int i=0; i<count; i++) {
				// id
				int id=fgetc(f);
				
				// name
				int length=fgetc(f);
				std::string name;
				for (int j=0; j<length; j++)
					name+=(char) fgetc(f);
				
				// usable/plural
				bool usable=fgetc(f);
				bool plural=fgetc(f);
				
				// attributes
				int def=fgetc(f);
				int luck=fgetc(f);
				int pow=fgetc(f);
				int str=fgetc(f);
				
				// end byte
				fgetc(f);
				
				// save this item
				row=*(lstore->append());
				row[colRec.name]=name;
				
				ss << id;
				row[colRec.id]=ss.str();
				ss.str("");
				
				ss << def;
				row[colRec.defense]=ss.str();
				ss.str("");
				
				ss << luck;
				row[colRec.luck]=ss.str();
				ss.str("");
				
				ss << pow;
				row[colRec.power]=ss.str();
				ss.str("");
				
				ss << str;
				row[colRec.strength]=ss.str();
				ss.str("");
				
				row[colRec.usable]=usable;
				row[colRec.plural]=plural;
			}
			fclose(f);
			
			// message
			Gtk::MessageDialog md(*this, "Your database was loaded successfully.", true);
			md.run();
			return;
		}
		
		Gtk::MessageDialog md(*this, "Unable to open selected file.", true);
		md.run();
	}
};

// function to save the database to binary
void MainWindow::saveDatabaseBin() {
	Gtk::FileChooserDialog fcd(*this, "Save", Gtk::FILE_CHOOSER_ACTION_SAVE);
	fcd.add_button("Save", 0x00);
	fcd.add_button("Cancel", 0x01);
	
	if (fcd.run()==0x00) {
		FILE *f=fopen(fcd.get_filename().c_str(), "w");
		std::stringstream ss;
		if (f) {
			// save the header first
			fputc('C', f);
			fputc('R', f);
			fputc('P', f);
			fputc('G', f);
			
			// count
			fputc(lstore->children().size(), f);
			
			// save each item
			for (Gtk::TreeModel::iterator it=lstore->children().begin(); it!=lstore->children().end(); ++it) {
				if ((*it)) {
					// id
					ss << (*it)[colRec.id];
					fputc(atoi(ss.str().c_str()), f);
					ss.str("");
					
					// name
					ss << (*it)[colRec.name];
					std::string name=ss.str();
					fputc(name.size(), f);
					for (int j=0; j<name.size(); j++)
						fputc(name[j], f);
					ss.str("");
					
					// attributes
					ss << (*it)[colRec.usable];
					fputc(atoi(ss.str().c_str()), f);
					ss.str("");
					
					ss << (*it)[colRec.plural];
					fputc(atoi(ss.str().c_str()), f);
					ss.str("");
					
					ss << (*it)[colRec.defense];
					fputc(atoi(ss.str().c_str()), f);
					ss.str("");
					
					ss << (*it)[colRec.luck];
					fputc(atoi(ss.str().c_str()), f);
					ss.str("");
					
					ss << (*it)[colRec.power];
					fputc(atoi(ss.str().c_str()), f);
					ss.str("");
					
					ss << (*it)[colRec.strength];
					fputc(atoi(ss.str().c_str()), f);
					ss.str("");
					
					// end byte
					fputc(0x00, f);
				}
			}
			fclose(f);
			
			// message
			Gtk::MessageDialog md(*this, "Your database was saved successfully.", true);
			md.run();
			return;
		}
		
		Gtk::MessageDialog md(*this, "Unable to save file.", true);
	}
};

void MainWindow::aboutThis() {
};

// signal handler to start the item wizard
void MainWindow::startItemWizard() {
	Wizard *w=new Wizard;
	wizard=w;
	w->present();
	w->sigSaveItemRequest().connect(sigc::mem_fun(*this, &MainWindow::addItem));
	
	// remember to destroy this
	destroyQueue.push_back(w);
};

void MainWindow::startRmItemWizard() {
	// first check if there are any items at all
	if (lstore->children().empty()) {
		Gtk::MessageDialog md(*this, "There are no items in the database.", true);
		md.run();
		return;
	}

	Gtk::Dialog *d=new Gtk::Dialog("Remove Item", *this, true, true);
	d->set_border_width(4);
	
	// format the dialog
	Gtk::VBox *vbox=d->get_vbox();
	
	// add a text combo box 
	Gtk::ComboBoxText *cb=new Gtk::ComboBoxText;
	
	// cycle through the items
	for (Gtk::TreeModel::iterator it=lstore->children().begin(); it!=lstore->children().end(); ++it) {
		if ((*it)) {
			Glib::ustring text=(*it)[colRec.name];
			
			// append this item
			cb->append_text(text);
		}
	}
	if (!lstore->children().empty())
		cb->set_active(0);
	
	// label
	Gtk::Label *lab=new Gtk::Label("Select the item you want to remove.");
	
	// pack widgets
	vbox->pack_start(*manage(lab), Gtk::PACK_SHRINK);
	vbox->pack_start(*manage(cb), Gtk::PACK_SHRINK);
	
	// add buttons
	d->add_button("OK", 0x00);
	d->add_button("Cancel", 0x01);
	d->show_all_children();
	
	// run the dialog
	int id=d->run();
	
	// check the choice
	if (id==0x00) {
		Glib::ustring item=cb->get_active_text();
		
		// remove the row
		for (Gtk::TreeModel::iterator it=lstore->children().begin(); it!=lstore->children().end(); ++it) {
			if ((*it) && (*it)[colRec.name]==item) {
				lstore->erase(it);
				break;
			}
		}
	}
	
	// free memory
	delete d;
};

// function to launch the item editor wizard
void MainWindow::startEditItemWizard() {
	// first check if there are any items at all
	if (lstore->children().empty()) {
		Gtk::MessageDialog md(*this, "There are no items in the database.", true);
		md.run();
		return;
	}

	Gtk::Dialog *d=new Gtk::Dialog("Edit Item", *this, true, true);
	d->set_border_width(4);
	
	// format the dialog
	Gtk::VBox *vbox=d->get_vbox();
	
	// add a text combo box 
	Gtk::ComboBoxText *cb=new Gtk::ComboBoxText;
	
	// cycle through the items
	for (Gtk::TreeModel::iterator it=lstore->children().begin(); it!=lstore->children().end(); ++it) {
		if ((*it)) {
			Glib::ustring text=(*it)[colRec.name];
			
			// append this item
			cb->append_text(text);
		}
	}
	if (!lstore->children().empty())
		cb->set_active(0);
	
	// label
	Gtk::Label *lab=new Gtk::Label("Select the item you want to edit.");
	
	// pack widgets
	vbox->pack_start(*manage(lab), Gtk::PACK_SHRINK);
	vbox->pack_start(*manage(cb), Gtk::PACK_SHRINK);
	
	// add buttons
	d->add_button("OK", 0x00);
	d->add_button("Cancel", 0x01);
	d->show_all_children();
	
	// run the dialog
	int id=d->run();
	
	// check the choice
	if (id==0x00) {
		Wizard *w=new Wizard(true);
		w->setOriginalItem(cb->get_active_text());
		
		// update pointer to wizard
		wizard=w;
		
		// iterate over the rows and find the target row. then preload the entries in the wizard with values
		// stored in the model
		for (Gtk::TreeModel::iterator it=lstore->children().begin(); it!=lstore->children().end(); ++it) {
			if ((*it) && (*it)[colRec.name]==cb->get_active_text().c_str()) {
				// preload entries
				w->nameEntry->set_text((*it)[colRec.name]);
				w->idEntry->set_text((*it)[colRec.id]);
				w->luckEntry->set_text((*it)[colRec.luck]);
				w->defEntry->set_text((*it)[colRec.defense]);
				w->powEntry->set_text((*it)[colRec.power]);
				w->strEntry->set_text((*it)[colRec.strength]);
				w->usableCB->set_active((*it)[colRec.usable] ? 0 : 1);
				w->pluralCB->set_active((*it)[colRec.plural] ? 0 : 1);
		
				w->present();
				w->sigSaveItemRequest().connect(sigc::mem_fun(*this, &MainWindow::editItem));
		
				// add to queue
				this->destroyQueue.push_back(w);
				
				break;
			}
		}
	}
	
	// free memory
	delete d;
};

// function to add an item to the database
void MainWindow::addItem() {
	// append a row
	Gtk::TreeModel::Row row=*(lstore->append());

	row[colRec.name]=wizard->nameEntry->get_text();
	row[colRec.id]=wizard->idEntry->get_text();
	row[colRec.usable]=wizard->usableCB->get_active_text()=="Yes" ? true : false;
	row[colRec.plural]=wizard->pluralCB->get_active_text()=="Yes" ? true : false;
	row[colRec.luck]=wizard->luckEntry->get_text();
	row[colRec.defense]=wizard->defEntry->get_text();
	row[colRec.power]=wizard->powEntry->get_text();
	row[colRec.strength]=wizard->strEntry->get_text();
};

// function to remove an item from the list
void MainWindow::removeItem() {
	Glib::RefPtr<Gtk::TreeView::Selection> sel=tview->get_selection();
	if (sel) {
		Gtk::TreeModel::iterator it=sel->get_selected();
		
		if ((*it) && it)
			lstore->erase(it);
	}
};

// function to edit an item
void MainWindow::editItem() {
	for (Gtk::TreeModel::iterator it=lstore->children().begin(); it!=lstore->children().end(); ++it) {
		if ((*it) && (*it)[colRec.name]==wizard->getOriginalItem().c_str()) {
			(*it)[colRec.name]=wizard->nameEntry->get_text();
			(*it)[colRec.id]=wizard->idEntry->get_text();
			(*it)[colRec.usable]=wizard->usableCB->get_active_text()=="Yes" ? true : false;
			(*it)[colRec.plural]=wizard->pluralCB->get_active_text()=="Yes" ? true : false;
			(*it)[colRec.luck]=wizard->luckEntry->get_text();
			(*it)[colRec.defense]=wizard->defEntry->get_text();
			(*it)[colRec.power]=wizard->powEntry->get_text();
			(*it)[colRec.strength]=wizard->strEntry->get_text();
		}
	}
};
