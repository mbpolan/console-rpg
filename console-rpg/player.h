// player.h: holds player class and member data
#include <iostream>

class player {
	public:
		player(int fixedHP, int fixedMP, int fixedHeight, int fixedAge); // our constructor
		virtual ~player();
		
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

		void setLook(player*);
		void setHair(std::string hairColor) {hair=hairColor;}
		void setTorso(std::string torsoColor) {torso=torsoColor;}
		void setLegs(std::string legsColor) {legs=legsColor;}
		std::string getHair() const {return hair;}
		std::string getTorso() const {return torso;}
		std::string getLegs() const {return legs;}
		
		int savePlayerData(player*);
		
		void setHeadItem(item*);
		void setTorsoItem(item*);
		void setLegsItem(item*);
		void setBootsItem(item*);
		std::string getHeadItem() const {return headEq;}
		std::string getTorsoItem() const {return torsoEq;}
		std::string getLegsItem() const {return legEq;}
		std::string getBootsItem() const {return bootEq;}
		std::string displayInventory(player*);
		
		void removeInventoryItem(int);
		void addInventoryItem(item*);
		int searchInventory(player*,std::string);
		
	private:
		int *currentHP;
		int *currentMP;
		int *playerHeight;
		int *playerAge;
		
		std::string *playerName;
		std::string hair, legs, torso;
		std::string headEq,torsoEq,legEq,bootEq;
};
