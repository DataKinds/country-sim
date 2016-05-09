#include <string>
#include <vector>

typedef enum Gender { 
	MALE, 
	FEMALE 
} Gender;

class Person {
private:
	std::string genPersonId(long generation);
	std::string genRandomString(unsigned int length);
public:
	Person();
	std::vector<std::string> name; //{firstName, surName, middleNames (optional)}
	std::string id;
	Gender gender = Gender::MALE;
	int age = 0;
	int money = 0;
	int happinessPercent = 0;
	signed char ideoEcononomy = 0; //Range is -3 (collectivist) to +3 (individualist)
	signed char ideoPhilosophy = 0; //Range is -3 (rationalist) to +3 (spiritualist)
	signed char ideoMilitary = 0; //Range is -3 (pacifist) to +3 (militarist)
	signed char ideoGovernment = 0; //Range is -3 (democratic) to +3 (autocratic)
};
