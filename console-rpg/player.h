#include <iostream>
using namespace std;

class player {
	public:
		player(int fixedHP, int fixedMP);
		~player() {};
		int getHP() const {return *currentHP;}
		void setHP(int hp) {*currentHP=hp;}
		
		int getMP() const {return *currentMP;}
		void setMP(int mp) {*currentMP=mp;}
		
		void setGender(std::string initialGender) {*playerGender=initialGender;}
		std::string getGender() {return *playerGender;}

		void gameWorld();

	private:
		int *currentHP;
		int *currentMP;
		std::string *playerGender;
};

player::player(int fixedHP, int fixedMP) {
	currentHP=new int;
	currentMP=new int;
	playerGender=new std::string;
	*currentHP=fixedHP;
	*currentMP=fixedMP;
};

