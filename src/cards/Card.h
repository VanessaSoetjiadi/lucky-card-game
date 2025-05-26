#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Card {
  protected:
  bool chosen; // if user picked the card or not
  public:
    virtual sf::Texture& draw() = 0;
    virtual int randomizer() = 0;
    virtual ~Card() = default;
};

#endif //CARD_H