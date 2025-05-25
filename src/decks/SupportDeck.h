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

      // Initialise the deck with 1 Support cards
      this->deck.push_back(new SupportCard());
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
        // Add new Support card to the deck
        this->deck.push_back(new SupportCard());
      };
    };

    vector<SupportCard*> getDeck() 
    {
      return this->deck;
    };

    ~SupportDeck() {
      //deck.clear(); // Clear the vector of Support cards
    };

};

#endif