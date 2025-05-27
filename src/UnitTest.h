#ifndef UNITTEST_H
#define UNITTEST_H

#include "decks/InitDeck.h"
#include "decks/PlayingDeck.h"
#include "decks/JokerDeck.h"
#include "decks/SupportDeck.h"

#include "Hand.h"

class UnitTest {
  public:
    void testAll() 
    {
      testInitDeck();
      testPlayingDeck();
      testEffectsDeck();
      testCheckHandType();
    };

    // playing cards relevance
    void testInitDeck() // testing the initial deck initializations
    {
      InitDeck initialDeck;
      initialDeck.makeDeck();

      if (initialDeck.getCurrentCards() != 52) // test if makedeck initializes 52 cards
      {
        cout << "Didn't make 52 cards" << endl;
      };

      // randomly picks a card (Club2) and test the return functions
      if (initialDeck.getDeck()[0]->get_suit().compare("Club")) 
      {
        cout << "Incorrect suit" << endl;
      };

      if (initialDeck.getDeck()[0]->get_chips() != 2) 
      {
        cout << "Incorrect rank" << endl;
      };
    };

    void testPlayingDeck() // testing the playing deck initializations & functionalities
    {
      InitDeck initialDeck;
      initialDeck.makeDeck();
      
      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      if (playDeck.getCurrentCards() != 8) // test if playingDeck correctly takes 8 cards from InitDeck
      {
        cout << "Didn't take 8 cards" << endl;
      };

      Hand hand;

      // test give and restore, Hand takes 3 cards from playDeck, playDeck replenishes these cards
      playDeck.getDeck()[2]->chosen_true();
      playDeck.getDeck()[5]->chosen_true();
      playDeck.getDeck()[7]->chosen_true();

      hand.discardPlayingCards(playDeck);
      if (playDeck.getCurrentCards() != 5) 
      {
        cout << "Didn't take 3 cards" << endl;
      };

      playDeck.makeDeck(initialDeck);
      if (playDeck.getCurrentCards() != 8) 
      {
        cout << "Didn't restore the 3 cards" << endl;
      };
    };

    void testSortingRank()
    {
      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << endl;
      };

      playDeck.sortInRanks(); // testing sorting by ranks

      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << endl;
      };
    };

    void testSortingSuit() 
    {
      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      for (int i = 2; i < 4; i++) 
      {
        playDeck.getDeck()[i]->set_suit(Suit[3]);
      };
      
      for (int i = 6; i < 8; i++) 
      {
        playDeck.getDeck()[i]->set_suit(Suit[0]);
      };

      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << endl;
      };

      playDeck.sortInSuits(); // testing sorting by suits

      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << endl;
      };
    };

    // effects cards relevance
    void testEffectsDeck() 
    {
      JokerDeck jkDeck;
      jkDeck.makeDeck();
      if (jkDeck.getCurrentCards() != 2) // check if jokerDeck initializes with 2 cards
      {
        cout << "Didn't initialize 2 cards" << endl;
      };

      jkDeck.addEffectCard(); // check if another joker card is added
      if (jkDeck.getCurrentCards() != 3) 
      {
        cout << "Third card isn't added" << endl;
      };
      
      SupportDeck spDeck;
      spDeck.makeDeck();
      if (spDeck.getCurrentCards() != 1) // check if supportDeck initializes with 1 card
      {
        cout << "Didn't initialize 1 card" << endl;
      };

      spDeck.addEffectCard(); // check if another support card is added
      if (spDeck.getCurrentCards() != 2) 
      {
        cout << "Second card isn't added" << endl;
      };
    };

    void testCalculateEffectsCards() 
    {
      Hand hand;
      JokerDeck jkDeck;
      SupportDeck spDeck;

      spDeck.getDeck()[0]->set_Used();

      for (int i = 0; i < 4; i++) // checks if joker card runs out of lifespan, it'll be discarded
      {
        hand.calculateEffectsCards(jkDeck, spDeck);
      };

      if (spDeck.getCurrentCards() != 0) 
      {
        cout << "Support card isn't used" << endl;
      };

      if (jkDeck.getCurrentCards() == 2) 
      {
        cout << "Joker cards weren't used" << endl;
      };
    };

    // hand class relevance
    void testAddingHandsAndDiscardCount() 
    {
      Hand hand;
      InitDeck initialDeck;
      initialDeck.makeDeck();
      
      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      // setting the colors to each black and blue
      playDeck.getDeck()[0]->chosen_true();
      playDeck.getDeck()[1]->chosen_true();
      playDeck.getDeck()[0]->set_color(CardColor[1]);
      playDeck.getDeck()[1]->set_color(CardColor[2]);
      
      hand.add_handsCount (playDeck); // checking whether code adds another hand count if there's a black card
      hand.add_discardsCount (playDeck); // checking whether code adds another hand count if there's a blue card

      if (hand.get_handsCount() != 5) // initial hand and discard are 4, thus must be 5 for each
      {
        cout << "Hand count isn't added" << endl;
      };

      if (hand.get_discardsCount() != 5) 
      {
        cout << "Discard count isn't added" << endl;
      };
    };

    void testCheckHandType() // checking for the important handtypes
    {
      testRoyalFlush(); // checking for royal flush
      testFlush(); // checking for flush
      testFourOfaKind(); // checking for four of a kind
      testFullHouse(); // checking for full house
      testTwoPair(); // checking for two pair
      testStraight(); // checking straight flush
    };

    // list of hands
    void testRoyalFlush() 
    {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);
      
      int n = 14;
      for (int i = 0; i < 5; i++) 
      {
        playDeck.getDeck()[i]->set_rank(n);
        playDeck.getDeck()[i]->set_chips(n);
        playDeck.getDeck()[i]->set_suit(Suit[1]);
        playDeck.getDeck()[i]->chosen_true();
        n--;
      };

      if (hand.checkHandType(playDeck) != 20) 
      {
        cout << "Royal Flush isn't identified" << endl;
      };
    };

    void testFlush() 
    {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      for (int i = 0; i < 5; i++)
      {
        playDeck.getDeck()[i]->set_suit(Suit[3]);
        playDeck.getDeck()[i]->chosen_true();
      };

      if (hand.checkHandType(playDeck) != 24) 
      {
        cout << "Flush isn't identified" << endl;
      };
    };

    void testFourOfaKind() 
    {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      for (int i = 0; i < 4; i++) 
      {
        playDeck.getDeck()[i]->set_rank(11);
        playDeck.getDeck()[i]->chosen_true();
      };

      if (hand.checkHandType(playDeck) != 22) 
      {
        cout << "Four of a Kind isn't identified" << endl;
      };
    };

    void testFullHouse() 
    {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      for (int i = 0; i < 3; i++) 
      {
        playDeck.getDeck()[i]->set_rank(11);
        playDeck.getDeck()[i]->chosen_true();
      };
      for (int i = 3; i < 5; i++) 
      {
        playDeck.getDeck()[i]->set_rank(10);
        playDeck.getDeck()[i]->chosen_true();
      };

      if (hand.checkHandType(playDeck) != 23) 
      {
        cout << "Full House isn't identified" << endl;
      };
    };

    void testTwoPair() 
    {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      for (int i = 0; i < 2; i++) 
      {
        playDeck.getDeck()[i]->set_rank(2);
        playDeck.getDeck()[i]->chosen_true();
      };
      for (int i = 2; i < 4; i++) 
      {
        playDeck.getDeck()[i]->set_rank(4);
        playDeck.getDeck()[i]->chosen_true();
      };

      if (hand.checkHandType(playDeck) != 27) 
      {
        cout << "Two Pair isn't identified" << endl;
      };
    };

    void testStraight() 
    {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      int n = 12;
      for (int i = 0; i < 5; i++) 
      {
        playDeck.getDeck()[i]->set_rank(n);
        playDeck.getDeck()[i]->set_chips(n);
        playDeck.getDeck()[i]->set_suit(Suit[1]);
        playDeck.getDeck()[i]->chosen_true();
        n--;
      };

      if (hand.checkHandType(playDeck) != 21) 
      {
        cout << "Straight Flush isn't identified" << endl;
      };
    };
};      

#endif //UNITTEST_H