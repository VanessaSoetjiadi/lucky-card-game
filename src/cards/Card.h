#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

//ADDITIONAL LIBRARY
#include <random>

using namespace std;

class Card {
  public:
    virtual void draw() = 0;
    virtual int randomizer() = 0;
    virtual ~Card() = default;
};

#endif