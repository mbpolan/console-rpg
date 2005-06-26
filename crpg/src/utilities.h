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
// utilities.h: various functions that don't fit into classes

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include "player.h"

/// The Utility namespace
namespace Utilities {
	/// Checks to see if this word starts with a vowel
	bool hasVowel(std::string str);
	
	/// Convert a player's vocation to a string
	std::string vocToString(VOCATION voc);
	
	/// Capitalize the first letter of a string
	std::string capFirst(std::string str);
	
	/// Convert an int to VOCATION
	VOCATION itov(int num);
};

#endif
