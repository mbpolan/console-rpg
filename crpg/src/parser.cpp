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
// parser.cpp: implementations of Parser class

#include "exception.h"
#include "parser.h"

// constructor
Parser::Parser(std::string path): filePath(path) {
	lState=lua_open();
	
	// try to load the file
	if (lua_dofile(lState, path.c_str()))
		throw CLoadErrorEx();
};

// destructor
Parser::~Parser() {
	if (lState)
		lua_close(lState);
};
 
// function to get a string value from the lua state
std::string Parser::getStringValue(std::string variable) {
	lua_getglobal(lState, variable.c_str());
	
	// get the string length
	int length=(int) lua_strlen(lState, -1);
	
	// create a new std::string
	std::string s(lua_tostring(lState, -1), length);
	
	// remove this from the stack
	lua_pop(lState, 1);
	
	// return this string
	return s;
};

// function to get an int value from the lua state
int Parser::getIntegralValue(std::string variable) {
	lua_getglobal(lState, variable.c_str());
	
	// get this value via lua_tonumber()
	int val=(int) lua_tonumber(lState, -1);
	
	// remove this from the stack
	lua_pop(lState, 1);
	
	// return the value
	return val;
};
