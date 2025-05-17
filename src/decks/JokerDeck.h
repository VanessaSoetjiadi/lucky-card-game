#ifndef JOKERDECK_H
#define JOKERDECK_H

#include "AbstractEffectsDeck.h"
#include "JokerCard.h"

class JokerDeck : public Deck {
  private:
    vector<unique_ptr<JokerCard>> deck; // Vector to hold Joker cards
  public:
    //CONSTRUCTOR
    JokerDeck() {
      // Initialize the deck with Joker cards
      for (int i = 0; i < 4; i++) { // Assuming 4 Jokers
        deck.push_back(make_unique<JokerCard>(5, 50, 2)); // Example lifespan, chips, and mults
      }
    };
    //MAKEDECK JOKER
    void makeDeck() override {
      // This function can be used to initialize or reset the Joker deck if needed
      deck.clear(); // Clear the existing deck
      for (int i = 0; i < 4; i++) { // Assuming 4 Jokers
        deck.push_back(make_unique<JokerCard>(5, 50, 2)); // Example lifespan, chips, and mults
      }
    };
    
    //DISCARD CARD (ERASE FROM DECK) COPY FROM HAND
    unique_ptr<JokerCard> discardCard(int index) {
      if (index < 0 || index >= deck.size()) {
        return nullptr; 
      }
      unique_ptr<JokerCard> removed = std::move(deck[index]); // Move the card at the specified index to a unique_ptr
      deck.erase(deck.begin() + index); // Remove the card from the deck at the specified index
      return std::move(removed); // Return the removed joker card
    };
    
    //GET CURRENT CARDS (USEFUL FOR DISCARD CARD)
    vector<unique_ptr<JokerCard>>& getDeck() {
      return deck; // Joker Deck
    };
    
    //GETTERS
    int getCurrentCards() {
      return deck.size(); // Joker Deck size
    };

    //SETTERS
    void addJokerCard(int lifespan, int bonus_chips, int bonus_mults) {
      deck.push_back(make_unique<JokerCard>(lifespan, bonus_chips, bonus_mults)); // Add new Joker card to the deck
    };
    
    //DESTRUCTOR
    ~JokerDeck() {
      deck.clear(); // Clear the vector of Joker cards
    };

};

#endif