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
    void setButtonPosition(sf::Vector2f &buttonPosition);
    void initText(std::string &text, sf::Font &font, int textCharSize);
    bool isPressed(sf::RenderWindow &window);
    void drawButton(sf::RenderWindow &window);
};

Button::Button () {}

Button::Button (sf::Vector2f &buttonSize) {
    sf::Vector2f outlineSize = buttonSize;
    outlineSize.x += 20, outlineSize.y += 20;
    theButton.setSize(buttonSize);
    theButton.setFillColor(sf::Color::Black);
    theOutline.setSize(outlineSize);
    theOutline.setFillColor(sf::Color::White);
}

void Button::initText(std::string &text, sf::Font &font, int textCharSize) {
    theText.setString(text);
    theText.setCharacterSize(textCharSize);
    theText.setFont(font);
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

bool Button::isPressed(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPos = theButton.getPosition();
    sf::Vector2f buttonSize = theButton.getSize();
    return (buttonPos.x <= mousePos.x && mousePos.x <= buttonPos.x + buttonSize.x
         && buttonPos.y <= mousePos.y && mousePos.y <= buttonPos.y + buttonSize.y
         && sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

void Button::drawButton(sf::RenderWindow &window) {
    window.draw(theOutline);
    window.draw(theButton);
    window.draw(theText);
}

#endif