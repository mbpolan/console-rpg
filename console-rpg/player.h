// player.h: holds player class and member data
#include <iostream>

class player {
	public:
		player(int fixedHP, int fixedMP, int fixedHeight, int fixedAge); // our constructor
		~player();
		int getHP() const {return *currentHP;}
		void setHP(int hp) {*currentHP=hp;}
		
		int getMP() const {return *currentMP;}
		void setMP(int mp) {*currentMP=mp;}
		
		void setName(std::string initialName) {*playerName=initialName;}
		std::string getName() const {return *playerName;}

		void setHeight(int height) {*playerHeight=height;}
		int getHeight() const {return *playerHeight;}

		void setAge(int age) {*playerAge=age;}
		int getAge() const {return *playerAge;}

		void setLook(player&);
		void setHair(std::string hairColor) {hair=hairColor;}
		void setTorso(std::string torsoColor) {torso=torsoColor;}
		void setLegs(std::string legsColor) {legs=legsColor;}

	private:
		int *currentHP;
		int *currentMP;
		int *playerHeight;
		int *playerAge;
		std::string hair, legs, torso;
		std::string *playerName;
};

player::player(int fixedHP, int fixedMP, int fixedHeight, int fixedAge) {
	currentHP=new int(fixedHP);
	currentMP=new int(fixedMP);
	playerHeight=new int(fixedHeight);
	playerAge=new int(fixedAge);
	playerName=new std::string;
	hair="brown", legs="blue", torso="brown";
	*playerName="Arbba";
};

player::~player() {
	delete currentHP;
	delete currentMP;
	delete playerName;
	delete playerHeight;
	delete playerAge;
	currentHP=0;
	currentMP=0;
	playerName=0;
	playerHeight=0;
	playerAge=0;
};

