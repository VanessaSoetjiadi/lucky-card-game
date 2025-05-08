#ifndef SUPPORTCARD_H
#define SUPPORTCARD_H

#include "EffectCard.h"

class SupportCard : public EffectCard {
  private:
    bool isUsed;
  public:
    SupportCard(int bonus_chips, int bonus_mults): isUsed(false) 
    {
      set_bonus_chips(bonus_chips);
      set_bonus_mults(bonus_mults);
    };

    //IF CARD IS USED
    void supportIsUsed() 
    {
      this->isUsed = true;
    };

    //MAKE GETTERS

    ~SupportCard() {};
};

#endif