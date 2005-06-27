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

#include <iostream>

// version
const std::string version="0.3.0";

// clear screen macro for linux
#ifdef __LINUX__
#define CRPG_CLEAR_SCREEN system("clear")
#endif

// clear screen macro for win32
#ifdef __WIN32__
#define CRPG_CLEAR_SCREEN system("cls")
#endif

// game class defines
// define's for menu
#define GAME_MENU_NEW_GAME	1
#define GAME_MENU_LOAD_GAME	2
#define GAME_MENU_OPTIONS	3

// different types of situations that could result from movement
#define GAME_MOVEMENT_OUT_OF_BOUNDS	0
#define GAME_MOVEMENT_OK		1
#define GAME_MOVEMENT_BLOCKING_SPACE	2

// skills
#define SKILL_DEFENSE	0
#define SKILL_LUCK	1
#define SKILL_POWER	2
#define SKILL_STRENGTH	3

// player equipment slots
#define PLAYER_SLOT_HEAD	0
#define PLAYER_SLOT_TORSO	1
#define PLAYER_SLOT_LEFT_ARM	2
#define PLAYER_SLOT_RIGHT_ARM	3
#define PLAYER_SLOT_LEGS	4
#define PLAYER_SLOT_BOOTS	5

#endif
