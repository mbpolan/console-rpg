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

 /***************************************************************************
  * Start spAttackAction class implementation
  **************************************************************************/

// spAttackAction default constructor
spAttackAction::spAttackAction(): attackAction(100, 0) {
	count=1;
};

// spAttackAction constructor taking extra count parameter
spAttackAction::spAttackAction(int damage, int mana_reduc, int _count): attackAction(damage, mana_reduc) {
	count=_count;
};

// method to add a byte to the buffer
void spAttackAction::addByte(char byte) {
	if (buffer[0]!=(char) 0x02)
		buffer.insert(0, "2");
	
	buffer+=(char) byte;
};

// method to add another buffer into this one
void spAttackAction::addBuffer(std::string buf, bool clear) {
	if (clear)
		buffer.clear();
	
	buffer+=buf;
};

// method to add an effect to take place on a specific turn
void spAttackAction::addTurnEffect(int turn, statusEffect e, bool replace) {
	if (effects[turn] && !replace)
		return;
	
	else if (!effects[turn])
		effects[turn]=e;
};

void spAttackAction::build() {
	std::stringstream ss;
	
	if (buffer[0]!=(char) 0x02)
		buffer.insert(0, "2");
	
	// count of all bytes
	int byte_count=0;
	
	// add damage and mana reduction first
	buffer+=attack_damage;
	buffer+=mana_reduction;
	byte_count+=2;
	
	// add a count of how many turns this attack lasts
	ss << count;
	buffer+=ss.str();
	byte_count+=1;
	ss.str("");
	
	// add turn effects
	for (int i=0; i<effects.size(); i++) {
		ss << effects[i];
		buffer+=ss.str();
		byte_count+=1;
		
		ss.str("");
	}
	
	// add initial attack effects
	buffer+=poisonous;
	buffer+=electrifying;
	buffer+=burning;
	buffer+=strong;
	byte_count+=4;
	
	// finally add the total amount of bytes
	ss << byte_count;
	buffer.insert(1, ss.str());
	
	// signify that this action is built
	built=true;
	
	return;
};

 /***************************************************************************
  * Start magicAttackAction class implementation
  **************************************************************************/

 // magicAttackAction constructor
 magicAttackAction::magicAttackAction(): spAttackAction() {
 	name="";
};

// makeAttackAction constructor taking extra parameters
magicAttackAction::magicAttackAction(int damage, int mana_reduc, int count, statusEffect init_effect): spAttackAction(damage, mana_reduc, count) {
	name="";
	effects[0]=init_effect;
};

// method for adding a byte to the buffer
void magicAttackAction::addByte(char byte) {
	if (buffer[0]!=(char) 0x03)
		buffer.insert(0, "3");
	
	buffer+=(char) byte;
};

// method for adding another buffer into this one
void magicAttackAction::addBuffer(std::string buf, bool clear) {
	if (clear)
		buffer.clear();
	
	buffer+=buf;
};

void magicAttackAction::build() {
	std::stringstream ss;
	
	if (buffer[0]!=(char) 0x03)
		buffer.insert(0, "3");
		
	// count of bytes
	int byte_count=0;
	
	// add damage and mana reduction
	buffer+=attack_damage;
	buffer+=mana_reduction;
	byte_count+=2;
	
	// add name length
	buffer+=name.length();
	byte_count+=1;
	
	// add the attack name
	buffer+=name;
	
	// add a count of how many turns this attack lasts
	ss << count;
	buffer+=ss.str();
	byte_count+=1;
	ss.str("");
	
	// add turn effects
	for (int i=0; i<effects.size(); i++) {
		ss << effects[i];
		buffer+=ss.str();
		byte_count+=1;
		
		ss.str("");
	}
	
	// add initial attack effects
	buffer+=poisonous;
	buffer+=electrifying;
	buffer+=burning;
	buffer+=strong;
	byte_count+=4;
	
	// finally add the total amount of bytes
	ss << byte_count;
	buffer.insert(1, ss.str());
	
	// signify that this action is built
	built=true;
	
	return;
};
