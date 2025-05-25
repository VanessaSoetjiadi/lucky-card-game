#ifndef JOKERDECK_H
#define JOKERDECK_H

#include "AbstractEffectsDeck.h"
#include "../cards/JokerCard.h"

class JokerDeck : public AbstractEffectsDeck {
  private:
    vector<JokerCard*> deck; // vector to hold Joker cards
  public:
    JokerDeck() {
      this->set_maximumNumCards(4);
    };
    
    // pure virtual functions override
    void discardCard(int idx) override
    {
      this->deck.erase(this->deck.begin() + idx);
    };
    
    int getCurrentCards() override
    {
      return this->deck.size();
    };

    void addEffectCard() override
    {
      // adds card if deck isn't full
      if (this->getCurrentCards() < this->get_maximumNumCards()) {
        // add a new joker card into the deck, rnd is for the lifespan
        int rnd = ((rand() % 4) + 1);
        this->deck.push_back(new JokerCard(rnd));
      };
    };

    void makeDeck() override
    {
      deck.clear(); // clears the vector first
      
      // initialize the deck with 2 Joker cards
      for (int i = 0; i < 2; i++) 
      {
        // random number for the lifespan (max 4 rounds)
        int rnd = (rand() % 4) + 1;
        this->deck.push_back(new JokerCard(rnd));
      }
    };

    vector<JokerCard*> getDeck() 
    {
      return this->deck;
    };
    
    ~JokerDeck() {
      deck.clear(); // clear the vector of joker cards
    };

};

#endif //JOKERDECK_H