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
#include "threads.h"

/** Class that prepares an event for execution.
  * Event is a class that stores two members: a pointer to a routine
  * function and the arguments for that function. An instance of Event
  * should be made available to the Game event thread where it will be
  * processed and executed.
*/
class Event {
	public:
		/** Factory function to create an event
		  * \param name A name for this event
		  * \param _routine The function to be executed
		  * \param data Data passed to the routine function
		  * \param time The amount of time in seconds that needs to pass for this event to take place
		*/
		static Event* create(std::string name, TVoid (*_routine)(void*), void *data, double _time) {
			Event *e=new Event;
			e->eventName=name;
			e->routine=_routine;
			e->eventData=data;
			e->time=_time;
			
			return e;
			
		};
		
		/// Name for this event
		std::string eventName;
		
		/// Data for this event
		void *eventData;
		
		/// Routine to do
		TVoid (*routine)(void*);
		
		/// Expire time
		double time;
		
	private:
		/// Hidden constructor
		Event() {};
};

#endif
