#include "Country.h"

void Country::addAsset(std::string name) {
	Asset tempAsset;
	tempAsset.name = name;
	economy.assets.push_back(tempAsset);
}

Country::Country(std::string name) {
	this->name = name;
	addAsset("Precious metal"); // TBA: Uranium, electricity, fabric, plastic; also, alphabetize
	addAsset("Iron");
	addAsset("Copper");
	addAsset("Petroleum");
	addAsset("Coal");
	addAsset("Meat");
	addAsset("Produce");
	addAsset("Water");
	addAsset("Cars");
	addAsset("Medicine");
	addAsset("Stone");
	addAsset("Steel");
	addAsset("Electronics");
	addAsset("Wood");
	//fill out initial population
	for (unsigned int i = 0; i < society.totalPopulation; i++) {
		Gender gender = (rand() % 2 == 1 ? Gender::MALE : Gender::FEMALE);
		Ideals ideals;
		ideals.economy = 2*((double)rand()/RAND_MAX)-1;
		ideals.philosophy = 2*((double)rand()/RAND_MAX)-1;
		ideals.military = 2*((double)rand()/RAND_MAX)-1;
		ideals.government = 2*((double)rand()/RAND_MAX)-1;
		society.people.push_back(new Person(0));
		const char* personId = society.people.at(society.people.size()-1)->id.c_str();
		printf("Generated a person with ID %s\n", personId);
		printf("    Their gender is %s\n", (gender == Gender::MALE ? "male" : "female"));
		printf("    Their ideals are:\n");
		printf("    	Economic: %f\n", ideals.economy);
		printf("    	Philosophical: %f\n", ideals.philosophy);
		printf("    	Militarily: %f\n", ideals.military);
		printf("    	Governmental: %f\n", ideals.government);

	} 
}

void Country::tick() {

}
