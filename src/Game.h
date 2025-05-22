#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Hand.h"

using namespace std;

class Game {
  private:
    int minimumScore;
    int round;
    int difficulty;
    bool lose_status;
    vector<int> highscores;
  public:
    Game(): round(0), minimumScore(100)
    {
      JokerDeck jkDeck;
      SupportDeck spDeck;

      runGame(jkDeck, spDeck);
    };

    void runGame(JokerDeck jkDeck, SupportDeck spDeck) {
      lose_status = false;

      while (lose_status == false) {
        round++;

        int d = 0; //placeholder for input difficulty

        while (d < 1 || d > 3) { // inputting the difficulty level
          cout << "Please select difficulty: 1, 2, 3\n";
          cout << "Answer: ";
          cin >> d;
        };
        cout << "\n";

        switch(d) // determining the minimum score based on the difficulty chosen
        {
          case 1:
            minimumScore += 75*round;
            break;
          case 2:
            minimumScore += 150*round;
            break;
          case 3:
            minimumScore += 250*round;
            break;
          default:
            minimumScore += 75*round;
            break;
        };

        cout << "You'll need " << minimumScore << " to win!" << "\n";

        // add joker card every 2 rounds
        if (round % 2 == 0) 
        {
          jkDeck.addEffectCard();
        };

        // add support card every 4 rounds
        if (round % 4 == 0) 
        {
          spDeck.addEffectCard();
        };

        // initilizations
        Hand hand;

        InitDeck initialDeck;
        initialDeck.makeDeck();

        PlayingDeck playDeck;
        
        // game loop
        while (hand.get_handsCount() > 0 && hand.get_totalScore() < minimumScore) 
        {
          playDeck.makeDeck(initialDeck);
          hand.set_totalChips(0);
          hand.set_totalMults(0);

          // printing the decks on the terminal, and others (hand & discard counts)
          cout << "-----------------------------------------------------------" << endl;
          print_playingDeck(playDeck);
          print_jokerDeck(jkDeck);
          print_supportDeck(spDeck);

          cout << "Hands count: " << hand.get_handsCount() << " | " << "Discards count: " << hand.get_discardsCount() << "\n\n";

          // both are reset every iteration/round
          int n = 0, m = 0; // n is for the option, m is for the deck
          string idx = ""; // user input for the chosen indexes

          while(n < 1 || n > 2) // input validation for the options
          {
            cout << "Please select one of the following:\n1. Play/use cards\n";
            if (jkDeck.getCurrentCards() > 0 || spDeck.getCurrentCards() > 0 || hand.get_discardsCount() > 0) 
            {
              cout << "2. Discard cards\n"; // available only if there are cards to be discarded
            };
            cout << "Answer: ";
            cin >> n;
            cout << "\n";
          };

          switch(n) {
            case 1: // play/use cards
              while(m < 1 || m > 2) 
              {
                cout << "Please select one of the following:\n1. Play cards\n";
                if (spDeck.getCurrentCards() > 0) 
                {
                  cout << "2. Use support cards\n";
                };
                cout << "Answer: ";
                cin >> m;
                cout << "\n";
              };
      
              switch(m) // play playing cards, or use support cards
              {
                case 1:
                  cout << "Please input the indexes of the cards that you wanna play: ";
                  cin >> idx;
                  indexValidator(idx, playDeck, 1);
                  pickPlayingCards(idx, playDeck); // making the cards chosen = true
                  hand.calculateTotalScore(playDeck, jkDeck, spDeck);
                  break;
                case 2:
                  cout << "Please input the indexes of the support cards that you wanna use: ";
                  cin >> idx;
                  indexValidator(idx, spDeck, 2);
                  pickSupportCards(idx, spDeck);
                  break;
                default:
                  break;
              };
              break;
            case 2: // discard cards
              while(m < 1 || m > 3) 
              {
                cout << "Please select one of the following:\n";
                if (hand.get_discardsCount() > 0) {
                  cout << "1. Discard playing cards\n";
                };
                if (spDeck.getCurrentCards() > 0) {
                  cout << "2. Discard support cards\n";
                };
                if (jkDeck.getCurrentCards() > 0) {
                  cout << "3. Discard joker cards\n";
                };
                cout << "Answer: ";
                cin >> m;
                cout << "\n";
              };
      
              switch(m) 
              {
                case 1:
                  cout << "Please input the indexes of the playing cards that you wanna discard: ";
                  cin >> idx;
                  indexValidator(idx, playDeck, 1);
                  pickPlayingCards(idx, playDeck);
                  hand.discardPlayingCards(playDeck);
                  hand.subtract_discardsCount();
                  break;
                case 2:
                  cout << "Please input the indexes of the support cards that you wanna discard: ";
                  cin >> idx;
                  indexValidator(idx, spDeck, 2);
                  hand.manualDiscardEffectsCards(idx, spDeck);
                  break;
                case 3:
                  cout << "Please input the indexes of the joker cards that you wanna discard: ";
                  cin >> idx;
                  indexValidator(idx, jkDeck, 3);
                  hand.manualDiscardEffectsCards(idx, jkDeck);
                  break;
                default:
                  break;
              };
              break;
            default:
              break;
          };
      
          cout << "Your score: " << hand.get_totalScore() << " | " << "Score needed: " << minimumScore << "\n\n";          
        };

        if (hand.get_handsCount() < 1 && hand.get_totalScore() < minimumScore) 
        {
          cout << "You Lost." << "\n";
          lose_status = true;
        } else {
          cout << "You Win!" << "\n\n";
        };
      };
    };

    void renderAll() 
    {
      
    };

    //SETTERS
    void set_difficulty(int inpt) 
    {
      this->difficulty = inpt;
    };
    
    //GETTERS
    int get_difficulty() {
      return this->difficulty;
    };

    void print_playingDeck(PlayingDeck& playDeck) {
      cout << "[ ";
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << ", ";
      };
      cout << "]\n\n";
    };

    void print_jokerDeck(JokerDeck& jkDeck) 
    {
      if (!jkDeck.getDeck().empty()) 
      {
        for (int i = 0; i < jkDeck.getCurrentCards(); i++) 
        {
          cout << "Joker" << jkDeck.getDeck()[i]->get_rarity() << " bonus Chips: " << jkDeck.getDeck()[i]->get_bonus_chips() << ", bonus Mults: " << jkDeck.getDeck()[i]->get_bonus_mults() << ", lifespan: " << jkDeck.getDeck()[i]->get_lifespan() << " | ";
        };
        cout << "\n\n";
      } else {
        cout << "You don't have any Joker cards!\n\n";
      };
    };

    void print_supportDeck(SupportDeck& spDeck) 
    {
      if (!spDeck.getDeck().empty()) 
      {
        for (int i = 0; i < spDeck.getCurrentCards(); i++) 
        {
          cout << "Support" << spDeck.getDeck()[i]->get_rarity() << " bonus Chips: " << spDeck.getDeck()[i]->get_bonus_chips() << ", bonus Mults: " << spDeck.getDeck()[i]->get_bonus_mults() << " | ";
        };
        cout << "\n\n";
      } else {
        cout << "You don't have any Support cards!\n\n";
      };
    };

    void indexValidator(string& index, Deck& deck, int m) // m is the deck affected
    {
      int currentCards = deck.getCurrentCards();
      bool isValid = false;

      while (!isValid) 
      {
        isValid = true; // assume valid until proven otherwise
        map<char, int> indexMap; // for tracking duplicates

        // check if the user is trying to pick more than 5 cards
        if (m == 1) 
        {
          if (index.length() > 5) 
          {
            cout << "please pick **up to 5** cards for each play/discard: ";
            cin >> index;
            isValid = false;
            continue;
          }
        } else {
          if (index.length() > deck.getCurrentCards()) 
          {
            cout << "please pick **up to "<< deck.getCurrentCards() << "** cards for each play/discard: ";
            cin >> index;
            isValid = false;
            continue;
          }
        };
        

        for (int i = 0; i < index.length(); i++) 
        {
          // check if the index chosen are less than or equal to the number of cards in the deck
          int idx = index[i] - '0';
          if (idx < 0 || idx >= currentCards) 
          {
            cout << "Please pick an index **within the deck's range (0-" << (currentCards - 1) << "): ";
            cin >> index;
            isValid = false;
            break;
          }

          // check if there's a duplicate number
          if (indexMap[index[i]]++ > 0) { 
            cout << "Duplicate index (" << index[i] << "). Pick unique indices: ";
            cin >> index;
            isValid = false;
            break;
          }
        };
      }
    };

    void pickPlayingCards(string& index, PlayingDeck& playDeck) 
    {
      cout << "You chose: ";
      for (int i = 0; i < index.length(); i++) 
      {
        playDeck.getDeck()[index[i] - '0']->chosen_true();
        cout << playDeck.getDeck()[index[i] - '0']->get_suit() << playDeck.getDeck()[index[i] - '0']->get_rank() << ", ";
      };
      cout << "\n\n";
    };

    void pickSupportCards(string& index, SupportDeck& spDeck) 
    {
      for (int i = 0; i < index.length(); i++) 
      {
        spDeck.getDeck()[index[i] - '0']->set_Used();
        cout << "Support" << spDeck.getDeck()[i]->get_rarity() << " will be used next hand played.";
      };
    };

    ~Game() {};
};

#endif //GAME_H