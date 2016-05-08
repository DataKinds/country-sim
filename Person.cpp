#include <sstream>
#include <ctime>
#include "Person.h"

std::string Person::genRandomString(int length) {
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
	std::ostringstream os;
	os << generation << std::time(nullptr) << genRandomString(8);
	return (std::string)os.str();
}