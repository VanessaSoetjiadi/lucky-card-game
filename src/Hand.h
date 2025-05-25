#ifndef HAND_H
#define HAND_H

#include <map>
#include <algorithm>

#include "decks/InitDeck.h"
#include "decks/PlayingDeck.h"
#include "decks/JokerDeck.h"
#include "decks/SupportDeck.h"

const string Hands [] = { "Royal Flush", "Straight Flush", "Four of a Kind", "Full House", "Flush", "Straight", "Three of a Kind", "Two Pair", "Pair", "High Card" };

class Hand {
  private:
    int maximumNumCards;
    int totalChips;
    int totalMults;
    int totalScore;
    int handsCount;
    int discardsCount;
  public:
    Hand(): maximumNumCards(5), totalChips(0), totalMults(1), totalScore(0), handsCount(4), discardsCount(2) {};

    void calculateChips (PlayingDeck& playDeck) // calculating the total chips received from the hand played
    {
      int sum = 0;
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        if (playDeck.getDeck()[i]->get_chosen() == true) 
        {
          this->totalChips += playDeck.getDeck()[i]->get_chips();
          sum += playDeck.getDeck()[i]->get_chips();
        };
      };
      cout << "Total chips from cards: " << sum << " | ";
    };

    int checkHandType(PlayingDeck& playDeck) // checking the hand type
    {
      // initializing the counters
      map<string, int> rankCount;
      map<string, int> suitCount;
      vector<int> rankValues; // for the ranks, to know if they're consecutive or not

      bool isFlush = false; // check if there's a flush (5 cards from the same suit)
      bool isStraight = false; // check if there's a straight (consecutive cards)

      bool rankHasThree = false, rankHasTwo = false; // for full house, pairs - checks if there's 3 cards of the same rank, and 2 cards of the same rank

      int pairs = 0; // for two pairs

      for (const auto& card : playDeck.getDeck()) {
        if (card->get_chosen() == true) {
          rankCount[card->get_rank()]++;
          suitCount[card->get_suit()]++;
          rankValues.push_back(card->get_chips()); // chips instead of ranks, because chips are in integers, no need for stoi
        }
      }

      if (rankValues.size() > 4) // flush & straight & full house only works if there's 5 cards
      {
        for (const auto& entry : suitCount) {
          if (entry.second >= 5) {
            isFlush = true;
            break;
          };
        };
        
        if (isConsecutive(rankValues) == true) {
          isStraight = true;
        };

        // royal flush (same suit, must be A K J Q 10)
        if (isFlush && isStraight && rankValues.back() == 14) {
          return 20;
        };

        // straight flush (same suit, 5 cards in consecutive order)
        if (isFlush && isStraight) {
          return 21;
        };

        // straight
        if (isStraight) {
          return 25;
        };

        // flush
        if (isFlush) {
          return 24;
        };
      };

      // full house (this is placed outside because it has rankHasThree and rankHasTwo bool - both doesn't need 5 cards to be true)
      for (const auto& entry : rankCount) {
        if (entry.second == 3) rankHasThree = true;
        if (entry.second == 2) rankHasTwo = true;
      };
      if (rankHasThree && rankHasTwo) {
        return 23;
      };

      for (const auto& entry : rankCount) { // four of a kind (4 cards with matching ranks)
        if (entry.second == 4) {
          return 22;
        }
      }

      for (const auto& entry : rankCount) { // two pairs
        if (entry.second == 2) pairs++;
      }
      if (pairs >= 2) {
        return 27;
      }

      if (rankHasThree) { // three of a kind
        return 26;
      }

      if (pairs == 1) { // pair
        return 28;
      }
    
      return rankValues.back(); // high card, plays the highest card within entire deck
    };

    string calculateHandsPoints(int hands) // determining the bonus chips and mults obtained from the hand type
    {
      switch(hands) 
      {
        case 20: // royal flush
          totalChips += 100;
          totalMults += 8;
          return Hands[0];
        case 21: // straight flush
          totalChips += 100;
          totalMults += 8;
          return Hands[1];
        case 22: // four of a kind
          totalChips += 60;
          totalMults += 7;
          return Hands[2];
        case 23: // full house
          totalChips += 40;
          totalMults += 4;
          return Hands[3];
        case 24: // flush
          totalChips += 35;
          totalMults += 4;
          return Hands[4];
        case 25: // straight
          totalChips += 30;
          totalMults += 3;
          return Hands[5];
        case 26: // three of a kind
          totalChips += 30;
          totalMults += 3;
          return Hands[6];
        case 27: // two pair
          totalChips += 20;
          totalMults += 2;
          return Hands[7];
        case 28: // pair
          totalChips += 10;
          totalMults += 2;
          return Hands[8];
        default: // high card
          totalChips += hands;
          return Hands[9];
      };
    };

    void calculateEffectsCards(JokerDeck& jkDeck, SupportDeck& spDeck) // calculating the total bonus effects received from the effects cards
    {
      int totalChipstemp = 0;
      int totalMultstemp = 0;
      
      for (int i = 0; i < jkDeck.getCurrentCards(); i++) // getting total bonuses from joker deck
      {
        this->totalChips += jkDeck.getDeck()[i]->get_bonus_chips();
        this->totalMults += jkDeck.getDeck()[i]->get_bonus_mults();
        jkDeck.getDeck()[i];
        totalChipstemp += jkDeck.getDeck()[i]->get_bonus_chips();
        totalMultstemp += jkDeck.getDeck()[i]->get_bonus_mults();
        jkDeck.getDeck()[i]->subtract_lifespan();
      };

      for (int i = spDeck.getCurrentCards() - 1; i >= 0; i--) // getting total bonuses from the support deck
      {
        if (spDeck.getDeck()[i]->get_isUsed() == true) 
        {
          this->totalChips += spDeck.getDeck()[i]->get_bonus_chips();
          this->totalMults += spDeck.getDeck()[i]->get_bonus_mults();
          totalChipstemp += spDeck.getDeck()[i]->get_bonus_chips();
          totalMultstemp += spDeck.getDeck()[i]->get_bonus_mults();
        };
      };

      cout << "Bonuses obtained from effects cards: Chips: " << totalChipstemp << ", Mults: " << totalMultstemp << "\n";
    };

    void calculateTotalScore(PlayingDeck& playDeck, JokerDeck& jkDeck, SupportDeck& spDeck) // when the hand button is pressed
    {
      add_handsCount(playDeck);
      add_discardsCount(playDeck);

      cout << "You played: " << calculateHandsPoints(checkHandType(playDeck)) << " | ";
      cout << "Bonuses obtained from Hands: Chips: " << totalChips << ", Mults: " << totalMults << " | ";

      calculateChips(playDeck);
      calculateEffectsCards(jkDeck, spDeck);

      discardPlayingCards(playDeck);
      autoDiscardEffectsCards(jkDeck, spDeck);

      cout << "Total Chips x Total Mults: " << totalChips << " x " << totalMults << "\n";
      this->totalScore = this->totalChips*this->totalMults;

      handsCount--;
    };

    void discardPlayingCards(PlayingDeck& playDeck) 
    {
      for (int i = playDeck.getCurrentCards() - 1; i >= 0; i--) 
      {
        if (playDeck.getDeck()[i]->get_chosen() == true) 
        {
          playDeck.discardCard(i);
        };
      };
    };

    void manualDiscardEffectsCards(string index, AbstractEffectsDeck& effectsDeck) 
    { // used in the Game class when user discards an effectsCard
      std::sort(index.begin(), index.end(), std::greater<char>());
      for (int i = 0; i < index.length(); i++) 
      {
        effectsDeck.discardCard(i);
      };
    };

    void autoDiscardEffectsCards(JokerDeck& jkDeck, SupportDeck& spDeck)
    { // used in the Hand class, embedded in calculatetotalscore, automatically check if there's any effectscard to be discarded
      for (int i = jkDeck.getCurrentCards() - 1; i >= 0; i--) // checking the joker deck
      {
        if (jkDeck.getDeck()[i]->get_lifespan() < 1) 
        {
          jkDeck.discardCard(i);
        };
      };

      for (int i = spDeck.getCurrentCards() - 1; i >= 0; i--) // checking the support deck
      {
        if (spDeck.getDeck()[i]->get_isUsed() == true) 
        {
          spDeck.discardCard(i);
        };
      };
    };

    void add_handsCount (PlayingDeck& playDeck) // adds bonus hand count from the color of the cards (black)
    {
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        if (playDeck.getDeck()[i]->get_chosen() == true) 
        {
          if (playDeck.getDeck()[i]->get_color().compare(CardColor[1]) == 0) {
            cout << playDeck.getDeck()[i]->get_suit() << playDeck.getDeck()[i]->get_rank() << " was a black card | Bonus hand turn has been added" << endl;
            this->handsCount++;
          };
        };
      };
    };

    void add_discardsCount (PlayingDeck& playDeck) // adds bonus discard count from the color of the cards (blue)
    {
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        if (playDeck.getDeck()[i]->get_chosen()) 
        { 
          if (playDeck.getDeck()[i]->get_color().compare(CardColor[2]) == 0) {
            cout << playDeck.getDeck()[i]->get_suit() << playDeck.getDeck()[i]->get_rank() << " was a blue card | Bonus discards has been added" << endl;
            this->discardsCount++;
          };
        };
      };
    };

    void subtract_handsCount() // reduce hand count by one, happens when user plays a hand
    {
      handsCount--;
    };

    void subtract_discardsCount() // reduce discard count by one, happens when user discard playing cards
    {
      discardsCount--;
    };

    bool isConsecutive(const vector<int>& numbers) { // checks if numbers are consecutive (for straight)
      if (numbers.empty()) { // 
        return false;
      }
      
      // find min and max of a vector
      int min_num = *min_element(numbers.begin(), numbers.end());
      int max_num = *max_element(numbers.begin(), numbers.end());
      
      if (max_num - min_num + 1 != numbers.size()) { // checks if the count matches the expected range, if not, false
        return false;
      }
    
      vector<bool> visited(numbers.size(), false); // checks for duplicates
      
      for (int num : numbers) {
        int index = num - min_num;
        if (index < 0 || index >= numbers.size() || visited[index]) {
          return false;
        }
        visited[index] = true;
      }
      
      return true;
    }

    //SETTERS
    void set_totalChips(int n) 
    {
      this->totalChips = n;
    };

    void set_totalMults(int n) 
    {
      this->totalChips = n;
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
