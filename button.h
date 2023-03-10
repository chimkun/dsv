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
    Button (sf::Vector2f &buttonSize, std::string &text, sf::Font &font, int textCharSize);
    void setButtonPosition(sf::Vector2f &buttonPosition);
    void drawButton(sf::RenderWindow &window);
    bool isPressed(sf::RenderWindow &window);
};

Button::Button (sf::Vector2f &buttonSize, std::string &text, sf::Font &font, int textCharSize) {
    sf::Vector2f outlineSize = buttonSize;
    outlineSize.x += 20, outlineSize.y += 20;
    theButton.setSize(buttonSize);
    theButton.setFillColor(sf::Color::Black);
    theOutline.setSize(outlineSize);
    theOutline.setFillColor(sf::Color::White);
    theText.setString(text);
    theText.setFont(font);
    theText.setCharacterSize(textCharSize);
    theText.setFillColor(sf::Color::White);
}

void Button::setButtonPosition(sf::Vector2f &buttonPosition) {
    sf::Vector2f outlinePosition = buttonPosition;
    outlinePosition.x -= 10, outlinePosition.y -= 10;
    theButton.setPosition(buttonPosition);
    theOutline.setPosition(outlinePosition);
    sf::FloatRect textBounds = theText.getGlobalBounds();
    sf::FloatRect buttonBounds = theButton.getGlobalBounds();
    float buttonHeight = buttonBounds.height, textHeight = textBounds.height;
    float buttonWidth = buttonBounds.width, textWidth = textBounds.width;
    theText.setPosition(sf::Vector2f(buttonBounds.left + (buttonWidth - textWidth) / 2 + 10, buttonBounds.top + (buttonHeight - textHeight) / 2));
}

void Button::drawButton(sf::RenderWindow &window) {
    window.draw(theOutline);
    window.draw(theButton);
    window.draw(theText);
}

#endif