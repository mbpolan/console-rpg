/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
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
 
 #include <sstream>
 #include "battlesystem.h"

// battleAction class constructor 
battleAction::battleAction() {
	buffer="";
	built=false;
};

// virtual battleAction method to reset data
void battleAction::clear() {
	buffer="";
	built=false;
};

// method to add bytes to the buffer
void battleAction::addByte(char byte) {
	if (buffer[0] != 0x00)
		buffer.insert(0, "0");
	
	buffer+=(char) byte;
};

// method to add another buffer into this
void battleAction::addBuffer(std::string buf, bool clear) {
	if (clear)
		buffer.clear();
	
	buffer+=buf;
};

// build the complete action
void battleAction::build() {
	if (buffer[0]!=(char) 0x00)
		buffer.insert(0, "0");
	
	// length
	buffer+=(char) 0x00;
};

 /***************************************************************************
  * Start attackAction class implementation
  **************************************************************************/

// attackAction class constructor  
attackAction::attackAction() {
 	attack_damage=0;
	mana_reduction=0;
	
	poisonous=false;
	electrifying=false;
	burning=false;
	strong=false;
};

// attackAction class constructor taking 2 ints
attackAction::attackAction(int damage, int mana_reduc) {
 	attack_damage=damage;
	mana_reduction=mana_reduc;
	
	poisonous=false;
	electrifying=false;
	burning=false;
	strong=false;
};

// clear the internal buffer
void attackAction::clear() {
	buffer="";
	
 	attack_damage=0;
	mana_reduction=0;
	
	poisonous=false;
	electrifying=false;
	burning=false;
	strong=false;
};

// add a byte to the internal buffer
void attackAction::addByte(char byte) {
	if (buffer.empty())
		buffer+=(char) 0x01;
	
	buffer+=(char) byte;
};

// add another buffer into this one
void attackAction::addBuffer(std::string buf, bool clear) {
	if (clear)
		buffer.clear();
	
	buffer+=buf;
};

// method for creating a finalized buffer for this attack object
void attackAction::build() {
	std::stringstream ss;
	
	// first check if we have an identifier
	if (buffer[0]!=(char) 0x01)
		buffer.insert(0, "1");
	
	// count of all bytes that are added
	int byte_count=0;
	
	// now add the damage and mana
	buffer+=attack_damage;
	buffer+=mana_reduction;
	byte_count+=2;
	
	// add effects
	buffer+=poisonous;
	buffer+=electrifying;
	buffer+=burning;
	buffer+=strong;
	byte_count+=4;
	
	ss << byte_count;
	
	// finally add the size
	buffer.insert(1, ss.str().c_str());
	
	// signify that this attack object is now built
	built=true;
	
	return;
};
