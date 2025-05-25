#ifndef INITDECK_H
#define INITDECK_H

#include "AbstractPlayingDeck.h"

class InitDeck : public AbstractPlayingDeck {
  public:
    InitDeck() 
    {
      this->set_maximumNumCards(52);
    };

    // make the 52 initial playing cards (4 suits, 13 ranks)
    void makeDeck()
    {
      for (int i = 0; i < 4; i++) 
      {
        for (int j = 1; j < 14; j++) 
        {
          switch(i) 
          {
            case 0:
              this->deck.push_back(new PlayingCard(Suit[0], to_string(j + 1)));
              break;
            case 1:
              this->deck.push_back(new PlayingCard(Suit[1], to_string(j + 1)));
              break;
            case 2:
              this->deck.push_back(new PlayingCard(Suit[2], to_string(j + 1)));
              break;
            case 3:
              this->deck.push_back(new PlayingCard(Suit[3], to_string(j + 1)));
              break;
          };
        };
      };
    };

    ~InitDeck() {};
};

#endif //INITDECK_H