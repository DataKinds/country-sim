#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "Country.h"
#define WIDTH_WINDOW 1366
#define HEIGHT_WINDOW 768

std::string printProperty(std::string propertyName, std::string property, int indentLevel) {
	std::string indent = "  ";
	std::ostringstream propertyStringStream;
	for (int i = 0; i < indentLevel; i++) {
		propertyStringStream << indent;
	}
	propertyStringStream << propertyName << ": " << property << std::endl;
	return (std::string)propertyStringStream.str();
}
typedef enum UiTab {
	TRADE,
	ASSETS,
	POPULATION,
	SOCIAL
} UiTab;
class GameState {
public:
	std::vector<Country*> countries;
	UiTab currentTab;
	long day = 0;
	GameState() {}
};

GameState initGame() {
	GameState gameState;
	gameState.currentTab = UiTab::ASSETS;
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
	outputButton.id = buttonId;
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

void handleButtonPresses(std::string id, GameState* gameState) {
	std::cout << "Button clicked:" << id << std::endl;
	if (id == "topBarTradeButton") {
		gameState->currentTab = UiTab::TRADE;
	} else if (id == "topBarAssetsButton") {
		gameState->currentTab = UiTab::ASSETS;
	} else if (id == "topBarPopulationButton") {
		gameState->currentTab = UiTab::POPULATION;
	} else if (id == "topBarSocialButton") {
		gameState->currentTab = UiTab::SOCIAL;
	}
}

void tickGameState(GameState* gameState, Country* mainCountry) {
	gameState->day += 1;
	for (unsigned int i = 0; i < gameState->countries.size(); i++) {
		gameState->countries.at(i)->tick();
	}
}

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "OpenCountry (pre-alpha)");
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
								handleButtonPresses(currentButton.id, &gameState);
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
			"[LABOR]", //text
			statusFont, 16, //font, fontSize
			(int)(4*WIDTH_WINDOW/5), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarSocialButton" //id
			));
		window.draw(createButtonWithText(
			"[POPULATION]", //text
			statusFont, 16, //font, fontSize
			(int)(3*WIDTH_WINDOW/5), 10, //x, y
			100, 30, //w, h
			&buttons, //button vector
			"topBarPopulationButton" //id
			));


		if (gameState.currentTab == UiTab::ASSETS) {
			for (unsigned int i = 0; i < mainCountry->economy.assets.size(); i++) {
				std::ostringstream os;
				os << printProperty(mainCountry->economy.assets.at(i).name, "", 0);
				os << printProperty("Production rate", std::to_string(mainCountry->economy.assets.at(i).productionRate), 1);
				os << printProperty("Use rate", std::to_string(mainCountry->economy.assets.at(i).useRate), 1);
				os << printProperty("Import rate", std::to_string(mainCountry->economy.assets.at(i).importRate), 1);
				os << printProperty("Export rate", std::to_string(mainCountry->economy.assets.at(i).exportRate), 1);
				sf::Text assetsText;
				assetsText.setFont(statusFont);
				assetsText.setString((std::string)os.str());
				assetsText.setCharacterSize(16);
				assetsText.setColor(sf::Color::White);
				assetsText.setPosition((i % 3)*((int)WIDTH_WINDOW / 3)+100, ((int)i / 3)*((int)HEIGHT_WINDOW / 6)+100);
				window.draw(assetsText);
			}
		} else if (gameState.currentTab == UiTab::SOCIAL) {
			std::ostringstream os;
			os << printProperty("Total population", std::to_string(mainCountry->society.totalPopulation), 0);
			os << printProperty("Working population", std::to_string(mainCountry->society.workingPopulation), 1);
			os << printProperty("Social unrest (%)", std::to_string(mainCountry->society.unrestPercent), 0);
			sf::Text socialEffectText;
			socialEffectText.setFont(statusFont);
			socialEffectText.setString((std::string)os.str());
			socialEffectText.setCharacterSize(16);
			socialEffectText.setColor(sf::Color::White);
			socialEffectText.setPosition(100, 100);
			window.draw(socialEffectText);
		} else if (gameState.currentTab == UiTab::POPULATION) {
			std::ostringstream os;
			os << printProperty("Total population", std::to_string(mainCountry->society.totalPopulation), 0);
			os << printProperty("Birth rate", std::to_string(mainCountry->society.birthRate), 1);
			os << printProperty("Death rate", std::to_string(mainCountry->society.deathRate), 1);
			os << printProperty("Happiness (%)", std::to_string(mainCountry->society.happinessPercent), 0);
			sf::Text populationText;
			populationText.setFont(statusFont);
			populationText.setString((std::string)os.str());
			populationText.setCharacterSize(16);
			populationText.setColor(sf::Color::White);
			populationText.setPosition(100, 100);
			window.draw(populationText);
		} else if (gameState.currentTab == UiTab::TRADE) {
			sf::Text availableTradeText;
			availableTradeText.setFont(statusFont);
			availableTradeText.setString(printProperty("Available trades", "", 0));
			availableTradeText.setCharacterSize(16);
			availableTradeText.setColor(sf::Color::White);
			availableTradeText.setPosition(WIDTH_WINDOW - 100 - availableTradeText.getLocalBounds().width, 100);
			window.draw(availableTradeText);
			sf::Text acceptedTradeText;
			acceptedTradeText.setFont(statusFont);
			acceptedTradeText.setString(printProperty("Accepted trades", "", 0));
			acceptedTradeText.setCharacterSize(16);
			acceptedTradeText.setColor(sf::Color::White);
			acceptedTradeText.setPosition(100, 100);
			window.draw(acceptedTradeText);
		}

		window.display();
	}
	return 0;
}
