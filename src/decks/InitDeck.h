#ifndef INITDECK_H
#define INITDECK_H

#include "Deck.h"

class InitDeck : public Deck {
  private:
    vector<unique_ptr<Card>> deck;
    int maximum_num_cards;
  public:
    InitDeck(): maximum_num_cards(52) {};

    //MAKE 52 INITIAL CARDS IN DECK
    void makeDeck() override
    {
      for (int i = 0; i < 4; i++) 
      {
        for (int j = 0; j < 13; j++) 
        {
          switch(i + 1) 
          {
            case 1:
              this->deck.push_back(make_unique<PlayingCard>(Suit[0], to_string(j + 1)));
              break;
            case 2:
              this->deck.push_back(make_unique<PlayingCard>(Suit[1], to_string(j + 1)));
              break;
            case 3:
              this->deck.push_back(make_unique<PlayingCard>(Suit[2], to_string(j + 1)));
              break;
            case 4:
              this->deck.push_back(make_unique<PlayingCard>(Suit[3], to_string(j + 1)));
              break;
          };
        };
      };
    };

    vector<unique_ptr<Card>>& getDeck() {
      return this->deck;
    };

    //MOVES CARD FROM INITIAL DECK TO HAND DECK
    unique_ptr<Card> discardCard(string suit, string rank) override
    {
      for (int i = 0; i < this->maximum_num_cards; i++) 
      {
        auto playingCard = dynamic_cast<PlayingCard*>(this->deck[i].get());

        if (playingCard->getSuit() == suit && playingCard->getRank() == rank) 
        {
          std::unique_ptr<Card> removed = std::move(deck[i]);
          deck.erase(deck.begin() + i);
          return std::move(removed);
        };
      };
      return nullptr;
    };

    //GETTERS
    int getCurrentCards() 
    {
      return this->deck.size();
    };

    void makeDeck() override
    {
      this->makeDeck();
    };

    //DESTRUCTOR
    ~InitDeck() {};
};

#endif