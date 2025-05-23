#ifndef DECK_H
#define DECK_H

#include <vector>

class Deck {
  protected:
    int maximumNumCards;
  public:
    virtual void discardCard(int idx) = 0; // discards the card in index
    virtual int getCurrentCards() = 0; // returns the current cards in the deck
    virtual ~Deck() = default;

    //SETTER AND GETTER
    void set_maximumNumCards(int n) 
    {
      this->maximumNumCards = n;
    };
    
    int get_maximumNumCards() 
    {
      return this->maximumNumCards;
    };
};

#endif //DECK_H