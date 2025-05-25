#ifndef ABSTRACT_EFFECTS_DECK_H
#define ABSTRACT_EFFECTS_DECK_H

#include "Deck.h"

class AbstractEffectsDeck : public Deck {
    public:
        virtual ~AbstractEffectsDeck() = default; // Destructor
        virtual void addEffectCard() = 0; // Pure virtual function to add effect cards
};

#endif // ABSTRACT_EFFECTS_DECK_H

