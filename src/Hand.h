#ifndef HAND_H
#define HAND_H

#include <map>

#include "decks/InitDeck.h"
#include "decks/PlayingDeck.h"
#include "decks/JokerDeck.h"
#include "decks/SupportDeck.h"

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

    void calculateChips (PlayingDeck& playDeck) 
    {
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        if (playDeck.getDeck()[i]->get_chosen() == true) 
        {
          this->totalChips += playDeck.getDeck()[i]->get_chips();
        };
      };
    };

    int checkHandType(PlayingDeck& playDeck) 
    {
      map<string, int> rankCount;
      map<string, int> suitCount;
      vector<int> rankValues;

      for (const auto& card : playDeck.getDeck()) {
        if (card->get_chosen() == true) {
            rankCount[card->get_rank()]++;
            suitCount[card->get_suit()]++;
            rankValues.push_back(card->get_chips());
        }
      }


      // //CHECKER (DELETE LATER)
      // for (const auto& pair : rankCount) {
      //   std::cout << "Rank: " << pair.first << ", Count: " << pair.second << std::endl;
      // }

      // for (const auto& suitEntry : suitCount) {
      //   std::cout << "Suit: " << suitEntry.first 
      //   << ", Count: " << suitEntry.second << std::endl;
      // }

      bool isFlush = false;
      for (const auto& entry : suitCount) {
        if (entry.second >= 5) {
          isFlush = true;
          break;
        };
      };

      bool isStraight = false;
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

    // determining the bonus chips and mults obtained from the hand type
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

    // calculating the total bonus effects received from the effects cards
    void calculateEffectsCards(JokerDeck& jkDeck, SupportDeck& spDeck) 
    {
      // getting total bonuses from joker deck
      for (int i = 0; i < jkDeck.getCurrentCards(); i++) 
      {
        this->totalChips += jkDeck.getDeck()[i]->get_bonus_chips();
        this->totalMults += jkDeck.getDeck()[i]->get_bonus_mults();
        jkDeck.getDeck()[i]->subtract_lifespan();
      };

      // getting total bonuses from the support deck
      for (int i = spDeck.getCurrentCards() - 1; i >= 0; i--) 
      {
        if (spDeck.getDeck()[i]->get_isUsed()) 
        {
          this->totalChips += spDeck.getDeck()[i]->get_bonus_chips();
          this->totalMults += spDeck.getDeck()[i]->get_bonus_mults();

          // setting the card as already used
          spDeck.getDeck()[i]->set_Used();
        };
      };
    };

    // when the hand button is pressed
    void calculateTotalScore(PlayingDeck& playDeck, JokerDeck& jkDeck, SupportDeck& spDeck) 
    {
      add_handsCount(playDeck);
      add_discardsCount(playDeck);

      // cout << checkHandType(playDeck) << endl;
      // calculatePlayingCardsPoints(checkHandType(playDeck));

      calculateChips(playDeck);
      calculateEffectsCards(jkDeck, spDeck);

      this->totalScore = this->totalChips*this->totalMults;
    };

    void discardPlayingCards(string index, PlayingDeck& playDeck) 
    {
      // sort decreasing from the left, so that elements from the vectors are removed safely
      std::sort(index.begin(), index.end(), std::greater<char>());
      for (int i = 0; i < index.length(); i++) 
      {
        if (playDeck.getDeck()[index[i] - '0']->get_chosen() == true) 
        {
          playDeck.discardCard(index[i] - '0'); 
        };
      };
    };

    void discardEffectsCards(JokerDeck& jkDeck, SupportDeck& spDeck)
    {
      string idx; // indexes are stored safely in string first, before being removed entirely to avoid accessing the wrong memory.

      // checking the joker deck
      for (int i = 0; i < jkDeck.getCurrentCards(); i++) 
      {
        if (jkDeck.getDeck()[i]->get_lifespan() < 1) 
        {
          idx.append(to_string(i));
        };
      };

      // sorting decreasing
      std::sort(idx.begin(), idx.end(), std::greater<char>());

      // removing the cards from the joker deck
      for (int i = 0; i < idx.length(); i++) 
      {
        jkDeck.discardCard(idx[i] - '0');
      };

      // checking the support deck
      for (int i = 0; i < spDeck.getCurrentCards(); i++) 
      {
        if (spDeck.getDeck()[i]->get_isUsed() < 1) 
        {
          idx.append(to_string(i));
        };
      };

      // sorting decreasing
      std::sort(idx.begin(), idx.end(), std::greater<char>());

      // removing the cards from the support deck
      for (int i = 0; i < idx.length(); i++) 
      {
        spDeck.discardCard(idx[i] - '0');
      };
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

    void subtract_handsCount() 
    {
      handsCount--;
    };

    void subtract_discardsCount() 
    {
      discardsCount--;
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
