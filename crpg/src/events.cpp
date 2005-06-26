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
// events.cpp: implementations of Events namespace functions

#include "enemy.h"
#include "event.h"
#include "events.h"
#include "game.h"
#include "map.h"
#include "timer.h"

// function to control time of day/night
void* Events::controlTime(void *data) {
	Game *game=(Game*) data;
	
	// make sure to lock and unlock the mutex
	game->lock();
	
	// a day lasts 20 minutes
	if (game->getTimeTicks()==60*20) {
		game->setTimeTicks(0);
		game->changeDay();
	}
	
	// increment the ticks
	else
		game->setTimeTicks(game->getTimeTicks()+1);
	
	game->unlock();
	
	// keep this event in the queue
	game->appendEvent(Event::create("TIME_CONTROL_EVENT", &controlTime, game, 1));
	pthread_exit(NULL);
};

// function to manage spawning of enemies on the map
void* Events::spawnManage(void *data) {
	Game *game=(Game*) data;
	game->lock();
		
	Map *map=game->map();
	map->lock();
			
	// get a count of enemies
	int count=0;
	for (MapEnemyIterator it=map->enemies.begin(); it!=map->enemies.end(); ++it) {
		if ((*it))
			count+=1;
	}
		
	// maintain a minimum of 50 enemies
	if (count < 50) {
		int req=50-count;
				// respawn these enemies
		for (int i=0; i<req; i++) {
			srand(static_cast<unsigned> (time(NULL)));
			int x=rand()%map->getWidth();
			int y=rand()%map->getHeight();
			int z=0; // FIXME: correct this once layers are in
				
			// place the new enemy
			// TODO: enemy names and attributes
			map->placeEnemy(new Enemy("Enemy", 100, 50, Position(x, y, z)));
		}
	}
	map->unlock();
	game->unlock();
	
	// keep this event in the queue
	game->appendEvent(Event::create("SPAWN_MANAGE_EVENT", &spawnManage, game, 5)); // execute every 5 seconds
	pthread_exit(NULL);
};
