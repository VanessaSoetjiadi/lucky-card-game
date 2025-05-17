#ifndef ABSTRACT_EFFECTS_DECK_H
#define ABSTRACT_EFFECTS_DECK_H

#include "Deck.h"
#include <vector>

class AbstractPlayingDeck : public Deck {
private:
    vector<unique_ptr<Card>> deck; // Vector to hold PlayingCard objects
public:
    AbstractPlayingDeck(); // Default constructor
    AbstractPlayingDeck(int maxCards); // Constructor with maximum cards
    ~AbstractPlayingDeck(); // Destructor
    
    // Create the deck of cards
    vector<unique_ptr<Card>>& getDeck() {
        return this->deck; 
    }
    
    void sortSuits(){ // Sort the deck based on the suits
        std::sort(this->deck.begin(), this->deck.end(), [](const unique_ptr<Card>& a, const unique_ptr<Card>& b) {
            // Dynamic cast to PlayingCard to access Suit
            auto pa = dynamic_cast<PlayingCard*>(a.get()); 
            auto pb = dynamic_cast<PlayingCard*>(b.get()); 
            if (pa && pb) { 
                return pa->getSuit() < pb->getSuit(); // Compare suits
            }
            return false;
        });
    }
    void sortRanks(){ // Sort the deck based on the ranks
        std::sort(this->deck.begin(), this->deck.end(), [](const unique_ptr<Card>& a, const unique_ptr<Card>& b) {
            // Dynamic cast to PlayingCard to access Rank
            auto pa = dynamic_cast<PlayingCard*>(a.get());
            auto pb = dynamic_cast<PlayingCard*>(b.get());
            if (pa && pb) {
                return pa->getRank() < pb->getRank(); // Compare ranks
            }
            return false;
        });
    }
    virtual void addEffectCard() = 0; // Pure virtual function to add effect cards
};

#endif // ABSTRACT_EFFECTS_DECK_H

