#include <sstream>
#include <ctime>
#include "Person.h"

std::string Person::genRandomString(unsigned int length) {
	const std::string lookupTable = "abcdefghijklmnopqrstuvwxyz1234567890";
	std::ostringstream os;
	for (unsigned int i = 0; i < length; i++) {
		os << lookupTable[rand() % lookupTable.size()];
	}
	return (std::string)os.str();
}

//person id format:
//generation (padded to 6 digits) -
//birthdate (in unix time) -
//random 8? character identifier
std::string Person::genPersonId(long generation) {
	std::string generationString = std::to_string(generation);
	unsigned int amountToPad = 6 - generationString.size();
	std::ostringstream os;
	for (unsigned int i = 0; i < amountToPad; i++) {
		os << "0";
	}
	os << generation << "-" << std::time(nullptr) << "-" << genRandomString(8);
	return (std::string)os.str();
}

Person::Person(long generation) {
	id = genPersonId(generation);
	name = {"place", "holder", "name"};
	this->generation = generation;
}

Person::Person(long generation, Gender gender, Ideals ideals) {
	id = genPersonId(generation);
	name = {"place", "holder", "name"};
	this->generation = generation;
	this->gender = gender;
	this->ideals = ideals;
}