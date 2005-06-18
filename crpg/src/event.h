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
// event.h: Event class

#ifndef EVENT_H
#define EVENT_H

#include <iostream>

class Event {
	public:
		/// Factory function to create an event
		static Event* create(std::string name, void* (*_routine)(void*), void *data) {
			Event *e=new Event;
			e->eventName=name;
			e->routine=_routine;
			e->eventData=data;
			
			return e;
			
		};
		
		/// Name for this event
		std::string eventName;
		
		/// Data for this event
		void *eventData;
		
		/// Routine to do
		void* (*routine)(void*);
		
	private:
		/// Hidden constructor
		Event() {};
};

#endif
