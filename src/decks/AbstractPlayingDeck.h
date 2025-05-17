#ifndef ABSTRACT_EFFECTS_DECK_H
#define ABSTRACT_EFFECTS_DECK_H

#include "Deck.h"
#include <vector>

class AbstractPlayingDeck : public Deck {
private:
    vector<unique_ptr<Card>> deck;
public:
    AbstractPlayingDeck();
    AbstractPlayingDeck(int maxCards);
    ~AbstractPlayingDeck();
    
    vector<unique_ptr<Card>>& getDeck() {
        return this->deck;
    }
    void sortSuits(){
        std::sort(this->deck.begin(), this->deck.end(), [](const unique_ptr<Card>& a, const unique_ptr<Card>& b) {
            auto pa = dynamic_cast<PlayingCard*>(a.get());
            auto pb = dynamic_cast<PlayingCard*>(b.get());
            if (pa && pb) {
                return pa->getSuit() < pb->getSuit();
            }
            return false;
        });
    }
    void sortRanks(){
        std::sort(this->deck.begin(), this->deck.end(), [](const unique_ptr<Card>& a, const unique_ptr<Card>& b) {
            auto pa = dynamic_cast<PlayingCard*>(a.get());
            auto pb = dynamic_cast<PlayingCard*>(b.get());
            if (pa && pb) {
                return pa->getRank() < pb->getRank();
            }
            return false;
        });
    }
    virtual void addEffectCard() = 0;
};

#endif // ABSTRACT_EFFECTS_DECK_H

