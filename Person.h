#include <string>
#include <vector>

typedef enum Gender { 
	MALE, 
	FEMALE 
} Gender;

class Person {
private:
	std::string genPersonId(long generation);
	std::string genRandomString(int length);
public:
	Person();
	std::vector<std::string> name; //{firstName, surName, middleNames (optional)}
	//person id format:
	//generation (padded to 6 digits) -
	//birthdate (in unix time) -
	//random 8? character identifier
	std::string id;
	Gender gender = Gender::MALE;
	int age = 0;
	int money = 0;
	int happinessPercent = 0;
}