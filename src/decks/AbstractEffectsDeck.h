#ifndef ABSTRACT_EFFECTS_DECK_H
#define ABSTRACT_EFFECTS_DECK_H

#include "Deck.h"
#include <vector>

class AbstractEffectsDeck : public Deck {

public:
    AbstractEffectsDeck(int maxCards){}; // Constructor with maximum cards
    virtual ~AbstractEffectsDeck(){}; // Destructor
    
    virtual void makeDeck() = 0; // Pure virtual function to create the deck of cards
    virtual void addEffectCard() = 0; // Pure virtual function to add effect cards
};

#endif // ABSTRACT_EFFECTS_DECK_H

