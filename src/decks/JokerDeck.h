#ifndef JOKERDECK_H
#define JOKERDECK_H

#include "AbstractEffectsDeck.h"
#include "../cards/JokerCard.h"

class JokerDeck : public AbstractEffectsDeck {
  private:
    vector<JokerCard*> deck; // Vector to hold Joker cards
  public:
    JokerDeck() {
      this->set_maximumNumCards(4);

      //Initialize the deck with 2 Joker cards
      for (int i = 0; i < 2; i++) 
      {
        //Random number for the lifespan (max 4 rounds)
        int rnd = (rand() % 4) + 1;
        this->deck.push_back(new JokerCard(rnd));
      }
    };
    
    //PURE VIRTUAL FUNCTIONS OVERRIDE
    //FROM DECK
    void discardCard(int idx) override
    {
      this->deck.erase(this->deck.begin() + idx);
    };
    
    int getCurrentCards() override
    {
      return this->deck.size();
    };

    //FROM ABSTRACTEFFECTSDECK
    void addEffectCard() override
    {
      //Only add if deck is not full
      if (this->getCurrentCards() < this->get_maximumNumCards()) {
        // Add new Joker card to the deck
        int rnd = ((rand() % 4) - 1);
        this->deck.push_back(new JokerCard(rnd));
      };
    };

    vector<JokerCard*> getDeck() 
    {
      return this->deck;
    };

    
    
    ~JokerDeck() {
      //deck.clear(); // Clear the vector of Joker cards
    };

};

#endif