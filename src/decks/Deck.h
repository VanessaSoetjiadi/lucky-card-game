#ifndef DECK_H
#define DECK_H

//VECTOR LIB
#include <vector>

class Deck {
  protected:
    int maximumNumCards;
  public:
    //discards the card in the index
    virtual void discardCard(int idx) = 0;

    //returns the current cards in the deck
    virtual int getCurrentCards() = 0;

    //SETTER AND GETTER FOR MAX CARDS
    void set_maximumNumCards(int n) 
    {
      this->maximumNumCards = n;
    };
    
    int get_maximumNumCards() 
    {
      return this->maximumNumCards;
    };

    ~Deck() = default;
};

#endif //DECK_H