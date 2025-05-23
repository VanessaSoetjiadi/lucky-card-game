#ifndef ABSTRACT_EFFECTS_DECK_H
#define ABSTRACT_EFFECTS_DECK_H

#include "Deck.h"

class AbstractEffectsDeck : public Deck {
    public:
        virtual ~AbstractEffectsDeck() = default; // destructor
        virtual void addEffectCard() = 0; // pure virtual function to add effect cards
        virtual void makeDeck() = 0; // to reset the deck every new Game session
};

#endif // ABSTRACT_EFFECTS_DECK_H

