#ifndef SUPPORTDECK_H
#define SUPPORTDECK_H

#include "AbstractEffectsDeck.h"
#include "SupportCard.h"

class SupportDeck : public Deck {
  private:
    vector<unique_ptr<SupportCard>> deck; // Vector to hold Support cards
  public:
    //CONSTRUCTOR
    SupportDeck() {
      // Initialise the deck with Support cards
      for (int i = 0; i < 2; i++) { // Assuming 2 Support cards
        deck.push_back(make_unique<SupportCard>(20, 1)); // Example bonus chips and mults
      }
    };
    
    //MAKEDECK SUPPORT
    void makeDeck() override {
        // This function can be used to initialize or reset the Support deck if needed
        deck.clear(); // Clear the existing deck
        for (int i = 0; i < 2; i++) { // Assuming 2 Support cards
            deck.push_back(make_unique<SupportCard>(20, 1)); // Example bonus chips and mults
        }
    };

    //DISCARD CARD (ERASE FROM DECK) COPY FROM HAND
    unique_ptr<SupportCard> discardCard(int index) {
        if (index < 0 || index >= deck.size()) {
            return nullptr;
        }
        unique_ptr<SupportCard> removed = std::move(deck[index]); // Move the card at the specified index to a unique_ptr
        deck.erase(deck.begin() + index); // Remove the card from the deck at the specified index
        return std::move(removed); // Return the removed Support card
    };
    
    //GET CURRENT CARDS (USEFUL FOR DISCARD CARD)
    vector<unique_ptr<SupportCard>>& getDeck() {
      return deck; // Support Deck
    };

    //GETTERS
    int getCurrentCards() {
      return deck.size(); // Support Deck size
    };

    //SETTERS
    void addSupportCard(int bonus_chips, int bonus_mults) {
      deck.push_back(make_unique<SupportCard>(bonus_chips, bonus_mults)); // Add new Support card to the deck
    };

    //DESTRUCTOR
    ~SupportDeck() {
        deck.clear(); // Clear the vector of Support cards
    };

};

#endif