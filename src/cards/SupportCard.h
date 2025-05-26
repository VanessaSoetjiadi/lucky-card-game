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
      this->chosen = false;

      int bonusChips = 0; 
      int bonusMults = 0;

      texture.loadFromFile("assets/cards/spades_A.png");

      switch (rnd) 
      {
        case 0: // common
          bonusChips = (rand() % 4) + 1;
          bonusMults = (rand() % 4) + 1;
          break;
        case 1: // rare
          bonusChips = (rand() % 8) + 1;
          bonusMults = (rand() % 8) + 1;
          break;
        case 2: // super rare
          bonusChips = (rand() % 15) + 1;
          bonusMults = (rand() % 15) + 1;
          break;
      };

      set_bonus_chips(bonusChips);
      set_bonus_mults(bonusMults);
    };

    int randomizer() override 
    {
      int rnd = rand() % 100;
      if (rnd > 95) return 2;
      else if (rnd > 75) return 1;
      else return 0;
    };

    //GETTERS
    bool get_isUsed()
    {
      return this->isUsed; // return if user picked/use the card or not
    };
    
    void set_Used()
    {
      this->isUsed = true; // user picked to use the card
    };

    ~SupportCard() {};
};

#endif //SUPPORTCARD_H