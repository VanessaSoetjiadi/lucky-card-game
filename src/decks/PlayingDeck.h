#ifndef PLAYINGDECK_H
#define PLAYINGDECK_H

#include <random>

#include "InitDeck.h"

class PlayingDeck : public AbstractPlayingDeck {
  public:
    PlayingDeck() 
    {
      this->set_maximumNumCards(8);
    };

    // taking 8 cards from the initial deck
    void makeDeck(InitDeck& initialDeck) 
    {
      while(this->getCurrentCards() < this->get_maximumNumCards())
      {
        int rnd = (rand() % initialDeck.getCurrentCards());

        if (initialDeck.getDeck()[rnd] != nullptr) 
        {
          this->deck.push_back(initialDeck.getDeck()[rnd]);
          initialDeck.discardCard(rnd);
        };
      };
    };

    ~PlayingDeck() {};
};

#endif //PLAYINGDECK_H