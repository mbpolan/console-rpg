#include <iostream>
using namespace std;

class player {
	public:
		player(int fixedHP, int fixedMP); // our constructor
		~player() {};
		int getHP() const {return *currentHP;}
		void setHP(int hp) {*currentHP=hp;}
		
		int getMP() const {return *currentMP;}
		void setMP(int mp) {*currentMP=mp;}
		
		void setName(std::string initialName) {*playerName=initialName;}
		std::string getName() {return *playerName;}

//		void gameWorld(); // may tie this in with the map later

	private:
		int *currentHP;
		int *currentMP;
		std::string *playerName;
};

player::player(int fixedHP, int fixedMP) {
	currentHP=new int;
	currentMP=new int;
	playerName=new std::string;
	*currentHP=fixedHP;
	*currentMP=fixedMP;
	*playerName="Arbba";
};

