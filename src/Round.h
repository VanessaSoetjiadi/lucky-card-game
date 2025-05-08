#ifndef ROUND_H
#define ROUND_H

#include "decks/InitDeck.h"
#include "decks/PlayingDeck.h"
#include "Hand.h"

class Round {
  private:
    int round;
    int minimumScore;
  public:
    Round(): round(0), minimumScore(0)
    {
      this->newRound();
    };

    void newRound() 
    {
      this->round++;
      cout << "Round: " << this->round << endl;

      //INITIALIZE DECK
      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      Hand hand;

      this->set_minimum_score();
      cout << "You need " << this->minimumScore << " to win!" << endl;

      //GAME LOOP
      while (hand.get_num_hands() > 0 && hand.get_total_score() < this->minimumScore) 
      {
        playDeck.makeDeck(initialDeck);
        playDeck.printDeck();

        hand.pushHand(playDeck);
        
        cout << "Hands left: " << hand.get_num_hands() << endl;
        cout << "Your current score: " << hand.get_total_score() << endl << endl;

        if (hand.get_total_score() > this->minimumScore) 
        {
          cout << "\n\nYOU WIN! Loading new Round..." << endl;
          this->newRound();
        };
      };

      //Losing feature
      int n;
      cout << "You Lose, play again? 1 for yes, 0 for no: ";
      cin >> n;

      if (n == 1) 
      {
        this->set_round(0);
        this->newRound();
      };
    };

    //Setters
    void set_round(int r) 
    {
      this->round = r;
    };

    void set_minimum_score() 
    {
      this->minimumScore = 150 + (this->round - 1)*150;
    };

    ~Round() {};
};

#endif