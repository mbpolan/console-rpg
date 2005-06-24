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
// events.cpp: implementations of Events namespace functions

#include "event.h"
#include "events.h"
#include "game.h"
#include "timer.h"

// function to control time of day/night
void* Events::controlTime(void *data) {
	Game *game=(Game*) data;
	
	// initial timer
	Timer timer;
	timer.init();
	
	// change the day every set amount of time
	while(1) {
		// FIXME: get a more realistic time value here
		if (timer.time()==10*1000000) {
/*			if (game->isDay())
				game->setDay(false);
			
			else
				game->setDay(true);*/
			break;
		}
	}
	timer.halt();
	
	// keep this event in the queue
	game->appendEvent(Event::create("TIME_CONTROL_EVENT", &controlTime, game, 1000000));
	pthread_exit(NULL);
};
