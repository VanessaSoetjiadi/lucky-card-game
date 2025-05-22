#include "Game.h"
#include "UnitTest.h"

#include <algorithm>

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
  bool indexWithinBounds = false;
  while(index.length() > effectsDeck.getCurrentCards()) 
  {
    //Out of bound as in user is discarding more cards than jkDeck has.
    cout << "\nIndex out of bound. Please select the VALID card indexes that you want to discard: ";
    cin >> index;
  };

  while(indexWithinBounds == false) 
  {
    for(int i = 0; i < index.length(); i++) 
    {
      if (index[i] - '0'> effectsDeck.getCurrentCards() - 1) 
      {
        indexWithinBounds = false;
        //Out of bound as in user is accessing an index that is not on jkDeck's vector. For instance, user wanna access the index 3, that doesn't exist in jkDeck since jkDeck only has 2 cards (In this situation). 
        cout << "Please input an index WITHIN bounds: ";
        cin >> index;
        break;
      } else {
        indexWithinBounds = true;
      };
    };
  };

  if (index.length() > 1) 
  {
    std::sort(index.begin(), index.end(), std::greater<char>());
    for (int i = 0; i < index.length(); i++) 
    {
      effectsDeck.discardCard(index[i] - '0');
    };
  } else {
    effectsDeck.discardCard(index[0] - '0');
  };
};

void chooseCard(string& index, PlayingDeck& playDeck) 
{
  bool indexWithinBounds = false;
  // maximum number of cards to be picked is 5
  while(index.length() > 5) 
  {
    // out of bound as in user is discarding more cards than jkDeck has.
    cout << "Please pick less than or equal to 5 cards for each play/discard: ";
    cin >> index;
  };

  while(indexWithinBounds == false) 
  {
    for(int i = 0; i < index.length(); i++) 
    {
      if (index[i] - '0'> playDeck.getCurrentCards() - 1) 
      {
        indexWithinBounds = false;
        // out of bound as in user is accessing an index that is not on jkDeck's vector. For instance, user wanna access the index 3, that doesn't exist in jkDeck since jkDeck only has 2 cards (In this situation). 
        cout << "Please pick an index within the array: ";
        cin >> index;
        break;
      } else {
        indexWithinBounds = true;
      };
    };
  };

  for (int i = 0; i < index.length(); i++) 
  {
    playDeck.getDeck()[index[i] - '0']->chosen_true();
  };
};

int main()
{
  std::srand(std::time(nullptr));
  //Game game;
  //UnitTest unitTest;

  Hand hand;

  InitDeck initialDeck;
  initialDeck.makeDeck();

  PlayingDeck playDeck;
  playDeck.makeDeck(initialDeck);

  JokerDeck jkDeck;
  SupportDeck spDeck;

  printPlayingDeck(playDeck);
  printJokerDeck(jkDeck);
  printSupportDeck(spDeck);
  
  int n = 1, m; // n is yes or no, m is for deck options
  string idx; // index of the chosen cards
  bool idxWithinBounds = false; // bool for if index is out of bound

  // discarding a card in joker/support deck. This can be done multiple times, until the deck of effectsCards are empty.
  cout << "Would you like to discard some Joker/Support cards?: 1 Yes, 2 No\n" ;
  cout << "Answer: ";
  cin >> n;
  cout << "\n";

  while(n == 1) 
  {
    if (jkDeck.getDeck().empty() && spDeck.getDeck().empty()) 
    {
      cout << "You don't have any joker nor support cards to discard.\n\n";
      n = 2;
    } else {
      cout << "Please select the deck that you want to discard from: 1 Joker, 2 Support\n";
      cout << "Answer: ";
      cin >> m;
      cout << "\n";

      if (jkDeck.getDeck().empty() && m == 1) {
        cout << "You don't have any Joker cards to discard.\n\n";
        continue; // immediately iterates to the next loop
      } else if (spDeck.getDeck().empty() && m == 2) {
        cout << "You don't have any Support cards to discard.\n\n";
        continue;
      };

      cout << "Please select the card indexes that you want to discard: "; //You can do multiple
      cin >> idx;

      switch(m) 
      {
        case 1:
          removeCard(idx, jkDeck);
          break;
        case 2:
          removeCard(idx, spDeck);
          break;
        default:
          break;
      };

      cout << "\n";
      cout << "Card discarded, your current deck is now: " << endl;

      printPlayingDeck(playDeck);
      printJokerDeck(jkDeck);
      printSupportDeck(spDeck);

      if (jkDeck.getDeck().empty() && spDeck.getDeck().empty()) {
        n = 2;
      } else {
        cout << "Do you still want to discard from your Joker/Support deck?: 1 Yes, 2 No" << endl;
        cout << "Answer: ";
        cin >> n;
        cout << "\n";
      };
    };
  };
  
  // asking the player to play/discard cards
  cout << "Do you want to play/discard your playing cards?: 1 Play, 2 Discard" << endl;
  cout << "Answer: ";
  cin >> n;

  switch(n) 
  {
    // both cases, maximum 5 cards can be picked
    case 1:
      cout << "Please select the card indexes that you want to play: ";
      cin >> idx;

      chooseCard(idx, playDeck);

      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        if (playDeck.getDeck()[i]->get_chosen()) 
        {
          cout << playDeck.getDeck()[i]->get_suit() << playDeck.getDeck()[i]->get_rank() << endl;
        };
      };

      hand.calculateTotalScore(playDeck, jkDeck, spDeck);
      hand.subtract_handsCount();

      cout << hand.get_totalScore() << endl;
      break;
    case 2:
      if (!(hand.get_discardsCount() < 1)) 
      {
        cout << "Please select the card indexes that you want to discard: ";
        cin >> idx;
  
        // choose card here is used to check whether or not the inputs are valid
        chooseCard(idx, playDeck);
        hand.discardPlayingCards(idx, playDeck);
        hand.discardEffectsCards(jkDeck, spDeck);

        hand.subtract_discardsCount();
      } else {
        cout << "You don't have anymore discards!" << endl;
        break;
      };
      break;
    default:
      break;
  };

  return 0;
}