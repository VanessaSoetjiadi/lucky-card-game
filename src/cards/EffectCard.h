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
    void choose() // toggle chosen value
    {
      chosen = !chosen;
    };
    
    void chosen_true() // positive-only choose
    {
      this->chosen = true;
    };

    // pure virtual functions override
    sf::Texture& draw() override
    {     
      return this->texture;
    };
    
    virtual std::string get_text_description() {
      std::string desc;
      desc = this->rarity + "\n";
      desc += std::to_string(this->bonus_chips) + " Chips\n";
      desc += std::to_string(this->bonus_mults) + " Mults\n";
      return desc;
    }

    sf::Text get_description(float x, float y) {
      sf::Text text;
      text.setCharacterSize(10);
      text.setPosition({x,y});
      text.setFillColor(sf::Color::White);
      text.setString(this->get_text_description());
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

    bool get_chosen() 
    {
      return this->chosen;
    };

    ~EffectCard() {};
};

#endif //EFFECTCARD_H