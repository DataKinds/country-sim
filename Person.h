#include <string>
#include <vector>
#define STARTING_POPULATION 100

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
	std::string genRandomString(unsigned int length);
public:
	Person(long generation);
	long generation = 0; //generation of person (parents = 0, son = 1, grandson = 2, etc.)
	std::vector<std::string> name; //{firstName, surName, middleNames (optional)}
	std::string id;
	Gender gender = Gender::MALE;
	int age = 0;
	int money = 0;
	double happinessPercent = 1; //0 to 1
	double ideoEcononomy = 0; //Range is -1 (collectivist) to +1 (individualist)
	double ideoPhilosophy = 0; //Range is -1 (rationalist) to +1 (spiritualist)
	double ideoMilitary = 0; //Range is -1 (pacifist) to +1 (militarist)
	double ideoGovernment = 0; //Range is -1 (democratic) to +1 (autocratic)
};
