// movement.h: holds movement system and map stuff
#include <iostream>
#include "map.h"

#ifndef __nMovement
#define __nMovement

class movement { 
	public:
		movement(); // our constructor
		virtual ~movement() {};

		// movement methods
		void moveN(map*);
		void moveS(map*);
		void moveW(map*);
		void moveE(map*);
		void moveNE(map*);
		void moveNW(map*);
		void moveSE(map*);
		void moveSW(map*);

		// other methods
		void look(map*);
		void placeItem(item*,map*);
		void removeItem(item*,map*);
		void spawnMapItems(movement*,map*);

		// public accessors
		signed int getCurrentPosition(map*) const;

		// time related methods
		void checkTime();
		int controlTime(int);
		int getStepCount() const {return stepCount;}
		
	private:
		std::string itemWarning;
		bool fDay;
		int stepCount;
};

#endif

