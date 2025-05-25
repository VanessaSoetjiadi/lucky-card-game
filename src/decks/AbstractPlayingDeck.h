#ifndef ABSTRACT_PLAYING_DECK_H
#define ABSTRACT_PLAYING_DECK_H

#include <algorithm>

#include "Deck.h"
#include "../cards/PlayingCard.h"

class AbstractPlayingDeck : public Deck {
    protected:
        vector<PlayingCard*> deck; // vector to hold PlayingCard objects
    public:
        vector<PlayingCard*> getDeck() 
        {
            return this->deck;
        };

        void sortInSuits() // sort the deck based on their suits (alphabetical order)
        {
            std::sort(deck.begin(), deck.end(),
            [](PlayingCard* a, PlayingCard* b) {
                return a->get_suit() < b->get_suit();
            });
        };

        void sortInRanks() // sort the deck based on their ranks
        {
            std::sort(deck.begin(), deck.end(), 
            [](PlayingCard* a, PlayingCard* b) {
                return a->get_chips() < b->get_chips();
            });
        };

        // pure virtual functions override
        int getCurrentCards() override
        {
            return this->deck.size();
        };

        void discardCard(int idx) override
        {
            this->deck.erase(this->deck.begin() + idx);
        };
};

#endif //ABSTRACT_PLAYING_DECK_H

