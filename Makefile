CC=g++
INPUT_FILES=main.cpp Country.cpp Person.cpp
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
ARGS=-g -std=c++11 -Wall

all:
	$(CC) $(INPUT_FILES) -o country.out $(ARGS) $(LIBS)