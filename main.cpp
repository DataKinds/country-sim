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
		for (int i = 0; i < economy.assets.size(); i++) {
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

class GameState {
public:
	std::vector<Country> countries;
	GameState() {}
};

GameState initGame() {
	GameState gameState;
	gameState.countries.push_back(Country("USSR"));
	return gameState;
}

struct Button {
	std::string id;
	bool enabled;
	bool pressed;
	int x;
	int y;
	int w;
	int h;
};
sf::Text createButtonWithText(std::string text, sf::Font font, int charSize, int x, int y, int w, int h, std::vector<Button>* buttons, std::string buttonId, bool enabled) {
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
	outputButton.enabled = enabled;
	buttons->push_back(outputButton);
	return outputText;
}
Button* getButtonById(std::string id, std::vector<Button> buttons) {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons.at(i).id == id) {
			return &buttons.at(i);
		}
	}
	return nullptr;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "SFML");
	GameState gameState = initGame();
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
					for (int i = 0; i < buttons.size(); i++) {
						Button currentButton = buttons.at(i);
						if (currentButton.x < e.mouseButton.x && (currentButton.x + currentButton.w) > e.mouseButton.x) {
							if (currentButton.y < e.mouseButton.y && (currentButton.y + currentButton.h) > e.mouseButton.y) {
								buttons.at(i).pressed = true;
							}
						}
					}
				}
			} else if (e.type == sf::Event::MouseButtonReleased) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < buttons.size(); i++) {
						buttons.at(i).pressed = false;
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
		sf::Text tradeText = createButtonWithText(
			"[TRADE]", //text
			statusFont, 16, //font, fontSize
			30, 30, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarTradeButton", //id
			true //enabled
			);
		window.draw(tradeText);
		sf::Text assetText = createButtonWithText(
			"[ASSETS]", //text
			statusFont, 16, //font, fontSize
			(int)(2*WIDTH_WINDOW/4), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarAssetButton", //id
			true //enabled
			);
		window.draw(assetText);
		sf::Text populationText = createButtonWithText(
			"[POPULATION]", //text
			statusFont, 16, //font, fontSize
			(int)(3*WIDTH_WINDOW/4), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarPopulationButton", //id
			true //enabled
			);
		window.draw(populationText);


		sf::Text countryStatus;
		countryStatus.setFont(statusFont);
		countryStatus.setString(gameState.countries.at(0).prettyPrint());
		countryStatus.setCharacterSize(10);
		countryStatus.setColor(sf::Color::White);
		countryStatus.setPosition(10, 10);
		window.draw(countryStatus);
		window.display();
	}
	return 0;
}