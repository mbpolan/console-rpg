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
// eventprocessor.h: the EventProcessor class

#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

#include <queue>
#include "event.h"

/** Class that manages the execution of events.
  * EventProcessor is a convenience class that helps to manage to processing
  * and execution of Event objects. Events can be added to the queue by calling
  * appendEvent().
  *
  * This class uses the STL's queue template to manage Events.
*/
class EventProcessor {
	public:
		/// Constructor
		EventProcessor();
		
		/// Destructor
		virtual ~EventProcessor();
		
		/** Function that adds an event to the queue
		  * \param e The event to be added to the event queue
		*/
		void appendEvent(Event *e);
		
	protected:
		/// Function to initialize the internal event thread
		static void* initThread(void*);
		
		/// The event queue
		std::queue<Event*> eventQueue;
};

#endif
