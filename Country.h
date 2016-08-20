#pragma once
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
		long double exportRate = 0;
		long double importRate = 0;
		long double productionRate = 0;
		long double useRate = 0;
	};
	struct Trade {

	};
	struct EconomyState {
		long gdp = 0;
		long money = 0;
		std::vector<Asset> assets;
	} economy;

	struct SocialState {
		std::vector<Person*> people;
		long totalPopulation = STARTING_POPULATION;
		long workingPopulation = 0;
		double birthRate = 0;
		double deathRate = 0;
		double unrestPercent = 0; //0 to 1
		double happinessPercent = 0; //0 to 1
	} society;

	void tick();
};
