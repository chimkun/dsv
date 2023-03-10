#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "button.h"
#include "menu.h"

int main()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML User Interface");
    window.clear(sf::Color::Blue);
    window.display();

    sf::Font font;
    if (!font.loadFromFile("src\\font\\PlatinumSignOver.ttf")) {
        std::cout << "Font file not found!\n";
        return -1;
    }

    sf::Text text("DS VISUALIZER", font, 150);
    text.setFillColor(sf::Color::White);
    text.setPosition(225, 80);

    std::string buttonText = "SELECT";
    sf::Vector2f testButtonPosition(400.f, 400.f), testButtonSize(300.f, 150.f);
    Button testButton(testButtonSize, buttonText, font, 50);
    testButton.setButtonPosition(testButtonPosition);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(text);
        testButton.drawButton(window);
        window.display();
    }
    return 0;
}