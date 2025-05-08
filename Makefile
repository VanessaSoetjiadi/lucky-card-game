# Makefile

SFML_PATH = /opt/homebrew/Cellar/sfml@2/2.6.2_1

all: compile

#to check for memory leak -fsanitize=address -g

compile: 
	g++ -fsanitize=address -g src/main.cpp -std=c++17 -I${SFML_PATH}/include -o main -L${SFML_PATH}/lib -lsfml-graphics -lsfml-window -lsfml-system
	./main