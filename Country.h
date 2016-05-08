#include <string>
#include <vector>
#include "Person.h"

class Country {
private:
	void addAsset(std::string name);
	Person getPersonById(std::string id);
public:
	std::string name;
	Country(std::string name);
	struct Asset {
		std::string name;
		int exportRate = 0;
		int importRate = 0;	
		int productionRate = 0;
		int useRate = 0;
	};
	struct Trade {

	};
	struct EconomyState {
		int gdp = 0;
		int money = 0;
		std::vector<Asset> assets;
	} economy;

	struct SocialState {
		std::vector<Person*> people;
		int totalPopulation = 100; 
		int workingPopulation = 0;
		int birthRate = 0;
		int deathRate = 0;
		int unrestPercent = 0;
		int happinessPercent = 0;
	} society;

	void tick();
};