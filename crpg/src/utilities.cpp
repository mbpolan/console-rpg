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
// utilities.h: implementations of Utilities namespace functions

#include "definitions.h"
#include "utilities.h" 
 
// check to see if this word has a vowel in the beginning
bool Utilities::hasVowel(std::string str) {
	char a=str[0];
	if (a=='a' || a=='e' || a=='i' || a=='o' || a=='u' ||
	    a=='A' || a=='E' || a=='I' || a=='O' || a=='U')
		return true;
	
	else
		return false;
};

// convert a vocation to string
std::string Utilities::vocToString(VOCATION VOC) {
	std::string str;
	switch(VOC) {
		case VOCATION_KNIGHT: str="knight"; break;
		case VOCATION_PALADIN: str="paladin"; break;
		case VOCATION_MAGE: str="mage"; break;
	}
	
	return str;
};

// capitalize the first letter of a word
std::string Utilities::capFirst(std::string str) {
	std::string s;
	s+=toupper(str.c_str()[0]);
	str.erase(0,1);
	s+=str;
	
	return s;
};

// convert an int to player vocation
VOCATION Utilities::itov(int num) {
	switch(num) {
		case VOCATION_KNIGHT: return VOCATION_KNIGHT;
		case VOCATION_PALADIN: return VOCATION_PALADIN;
		case VOCATION_MAGE: return VOCATION_MAGE;
	}
};

// convert a load method to int
int Utilities::mtoi(std::string method) {
	std::transform(method.begin(), method.end(), method.begin(), tolower);
	if (method=="binary")
		return MAP_LOAD_METHOD_BINARY;
	
	else if (method=="xml")
		return MAP_LOAD_METHOD_XML;
	
	else
		return -1;
};
