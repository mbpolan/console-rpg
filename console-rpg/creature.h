// creature.h: holds the ADT creature class

class creature {
	public:
		virtual ~creature() {};
		
		virtual int getHP() const =0;
		virtual void setHP(int) =0;
	
		virtual int getMP() const =0;
		virtual void setMP(int) =0;
		
		virtual void setName(std::string) =0;
		virtual std::string getName() const =0;
		
		virtual void setLuck(int) =0;
		virtual int getLuck() const =0;
		
		virtual void setPower(int) =0;
		virtual int getPower() const =0;
		
		virtual void setStrength(int) =0;
		virtual int getStrength() const =0;
		
		virtual void setDefense(int) =0;
		virtual int getDefense() const =0;

};

