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
// timer.h: the Timer class

#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include "exception.h"

/** Class that manages time.
  * Timer works just like a stopwatch. You can start the timer by calling
  * init() and stop it with halt(). This class is useful if you wish to
  * wait for a certain amount of time to pass before proceeding in the program.
  *
  * To get the amount of time (in microseconds) that passed since Timer was started
  * can be done by a call to time().
*/
class Timer { 
	public:
		/// Constructor
		Timer(): running(false), initTime(0) {};
		
		/// Destructor
		virtual ~Timer() {};
		
		/// Start the Timer
		/** Throws an instance of CTimerRunningEx if you call this
		  * function when the Timer is already running.
		*/
		void init();
		
		/// Stop the Timer.
		/** Throws an instance of CTimerStoppedEx if you call this
		  * function when the Timer is already stopped.
		*/
		void halt();
		
		/// Reset the timer back to 0 microseconds
		/** The Timer object must be already running! Throws an instance 
		  * of CTimerStoppedEx if you call this function when the Timer is 
		  * stopped.
		*/
		void reset();
		
		/** Get the time that passed since the timer was started.
		  * \return The amount of time in microseconds.
		*/
		double time() const;
		
		/** Check if this Timer is already running.
		  * \return true if running, otherwise false.
		*/
		bool isRunning() const { return running; };
		
	protected:
		/// Time when started
		clock_t initTime;
		
		/// Running
		bool running;
};

#endif
