#ifndef JOKERCARD_H
#define JOKERCARD_H

#include "EffectCard.h"

class JokerCard : public EffectCard {
  private:
    int lifeSpan;
  public:
    JokerCard(int lifespan, int bonus_chips, int bonus_mults): lifeSpan(lifespan) 
    {
      set_bonus_chips(bonus_chips);
      set_bonus_mults(bonus_mults);
    };

    //MAKE GETTERS
    int get_lifespan()
    {
      return this->lifeSpan; // Return the lifespan of the Joker card
    };

    void subtract_lifespan(int n) 
    {
      this->lifeSpan -= n; // Subtract lifespan by n
      if (this->lifeSpan < 0) {
        this->lifeSpan = 0; // Ensure lifespan does not go below 0
      }
    };

    ~JokerCard() {};
};

#endif