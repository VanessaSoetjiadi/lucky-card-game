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
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 250);

    sf::RectangleShape rect({100,150});
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(500,300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                }
            if (event.type == sf::Event::MouseButtonPressed) {
                std::string coords = std::to_string(event.mouseButton.x) + ", " + std::to_string(event.mouseButton.y);
                title.setString(coords);
                if ((500 <= event.mouseButton.x && event.mouseButton.x <= 600) && (300 <= event.mouseButton.y && event.mouseButton.y <= 450)) {
                    title.setFillColor(sf::Color::Green);
                }
                else {
                    title.setFillColor(sf::Color::White);
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(rect);
        window.display();
    }

    return 0;
}
