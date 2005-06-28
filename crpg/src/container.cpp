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
// container.cpp: implementations of Container class

#include "container.h"

// destructor
Container::~Container() {
	// clear out the contents
	ContainerIterator it=items.begin();
	while(it!=items.end()) {
		if ((*it)) {
			delete (*it);
			it=items.erase(it);
		}
		
		else
			++it;
	}
};

// overloaded operator<<
void Container::operator<<(Item *item) {
	addItem(item);
};

// function to add an item to the container
void Container::addItem(Item *item) {
	if (items.size()<maxItems)
		items.push_back(item);
};

// function to get an item by position
Item* Container::getItemByPos(int pos) {
	int c=0;
	for (ContainerIterator it=items.begin(); it!=items.end(); ++it) {
		if ((*it) && c==pos)
			return (*it);
		
		else
			c+=1;
	}
	
	return NULL;
};

// function to remove an item by position
void Container::removeItemByPos(int pos) {
	int c=0;
	for (ContainerIterator it=items.begin(); it!=items.end(); ++it) {
		if ((*it) && c==pos) {
			it=items.erase(it);
			break;
		}
		
		c+=1;
	}
};

// function to remove all items that match the specified id
void Container::removeItemsByID(int id) {
	ContainerIterator it=items.begin();
	while(it!=items.end()) {
		if ((*it) && (*it)->getID()==id) {
			it=items.erase(it);
			break;
		}
	}
};

// function to check if the container has this item
bool Container::hasItem(int id) {
	for (ContainerIterator it=items.begin(); it!=items.end(); ++it) {
		if ((*it) && (*it)->getID()==id)
			return true;
	}
	
	return false;
};

// function to check if another item can be added to the container
bool Container::canAddItem() const {
	if (items.empty())
		return true;
	
	else if (items.size()+1==maxItems)
		return false;
	
	else
		return true;
};

// function to display the contents of this Container
void Container::displayContents() {
	// lets first check if the backpack is empty
	if (this->empty()) {
		std::cout << "Your backpack is empty.\n";
		return;
	}
	
	// display each item in a numbered list
	std::cout << "Backpack Contents (" << items.size() <<  "/" << maxItems << ")";
	std::cout << "\n~~~~~~~~~~~~~~~\n";
	
	int c=0;
	for (ContainerIterator it=items.begin(); it!=items.end(); ++it) {
		if ((*it))
			std::cout << c+1 << ") " << (*it)->getName() << std::endl;
		
		c+=1;
	}
	std::cout << "~~~~~~~~~~~~~~~\n";
};
