#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "window title");

    // load font from file
    sf::Font font;
    if (!font.loadFromFile("assets/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Lucky Card Game");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 250);


    // create an array of rectangles
    sf::Color colours[5] = {sf::Color::Red,sf::Color::Yellow,sf::Color::Green,sf::Color::Blue,sf::Color::Magenta};
    std::vector<sf::RectangleShape> hand;
    for (int i = 0; i < 5; i++) {
        sf::RectangleShape rect;
        hand.push_back(rect);
        hand[i].setSize({100, 150});
        hand[i].setFillColor(colours[i]);
        hand[i].setPosition(150 + i * 110, 300);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // text pop up confirmation
                window.close();
                }
            if (event.type == sf::Event::MouseButtonPressed) {
                std::string coords = std::to_string(event.mouseButton.x) + ", " + std::to_string(event.mouseButton.y);
                title.setString(coords);

                // set default colour to white
                title.setFillColor(sf::Color::White);

                // then check for each card in hand
                for (int i = 0; i < 5; i++) {
                    int left = hand[i].getPosition().x;
                    int right = left + hand[i].getSize().x;
                    int top = hand[i].getPosition().y;
                    int bottom = top + hand[i].getSize().y;
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;

                    if ((left <= x && x <= right) && (top <= y && y <= bottom)) {
                        title.setFillColor(hand[i].getFillColor());
                    }
                }

                
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        for (int i = 0; i < 5; i++) {
            window.draw(hand[i]);
        }
        window.display();
    }

    return 0;
}
