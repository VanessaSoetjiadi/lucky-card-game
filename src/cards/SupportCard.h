#ifndef SUPPORTCARD_H
#define SUPPORTCARD_H

#include "EffectCard.h"

class SupportCard : public EffectCard {
  private:
    bool isUsed;
  public:
    SupportCard(): isUsed(false) 
    {
      int rnd = randomizer();
      this->rarity = Rarity[rnd];

      int bonusChips = 0; 
      int bonusMults = 0;

      switch (rnd) 
      {
        case 0: //COMMON
          bonusChips = (rand() % 10) + 1;
          bonusMults = (rand() % 10) + 1;
          break;
        case 1: //RARE
          bonusChips = (rand() % 30) + 1;
          bonusMults = (rand() % 30) + 1;
          break;
        case 2: //SUPER RARE
          bonusChips = (rand() % 50) + 1;
          bonusMults = (rand() % 50) + 1;
          break;
      };

      set_bonus_chips(bonusChips);
      set_bonus_mults(bonusMults);
    };

    //PURE
    void draw() override
    {
      
    };

    int randomizer() override 
    {
      int rnd = rand() % 100;
      if (rnd > 95) return 2;
      else if (rnd > 75) return 1;
      else return 0;
    };

    //GETTERS
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

#endif //SUPPORTCARD_H