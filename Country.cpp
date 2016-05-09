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
}

void tick() {

}
