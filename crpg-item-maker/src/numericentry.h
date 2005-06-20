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
 
#ifndef NUMERICENTRY_H
#define NUMERICENTRY_H

#include <iostream>

// an entry that accepts only numeric input
class NumericEntry: public Gtk::Entry {
	public:
		NumericEntry() {};
		virtual ~NumericEntry() {};
		
		// signals
		sigc::signal<void>& sigTextInserted() { return sig_textInserted; };
		sigc::signal<void>& sigTextDeleted() { return sig_textDeleted; };
		
	protected:
		// signal handlers
		virtual void insert_text_vfunc(const Glib::ustring &text, int &pos) {
			if ((atof(text.c_str()) && text!="0") || text=="0" || text=="." || text=="-") {
				Gtk::Entry::insert_text_vfunc(text, pos);
				
				// make sure to emit the signal _only_ when numbers are inserted
				if (text!="-" && text!=".")
					sigTextInserted().emit();
			}
		};
		
		virtual void on_delete_text(int start_pos, int end_pos) {
			Gtk::Editable::on_delete_text(start_pos, end_pos);
			sigTextDeleted().emit();
		};
		
		sigc::signal<void> sig_textInserted;
		sigc::signal<void> sig_textDeleted;
};

#endif
