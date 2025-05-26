#ifndef EFFECTCARD_H
#define EFFECTCARD_H

#include "Card.h"

// rarity const for all the effectsCards, each having their own bonus effects
const string Rarity[] { "Common", "Rare", "Super Rare" };

class EffectCard : public Card {
  protected:
    string rarity;
    int bonus_mults; // multipliers, multiplies the chips to get total score
    int bonus_chips;
    sf::Texture texture;
  public:
    // pure virtual functions override
    sf::Texture& draw() override
    {     
      return this->texture;
    };
    
    sf::Text& get_description(int x, int y, sf::Font font) {
      sf::Text text;
      text.setFont(font);
      text.setColor(sf::Color::White);
      text.setCharacterSize(10);
      text.setPosition({x,y});
      std::string description = "abc";
      text.setString(description);
      return text;
    }

    //SETTERS
    void set_bonus_mults(int n) 
    {
      this->bonus_mults = n; // set bonus multipliers for the effect card
    };

    void set_bonus_chips(int n) 
    {
      this->bonus_chips = n; // set bonus chips for the effect card
    };

    //GETTERS
    string get_rarity() 
    {
      return this->rarity; // return the rarity of the effect card
    };
    
    int get_bonus_chips() 
    {
      return this->bonus_chips; // return the bonus chips of the effect card
    };

    int get_bonus_mults() 
    {
      return this->bonus_mults; // return the bonus mults of the effect card
    };

    ~EffectCard() {};
};

#endif //EFFECTCARD_H