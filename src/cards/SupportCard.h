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

    //MAKE GETTERS
    bool get_isUsed() const 
    {
      return this->isUsed; // Return if card is used/not
    };
    
    void set_Used()
    {
      this->isUsed = true; // Set card as used
    };

    ~SupportCard() {};
};

#endif