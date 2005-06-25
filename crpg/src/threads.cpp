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
// threads.cpp: implementations of Threads namespace

#include "threads.h"

// function to create a thread
int Threads::CreateThread(void *(*function) (void*), void *data) {
	// our thread
	pthread_t thread;

	// attribute
	pthread_attr_t attr;
	
	// initialize the attribute
	pthread_attr_init(&attr);
	
	// add a deattachable attribute
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	// create the thread and return the ID
	return (pthread_create(&thread, &attr, function, (void*) data));
}; 

// check threads for equality of ID's
int Threads::ThreadsEqual(TThread &thread1, TThread &thread2) {
	// check if both thread id's are the same
	return (pthread_equal(thread1, thread2));
};

// function to initialze a mutex
void Threads::MutexInit(TMutex &m) {
	// create a mutex attribute
	pthread_mutexattr_t attr;
	
	// initialze the mutex
	pthread_mutexattr_init(&attr);
	
	// set a PTHREAD_MUTEX_RECURSIVE_NP attribute
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	
	// initialize the mutex and its attribute
	pthread_mutex_init(&m, &attr);
};

// lock a thread
void Threads::LockMutex(TMutex &m) {
	// lock this mutex
	pthread_mutex_lock(&m);
};

// unlock a mutex
void Threads::UnlockMutex(TMutex &m) {
	// unlock this mutex
	pthread_mutex_unlock(&m);
};

// join two threads
int Threads::JoinThreads(TThread &t, void** status) {
	// join threads
	return (pthread_join(t, status));
};
