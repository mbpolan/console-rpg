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
// exception.h: Exception and friend classes

#ifndef EXCEPTION_H
#define EXCEPTION_H

/** General exception class.
  * This is a base class from which all exceptions derive from.
*/
class CException {
	public:
		/** Constructor
		  * \param msg The error message this exception holds
		  * \param _fatal A fatal exception (halts program)
		*/
		CException(const char *msg, bool _fatal=false): message(msg), fatal(_fatal) {};
		
		/** Returns the exception message
		  * \return The message in an std::string
		*/
		const char* what() const { return message; };
		
		/** Returns whether or not this exception is fatal
		  * \return true if this exception is fatal, false otherwise
		*/
		bool isFatal() const { return fatal; };
	
	protected:
		/// Message
		const char* message;
		
		/// Whether or not this exception is fatal
		bool fatal;
};

/** File loading exception.
  * Exception thrown when a file can't be loaded. 
*/
class CLoadErrorEx: public CException {
	public:
		/// Constructor
		CLoadErrorEx(): CException("Unable to load file!", true) {};
};

#endif
