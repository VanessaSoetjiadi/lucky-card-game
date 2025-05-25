#ifndef EFFECTCARD_H
#define EFFECTCARD_H

#include "Card.h"

const string Rarity[] { "Common", "Rare", "Super Rare" };

class EffectCard : public Card {
  protected:
    string rarity;
    int bonus_mults;
    int bonus_chips;
  public:
    //SETTERS
    void set_bonus_mults(int n) 
    {
      this->bonus_mults = n; // Set bonus multipliers for the effect card
    };

    void set_bonus_chips(int n) 
    {
      this->bonus_chips = n; // Set bonus chips for the effect card
    };

    //GETTERS
    string get_rarity() 
    {
      return this->rarity; // Return the rarity of the effect card
    };
    
    int get_bonus_chips() 
    {
      return this->bonus_chips;
    };

    int get_bonus_mults() 
    {
      return this->bonus_mults;
    };

    ~EffectCard() {};
};

#endif //EFFECTCARD_H