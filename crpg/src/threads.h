/***************************************************************************
 *   Copyright (C) 2005 by KanadaKid                                       *
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
 ***************************************************************************
 * Simple threading functions using PThreads. All are inside the T         *
 * namespace.                                                              *
 **************************************************************************/
 
#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

// Threads namespace
namespace Threads {
	/// typedef'd pthread_mutex_t variable
	typedef pthread_mutex_t TMutex;
	
	/// typedef'd pthread_thread_t variable
 	typedef pthread_t TThread;
	
	/// typedef'd pthread_once_t variable
	typedef pthread_once_t TOnceThread;

	/// Function to create a thread
	int CreateThread(void *(*function) (void*), void *data);
	
	/// Check threads for equality of ID's
	int ThreadsEqual(TThread &thread1, TThread &thread2);
	
	/// Function to initialze a mutex
	void MutexInit(TMutex &m);
	
	/// Lock a mutex
	void LockMutex(TMutex &m);
	
	/// Unlock a mutex
	void UnlockMutex(TMutex &m);
	
	/// Join threads
	int JoinThreads(TThread &t, void** status);
};

#endif
