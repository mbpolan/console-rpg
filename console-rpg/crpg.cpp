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

// crpg.cpp: main file
#include <iostream>
#include "definitions.h"

#ifdef __LINUX__
std::string clientOS="Linux";
#endif

#ifdef __WINDOWS__
std::string clientOS="Windows";
#endif

main(int argc, char *argv[]) {
	std::cout << "\n==================================";
	std::cout << "\n\tConsole-RPG 0.2.0" << std::endl;
	std::cout << "\t" << clientOS << " Version" << std::endl;
	std::cout << "==================================\n\n";
	menu(); // call menu()
}
