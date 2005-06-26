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
// player.cpp: implementations of the Player class and others

#include "definitions.h"
#include "player.h"

// default constructor for Player
Player::Player(): Creature(), traits(0, 0, 0, 0) {
};

// constructor taking various parameters
Player::Player(std::string _name, Position pos, PlayerTraits ptraits, int hp, int hpNow, int mp, int mpNow): 
		Creature(_name, pos, hp, hpNow), traits(ptraits), maxMagicPts(mp), magicPts(mpNow) {
};

// destructor
Player::~Player() {
	delete [] equipment;
};

// function to equip an item
Item* Player::equip(int slot, Item *item) {
	if (isEquipped(slot)) {
		Item *prev=equipment[slot];
		equipment[slot]=item;
		
		// return the previously equipped item
		return prev;
	}
	
	else {
		equipment[slot]=item;
		return NULL;
	}
};

// function to unequip an item
Item* Player::unequip(int slot) {
	if (isEquipped(slot)) {
		Item *item=equipment[slot];
		equipment[slot]=0;
		
		return item;
	}
	
	else
		return NULL;
};

// function to check if a slot is occuppied
bool Player::isEquipped(int slot) {
	if (!equipment[slot])
		return false;
	
	else
		return true;
};
