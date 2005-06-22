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
// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <gtkmm/actiongroup.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/table.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>
#include "wizard.h"

// main window that is first shown
class MainWindow: public Gtk::Window {
	public:
		MainWindow();
		virtual ~MainWindow();
		
	private:
		// signal handlers
		void newDatabase();
		void openDatabase();
		void saveDatabase();
		void aboutThis();
		void startItemWizard();
		void startRmItemWizard();
		void startEditItemWizard();
		void addItem();
		void removeItem();
		void editItem();
		
		// containers
		Gtk::ScrolledWindow *sWindow;
		Gtk::Table *table;
		
		// widgets
		Gtk::Label *titleLabel;
		Gtk::Button *addItemButton;
		Gtk::Button *rmItemButton;
		Gtk::Button *editItemButton;
		
		Gtk::TreeView *tview;
		Glib::RefPtr<Gtk::ListStore> lstore;
		
		// column record
		class ColumnRecord: public Gtk::TreeModel::ColumnRecord {
			public:
				ColumnRecord() {
					add(name);
					add(id);
					add(usable);
					add(luck);
					add(defense);
					add(power);
					add(strength);
				};
				
				// columns
				Gtk::TreeModelColumn<Glib::ustring> name;
				Gtk::TreeModelColumn<Glib::ustring> id;
				Gtk::TreeModelColumn<bool> usable;
				Gtk::TreeModelColumn<Glib::ustring> luck;
				Gtk::TreeModelColumn<Glib::ustring> defense;
				Gtk::TreeModelColumn<Glib::ustring> power;
				Gtk::TreeModelColumn<Glib::ustring> strength;
		};
		
		// instance of ColumnRecord class
		ColumnRecord colRec;
		
		// misc stuff
		Glib::RefPtr<Gtk::ActionGroup> actionGroup;
		Glib::RefPtr<Gtk::UIManager> uiManager;
		
		// item wizards
		Wizard *wizard;
		
		// destroy queue
		std::list<Gtk::Widget*> destroyQueue;
};

#endif
