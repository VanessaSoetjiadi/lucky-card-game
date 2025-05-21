#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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
    title.setFillColor(sf::Color::Green);
    title.setPosition(200, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                }
            if (event.type == sf::Event::MouseButtonPressed) {
                std::string coords = std::to_string(event.mouseButton.x) + ", " + std::to_string(event.mouseButton.y);
                title.setString(coords);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.display();
    }

    return 0;
}
