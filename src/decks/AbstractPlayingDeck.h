#ifndef ABSTRACT_PLAYING_DECK_H
#define ABSTRACT_PLAYING_DECK_H

#include <algorithm>

#include "Deck.h"
#include "../cards/PlayingCard.h"

class AbstractPlayingDeck : public Deck {
    protected:
        vector<PlayingCard*> deck; // Vector to hold PlayingCard objects
    public:
        vector<PlayingCard*> getDeck() 
        {
            return this->deck;
        };

        //VIRTUAL FUNCTIONS IMPLEMENTED
        int getCurrentCards() override
        {
            return this->deck.size();
        };

        void discardCard(int idx) override
        {
            this->deck.erase(this->deck.begin() + idx);
        };

        void sortInSuits() // Sort the deck based on the suits
        {
            std::sort(deck.begin(), deck.end(),
            [](PlayingCard* a, PlayingCard* b) {
                return a->get_suit() < b->get_suit();
            });
        };

        void sortInRanks() // Sort the deck based on the ranks
        {
            std::sort(deck.begin(), deck.end(), 
            [](PlayingCard* a, PlayingCard* b) {
                return a->get_chips() < b->get_chips();
            });
        };
};

#endif //ABSTRACT_PLAYING_DECK_H

