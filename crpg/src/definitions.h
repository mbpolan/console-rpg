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
// definitions.h: various definitions

#ifndef DEFINITIONS_H
#define DEFINITIONS_H 

// clear screen macro
#define CRPG_CLEAR_SCREEN system("clear")

// game class defines
// define's for menu
#define GAME_MENU_NEW_GAME	1
#define GAME_MENU_LOAD_GAME	2
#define GAME_MENU_OPTIONS	3

// different types of situations that could result from movement
#define GAME_MOVEMENT_OUT_OF_BOUNDS	0
#define GAME_MOVEMENT_OK		1
#define GAME_MOVEMENT_BLOCKING_SPACE	2

#endif
