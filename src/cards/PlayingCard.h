#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

#include "Card.h"

const string CardColor[] { "Red", "Black", "Blue" };

const string Suit[] { "Heart", "Club", "Spade", "Diamond" };

class PlayingCard : public Card {
  private:
    int chips;
    string color;
    string suit;
    string rank;
  public:
    PlayingCard(string suit, string rank): suit(suit), rank(rank) 
    {
      int random = this->randomizer();
      this->color = CardColor[random];

      //SETTING THE CHIPS & RANK
      set_chips();
      set_rank(rank);
    };

    //PURE INHERITED
    virtual void draw() 
    {

    };
    
    //RANDOMIZING THE COLOR
    virtual int randomizer() 
    {
      int max_percentage = 99;
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<> dis(0, max_percentage);

      if (dis(gen) < 70) return 0;
      else if (dis(gen) < 85) return 1;
      else return 2;
    };

    //SETTERS
    void set_chips() 
    {
      this->chips = stoi(this->rank);
    };

    void set_rank(string rank) 
    {
      int temp = stoi(rank);
      if (temp > 9) 
      {
        switch(temp) 
        {
          case 10:
            this->rank = 'J';
            break;
          case 11:
            this->rank = 'K'; 
            break;
          case 12:
            this->rank = 'Q'; 
            break;
          case 13:
            this->rank = 'A'; 
            break;
        };
      } else 
      {
        this->rank = rank;
      };
    };

    //GETTERS
    string getSuit() 
    { 
      return this->suit; 
    };

    string getRank() 
    { 
      return this->rank; 
    };

    string getColor() 
    { 
      return this->color; 
    };

    int getChips() 
    {
      return this->chips;
    };

    ~PlayingCard() {};
};

#endif