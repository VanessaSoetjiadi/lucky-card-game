#include "Game.h"
#include "UnitTest.h"

#include <algorithm>
#include <map>

void printPlayingDeck(PlayingDeck& playDeck) 
{
  cout << "[ ";
  for (int i = 0; i < playDeck.getCurrentCards(); i++) 
  {
    cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << ", ";
  };
  cout << "]\n\n";
};

void printJokerDeck(JokerDeck& jkDeck) 
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

void printSupportDeck(SupportDeck& spDeck)
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

void removeCard(string& index, AbstractEffectsDeck& effectsDeck) 
{
  const int currentCards = effectsDeck.getCurrentCards();
  bool isValid = false;

  while (!isValid) 
  {
    isValid = true; // assume valid until proven otherwise

    // check if the user is trying to discard more cards than available
    if (index.length() > currentCards) 
    {
      cout << "Inputted more index than what the deck has, please input less: ";
      cin >> index;
      isValid = false;
      continue; // restart validation with the new input
    }

    // check each index for validity
    for (char c : index) 
    {
      const int idx = c - '0';
      if (idx < 0 || idx >= currentCards) 
      {
        cout << "Please input index below " << currentCards - 1 << ": ";
        cin >> index;
        isValid = false;
        break;
      }
    }
  }

  // remove cards from highest index to avoid shifting issues
  if (!index.empty()) 
  {
    std::sort(index.begin(), index.end(), std::greater<char>());
    for (char c : index) 
    {
      effectsDeck.discardCard(c - '0');
    }
  }
}

void chooseEffectCard(string& index, AbstractEffectsDeck& effectsDeck) 
{
  const int currentCards = effectsDeck.getCurrentCards();
  bool isValid = false;

  while (!isValid) 
  {
    isValid = true; // assume valid until proven otherwise
    map<char, int> indexMap; // for tracking duplicates

    // check if the user is trying to pick more than 5 cards
    if (index.length() > 5) 
    {
      cout << "please pick **up to 5** cards for each play/discard: ";
      cin >> index;
      isValid = false;
      continue;
    }

    // check each index for validity (must be within deck bounds); basically below 7 since that's the maximum index playingDeck can have.
    for (int i = 0; i < index.length(); i++) 
    {
      int idx = index[i] - '0';
      if (idx < 0 || idx >= currentCards) 
      {
        cout << "Please pick an index **within the deck's range (0-" << (currentCards - 1) << "): ";
        cin >> index;
        isValid = false;
        break;
      }

      if (indexMap[index[i]]++ > 0) { // if count exceeds 0, that means there's a duplicate number
        cout << "Duplicate index (" << index[i] << "). Pick unique indices: ";
        cin >> index;
        isValid = false;
        break;
      }
    };
  }
}

void chooseCard(string& index, PlayingDeck& playDeck) 
{
  const int currentCards = playDeck.getCurrentCards();
  bool isValid = false;

  while (!isValid) 
  {
    isValid = true; // assume valid until proven otherwise
    map<char, int> indexMap; // for tracking duplicates

    // check if the user is trying to pick more than 5 cards
    if (index.length() > 5) 
    {
      cout << "please pick **up to 5** cards for each play/discard: ";
      cin >> index;
      isValid = false;
      continue;
    }

    // check each index for validity (must be within deck bounds); basically below 7 since that's the maximum index playingDeck can have.
    for (int i = 0; i < index.length(); i++) 
    {
      int idx = index[i] - '0';
      if (idx < 0 || idx >= currentCards) 
      {
        cout << "Please pick an index **within the deck's range (0-" << (currentCards - 1) << "): ";
        cin >> index;
        isValid = false;
        break;
      }

      if (indexMap[index[i]]++ > 0) { // if count exceeds 0, that means there's a duplicate number
        cout << "Duplicate index (" << index[i] << "). Pick unique indices: ";
        cin >> index;
        isValid = false;
        break;
      }
    };
  }

  // mark chosen cards (no sorting needed since order doesn't matter for selection)
  cout << "You chose: ";
  for (int i = 0; i < index.length(); i++) 
  {
    playDeck.getDeck()[index[i] - '0']->chosen_true();
    cout << playDeck.getDeck()[index[i] - '0']->get_suit() << playDeck.getDeck()[index[i] - '0']->get_rank() << ", ";
  };
  cout << "\n\n";
}

int main()
{
  //Game game;
  //UnitTest unitTest;

  std::srand(std::time(nullptr));
  
  Hand hand;

  InitDeck initialDeck;
  initialDeck.makeDeck();

  PlayingDeck playDeck;

  JokerDeck jkDeck;
  SupportDeck spDeck;

  int minimumScore = 1000;

  // asks the user what they wanna do
  while (hand.get_handsCount() > 0 && hand.get_totalScore() < minimumScore) 
  {
    playDeck.makeDeck(initialDeck);
    cout << "Your current deck: " << endl;
    printPlayingDeck(playDeck);
    printJokerDeck(jkDeck);
    printSupportDeck(spDeck);

    cout << "Hands count: " << hand.get_handsCount() << " | " << "Discards count: " << hand.get_discardsCount() << "\n\n";
    
    int n = 0, m = 0; // n is yes or no, m is for deck options
    string idx; // index of the chosen cards

    while(n < 1 || n > 2) 
    {
      cout << "please select one of the following:\n1. play/use cards\n";
      if (jkDeck.getCurrentCards() > 0 || spDeck.getCurrentCards() > 0 || hand.get_discardsCount() > 0) 
      {
        cout << "2. discard cards\n";
      };
      cout << "Answer: ";
      cin >> n;
      cout << "\n";
    };

    switch(n) {
      case 1: // play/use cards
        while(m < 1 || m > 2) 
        {
          cout << "Please select one of the following:\n1. play cards\n";
          if (spDeck.getCurrentCards() > 0) 
          {
            cout << "2. use support cards\n";
          };
          cout << "Answer: ";
          cin >> m;
          cout << "\n";
        };

        switch(m) 
        {
          case 1:
            cout << "please input the indexes of the cards that you wanna play: ";
            cin >> idx;
            chooseCard(idx, playDeck);
            hand.calculateTotalScore(playDeck, jkDeck, spDeck);
            break;
          case 2:
            cout << "please input the indexes of the support cards that you wanna use: ";
            cin >> idx;
            chooseEffectCard(idx, spDeck);
            for (int i = 0; i < idx.length(); i++) 
            {
              spDeck.getDeck()[idx[i] - '0']->set_Used();
            };
            break;
          default:
            break;
        };
        break;
      case 2: // discard cards
        while(m < 1 || m > 3) 
        {
          cout << "please select one of the following:\n";
          if (hand.get_discardsCount() > 0) {
            cout << "1. discard playing cards\n";
          };
          if (spDeck.getCurrentCards() > 0) {
            cout << "2. discard support cards\n";
          };
          if (jkDeck.getCurrentCards() > 0) {
            cout << "3. discard joker cards\n";
          };
          cout << "Answer: ";
          cin >> m;
          cout << "\n";
        };

        switch(m) 
        {
          case 1:
            cout << "please input the indexes of the playing cards that you wanna discard: ";
            cin >> idx;
            chooseCard(idx, playDeck);
            hand.discardPlayingCards(playDeck);
            hand.subtract_discardsCount();
            break;
          case 2:
            cout << "please input the indexes of the support cards that you wanna discard: ";
            cin >> idx;
            chooseEffectCard(idx, spDeck); // only checking whether or not input is valid
            hand.discardEffectsCards(idx, spDeck);
            break;
          case 3:
            cout << "please input the indexes of the joker cards that you wanna discard: ";
            cin >> idx;
            chooseEffectCard(idx, jkDeck);
            hand.discardEffectsCards(idx, jkDeck);
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
  return 0;
}