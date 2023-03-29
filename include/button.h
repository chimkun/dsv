#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape theButton;
    sf::RectangleShape theOutline;
    sf::Text theText;
public: 
    Button ();
    Button (sf::Vector2f &buttonSize);
    void initText(std::string &text, int textCharSize);
    void setButtonPosition(sf::Vector2f &buttonPosition);
    bool isPressed(sf::RenderWindow &window);
    void drawButton(sf::RenderWindow &window);
};

#endif