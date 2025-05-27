#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream> // for file operations of leaderboard
#include <string> // for string of player name
#include "Hand.h"

using namespace std;

// LeaderboardEntry struct
struct LeaderboardEntry {
  string name;
  int score;

  LeaderboardEntry() : name(""), score(0) {}
  LeaderboardEntry(string n, int s) : name(n), score(s) {}
  bool operator<(const LeaderboardEntry& other) const {
    return score > other.score;
  }
};

// used to allow detection of clicking on the sprite
struct CardSprite {
  sf::Sprite sprite;
  PlayingCard* card;
};

struct JokerSprite {
  sf::Sprite sprite;
  JokerCard* card;
  sf::Text description;
};

struct SupportSprite {
  sf::Sprite sprite;
  SupportCard* card;
  sf::Text description;
};

struct Button {
  sf::RectangleShape rectangle;
  std::string type;
};

struct IndexSet {
  std::string playing_cards;
  std::string joker_cards;
  std::string support_cards;
};

class Game {
  private:
    int minimumScore;
    int round;
    int difficulty;
    bool lose_status;
    vector<LeaderboardEntry> highscores;
    const string leaderboardFile = "leaderboard.txt";
    const int maxLeaderboardEntries = 10;
    string playerName;
    bool nameEntered;
    sf::RenderWindow window;
    sf::Font font;
    vector<CardSprite> card_sprites; // vector of playing cards
    vector<JokerSprite> joker_sprites; // vector of jokers
    vector<SupportSprite> support_sprites; // vector of supports. note - support cards don't actually use a unique sprite, just text on placeholder sprite
    vector<Button> buttons; // vector to hold play button and discard button
    JokerDeck jkDeck;
    SupportDeck spDeck;

    void showMainMenu() {
      // allow user to choose an action, and perform the action using a switch statement
      std::string strings[3] = {"Play","Leaderboard","Exit"};
      std::string title = "Lucky Card Game";
      sf::Color colours[3] = {sf::Color::Green,sf::Color::Yellow,sf::Color::Red};
      int choice = getChoice(title,3,strings,colours);
      switch(choice) {
        case 0:
          handleNameInput();
          if (nameEntered) {
            // resets the joker, support deck for new games
            jkDeck.makeDeck();
            spDeck.makeDeck();

            // runs the game
            sfml_runGame(jkDeck, spDeck);
          }
          break;
        case 1:
          displayLeaderboard();
          break;
        default:
          window.close();
          break;
      } 
    }
    
    void loadLeaderboard() {
      highscores.clear();
      ifstream file(leaderboardFile);
      if (file.is_open()) {
        string line;
        LeaderboardEntry entry;
        while (file >> entry.name >> entry.score) {
          highscores.push_back(entry);
        }
        file.close();
        sort(highscores.begin(), highscores.end());
        if (highscores.size() > maxLeaderboardEntries) {
          highscores.resize(maxLeaderboardEntries);
        }
      }
    }

    void saveLeaderboard() {
      ofstream file(leaderboardFile);
      if (file.is_open()) {
        for (int i = 0; i < highscores.size(); i++) {
          file << highscores[i].name << " " << highscores[i].score << "\n";
        }
        file.close();
      }
    }

    void updateLeaderboard(const string& name, int score) {
      if (score < 0) {
        sf::Text errorMsg; // initialize text object 'errorMsg'
        errorMsg.setString("Error: Score cannot be negative."); // set text
        errorMsg.setCharacterSize(20); // set character size
        errorMsg.setFillColor(sf::Color::Red); // set text color
        errorMsg.setPosition(window.getSize().x/2 - errorMsg.getGlobalBounds().width/2, 150); // set text position
        window.draw(errorMsg); // draw everything of text object 'errorMsg'
        window.display(); // display error message (this is used and not other places as this is appearing in the current frame)

        sf::sleep(sf::seconds(3)); // 3 seconds to know error happend 
        return;
      }
      highscores.push_back(LeaderboardEntry(name, score));
      sort(highscores.begin(), highscores.end());
      if (highscores.size() > maxLeaderboardEntries) {
        highscores.resize(maxLeaderboardEntries);
      }
      saveLeaderboard();
    }

    void displayLeaderboard() {
      window.clear(sf::Color::Black); // clearing the window to make sure that there is no residue of the previous frame
      
      sf::Text title; // initialize text object 'title'
      title.setFont(font); // set font
      title.setString("LEADERBOARD"); // set text
      title.setCharacterSize(30); // set character size
      title.setFillColor(sf::Color::White); // set text color
      title.setPosition(window.getSize().x/2 - title.getGlobalBounds().width/2, 50); // set text position
      window.draw(title); // draw everything of text object 'title'

      if (highscores.empty()) {
        sf::Text noScores; // initialize text object 'noScores'
        noScores.setFont(font); // set font
        noScores.setString("No scores recorded yet!"); // set text
        noScores.setCharacterSize(20); // set character size
        noScores.setFillColor(sf::Color::White); // set text color
        noScores.setPosition(window.getSize().x/2 - noScores.getGlobalBounds().width/2, 150); // set text position
        window.draw(noScores); // draw everything of text object 'noScores'
      } 
      else {
        for (int i = 0; i < highscores.size(); i++) { // loop thru each entry
          sf::Text entry; // initialize text object 'entry'
          entry.setFont(font); // set font  
          entry.setString(to_string(i + 1) + ". " + highscores[i].name + " - " + to_string(highscores[i].score)); // set text
          entry.setCharacterSize(20); // set character size
          entry.setFillColor(sf::Color::White); // set text color
          entry.setPosition(50, 150 + i * 40); // set text position
          window.draw(entry); // draw everything of text object 'entry'
        }
      }

      sf::RectangleShape backButton; // initialize rectangle object 'backButton'
      backButton.setSize({100, 40}); // set button size 
      backButton.setFillColor(sf::Color::Green); // set button color
      backButton.setPosition(window.getSize().x/2 - 50, window.getSize().y - 100); // set button position
      window.draw(backButton); // draw everything of rectangle object 'backButton'

      sf::Text backText; // initialize text object 'backText'
      backText.setFont(font); // set font
      backText.setString("Back"); // set text
      backText.setCharacterSize(20); // set character size
      backText.setFillColor(sf::Color::Black); // set text color to black
      backText.setPosition(window.getSize().x/2 - 25, window.getSize().y - 88); // set text position
      window.draw(backText); // draw everything of text object 'backText'

      window.display(); // display leaderboard

      while (window.isOpen()) { // while window is open we check for windows is closed or not else if we check we clicked the back button or not, if back button is clicked we display the main menu
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();
          }
          if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (backButton.getGlobalBounds().contains(mousePos)) { // we check for the mouse being over the back button (mouse position is bounded in the region of  back button)
              showMainMenu();
              return;
            }
          }
        }
      }
    }

    void handleNameInput() {
      sf::Text nameAskPrompt; // initialize text object 'nameAskPrompt'
      nameAskPrompt.setFont(font); // set font
      nameAskPrompt.setString("Enter your name (max 15 chars, no spaces):"); // set text
      nameAskPrompt.setCharacterSize(20); // set character size
      nameAskPrompt.setFillColor(sf::Color::White); // set text color
      nameAskPrompt.setPosition(50, window.getSize().y/2 - 50); // set text position

      sf::Text nameInput; // initialize text object 'nameInput'
      nameInput.setFont(font); // set font
      nameInput.setCharacterSize(20); // set character size
      nameInput.setFillColor(sf::Color::Black); // set text color
      nameInput.setPosition(60, window.getSize().y/2 + 15); // set text position

      sf::RectangleShape nameInputBox; // initialize rectangle object 'nameInputBox'
      nameInputBox.setSize({300, 40}); // set box size
      nameInputBox.setFillColor(sf::Color::White); // set box color to white
      nameInputBox.setOutlineThickness(2); // set boundary thickness
      nameInputBox.setOutlineColor(sf::Color::White); // set boundary color
      nameInputBox.setPosition(50, window.getSize().y/2 + 10); // set text position

      while (window.isOpen() && !nameEntered) {
        sf::Event event; 
        while (window.pollEvent(event)) {
          // Window close
          if (event.type == sf::Event::Closed) {
            window.close();
          }
          // Text Input (backspace, normal text, and space)
          if (event.type == sf::Event::TextEntered) {
            // Backspace
            if (event.text.unicode == '\b' && !playerName.empty()) {
              playerName.pop_back();
            }
            // Space, newline, return, tab and 15 characters limit and alphabet characters only
            else if ((event.text.unicode > 64 && event.text.unicode < 91 || event.text.unicode > 96 && event.text.unicode < 123) && playerName.length() < 15 && event.text.unicode != ' ' && event.text.unicode != '\n' && event.text.unicode != '\r' && event.text.unicode != '\t') {
              playerName += static_cast<char>(event.text.unicode);
            }
            nameInput.setString(playerName);
          }
          // Enter key pressed
          if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Return && !playerName.empty()) {
              nameEntered = true;
            }
          }
        }

        // display window
        window.clear(sf::Color::Black); // clear the window to make sure that there is no residue of the previous frame
        window.draw(nameAskPrompt); // draw the text object 'nameAskPrompt'
        window.draw(nameInputBox); // draw the rectangle object 'nameInputBox'
        window.draw(nameInput); // draw the text object 'nameInput'
        window.display(); // display the window
      }
    }


  public:
    // constructor
    Game(): round(0), minimumScore(100), difficulty(1), window(sf::VideoMode(800, 600), "Lucky Card Game")
    {
      loadLeaderboard();
      
      // window setup
      window.setSize({800,600});
      window.setTitle("Lucky Card Game");
      if (!font.loadFromFile("assets/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
      }

      showMainMenu();
    };

    // user chooses what they would like to do
    int getChoice(std::string title_string,int num_options,std::string strings[],sf::Color colours[]) {
      // create graphics for menu buttons
      float b_width = 200;
      float b_height = 30;
      std::vector<sf::RectangleShape> menu_buttons;
      std::vector<sf::Text> menu_texts;
      for (int i = 0; i < num_options; i++) {
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
      title.setString(title_string);
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

                // then check for button on screen
                for (int i = 0; i < num_options; i++) {
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
        for (int i = 0; i < num_options; i++) {
            window.draw(menu_buttons[i]);
            window.draw(menu_texts[i]);
        }
        window.draw(title);
        window.display();
      }
      return 0; // if the window closes, return the first option by default
    };

    // temporary function 'sfml_runGame()' to replace 'runGame()' during sfml development
    void sfml_runGame(JokerDeck jkDeck, SupportDeck spDeck) {
      // main gameplay loop
      lose_status = false;
      while (lose_status == false) {
        round++;

        // get input for difficulty
        std::string diff_strings[3] = {"Easy","Medium","Difficult"};
        sf::Color diff_colours[3] = {sf::Color::White,sf::Color::White,sf::Color::White};
        int d = getChoice("Round " + std::to_string(round) +": Select Difficulty",3,diff_strings,diff_colours);
        if (!window.isOpen()) {return;} // ensure window is still open before continuing

        switch(d) // determining the minimum score based on the difficulty chosen
        {
          case 0:
            minimumScore += 75*round;
            break;
          case 1:
            minimumScore += 150*round;
            break;
          case 2:
            minimumScore += 250*round;
            break;
          default:
            minimumScore += 75*round;
            break;
        };
        
        std::string display = "You'll need " + std::to_string(minimumScore) + " to win!";
        std::string strings[1] = {"Continue"};
        sf::Color colours[1] = {sf::Color::White};
        getChoice(display,1,strings,colours); // this function will return an int, but we don't need it, we only need to wait for the return
        if (!window.isOpen()) {return;} // ensure window is still open before continuing
        
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

        playDeck.makeDeck(initialDeck);

        std::string most_recent = ""; // string used to display the result of the most recent hand

        // game loop
        while (window.isOpen() && hand.get_handsCount() > 0 && hand.get_totalScore() < minimumScore) { // while the round is still going
          displayAll(playDeck, jkDeck, spDeck, hand.get_totalScore(), hand.get_handsCount(), most_recent); // display everything

          sf::Event event;
          while (window.pollEvent(event)) { // get event from sfml
            if (event.type == sf::Event::Closed) { // close button
              window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) { // mouse button
              sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
              // render playing cards
              for (int i = 0; i < card_sprites.size(); i++) { // for each playing card
                if (card_sprites[i].sprite.getGlobalBounds().contains(mousePos)) { // if mouse is over the card
                  card_sprites[i].card->choose(); // toggle the card's chosen state
                }
              }
              // same for jokers
              for (int i = 0; i < joker_sprites.size(); i++) {
                if (joker_sprites[i].sprite.getGlobalBounds().contains(mousePos)) {
                  joker_sprites[i].card->choose();
                }
              }
              // same for supports
              for (int i = 0; i < support_sprites.size(); i++) {
                if (support_sprites[i].sprite.getGlobalBounds().contains(mousePos)) {
                  support_sprites[i].card->choose();
                }
              }

              IndexSet indexes = getChosenIndexes(); // get indexes of chosen cards, which informs behaviour of play/discard buttons

              // detect buttons
              for (int i = 0; i < buttons.size(); i++) {
                if (buttons[i].rectangle.getGlobalBounds().contains(mousePos)) {
                  if (buttons[i].type == "play") {
                    pickSupportCards(indexes.support_cards, spDeck);
                    most_recent = hand.calculateTotalScore(playDeck, jkDeck, spDeck);
                    playDeck.makeDeck(initialDeck);
                  }
                  else if (buttons[i].type == "discard") {
                    hand.discardPlayingCards(playDeck);
                    hand.manualDiscardEffectsCards(indexes.joker_cards, jkDeck);
                    hand.manualDiscardEffectsCards(indexes.support_cards, spDeck);
                    playDeck.makeDeck(initialDeck);
                  }
                  else if (buttons[i].type == "sort_ranks") {
                    playDeck.sortInRanks();
                  }
                  else if (buttons[i].type == "sort_suits") {
                    playDeck.sortInSuits();
                  }
                }
              }
            }
          }
        }
        // after round ends
        if (hand.get_handsCount() < 1 && hand.get_totalScore() < minimumScore) 
        {
          std::string display = "Round lost.";
          std::string strings[1] = {"Continue"};
          sf::Color colours[1] = {sf::Color::White};
          getChoice(display,1,strings,colours); // this function will return an int, but we don't need it, we only need to wait for the return
          if (!window.isOpen()) {return;} // ensure window is still open before continuing
          //highscores.push_back(hand.get_totalScore()); // push the high score?
          lose_status = true;
        } else {
          std::string display = "Round won!";
          std::string strings[1] = {"Continue"};
          sf::Color colours[1] = {sf::Color::White};
          getChoice(display,1,strings,colours); // this function will return an int, but we don't need it, we only need to wait for the return
          if (!window.isOpen()) {return;} // ensure window is still open before continuing
        };
      }
    }

    IndexSet getChosenIndexes() {
        IndexSet indexes;
        for (int i = 0; i < card_sprites.size(); i++)
            if (card_sprites[i].card->get_chosen())
                indexes.playing_cards += std::to_string(i);
        for (int i = 0; i < joker_sprites.size(); i++)
            if (joker_sprites[i].card->get_chosen())
                indexes.joker_cards += std::to_string(i);
        for (int i = 0; i < support_sprites.size(); i++)
            if (support_sprites[i].card->get_chosen())
                indexes.support_cards += std::to_string(i);
        return indexes;
    }  
    // display everything and return the index of currently chosen cards
    void displayAll(PlayingDeck& playDeck, JokerDeck& jkDeck, SupportDeck& spDeck, int current_score, int hands_remaining, std::string most_recent) {
      card_sprites.clear(); // reset vector of drawables
      joker_sprites.clear();
      support_sprites.clear();
      buttons.clear();
      window.clear(sf::Color::Black);

      bool can_play = false; //    used to decide if play/discard buttons are rendered
      bool can_discard = false; // in the for loops, if at least one card is chosen, the button will be rendered
      
      int num_chosen = 0;
      // add cards in playDeck
      int x = 20; // a tracker is used for x coord because the size of each card can vary,
      //             therefore using a multiple of i is not adequate
      //             this applies to jkDeck and spDeck also
      for (int i = 0; i < playDeck.getCurrentCards(); i++) {
        PlayingCard* card = playDeck.getDeck()[i];
        sf::Sprite sp(card->draw());
        if (card->get_chosen()) {
          sp.scale(0.3,0.3);
          num_chosen += 1;
          can_play = true;
          can_discard = true;
        } // scale depends on if card is chosen or not
        else {sp.scale(0.25,0.25);}
        sp.setPosition(x,window.getSize().y-sp.getGlobalBounds().height-20);
        x += sp.getGlobalBounds().width + 20; // increment x co-ord

        card_sprites.push_back({sp,card});
      };

      if (num_chosen > 5) {can_play = false;}

      // add cards in jkDeck
      x = 20;
      for (int i = 0; i < jkDeck.getCurrentCards(); i++) {
        JokerCard* card = jkDeck.getDeck()[i];
        sf::Sprite sp(card->draw());
        if (card->get_chosen()) {
          sp.scale(0.3,0.3);
          can_discard = true;
        } // scale depends on if card is chosen or not
        else {sp.scale(0.25,0.25);}
        sp.setPosition(x,20);

        sf::Text desc = card->get_description(x,sp.getGlobalBounds().height+30);
        desc.setFont(font);

        x+= sp.getGlobalBounds().width + 20;
        joker_sprites.push_back({sp,card,desc});
      }

      // add cards in spDeck
      x = window.getSize().x; // initial x coordinate is the right border
      for (int i = 0; i < spDeck.getCurrentCards(); i++) {
        SupportCard* card = spDeck.getDeck()[i];
        sf::Sprite sp(card->draw());
        if (card->get_chosen()) {
          sp.scale(0.3,0.3);
          can_discard = true;
        } // scale depends on if card is chosen or not
        else {sp.scale(0.25,0.25);}
        x -= (sp.getGlobalBounds().width + 20); // x is iterated before drawing because
        //                                         these cards fill from the right
        sp.setPosition(x,20);

        sf::Text desc = card->get_description(x,sp.getGlobalBounds().height+30);
        desc.setFont(font);
        support_sprites.push_back({sp,card,desc});
      }
      
      // draw all cards
      for (int i = 0; i < card_sprites.size(); i++) {
        window.draw(card_sprites[i].sprite);
      }
      for (int i = 0; i < joker_sprites.size(); i++) {
        window.draw(joker_sprites[i].sprite);
        window.draw(joker_sprites[i].description);
      }
      for (int i = 0; i < support_sprites.size(); i++) {
        window.draw(support_sprites[i].sprite);
        window.draw(support_sprites[i].description);
      }

      // play button
      if (can_play) {
        //create rectangle
        sf::RectangleShape play_rect;
        play_rect.setFillColor(sf::Color::Green);
        play_rect.setSize({80,30});
        float a = window.getSize().x - 100;
        float b = window.getSize().y - 90;
        play_rect.setPosition({a,b});
        // create text
        sf::Text play_text;
        play_text.setFillColor(sf::Color::Black);
        play_text.setFont(font);
        play_text.setCharacterSize(20);
        play_text.setPosition({a,b});
        play_text.setString("Play");
        // add to vector for click detection and draw
        buttons.push_back({play_rect,"play"});
        window.draw(play_rect);
        window.draw(play_text);
      }

      // discard button
      if (can_discard) {
        // rectangle
        sf::RectangleShape discard_rect;
        discard_rect.setFillColor(sf::Color::Red);
        discard_rect.setSize({80,30});
        float a = window.getSize().x - 100;
        float b = window.getSize().y - 50;
        discard_rect.setPosition({a,b});
        // text
        sf::Text discard_text;
        discard_text.setFillColor(sf::Color::Black);
        discard_text.setFont(font);
        discard_text.setCharacterSize(20);
        discard_text.setPosition({a,b});
        discard_text.setString("Discard");
        // add to vector and draw
        buttons.push_back({discard_rect,"discard"});
        window.draw(discard_rect);
        window.draw(discard_text);
      }

      // sort buttons
      sf::RectangleShape sort_ranks_rect;
      sort_ranks_rect.setFillColor(sf::Color::Yellow);
      sort_ranks_rect.setSize({40,30});
      float a = window.getSize().x - 100;
      float b = window.getSize().y - 130;
      sort_ranks_rect.setPosition({a,b});
      // text
      sf::Text sort_ranks_text;
      sort_ranks_text.setFillColor(sf::Color::Black);
      sort_ranks_text.setFont(font);
      sort_ranks_text.setCharacterSize(10);
      sort_ranks_text.setPosition({a,b});
      sort_ranks_text.setString("Sort by\nRank");
      // add to vector and draw
      buttons.push_back({sort_ranks_rect,"sort_ranks"});
      window.draw(sort_ranks_rect);
      window.draw(sort_ranks_text);

      sf::RectangleShape sort_suits_rect;
      sort_suits_rect.setFillColor(sf::Color::Cyan);
      sort_suits_rect.setSize({40,30});
      float c = window.getSize().x - 60;
      float d = window.getSize().y - 130;
      sort_suits_rect.setPosition({c,d});
      // text
      sf::Text sort_suits_text;
      sort_suits_text.setFillColor(sf::Color::Black);
      sort_suits_text.setFont(font);
      sort_suits_text.setCharacterSize(10);
      sort_suits_text.setPosition({c,d});
      sort_suits_text.setString("Sort by\nSuits");
      // add to vector and draw
      buttons.push_back({sort_suits_rect,"sort_suits"});
      window.draw(sort_suits_rect);
      window.draw(sort_suits_text);

      // create and draw score text
      sf::Text score_text;
      score_text.setFillColor(sf::Color::White);
      score_text.setFont(font);
      score_text.setCharacterSize(30);
      std::string score_string = "Score: " + std::to_string(current_score) + "/" + std::to_string(minimumScore) + " required\n" + std::to_string(hands_remaining) + " hands remaining";
      score_text.setString(score_string);
      float e = (window.getSize().x - score_text.getGlobalBounds().width) /2;
      float f = (window.getSize().y - score_text.getGlobalBounds().height) /2;
      score_text.setPosition({e,f});
      window.draw(score_text);

      // create and draw most recent text
      sf::Text most_recent_text;
      most_recent_text.setFillColor(sf::Color::White);
      most_recent_text.setFont(font);
      most_recent_text.setCharacterSize(15);
      most_recent_text.setString(most_recent);
      float g = (window.getSize().x - score_text.getGlobalBounds().width) /2;
      float h = (window.getSize().y - score_text.getGlobalBounds().height) /2 + score_text.getGlobalBounds().height + 5;
      most_recent_text.setPosition({g,h});
      window.draw(most_recent_text);
    
      window.display();
    }

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