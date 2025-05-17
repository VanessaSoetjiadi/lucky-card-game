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
      return this->lifeSpan;
    };

    void subtract_lifespan(int n) 
    {
      this->lifeSpan -= n;
    };

    ~JokerCard() {};
};

#endif