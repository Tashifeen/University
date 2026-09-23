#include <iostream>
#include <string>

class Drink {
	protected:
		double weight;
		std::string name;
	public:
		// Setters and getters
		void setName(std::string n) {name = n;}
		std::string getName() {return name;}

		void setWeight(double w) {weight = w;}
		double getWeight() {return weight;}

		// Virtual function
		virtual bool hasAlcohol() = 0;

		// Virtual destructor
		virtual ~Drink() {}
};
		
class Juice: public Drink {
	private:
		bool concentrate;
	public:
		// Constructor
		Juice(std::string n, double w, bool c) {
			name = n;
			weight = w;
			concentrate = c;
		}
		
		// Concentrate: Setter and getter
		void setConcentrate(bool c) {concentrate = c;}
		bool getConcentrate() {return concentrate;}

		bool hasAlcohol() override {
			return false;
		}
};

class Wine : public Drink {
	private:
		double abv;
	public:
		// Constructor
		Wine(std::string n, double w, double a) {
			name = n;
			weight = w;
			abv = a;
		}
		
		// setABV: Setter and getter
		void setABV(double a) {abv = a;}
		double getABV() {return abv;}

		bool hasAlcohol() override {
			return abv > 0.5;
		}
};

