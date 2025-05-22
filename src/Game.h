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
      JokerDeck jkDeck;
      SupportDeck spDeck;

      runGame(jkDeck, spDeck);
    };

    void runGame(JokerDeck jkDeck, SupportDeck spDeck) {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      string inpt = 0;
      while(hand.get_handsCount() > 0 && hand.get_totalScore() < minimumScore) 
      {
        cout << "Your deck: " << endl;
        
        // display playingCards
        cout << "[";
        for (int i = 0; i < playDeck.getCurrentCards(); i++) 
        {
          cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << endl;
        };
        cout << "]" << endl;

        // display jokerDeck information
        for (int i = 0; i < jkDeck.getCurrentCards(); i++) 
        {
          cout << "Joker " << i << "bonus chips:" << jkDeck.getDeck()[i]->get_bonus_chips();
        };

        cout << "input the index of the cards you want to play:" << endl;
        cin >> inpt;

        // for (int i = 0; i < inpt.length(); i++) 
        // {
        //   playDeck.getDeck()[stoi(inpt[i])]->get_chosen();
        // };
        
        hand.calculateTotalScore(playDeck, jkDeck, spDeck);
      };


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