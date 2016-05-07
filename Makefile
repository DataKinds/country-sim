all:
	g++ main.cpp Country.cpp -g -o country.out -std=c++11 -Wall -lsfml-graphics -lsfml-window -lsfml-system