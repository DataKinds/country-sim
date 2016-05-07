#include <string>
#include <vector>

class Country {
private:
	void addAsset(std::string name);
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
	typedef enum Gender { 
		MALE, 
		FEMALE 
	} Gender;
	typedef enum Age { 
		YOUNG,
		ADULT,
		OLD 
	} Age;
	typedef enum SocialClass { 
		LOWER,
		MIDDLE,
		UPPER 
	} SocialClass;
	struct Person {
		Gender gender = Gender::MALE;
		Age age = Age::YOUNG;
		SocialClass socialClass = SocialClass::LOWER;
		int happinessPercent = 0;
	};
	struct SocialState {
		std::vector<Person> people;
		int totalPopulation = 1000; 
		int workingPopulation = 0;
		int birthRate = 0;
		int deathRate = 0;
		int unrestPercent = 0;
		int happinessPercent = 0;
	} society;

	void tick();
};