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
 // playerList.h: contains the playerList template

#ifndef playerlist_h
#define playerlist_h
 
#include <iostream>
  
const int size=100; // fixed size for template

// our template class
template <class T>
class playerList {
	public:
		// constructors/destructor
		playerList();
		playerList(int);
		~playerList();

		//overloaded operators
		playerList &operator=(const playerList&);
		playerList &operator+=(const playerList&);
		T &operator[](int offset);
		const T &operator[](int offset) const;

		// public accessor
		int getLength() const {return length;}
		
		// member functions
		void clear();
		void fill(T&);

		// other methods/operators
		template <class> friend std::ostream &operator<<(std::ostream&,playerList<T>&);

	private:
		T *AType; // type of playerList
		int length; // length of playerList
};
 
 /***************************************
 / Implementations of playerList class */

 // default constructor
template <class T>
playerList<T>::playerList():length(size) {
	AType=new T[length];

	for (int i=0;i<length;i++)
		AType[i]=0;
};

// constructor taking an int (size)
template <class T>
playerList<T>::playerList(int size):length(size) {
	AType=new T[length];
	
	for (int i=0;i<length;i++)
		AType[i]=0;
};

// destructor for playerList template
template <class T>
playerList<T>::~playerList() {
	delete [] AType;
	AType=0;
};

// overloaded operator=
template <class T>
playerList<T> &playerList<T>::operator=(const playerList &rhs) {
	if (this==&rhs)
		return *this;

	int length=rhs.getLength();
	
	delete [] AType;
	type=new T[length];
	for (int i=0;i<length;i++)
		type[i]=rhs[i];

	return *this;
};
 
// overloaded operator+=
// this could use some more work ;)
 template <class T>
 playerList<T>& playerList<T>::operator+=(const playerList<T> &rhs) {
 	int orig=length;
	int total=length+rhs.getLength();
	playerList<T> temp;
	
	length=total;
	for (int i=0;i<length;i++)
		temp[i]=AType[i];
	delete [] AType;
	AType=new T[total];
	
	for (int i=0;i<orig;i++)
		AType[i]=temp[i];
	
	for (int i=0;i<rhs.getLength();i++)
		AType[orig++]=rhs[i];
		
	return *this;
};

// overloaded operator[]
template <class T>
T &playerList<T>::operator[](int offset) {
	if (offset>length)
		return AType[length-1];
	else
		return AType[offset];
};

// overloaded operator[] (const)
template <class T>
const T &playerList<T>::operator[](int offset) const {
	if (offset>length)
		return AType[length-1];
	else
		return AType[offset];
};

// member function clear
template <class T>
void playerList<T>::clear() {
	for (int i=0;i<length;i++)
		AType[i]=0;
};

// member function fill
template <class T>
void playerList<T>::fill(T &type) {
	clear();

	for (int i=0;i<length;i++)
		AType[i]=type;
};

// overloaded operator<<
template <class T>
std::ostream &operator<<(std::ostream &output,playerList<T> &rhs) {
	for (int i=0;i<rhs.getLength();i++)
		output << "[" << i << "]: " << rhs[i] << std::endl;
	return output;
};

#endif
