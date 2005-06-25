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
// eventprocessor.cpp: implementations of EventProcessor class

#include <time.h>
#include "eventprocessor.h"
#include "threads.h"
using namespace Threads;

// constructor
EventProcessor::EventProcessor() {
	CreateThread(initThread, this);
};

// destructor
EventProcessor::~EventProcessor() {
	// clear the eventQueue
	for (int i=0; i<eventQueue.size(); i++) {
		Event *e=eventQueue.front();
		if (e) {
			eventQueue.pop();
			delete e;
		}
	}
};

// function to initialize the main thread for events
void* EventProcessor::initThread(void *data) {
	EventProcessor *ep=(EventProcessor*) data;
	
	// event loop
	while(1) {
		// check for events
		if (ep->eventQueue.size()!=0) {
			Event *e=ep->eventQueue.front();
			//std::cout << "DEBUG: found event: " << e->eventName << std::endl;
			
			// allocate memory for an EventData struct
			struct EventData *eData=(struct EventData*) malloc(sizeof(struct EventData));
			eData->ep=ep;
			eData->e=e;
			
			// create a thread to handle this event
			CreateThread(eventHandler, (void*) eData);
			
			ep->eventQueue.pop();
		}
	}
};

// function to add an event to the queue
void EventProcessor::appendEvent(Event *e) {
	eventQueue.push(e);
};

// function to handle event execution and wait times
void* EventProcessor::eventHandler(void *data) {
	// cast the void pointer to a struct
	struct EventData *eData=(struct EventData*) data;
	EventProcessor *ep=eData->ep;
	Event *e=eData->e;
	
	// wait for this event
	clock_t wait;
	wait=clock()+e->time*CLOCKS_PER_SEC;
	while(clock() < wait) {};
	
	// create a thread to handle this event's routine
	CreateThread(e->routine, e->eventData);
	
	delete eData;
	pthread_exit(NULL);
};
