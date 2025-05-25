#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Hand.h"

using namespace std;

class Game {
  private:
    int minimumScore;
    int round;
    int difficulty;
    bool lose_status;
    vector<int> highscores;
    sf::RenderWindow window;
  public:
    // constructor
    Game(): round(0), minimumScore(100), difficulty(1), window(sf::VideoMode(800, 600), "Lucky Card Game")
    {
      // declared outside the switch so that it exists even if 
      JokerDeck jkDeck;
      SupportDeck spDeck;

      // window setup
      window.setSize({800,600});
      window.setTitle("Lucky Card Game");
      
      // allow user to choose an action, and perform the action using a switch statement
      int choice = mainMenu();
      switch(choice) {
        case 0:
          // resets the joker, support deck for new games
          jkDeck.makeDeck();
          spDeck.makeDeck();

          // runs the game
          run(jkDeck, spDeck);
          break;
        case 1:
          window.close();
          std::cout << "Leaderboard not yet implemented." << std::endl;
          break;
        default:
          window.close();
          break;
      }
    };

    // user chooses what they would like to do
    int mainMenu() {
      // create graphics for menu buttons

      // load font from file
      sf::Font font;
      if (!font.loadFromFile("assets/DejaVuSans.ttf")) {
          std::cerr << "Failed to load font\n";
          return 1;
      }
      sf::Color colours[3] = {sf::Color::Green,sf::Color::Yellow,sf::Color::Red};
      std::string strings[3] = {"Play","Leaderboard","Exit"};
      int b_width = 200;
      int b_height = 30;
      std::vector<sf::RectangleShape> menu_buttons;
      std::vector<sf::Text> menu_texts;
      for (int i = 0; i < 3; i++) {
          sf::RectangleShape rect;
          menu_buttons.push_back(rect);
          menu_buttons[i].setSize({b_width, b_height});
          menu_buttons[i].setFillColor(colours[i]);
          menu_buttons[i].setPosition(window.getSize().x/2 - b_width/2, window.getSize().y/2 - 2.5*b_height + 2*i*b_height);

          sf::Text text;
          menu_texts.push_back(text);
          menu_texts[i].setFillColor(sf::Color::Black);
          menu_texts[i].setString(strings[i]);
          menu_texts[i].setPosition(window.getSize().x/2 - b_width/2, window.getSize().y/2 - 2.5*b_height + 2*i*b_height);
          menu_texts[i].setFont(font);
          menu_texts[i].setCharacterSize(20);
      }

      sf::Text title;
      title.setFont(font);
      title.setCharacterSize(30);
      title.setString("Lucky Card Game");
      title.setFillColor(sf::Color::White);
      int t_height = title.getGlobalBounds().height;
      int t_width = title.getGlobalBounds().width;
      title.setPosition(window.getSize().x/2 - t_width/2, window.getSize().y/2 - 3.5*b_height - t_height);

      // loop to detect inputs and draw menu
      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                }
            if (event.type == sf::Event::MouseButtonPressed) {

                // then check for each card in hand
                for (int i = 0; i < 3; i++) {
                    int left = menu_buttons[i].getPosition().x;
                    int right = left + menu_buttons[i].getSize().x;
                    int top = menu_buttons[i].getPosition().y;
                    int bottom = top + menu_buttons[i].getSize().y;
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;

                    // when this if statement is true, it means that the button at index i was pressed;
                    if ((left <= x && x <= right) && (top <= y && y <= bottom)) {
                        return i;
                    }
                }
            }
        }

        // draw menu
        window.clear(sf::Color::Black);
        for (int i = 0; i < 3; i++) {
            window.draw(menu_buttons[i]);
            window.draw(menu_texts[i]);
        }
        window.draw(title);
        window.display();
      }
}

    // temporary function 'run()' to replace 'runGame()' during sfml development
    void run(JokerDeck jkDeck, SupportDeck spDeck) {
      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            // text pop up confirmation
            window.close();
            }
        }
      window.clear(sf::Color::Black);
      window.display();
      }
    }

    void runGame(JokerDeck jkDeck, SupportDeck spDeck) { // game loop
      lose_status = false;

      while (lose_status == false) {
        round++;

        int d = 0; //placeholder for input difficulty

        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        while (d < 1 || d > 3) { // inputting the difficulty level
          cout << "Please select difficulty: 1, 2, 3\n";
          cout << "Answer: ";
          cin >> d;
        };
        cout << "\n";

        switch(d) // determining the minimum score based on the difficulty chosen
        {
          case 1:
            minimumScore += 75*round;
            break;
          case 2:
            minimumScore += 150*round;
            break;
          case 3:
            minimumScore += 250*round;
            break;
          default:
            minimumScore += 75*round;
            break;
        };

        cout << "You'll need " << minimumScore << " to win!" << "\n";

        // add joker card every 2 rounds
        if (round % 2 == 0) 
        {
          jkDeck.addEffectCard();
        };

        // add support card every 4 rounds
        if (round % 4 == 0) 
        {
          spDeck.addEffectCard();
        };

        // initilizations
        Hand hand;

        InitDeck initialDeck;
        initialDeck.makeDeck();

        PlayingDeck playDeck;
        
        // game loop
        while (hand.get_handsCount() > 0 && hand.get_totalScore() < minimumScore) 
        {
          playDeck.makeDeck(initialDeck);
          hand.set_totalChips(0);
          hand.set_totalMults(0);

          cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

          // printing the all of the decks on terminal
          print_playingDeck(playDeck);
          cout << "->";
          print_jokerDeck(jkDeck);
          cout << "->";
          print_supportDeck(spDeck);

          cout << "Hands count: " << hand.get_handsCount() << " | " << "Discards count: " << hand.get_discardsCount() << "\n\n";

          // both are reset every iteration/round
          int n = 0, m = 0, x = 0; // n is for the option, m is for the deck, x is for the sorting
          string idx = ""; // user input for the chosen indexes
          bool allChosen = true; // checks whether or not all the support cards is being used

          while(n < 1 || n > 3) // input validation for the options
          {
            cout << "Please select one of the following:\n1. Play/use cards\n";
            if (jkDeck.getCurrentCards() > 0 || spDeck.getCurrentCards() > 0 || hand.get_discardsCount() > 0) 
            {
              cout << "2. Discard cards\n"; // available only if there are cards to be discarded
            };
            cout << "3. Sort cards\n";
            cout << "Answer: ";
            cin >> n;
            cout << "\n";
          };

          switch(n) {
            case 1: // play/use cards
              while(m < 1 || m > 2) 
              {
                cout << "Please select one of the following:\n1. Play cards\n";
                if (spDeck.getCurrentCards() > 0) 
                {
                  cout << "2. Use support cards\n";
                };
                cout << "Answer: ";
                cin >> m;
                cout << "\n";
              };
      
              switch(m) // play playing cards, or use support cards
              {
                case 1:
                  cout << "Please input the indexes of the cards that you wanna play: ";
                  cin >> idx;
                  indexValidator(idx, playDeck, 1);
                  pickPlayingCards(idx, playDeck); // making the cards chosen = true
                  hand.calculateTotalScore(playDeck, jkDeck, spDeck);
                  break;
                case 2:
                  for (int i = 0; i < spDeck.getCurrentCards(); i++) 
                  {
                    if (spDeck.getDeck()[i]->get_isUsed() == false) 
                    {
                      allChosen = false;
                      break;
                    };
                  };

                  if (allChosen == true) 
                  {
                    cout << "You're already using all of your support cards!\n";
                  } else {
                    cout << "Please input the indexes of the support cards that you wanna use: ";
                    cin >> idx;
                    indexValidator(idx, spDeck, 2);
                    pickSupportCards(idx, spDeck);
                  };
                  break;
                default:
                  break;
              };
              break;
            case 2: // discard cards
              while(m < 1 || m > 3) 
              {
                cout << "Please select one of the following:\n";
                if (hand.get_discardsCount() > 0) {
                  cout << "1. Discard playing cards\n";
                };
                if (spDeck.getCurrentCards() > 0) {
                  cout << "2. Discard support cards\n";
                };
                if (jkDeck.getCurrentCards() > 0) {
                  cout << "3. Discard joker cards\n";
                };
                cout << "Answer: ";
                cin >> m;
                cout << "\n";
              };
      
              switch(m) 
              {
                case 1:
                  cout << "Please input the indexes of the playing cards that you wanna discard: ";
                  cin >> idx;
                  indexValidator(idx, playDeck, 1);
                  pickPlayingCards(idx, playDeck);
                  hand.discardPlayingCards(playDeck);
                  hand.subtract_discardsCount();
                  break;
                case 2:
                  cout << "Please input the indexes of the support cards that you wanna discard: ";
                  cin >> idx;
                  indexValidator(idx, spDeck, 2);
                  hand.manualDiscardEffectsCards(idx, spDeck);
                  break;
                case 3:
                  cout << "Please input the indexes of the joker cards that you wanna discard: ";
                  cin >> idx;
                  indexValidator(idx, jkDeck, 3);
                  hand.manualDiscardEffectsCards(idx, jkDeck);
                  break;
                default:
                  break;
              };
              break;
            case 3: // sorting the playing cards
              cout << "Sort by:\n1. Suits\n2. Ranks\n";
              cout << "Answer: ";
              cin >> x;
              switch(x) 
              {
                case 1:
                  playDeck.sortInSuits();
                  break;
                case 2:
                  playDeck.sortInRanks();
                  break;
                default:
                  break;
              };
              break;
            default:
              break;
          };
      
          if (n == 1 && m == 1) // user plays the playing cards, which means score would change
          {
            cout << "Your score: " << hand.get_totalScore() << " | " << "Score needed: " << minimumScore << "\n";     
          };     
        };

        if (hand.get_handsCount() < 1 && hand.get_totalScore() < minimumScore) 
        {
          cout << "You Lost." << "\n";
          //highscores.push_back(hand.get_totalScore()); // push the high score?
          lose_status = true;
        } else {
          cout << "You Win!" << "\n\n";
        };
      };
    };

    // printers for terminal based prototype
    void print_playingDeck(PlayingDeck& playDeck) {
      cout << "[ ";
      for (int i = 0; i < playDeck.getCurrentCards(); i++) 
      {
        cout << playDeck.getDeck()[i]->get_suit() << " " << playDeck.getDeck()[i]->get_rank() << ", ";
      };
      cout << "]\n\n";
    };

    void print_jokerDeck(JokerDeck& jkDeck) 
    {
      if (!jkDeck.getDeck().empty()) 
      {
        for (int i = 0; i < jkDeck.getCurrentCards(); i++) 
        {
          cout << "Joker" << jkDeck.getDeck()[i]->get_rarity() << " bonus Chips: " << jkDeck.getDeck()[i]->get_bonus_chips() << ", bonus Mults: " << jkDeck.getDeck()[i]->get_bonus_mults() << ", lifespan: " << jkDeck.getDeck()[i]->get_lifespan() << " | ";
        };
        cout << "\n\n";
      } else {
        cout << "You don't have any Joker cards!\n\n";
      };
    };

    void print_supportDeck(SupportDeck& spDeck) 
    {
      if (!spDeck.getDeck().empty()) 
      {
        for (int i = 0; i < spDeck.getCurrentCards(); i++) 
        {
          cout << "Support" << spDeck.getDeck()[i]->get_rarity() << " bonus Chips: " << spDeck.getDeck()[i]->get_bonus_chips() << ", bonus Mults: " << spDeck.getDeck()[i]->get_bonus_mults() << " | ";
        };
        cout << "\n\n";
      } else {
        cout << "You don't have any Support cards!\n\n";
      };
    };

    void indexValidator(string& index, Deck& deck, int m) // m is the deck affected
    {
      int currentCards = deck.getCurrentCards();
      bool isValid = false;

      while (!isValid) 
      {
        isValid = true; // assume valid until proven otherwise
        map<char, int> indexMap; // for tracking duplicates

        // check if the user is trying to pick more than 5 cards
        if (m == 1) 
        {
          if (index.length() > 5) 
          {
            cout << "please pick **up to 5** cards for each play/discard: ";
            cin >> index;
            isValid = false;
            continue;
          }
        } else {
          if (index.length() > deck.getCurrentCards()) 
          {
            cout << "please pick **up to "<< deck.getCurrentCards() << "** cards for each play/discard: ";
            cin >> index;
            isValid = false;
            continue;
          }
        };
        

        for (int i = 0; i < index.length(); i++) 
        {
          // check if the index chosen are less than or equal to the number of cards in the deck
          int idx = index[i] - '0';
          if (idx < 0 || idx >= currentCards) 
          {
            if (currentCards > 1) 
            {
              cout << "Please pick an index **within the deck's range (0-" << (currentCards - 1) << "): ";
            } else {
              cout << "The only index that can be chosen is 0: ";
            };
            cin >> index;
            isValid = false;
            cout << "\n";
            break;
          }

          // check if there's a duplicate number
          if (indexMap[index[i]]++ > 0) { 
            cout << "Duplicate index (" << index[i] << "). Pick unique indices: ";
            cin >> index;
            isValid = false;
            cout << "\n";
            break;
          }
        };
      }
    };

    void pickPlayingCards(string& index, PlayingDeck& playDeck) 
    {
      cout << "You chose: ";
      for (int i = 0; i < index.length(); i++) 
      {
        playDeck.getDeck()[index[i] - '0']->chosen_true();
        cout << playDeck.getDeck()[index[i] - '0']->get_suit() << playDeck.getDeck()[index[i] - '0']->get_rank() << ", ";
      };
      cout << "\n\n";
    };

    void pickSupportCards(string& index, SupportDeck& spDeck) 
    {
      for (int i = 0; i < index.length(); i++) 
      {
        if (spDeck.getDeck()[index[i] - '0']->get_isUsed() == true) 
        {
          cout << "Support" << spDeck.getDeck()[i]->get_rarity() << " is already chosen to be used next hand played.\n";
        } else {
          spDeck.getDeck()[index[i] - '0']->set_Used();
          cout << "Support" << spDeck.getDeck()[i]->get_rarity() << " will be used next hand played.\n";
        };
      };
    };


    //SETTERS
    void set_difficulty(int inpt) 
    {
      this->difficulty = inpt;
    };
    
    //GETTERS
    int get_difficulty() {
      return this->difficulty;
    }; 

    sf::RenderWindow& getWindow() {
      // the RenderWindow class is non-copyable, so it is impossible to return directly,
      // therefore we set the return type as an address in the function definition
      return window;
    }

    ~Game() {};
};

#endif //GAME_H