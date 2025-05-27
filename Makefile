# Makefile

SFML_PATH = /opt/homebrew/Cellar/sfml@2/2.6.2_1

all: check-sfml compile run

#to check for memory leak -fsanitize=address -g

check-sfml:
    @pkg-config --exists sfml-graphics || (echo "SFML not found! Please install with: sudo apt install libsfml-dev" && false)
compile: 
	g++ src/main.cpp -std=c++17 -I${SFML_PATH}/include -o main -L${SFML_PATH}/lib -lsfml-graphics -lsfml-window -lsfml-system
run: 
	./main
clean:
	rm -f main
	