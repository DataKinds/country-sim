#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#define WIDTH_WINDOW 1366
#define HEIGHT_WINDOW 768

class Country {
public:
	std::string name;

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
	void addAsset(std::string name) {
		Asset tempAsset;
		tempAsset.name = name;
		economy.assets.push_back(tempAsset);
	}

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
		int totalPopulation = 0; 
		int workingPopulation = 0;
		int birthRate = 0;
		int deathRate = 0;
		int unrestPercent = 0;
	} society;

	Country(std::string name) {
		this->name = name;
		addAsset("Precious metal");
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

	std::string printProperty(std::string propertyName, std::string property, int indentLevel) {
		std::string indent = "  ";
		std::ostringstream propertyStringStream;
		for (int i = 0; i < indentLevel; i++) {
			propertyStringStream << indent;
		}
		propertyStringStream << propertyName << ": " << property << std::endl;
		return (std::string)propertyStringStream.str();
	}
	std::string prettyPrint() {
		std::ostringstream ostream;
		ostream << printProperty("Country", "USSR", 0);
		ostream << printProperty("Economy", "", 0);
		ostream << printProperty("GDP", std::to_string(economy.gdp), 1);
		ostream << printProperty("Money", std::to_string(economy.money), 1);
		ostream << printProperty("Assets", "", 1);
		for (unsigned int i = 0; i < economy.assets.size(); i++) {
			ostream << printProperty(economy.assets.at(i).name, "", 2);
			ostream << printProperty("Production rate", std::to_string(economy.assets.at(i).productionRate), 3);
			ostream << printProperty("Use rate", std::to_string(economy.assets.at(i).useRate), 3);
			ostream << printProperty("Import rate", std::to_string(economy.assets.at(i).importRate), 3);
			ostream << printProperty("Export rate", std::to_string(economy.assets.at(i).exportRate), 3);
		}
		ostream << printProperty("Society", "", 0);
		ostream << printProperty("Total population", std::to_string(society.totalPopulation), 1);
		ostream << printProperty("Birth rate", std::to_string(society.birthRate), 2);
		ostream << printProperty("Death rate", std::to_string(society.deathRate), 2);
		ostream << printProperty("Working population", std::to_string(society.workingPopulation), 2);
		ostream << printProperty("Social unrest (%)", std::to_string(society.unrestPercent), 1);
		return (std::string)ostream.str();
	}
};

typedef enum UiTab {
	TRADE,
	ASSETS,
	POPULATION,
	SOCIAL
} UiTab;
class GameState {
public:
	std::vector<Country*> countries;
	UiTab currentTab = UiTab::ASSETS;
	GameState() {}
};

GameState initGame() {
	GameState gameState;
	gameState.countries.push_back(new Country("USSR"));
	return gameState;
}

struct Button {
	std::string id;
	int x;
	int y;
	int w;
	int h;
};
sf::Text createButtonWithText(std::string text, sf::Font font, int charSize, int x, int y, int w, int h, std::vector<Button>* buttons, std::string buttonId) {
	sf::Text outputText;
	outputText.setFont(font);
	outputText.setString(text);
	outputText.setCharacterSize(charSize);
	outputText.setPosition(x, y);
	outputText.setColor(sf::Color::White);
	Button outputButton;
	outputButton.x = x;
	outputButton.y = y;
	outputButton.h = h;
	outputButton.w = w;
	buttons->push_back(outputButton);
	return outputText;
}
Button* getButtonById(std::string id, std::vector<Button> buttons) {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons.at(i).id == id) {
			return &buttons.at(i);
		}
	}
	return nullptr;
}

void handleButtonPresses(std::string id, GameState gameState) {
	if (id == "topBarTradeButton") {
		gameState.currentTab = UiTab::TRADE;
	} else if (id == "topBarAssetsButton") {
		gameState.currentTab = UiTab::ASSETS;
	} else if (id == "topBarPopulationButton") {
		gameState.currentTab = UiTab::POPULATION;
	} else if (id == "topBarSocialButton") {
		gameState.currentTab = UiTab::SOCIAL;
	}
}


int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "SFML");
	GameState gameState = initGame();
	Country* mainCountry = gameState.countries.at(0);
	sf::Font statusFont;
	statusFont.loadFromFile("SourceCodePro-Regular.ttf");
	std::vector<Button> buttons;
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			} else if (e.type == sf::Event::MouseButtonPressed) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					for (unsigned int i = 0; i < buttons.size(); i++) {
						Button currentButton = buttons.at(i);
						if (currentButton.x < e.mouseButton.x && (currentButton.x + currentButton.w) > e.mouseButton.x) {
							if (currentButton.y < e.mouseButton.y && (currentButton.y + currentButton.h) > e.mouseButton.y) {
								handleButtonPresses(currentButton.id, gameState);
							}
						}
					}
				}
			}
		}
		window.clear();
		//updates every frame
		buttons = {};
		//drawing stuff
		//draw and register top bar
		sf::RectangleShape topBar(sf::Vector2f(WIDTH_WINDOW, 50));
		topBar.setFillColor(sf::Color(32, 32, 32));
		window.draw(topBar);
		window.draw(createButtonWithText(
			"[TRADE]", //text
			statusFont, 16, //font, fontSize
			(int)(WIDTH_WINDOW/5), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarTradeButton" //id
			));
		window.draw(createButtonWithText(
			"[ASSETS]", //text
			statusFont, 16, //font, fontSize
			(int)(2*WIDTH_WINDOW/5), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarAssetsButton" //id
			));
		window.draw(createButtonWithText(
			"[POPULATION]", //text
			statusFont, 16, //font, fontSize
			(int)(3*WIDTH_WINDOW/5), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarPopulationButton" //id
			));
		window.draw(createButtonWithText(
			"[SOCIAL]", //text
			statusFont, 16, //font, fontSize
			(int)(4*WIDTH_WINDOW/5), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarSocialButton" //id
			));

		if (gameState.currentTab == UiTab::ASSETS) {
			for (unsigned int i = 0; i < mainCountry->economy.assets.size(); i++) {
				std::ostringstream os;
				os << mainCountry->printProperty(mainCountry->economy.assets.at(i).name, "", 0);
				os << mainCountry->printProperty("Production rate", std::to_string(mainCountry->economy.assets.at(i).productionRate), 1);
				os << mainCountry->printProperty("Use rate", std::to_string(mainCountry->economy.assets.at(i).useRate), 1);
				os << mainCountry->printProperty("Import rate", std::to_string(mainCountry->economy.assets.at(i).importRate), 1);
				os << mainCountry->printProperty("Export rate", std::to_string(mainCountry->economy.assets.at(i).exportRate), 1);
				sf::Text assetsText;
				assetsText.setFont(statusFont);
				assetsText.setString((std::string)os.str());
				assetsText.setCharacterSize(16);
				assetsText.setColor(sf::Color::White);
				assetsText.setPosition((i % 3)*((int)WIDTH_WINDOW / 3)+100, ((int)i / 3)*((int)HEIGHT_WINDOW / 6)+100);
				window.draw(assetsText);
			}
		}
		window.display();
	}
	return 0;
}