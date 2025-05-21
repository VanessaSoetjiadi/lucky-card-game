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
      //testInitDeck();
      //testPlayingDeck();
      //testEffectsDeck();
      //testCheckHandType();
      testSortingSuit();
    };

    void testInitDeck() 
    {
      InitDeck initialDeck;
      initialDeck.makeDeck();

      //TEST IF MAKEDECK PRODUCES 52 CARDS
      if (initialDeck.getCurrentCards() != 52) 
      {
        cout << "Didn't make 52 cards" << endl;
      };

      //RANDOMLY PICK VALUE AND DETERMINE IF THEY'RE RIGHT (HEART J)
      if (initialDeck.getDeck()[22]->get_suit().compare("Heart")) 
      {
        cout << "Incorrect suit" << endl;
      };

      if (initialDeck.getDeck()[22]->get_chips() != 11) 
      {
        cout << "Incorrect rank" << endl;
      };
    };

    void testPlayingDeck() 
    {
      InitDeck initialDeck;
      initialDeck.makeDeck();
      
      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      //TEST IF PLAYINGDECK CORRECTLY TAKES 8 CARDS FROM INITDECK
      if (playDeck.getCurrentCards() != 8) 
      {
        cout << "Didn't take 8 cards" << endl;
      };

      Hand hand;

      //CHOOSE 3 CARDS AT RANDOM, GIVE IT TO THE HAND CLASS, GET 3 CARDS RESTORED
      playDeck.getDeck()[2]->chosen_true();
      playDeck.getDeck()[5]->chosen_true();
      playDeck.getDeck()[7]->chosen_true();

      hand.checkHandType(playDeck);
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

    void testEffectsDeck() 
    {
      //Check if JokerDeck initializes with 2 cards
      JokerDeck jkDeck;
      if (jkDeck.getCurrentCards() != 2) 
      {
        cout << "Didn't initialize 2 cards" << endl;
      };

      //Check if another joker card is added
      jkDeck.addEffectCard();
      if (jkDeck.getCurrentCards() != 3) 
      {
        cout << "Third card isn't added" << endl;
      };
      
      SupportDeck spDeck;
      if (spDeck.getCurrentCards() != 1) 
      {
        cout << "Didn't initialize 1 card" << endl;
      };

      //Check if another joker card is added
      spDeck.addEffectCard();
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

      for (int i = 0; i < 4; i++) 
      {
        //iterates 4 times -> maximum lifespan of a joker card to see if it'll be discarded
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

    void testAddingHandsAndDiscardCount() 
    {
      //Testing the add_handsCount and add_discardCount from the colored cards in PlayingDeck
      Hand hand;
      InitDeck initialDeck;
      initialDeck.makeDeck();
      
      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      //Setting the colors to each black and blue
      playDeck.getDeck()[0]->chosen_true();
      playDeck.getDeck()[1]->chosen_true();
      playDeck.getDeck()[0]->set_color(CardColor[1]);
      playDeck.getDeck()[1]->set_color(CardColor[2]);
      
      hand.add_handsCount (playDeck);
      hand.add_discardsCount (playDeck);

      //Initial hand and discard count is fixed to 4, so must return 5
      if (hand.get_handsCount() != 5) 
      {
        cout << "Hand count isn't added" << endl;
      };

      if (hand.get_discardsCount() != 5) 
      {
        cout << "Discard count isn't added" << endl;
      };
    };

    void testCheckHandType() 
    {
      Hand hand;

      InitDeck initialDeck;
      initialDeck.makeDeck();

      PlayingDeck playDeck;
      playDeck.makeDeck(initialDeck);

      //Check for each of the HandType
      //Checking for ROYAL FLUSH
      testRoyalFlush(hand, playDeck);

      //Checking for FLUSH
      //testFlush(hand, playDeck);

      //Checking for Four of a Kind
      //testFourOfaKind(hand, playDeck);

      //Checking for FOUR OF A KIND
      //testFullHouse(hand, playDeck);

      //Checking for TWO PAIR
      //testTwoPair(hand, playDeck);

      //Checking for STRAIGHT FLUSH
      // int n = 13;
      // for (int i = 0; i < 5; i++) 
      // {
      //   //playDeck.getDeck()[i]->set_rank(i);
      //   playDeck.getDeck()[i]->chosen_true();
      //   cout << playDeck.getDeck()[i]->get_rank() << endl;
      // };

      // if (hand.checkHandType(playDeck).compare(Hands[2]) != 0) 
      // {
      //   cout << "Not Straight Flush" << endl;
      // };
    };

    void testFlush(Hand hand, PlayingDeck& playDeck) 
    {
      //Makes 5 cards has the same suit
      for (int i = 0; i < 5; i++) 
      {
        playDeck.getDeck()[i]->set_suit(Suit[3]);
        playDeck.getDeck()[i]->chosen_true();
      };
      
      if (hand.checkHandType(playDeck) == 25) 
      {
        cout << "Flush" << endl;
      };
    };

    void testFourOfaKind(Hand hand, PlayingDeck& playDeck) 
    {
      for (int i = 0; i < 4; i++) 
      {
        playDeck.getDeck()[i]->set_rank(11);
        playDeck.getDeck()[i]->chosen_true();
      };

      if (hand.checkHandType(playDeck) == 23) 
      {
        cout << "Four of a Kind" << endl;
      };
    };

    void testFullHouse(Hand hand, PlayingDeck& playDeck) 
    {
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

      if (hand.checkHandType(playDeck) == 24) 
      {
        cout << "Full House" << endl;
      };
    };

    void testTwoPair(Hand hand, PlayingDeck& playDeck) 
    {
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

      if (hand.checkHandType(playDeck) == 28) 
      {
        cout << "Two Pair" << endl;
      };
    };

    void testRoyalFlush(Hand hand, PlayingDeck& playDeck) 
    {
      int n = 14;
      for (int i = 0; i < 5; i++) 
      {
        playDeck.getDeck()[i]->set_rank(n);
        playDeck.getDeck()[i]->set_chips(n);
        playDeck.getDeck()[i]->set_suit(Suit[1]);
        playDeck.getDeck()[i]->chosen_true();
        n--;

        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_chips() << endl;
      };

      if (hand.checkHandType(playDeck) == 21) 
      {
        cout << "Royal Flush" << endl;
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

      playDeck.sortInRanks();

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

      playDeck.sortInSuits();

      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << endl;
      };
    };
};

#endif //UNITTEST_H