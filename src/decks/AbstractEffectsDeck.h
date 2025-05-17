#ifndef ABSTRACT_EFFECTS_DECK_H
#define ABSTRACT_EFFECTS_DECK_H

#include "Deck.h"
#include <vector>

class AbstractEffectsDeck : public Deck {
public:
    AbstractEffectsDeck();
    AbstractEffectsDeck(int maxCards);
    virtual ~AbstractEffectsDeck();
    
    virtual void makeDeck() = 0;
    virtual void addEffectCard() = 0;
};

#endif // ABSTRACT_EFFECTS_DECK_H

