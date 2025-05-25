#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

#include "Card.h"

// back color of the card, each having their own special effects
const string CardColor[] { "Red", "Black", "Blue" };

const string Suit[] { "Club", "Diamond", "Heart", "Spade" };

class PlayingCard : public Card {
  private:
    int chips;
    string color;
    string suit;
    string rank;
    bool chosen; // if user picked the card or not
  public:
    PlayingCard(string suit, string rank): suit(suit), rank(rank) 
    {
      this->color = CardColor[randomizer()];

      set_rank(stoi(rank));
    };

    void chosen_true() // set bool to true if picked
    {
      this->chosen = true;
    };

    // pure virtual functions override
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

    //SETTERS
    void set_chips(int rank)
    {
      this->chips = rank;
    };

    void set_rank(int rank) 
    {
      set_chips(rank);
      if (rank > 9) 
      {
        switch(rank)
        {
          case 10:
            this->rank = "10";
            break;
          case 11:
            this->rank = 'J';
            break;
          case 12:
            this->rank = 'K'; 
            break;
          case 13:
            this->rank = 'Q'; 
            break;
          case 14:
            this->rank = 'A'; 
            break;
        };
      } else {
        this->rank = to_string(rank);
      };
    };

    void set_color(string color) 
    {
      this->color = color;
    };

    void set_suit(string suit) 
    {
      this->suit = suit;
    };

    //GETTERS
    int get_chips() 
    {
      return this->chips;
    };

    bool get_chosen() 
    {
      return this->chosen;
    };

    string get_suit() 
    { 
      return this->suit;
    };

    string get_rank() 
    { 
      return this->rank;
    };

    string get_color() 
    { 
      return this->color;
    };

    ~PlayingCard() {};
};

#endif //PLAYINGCARD_H