#ifndef EFFECTCARD_H
#define EFFECTCARD_H

#include "Card.h"

const string Rarity[] { "Common", "Rare", "Special" };

class EffectCard : public Card {
  private:
    string rarity;
    int bonus_mults;
    int bonus_chips;
  public:
    EffectCard() {
      int random = this->randomizer();
      this->rarity = Rarity[random];
    };

    ////PURE INHERITED
    virtual void draw() {};
    
    virtual int randomizer() {
      int max_percentage = 99;
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<> dis(0, max_percentage);

      if (dis(gen) < 70) return 0;
      else if (dis(gen) < 85) return 1;
      else return 2;
    };

    //SETTERS
    void set_bonus_mults(int n) 
    {
      this->bonus_mults = n;
    };

    void set_bonus_chips(int n) 
    {
      this->bonus_chips = n;
    };

    //GETTERS
    string get_rarity() 
    {
      return this->rarity;
    };

    ~EffectCard() {};
};

#endif