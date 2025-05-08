#ifndef DECK_H
#define DECK_H

//ADDITIONAL LIBRARY
#include <vector>
#include <memory>

#include "../cards/PlayingCard.h"

class Deck {
  public:
    virtual void makeDeck() = 0;
    virtual unique_ptr<Card> discardCard(string suit, string rank) = 0;
};

#endif