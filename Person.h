#include <string>
#include <vector>

typedef enum Gender {
	MALE,
	FEMALE
} Gender;

typedef enum Occupation {
	CHILD,
	STUDENT,
	UNEMPLOYED,
	REBEL,
	CRIMINAL,
	LABORER,
	SCIENTIST,
	TEACHER,
	BUREAUCRAT,
	CLERK,
	FARMER,
	MINER,
	SOLDIER,
	OFFICER,
	DOCTOR,
	POLICEMAN,
	MANAGER,
	LANDOWNER
} Occupation;

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
	char age = 0;
	int money = 0;
	char happinessPercent = 0;
	signed char ideoEcononomy = 0; //Range is -3 (collectivist) to +3 (individualist)
	signed char ideoPhilosophy = 0; //Range is -3 (rationalist) to +3 (spiritualist)
	signed char ideoMilitary = 0; //Range is -3 (pacifist) to +3 (militarist)
	signed char ideoGovernment = 0; //Range is -3 (democratic) to +3 (autocratic)
};
