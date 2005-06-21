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
			 
	actionGroup->add(Gtk::Action::create("FileOpen", Gtk::Stock::OPEN, "_Open", "Open a database"),
			 sigc::mem_fun(*this, &MainWindow::openDatabase));
			
	actionGroup->add(Gtk::Action::create("FileSave", Gtk::Stock::SAVE, "_Save", "Save this database"),
			 sigc::mem_fun(*this, &MainWindow::saveDatabase));
			
	actionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT, "_Quit", "Quit CRPG Item Maker"),
			 sigc::mem_fun(*this, &MainWindow::hide));
			 
	actionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::HELP, "_About", "About CRPG Item Maker"),
			 sigc::mem_fun(*this, &MainWindow::aboutThis));
			
	actionGroup->add(Gtk::Action::create("FileMenu", "File"));
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
		"			<menuitem action='FileOpen'/>"
		"			<menuitem action='FileSave'/>"
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
	table=new Gtk::Table(4, 2, false);
	table->set_spacings(2);
	
	// create the label
	titleLabel=new Gtk::Label;
	titleLabel->set_markup("<b>Console RPG Item Maker</b>");
	
	// create buttons
	addItemButton=new Gtk::Button("Add Item");
	addItemButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::startItemWizard));
	
	rmItemButton=new Gtk::Button("Remove Item");
	rmItemButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::startRmItemWizard));
	
	// create the tree view
	sWindow=new Gtk::ScrolledWindow;
	lstore=Gtk::ListStore::create(colRec);
	tview=new Gtk::TreeView(lstore);
	
	// append columns
	tview->append_column_editable("Name", colRec.name);
	tview->append_column("ID", colRec.id);
	tview->append_column_editable("Usable", colRec.usable);
	tview->append_column("Luck", colRec.luck);
	tview->append_column("Defense", colRec.defense);
	tview->append_column("Power", colRec.power);
	tview->append_column("Strength", colRec.strength);
	
	// resizable columns
	for (int i=0; i<7; i++)
		tview->get_column(i)->set_resizable(true);
	
	sWindow->add(*manage(tview));
	sWindow->set_size_request(400, 290);
	
	// attach widgets
	table->attach(*manage(vb), 0, 2, 0, 1/*, Gtk::SHRINK*/);
	table->attach(*manage(titleLabel), 0, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(addItemButton), 0, 1, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(rmItemButton), 0, 2, 2, 3, Gtk::SHRINK, Gtk::SHRINK);
	table->attach(*manage(sWindow), 0, 2, 3, 4);
	
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
			saveDatabase();
	}
	
	// make a new database
	lstore->clear();
};

void MainWindow::openDatabase() {
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
				usable=row[colRec.usable] ? "1" : "0";
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

void MainWindow::saveDatabase() {
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

void MainWindow::aboutThis() {
};

// signal handler to start the item wizard
void MainWindow::startItemWizard() {
	Wizard *w=new Wizard;
	wizard=w;
	w->present();
	w->signalSaveItemRequest().connect(sigc::mem_fun(*this, &MainWindow::addItem));
	
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

// function to add an item to the database
void MainWindow::addItem() {
	// append a row
	Gtk::TreeModel::Row row=*(lstore->append());

	row[colRec.name]=wizard->nameEntry->get_text();
	row[colRec.id]=wizard->idEntry->get_text();
	row[colRec.usable]=wizard->usableCB->get_active_text()=="Yes" ? true : false;
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
