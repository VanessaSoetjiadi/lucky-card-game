#ifndef JOKERCARD_H
#define JOKERCARD_H

#include "EffectCard.h"

class JokerCard : public EffectCard {
  private:
    int lifeSpan;
  public:
    JokerCard(int lifespan): lifeSpan(lifespan) 
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

    //PURE VIRTUAL FUNCTIONS OVERRIDE
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
    int get_lifespan()
    {
      return this->lifeSpan; // Return the lifespan of the Joker card
    };

    void subtract_lifespan() //Subtracts the lifespan
    {
      this->lifeSpan--;
    };

    ~JokerCard() {};
};

#endif //JOKERCARD_H