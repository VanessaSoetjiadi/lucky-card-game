#ifndef HAND_H
#define HAND_H

#include <map>

#include "decks/InitDeck.h"
#include "decks/PlayingDeck.h"
#include "decks/JokerDeck.h"
#include "decks/SupportDeck.h"

const string Hands[] {"High Card", "Royal Flush", "Straight Flush", "Flush", "Four of a Kind", "Full House", "Straight", "Three of a Kind", "Two Pair", "Pair"};

class Hand {
  private:
    int maximumNumCards;
    int totalChips;
    int totalMults;
    int totalScore;
    int handsCount;
    int discardsCount;
  public:
    Hand(): maximumNumCards(5), totalChips(0), totalMults(0), totalScore(0),handsCount(4), discardsCount(4) {};

    //NOTE: For most of the calculating functions, we'll be iterating backwards since we're checking and deleting in one go.
    void calculateChips (PlayingDeck& playDeck) 
    {
      for (int i = playDeck.getCurrentCards() - 1; i >= 0; i--) 
      {
        if (playDeck.getDeck()[i]->get_chosen()) 
        {
          this->totalChips += playDeck.getDeck()[i]->get_chips();
          playDeck.discardCard(i);
        };
      };
    };

    int checkHandType(PlayingDeck& playDeck) 
    {
      map<string, int> rankCount;
      map<string, int> suitCount;

      for (const auto& card : playDeck.getDeck()) {
        //only add if it's chosen
        if (card->get_chosen()) 
        {
          rankCount[card->get_rank()]++; // Increment count for this rank
          suitCount[card->get_suit()]++; // Increment count for this suit
        };
      };

      //CHECKER (DELETE LATER)
      for (const auto& pair : rankCount) {
        std::cout << "Rank: " << pair.first << ", Count: " << pair.second << std::endl;
      }

      for (const auto& suitEntry : suitCount) {
        std::cout << "Suit: " << suitEntry.first 
        << ", Count: " << suitEntry.second << std::endl;
      }

      bool isFlush = false;
      for (const auto& entry : suitCount) {
        if (entry.second >= 5) {
          isFlush = true;
          break;
        };
      };

      bool isStraight = false;
      vector<int> rankValues;
      for (const auto& card : playDeck.getDeck()) {
        rankValues.push_back(card->get_chips());
      }
      std::sort(rankValues.begin(), rankValues.end());
      for (size_t i = 0; i <= rankValues.size() - 5; ++i) {
        if (rankValues[i + 4] == rankValues[i] + 4) {
          isStraight = true;
          break;
        }
      }

      //ROYAL FLUSH
      if (isFlush && isStraight && rankValues.back() == 14) {
        return 21;
      }

      //STRAIGHT FLUSH
      if (isFlush && isStraight) {
        return 22;
      }

      //FOUR OF A KIND
      for (const auto& entry : rankCount) {
        if (entry.second == 4) {
          return 23;
        }
      }

      //FULL HOUSE
      bool hasThree = false, hasTwo = false;
      for (const auto& entry : rankCount) {
        if (entry.second == 3) hasThree = true;
        if (entry.second == 2) hasTwo = true;
      }
      if (hasThree && hasTwo) {
        return 24;
      }

      //FLUSH
      if (isFlush) {
        return 25;
      }

      //THREE OF A KIND
      if (hasThree) {
        return 26;
      }

      // Check Straight
      if (isStraight) {
        return 27;
      }

      //TWO PAIR
      int pairs = 0;
      for (const auto& entry : rankCount) {
        if (entry.second == 2) pairs++;
      }
      if (pairs >= 2) {
        return 28;
      }

      //PAIR
      if (pairs == 1) {
        return 29;
      }

      //HIGH CARD
      return rankValues.back();
    };

    //DETERMINE BONUS MULTS, CHIPS FROM CheckHandType function
    void calculatePlayingCardsPoints(int hands) 
    {
      switch(hands) 
      {
        case 21:
          totalChips += 100;
          totalMults += 8;
          break;
        case 22:
          totalChips += 100;
          totalMults += 8;
          break;
        case 23:
          totalChips += 60;
          totalMults += 7;
          break;
        case 24:
          totalChips += 40;
          totalMults += 4;
          break;
        case 25:
          totalChips += 35;
          totalMults += 4;
          break;
        case 26:
          totalChips += 30;
          totalMults += 3;
          break;
        case 27:
          totalChips += 30;
          totalMults += 3;
          break;
        case 28:
          totalChips += 20;
          totalMults += 2;
          break;
        case 29:
          totalChips += 10;
          totalMults += 2;
          break;
        default:
          totalChips += hands;
          break;
      };
    };

    //CALCULATING THE TOTAL BONUS EFFECTS RECEIVED
    void calculateEffectsCards(JokerDeck& jkDeck, SupportDeck& spDeck) 
    {
      //Getting the total bonuses from the jokerDeck
      for (int i = jkDeck.getCurrentCards() - 1; i >= 0; i--) 
      {
        this->totalChips += jkDeck.getDeck()[i]->get_bonus_chips();
        this->totalMults += jkDeck.getDeck()[i]->get_bonus_mults();
        jkDeck.getDeck()[i]->subtract_lifespan();

        //Deleting the jokerCard if it's lifespan is 0
        if (jkDeck.getDeck()[i]->get_lifespan() < 1) 
        {
          jkDeck.discardCard(i);
        };
      };

      //Getting the total bonuses from the supportDeck
      for (int i = spDeck.getCurrentCards() - 1; i >= 0; i--) 
      {
        if (spDeck.getDeck()[i]->get_isUsed()) 
        {
          this->totalChips += spDeck.getDeck()[i]->get_bonus_chips();
          this->totalMults += spDeck.getDeck()[i]->get_bonus_mults();

          //Deleting the support card since it's been used
          spDeck.discardCard(i);
        };
      };
    };

    //WHEN HAND BUTTON IS PRESSED
    void calculateTotalScore(PlayingDeck& playDeck, JokerDeck& jkDeck, SupportDeck& spDeck) 
    {
      add_handsCount(playDeck);
      add_discardsCount(playDeck);

      calculatePlayingCardsPoints(checkHandType(playDeck));

      calculateChips(playDeck);
      calculateEffectsCards(jkDeck, spDeck);

      this->totalScore = this->totalChips*this->totalMults;
    };

    //SETTERS
    void add_handsCount (PlayingDeck& playDeck) 
    {
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        if (playDeck.getDeck()[i]->get_chosen()) 
        {
          if (playDeck.getDeck()[i]->get_color().compare(CardColor[1]) == 0) this->handsCount++;
        };
      };
    };

    void add_discardsCount (PlayingDeck& playDeck) 
    {
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        if (playDeck.getDeck()[i]->get_chosen()) 
        { 
          if (playDeck.getDeck()[i]->get_color().compare(CardColor[2]) == 0) this->discardsCount++;
        };
      };
    };

    //GETTERS
    int get_totalScore() 
    {
      return this->totalScore;
    };

    int get_handsCount() 
    {
      return this->handsCount;
    };

    int get_discardsCount() 
    {
      return this->discardsCount;
    };

    ~Hand() {};
};

#endif
