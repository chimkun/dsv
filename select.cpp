#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML User Interface");
    window.clear(sf::Color::Blue);
    window.display();

    sf::Font font;

    if (!font.loadFromFile("src\\font\\PlatinumSignOver.ttf")) {
        std::cout << "Font file not found!\n";
        return -1;
    }

    sf::Text text("HELLO WORLD!", font, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 100);
    // sf::RectangleShape
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(text);
        window.display();
    }
    return 0;
}