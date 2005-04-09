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

#ifndef db_h
#define db_h
 
// db.h: template class 'database' that holds various info depending on type
#include <fstream>
#include <vector>

#include "items.h"

// forward declarations
class item;

// template class database
template <class T>
class database {
	public:
		database(int maxSize=0);

    // accessor methods
    int size() const {return data.size();}

    void addObject(const T);
    void removeObject(int);

    T* getObject(int) const;

  private:
    std::vector<T> data;
    int dbMaxSize; // maximum size

    bool ignoreSize; // ignore size restrictions?

    void resync();
};

/******************************************************
 * Start template class database implementations...   *
 *****************************************************/

// constructor
template <class T>
database<T>::database(int maxSize): dbMaxSize(maxSize) {
  if (maxSize > 0)
    ignoreSize=false;

  else
    ignoreSize=true;
};

// add an object
template <class T>
void database<T>::addObject(const T obj) {
  if (!ignoreSize) {
    // db is full
    if (data.size() == dbMaxSize)
      return;
  }
        
  data.push_back(obj);
};

// remove an object
template <class T>
void database<T>::removeObject(int pos) {
  if (data[pos])
    delete data[pos];

  // resync the vector 
  // resync();
};

// return a pointer to an object in the vector
template <class T>
T* database<T>::getObject(int pos) const {
  return data[pos];
};

#endif
