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
        case 0: // common
          bonusChips = (rand() % 4) + 1;
          bonusMults = (rand() % 4) + 1;
          if (!this->texture.loadFromFile("assets/cards/joker_black.png")) {
            std::cerr << "Failed to load joker texture!" << std::endl;
          }
          break;
        case 1: // rare
          bonusChips = (rand() % 8) + 1;
          bonusMults = (rand() % 8) + 1;
          if (!this->texture.loadFromFile("assets/cards/joker_red.png")) {
            std::cerr << "Failed to load joker texture!" << std::endl;
          }
          break;
        case 2: // super rare
          bonusChips = (rand() % 15) + 1;
          bonusMults = (rand() % 15) + 1;
          if (!this->texture.loadFromFile("assets/cards/spades_A.png")) {
            std::cerr << "Failed to load joker texture!" << std::endl;
          }
          break;
      };

      set_bonus_chips(bonusChips);
      set_bonus_mults(bonusMults);
    };

    void subtract_lifespan() // decrease the lifespan by 1
    {
      this->lifeSpan--;
    };

    int randomizer() override // randomizer for card rarity
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

    ~JokerCard() {};
};

#endif //JOKERCARD_H