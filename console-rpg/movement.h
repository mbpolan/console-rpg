// movement.h: holds movement system and map stuff
#include <iostream>

class movement { 
	public:
		movement(int defaultX, int defaultY); // our constructor
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
	private:
		std::string itemWarning;
};

