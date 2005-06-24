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
// timer.cpp: implementations of Timer class

#include "timer.h"

// function to initialize the timer
void Timer::init() {
	if (running)
		throw CTimerRunningEx();
	
	else {
		running=true;
		initTime=clock();
	}
};

// function to stop the timer
void Timer::halt() {
	if (!running)
		throw CTimerStoppedEx();
	
	else
		running=false;
};

// function to reset the timer
void Timer::reset() {
	if (!running)
		throw CTimerStoppedEx();
	
	else
		initTime=0;
};

// function to get the time in microseconds that passed
double Timer::time() const {
	if (!running)
		throw CTimerStoppedEx();
	
	return (double) (clock()-initTime/CLOCKS_PER_SEC);
};
