#ifndef PLAYINGDECK_H
#define PLAYINGDECK_H

#include <random>

#include "Deck.h"
#include "InitDeck.h"

class PlayingDeck {
  private:
    vector<unique_ptr<Card>> deck;
    int maximum_num_cards;
  public:
    PlayingDeck(): maximum_num_cards(8) {};

    //DECK FOR PLAYING
    void makeDeck(InitDeck& initialDeck) 
    {
      while(this->deck.size() < this->maximum_num_cards) 
      {
        int random = randomizer(initialDeck);

        //RANDOMIZE CARD RETRIEVED FROM INITIAL DECK
        if (initialDeck.getDeck()[random] != nullptr) 
        {
          PlayingCard* pc = dynamic_cast<PlayingCard*>(initialDeck.getDeck()[random].get());
          
          string st = pc->getSuit();
          string rk = pc->getRank();

          unique_ptr<Card> removed = initialDeck.discardCard(st, rk);

          if (removed != nullptr) 
          {
            this->deck.push_back(std::move(removed));
          }
        };
      };
    };

    //NUMBER RANDOMIZER
    int randomizer(InitDeck& initialDeck) 
    {
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<> dis(0, initialDeck.getCurrentCards() - 1);

      return dis(gen); 
    };

    //(DELETE LATER) FOR TESTING
    void printDeck() 
    {
      cout << "[ "; 
      for (int i = 0; i < this->maximum_num_cards; i++) 
      {
        auto playingCard = dynamic_cast<PlayingCard*>(this->deck[i].get());
        cout << playingCard->getSuit() << playingCard->getRank() << " ";
      };
      cout << "]" << endl;
    };

    //CHOOSING HAND BELOW 5, ABOVE 5 IS NOT ALLOWED (NO ERROR)
    string pickHand() {
      //SIMULATION
      string nums;
      cout << "Input index to be handed (max 5): ";
      cin >> nums;

      while (nums.length() > 5 || nums.length() < 1)  
      {
        cout << "Please input something from Big to Small: ";
        cin >> nums;
      };
      
      return nums;
    };

    //CHOOSING DISCARD BELOW 5, ABOVE 5 IS NOT ALLOWED (NO ERROR)
    string pickDiscard() {
      //SIMULATION
      string nums;
      cout << "Input index to be discarded (max 5): ";
      cin >> nums;

      while (nums.length() < 1)  
      {
        cout << "Please input something: ";
        cin >> nums;
      };
      
      return nums;
    };

    vector<unique_ptr<Card>>& getDeck() 
    {
      return this->deck;
    };

    //MOVES THE CARD FROM PLAYDECK TO HAND, ERASE IT FROM HERE
    unique_ptr<Card> discardCard(int idx)
    {
      unique_ptr<Card> removed = std::move(this->deck[idx]);
      deck.erase(deck.begin() + idx);
      return std::move(removed);
    };

    //CURRENT NUMBER OF CARDS WITHIN VECTOR
    int getCurrentCards() 
    {
      return this->deck.size();
    };

    ~PlayingDeck() {};
};

#endif