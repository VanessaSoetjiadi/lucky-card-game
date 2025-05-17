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
    bool chosen;
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
      this->chips = stoi(this->rank); // Convert rank to integer for chips
    };

    void set_rank(string rank) 
    {
      int temp = stoi(rank); // Convert rank to integer for comparison
      if (temp > 9) // Check if rank is a face card
      {
        switch(temp) // Convert rank to string representation
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
        this->rank = rank; // Set rank as string
      };
    };

    void setChosen(bool chosen) 
    {
      this->chosen = chosen;  // Set if card is chosen/not
    };

    //GETTERS
    string getSuit() 
    { 
      return this->suit; // Return suit of the card
    };

    string getRank() 
    { 
      return this->rank; // Return rank of the card
    };

    string getColor() 
    { 
      return this->color; // Return color of the card
    };

    int getChips() 
    {
      return this->chips; // Return chips of the card
    };

    bool isChosen() 
    {
      return this->chosen; // Return if card is chosen/not
    };

    ~PlayingCard() {};
};

#endif