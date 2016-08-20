#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "Country.h"
#include "Constants.h"
#include "TabDrawing.h"

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
            TabDraw::assets(&window, statusFont, mainCountry);
		} else if (gameState.currentTab == UiTab::SOCIAL) {
            TabDraw::social(&window, statusFont, mainCountry);
		} else if (gameState.currentTab == UiTab::POPULATION) {
            TabDraw::population(&window, statusFont, mainCountry);
		} else if (gameState.currentTab == UiTab::TRADE) {
            TabDraw::trade(&window, statusFont, mainCountry);
		}
		std::ostringstream dateString;
		dateString << "Year: " << (int)(gameState.day / 365) << "; Day: " << gameState.day % 365;
		sf::Text currentGameDate;
		currentGameDate.setFont(statusFont);
		currentGameDate.setString(dateString.str());
		currentGameDate.setCharacterSize(16);
		currentGameDate.setColor(sf::Color::White);
		currentGameDate.setPosition(WIDTH_WINDOW - 200, 10);
		window.draw(currentGameDate);
		tickGameState(&gameState, mainCountry);
		window.display();
	}
	return 0;
}
