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
// parser.h: the Parser class

#ifndef PARSER_H
#define PARSER_H

#include <iostream>

extern "C" {
#include <lualib.h>
#include <lauxlib.h> 
#include <lua.h>
};

/** A simple Lua file parser.
  * The Parser class does the job of loading and getting
  * attributes from Lua files. When you call Parser's constructor,
  * make sure to specify the path to a file that you wish to load.
  * If the path points to an invalid file, an instance of CLoadErrorEx
  * will be thrown.
*/
class Parser {
	public:
		/** Constructor
		  * \param path The path to the target file
		*/
		Parser(std::string path);
		
		/// Destructor
		virtual ~Parser();
		
		/** Get a string value from the file
		  * \param variable The variable to lookup
		  * \return The string attribute associated with the target variable
		*/
		std::string getStringValue(std::string variable);
		
		/** Get an integral value from the file
		  * \param variable The variable to lookup
		  * \return The integral attribute associated with the target variable
		*/
		int getIntegralValue(std::string variable);
		
	protected:
		/// Instance of lua_State
		lua_State *lState;
		
		/// The path to the loaded file
		std::string filePath;
};

#endif
