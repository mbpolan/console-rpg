// player.h: holds player class and member data
#include <iostream>
#include "creature.h"

enum vocation {warrior,mage,archer};

class player: public creature {
	public:
		player();
		player(int,int,int,int); // new player constructor
		player(int,int,int,int,int,int); // enhanced constructor
		virtual ~player();
		
		// player specific definitions
		int getHP() const {return currentHP;}
		void setHP(int hp) {currentHP=hp;}
	
		int getMP() const {return currentMP;}
		void setMP(int mp) {currentMP=mp;}
		
		void setName(std::string initialName) {playerName=initialName;}
		std::string getName() const {return playerName;}
		
		void setLuck(int _luck) {luck=_luck;};
		int getLuck() const {return luck;}
		
		void setPower(int _power) {power=_power;}
		int getPower() const {return power;}
		
		void setStrength(int _strength) {strength=_strength;}
		int getStrength() const {return strength;}
		
		void setDefense(int _defense) {defense=_defense;}
		int getDefense() const {return defense;}
		
		void setHeight(int height) {playerHeight=height;}
		int getHeight() const {return playerHeight;}
		
		void setAge(int age) {playerAge=age;}
		int getAge() const {return playerAge;}
				
		void setVoc(vocation _vocation) {playerVocation=_vocation;}
		vocation getVoc() const {return playerVocation;}
		
		// level related stat accessors
		void setLevel(int _level) {level=_level;}
		int getLevel() const {return level;}
		void setExp(int _exp) {exp=_exp;}
		int getExp() const {return exp;}
		
		void increaseExp(int _exp) {exp+=_exp;} 
		void increaseLevel();
		
		// visual accessors
		void setLook(player*);
		void setHair(std::string hairColor) {hair=hairColor;}
		void setTorso(std::string torsoColor) {torso=torsoColor;}
		void setLegs(std::string legsColor) {legs=legsColor;}
		std::string getHair() const {return hair;}
		std::string getTorso() const {return torso;}
		std::string getLegs() const {return legs;}
		
		// for saving the data to a savefile
		int savePlayerData(player*);
		
		// item actions
		void setHeadItem(item*);
		void setTorsoItem(item*);
		void setLegsItem(item*);
		void setBootsItem(item*);
		std::string getHeadItem() const {return headEq;}
		std::string getTorsoItem() const {return torsoEq;}
		std::string getLegsItem() const {return legEq;}
		std::string getBootsItem() const {return bootEq;}
		std::string displayInventory(player*);
		
		// inventory actions
		void removeInventoryItem(int);
		void addInventoryItem(TYPE,std::string);
		int searchInventory(player*,std::string);

		// to display player's stats
		int displayStats(player*);
		
	private:
		int currentHP,currentMP,luck,strength,power,defense,level,exp;
		int playerHeight,playerAge;
		std::string playerName;
		std::string hair, legs, torso;
		std::string headEq,torsoEq,legEq,bootEq;
		vocation playerVocation;
};

