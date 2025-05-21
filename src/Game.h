#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Hand.h"

using namespace std;

class Game {
  private:
    int minimumScore;
    int round;
    int difficulty;
    bool lose_status;
    vector<int> highscores;
  public:
    Game(): round(0), lose_status(false), minimumScore(100)
    {
      
    };

    void runGame() 
    {
      
    };

    void renderAll() 
    {
      
    };

    //SETTERS
    void set_difficulty(int inpt) 
    {
      this->difficulty = inpt;
    };
    
    //GETTERS
    int get_difficulty() {
      return this->difficulty;
    };

    ~Game() {};
};

#endif //GAME_H