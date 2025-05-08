#ifndef HAND_H
#define HAND_H

//For sorting vectors and calculating the Hands
#include <algorithm>
#include <unordered_map>

#include "decks/PlayingDeck.h"

#include "cards/PlayingCard.h"
#include "cards/JokerCard.h"
#include "cards/SupportCard.h"

class Hand {
  private:
    vector<unique_ptr<Card>> deck;
    int maximum_num_cards;

    int total_chips;
    int total_mults;
    int total_score;

    int num_hands;
    int num_discards;

    unordered_map<int, int> rankCount;
    unordered_map<string, int> suitCount;
  public:
    Hand(): maximum_num_cards(5), total_chips(0), total_mults(0), num_hands(4), num_discards(4), total_score(0) {};

    //HAND BUTTON PRESSED
    void pushHand(PlayingDeck& playDeck) 
    {
      string idx = playDeck.pickHand();
      
      for(int i = 0; i < idx.length(); i++) 
      {
        int temp = stoi(string(1, idx[i]));

        if (playDeck.getDeck()[temp] != nullptr) 
        {
          unique_ptr<Card> removed = playDeck.discardCard(temp);
          if (removed != nullptr) 
          {
            this->deck.push_back(std::move(removed));
          }
        };
      };

      this->calculateScore();
      this->num_hands--;
    };

    //DISCARD BUTTON PRESSED----------------------------------------
    void discardHand(PlayingDeck& playDeck) 
    {
      string idx = playDeck.pickDiscard();
      
      for(int i = 0; i < idx.length(); i++) 
      {
        int temp = stoi(string(1, idx[i]));

        if (playDeck.getDeck()[temp] != nullptr) 
        {
          unique_ptr<Card> removed = playDeck.discardCard(temp);
          if (removed != nullptr) 
          {
            this->deck.push_back(std::move(removed));
          }
        };
      };

      this->discardCard();
      this->num_discards--;
    };

    //TOTALSCORE SPECIFIC FUNCTIONS
    //SORTING DESCENDING FROM LEFT TO RIGHT
    void sortHand() 
    {
      std::sort(this->deck.begin(), this->deck.end(), [](
        const unique_ptr<Card>& a, 
        const unique_ptr<Card>& b) 
      {
        
        auto pa = dynamic_cast<PlayingCard*>(a.get());
        auto pb = dynamic_cast<PlayingCard*>(b.get());

        if (pa && pb)
        {
          return pa->getRank() < pb->getRank();
        }

        return false;
      });

      //Stores data about Hand
      for (auto& card : this->deck) {
        auto playingCard = dynamic_cast<PlayingCard*>(card.get());
        if (playingCard) {
          rankCount[playingCard->getChips()]++;
          suitCount[playingCard->getSuit()]++;
        }
      }
    };

    //CALCULATE INDIVIDUAL CHIPS
    void calculateChips() 
    {
      for (int i = 0; i < this->getCurrentCards(); i++) 
      {
        auto pc = dynamic_cast<PlayingCard*>(this->deck[i].get());
        this->total_chips += pc->getChips();
      };
    };

    //CALCULATE TOTAL SCORE (CHIPS + MULTS)
    void calculateScore()
    {
      sortHand(); //NOT SURE IF NEED HERE
      calculateChips();
      //checkHand();
      //CHECK JOKER + SUPPORT BONUSES ADD HERE------------------------------
      this->discardCard();

      this->total_score = this->total_chips*(1 + this->total_mults);
    };

    //HAND TYPES (ADD MORE FUNCTIONS HERE)------------------------------
    void isPair() {
      for (auto& entry : rankCount) {
        if (entry.second == 2) 
        {
          add_total_chips(10);
          add_total_mults(2);
        };
      }
    }

    //COLLECTION OF HAND TYPES----------------------------------------
    void checkHand() 
    {
      isPair();
      //ADD MORE FUNCTIONS HERE
    };

    //CHECK JOKER IN USE, REDUCE THEIR LIFESPAN AFTER USAGE------------------
    //CHECK SUPPORT CARD BOOL, IF BOOL IS TRUE, THEN ADD BONUSES TO CALCULATE SCORE -------------------------------------------------------------

    //DELETE LATER - TO SEE IF HAS BEEN PRINTED
    void printDeck() 
    {
      cout << "[ "; 
      for (int i = 0; i < this->getCurrentCards(); i++) 
      {
        auto playingCard = dynamic_cast<PlayingCard*>(this->deck[i].get());
        cout << playingCard->getSuit() << playingCard->getRank() << " ";
      };
      cout << "]" << endl;
    };

    //ERASE CARD FROM VECTOR
    void discardCard() 
    {
      for (int i = this->getCurrentCards() - 1; i >= 0; i--) 
      {
        this->deck.erase(deck.begin() + i);
      };
    };

    //SETTERS
    void set_num_hands(int h) 
    {
      this->num_hands += h;
    };
    
    void set_num_discards(int d) 
    {
      this->num_discards += d;
    };

    void add_total_chips(int n) 
    {
      this->total_chips += n;
    };

    void add_total_mults(int n) 
    {
      this->total_mults += n;
    };

    //GETTERS
    int get_num_hands() 
    {
      return this->num_hands;
    };
    
    int get_num_discards() 
    {
      return this->num_discards;
    };

    int getCurrentCards() 
    {
      return this->deck.size();
    };

    int get_total_score() 
    {
      return this->total_score;
    };

    ~Hand() {};
};

#endif
