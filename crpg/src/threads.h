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

#ifdef __LINUX__
#include <pthread.h>
#endif

#ifdef __WIN32__
#include <process.h>
#include <windows.h>
#endif

// Threads namespace
namespace Threads {
	#ifdef __LINUX__
	/// typedef'd pthread_mutex_t variable
	typedef pthread_mutex_t TMutex;
	
	/// typedef'd pthread_thread_t variable
 	typedef pthread_t TThread;
	
	/// typedef'd pthread_once_t variable
	typedef pthread_once_t TOnceThread;
	
	/// #define'd void* for Linux compilation
	#define TVoid void*
	#endif
	
	#ifdef __WIN32__
	/// typedef'd CRITICAL_SECTION variable
	typedef CRITICAL_SECTION TMutex;
	
	/// #define'd void for Win32 compilation
	#define TVoid void
	#endif

	/// Function to create a thread
	int CreateThread(TVoid (*function) (void*), void *data);
	
	/// Function to initialze a mutex
	void MutexInit(TMutex &m);
	
	/// Lock a mutex
	void LockMutex(TMutex &m);
	
	/// Unlock a mutex
	void UnlockMutex(TMutex &m);
	
	#ifdef __LINUX__
	/// Check threads for equality of ID's
	int ThreadsEqual(TThread &thread1, TThread &thread2);
	
	/// Join threads
	int JoinThreads(TThread &t, void** status);
	#endif
};

#endif
