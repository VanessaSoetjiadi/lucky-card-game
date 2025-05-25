#ifndef SUPPORTDECK_H
#define SUPPORTDECK_H

#include "AbstractEffectsDeck.h"
#include "../cards/SupportCard.h"

class SupportDeck : public AbstractEffectsDeck {
  private:
    vector<SupportCard*> deck; // Vector to hold Support cards
  public:
    SupportDeck() {
      this->set_maximumNumCards(2);  
    };

    // pure virtual functions overrides
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
        // add a new support card into the deck
        this->deck.push_back(new SupportCard());
      };
    };

    void makeDeck() override
    {
      for (auto card : deck) delete card;
      deck.clear(); // clears the vector first
      
      // initialize the deck with 1 support card
      this->deck.push_back(new SupportCard());
    };

    vector<SupportCard*>& getDeck() 
    {
      return this->deck;
    };

    ~SupportDeck() {
      for (auto card : deck) {
        delete card;
      }
      deck.clear(); // clear the vector of support cards
    };

};

#endif //SUPPORTDECK_H