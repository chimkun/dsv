#include "button.h"
#include <iostream>

Button::Button () {}

Button::Button (sf::Vector2f &buttonSize) {
    sf::Vector2f outlineSize = buttonSize;
    outlineSize.x += 20, outlineSize.y += 20;
    theButton.setSize(buttonSize);
    theButton.setFillColor(sf::Color::Black);
    theOutline.setSize(outlineSize);
    theOutline.setFillColor(sf::Color::White);
}

void Button::initText(std::string &text, int textCharSize) {
    theText.setString(text);
    theText.setCharacterSize(textCharSize);
    theText.setFillColor(sf::Color::White);
}

void Button::setButtonPosition(sf::Vector2f &buttonPosition) {
    sf::Vector2f outlinePosition = buttonPosition;
    outlinePosition.x -= 10, outlinePosition.y -= 10;
    theButton.setPosition(buttonPosition);
    theOutline.setPosition(outlinePosition);
    sf::Font font;
    if (!font.loadFromFile("src\\font\\PlatinumSignOver.ttf")) {
        std::cout << "Font file not found!\n";
        exit(-1);
    }
    theText.setFont(font);
    //std::cerr << "done init\n";
    sf::FloatRect textBounds = theText.getGlobalBounds();
    sf::FloatRect buttonBounds = theButton.getGlobalBounds();
    float buttonHeight = buttonBounds.height, textHeight = textBounds.height;
    float buttonWidth = buttonBounds.width, textWidth = textBounds.width;
    //std::cerr << "buttonWidth: " << buttonWidth << "\ntextWidth: " << textWidth << "\nFontSize: " << theText.getCharacterSize() << "\n";
    theText.setPosition(sf::Vector2f(buttonBounds.left + (buttonWidth - textWidth) / 2 + 20, buttonBounds.top + (buttonHeight - textHeight) / 2 + 20));
    //theText.setPosition(buttonBounds.left + (buttonWidth - textWidth) / 2 + 10, buttonBounds.top + (buttonHeight - textHeight) / 2);

    
    //std::cerr << content.toAnsiString() << '\n';
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
    sf::Font font;
    if (!font.loadFromFile("src\\font\\PlatinumSignOver.ttf")) {
        std::cout << "Font file not found!\n";
        exit(-1);
    }
    window.draw(theOutline);
    window.draw(theButton);
    theText.setFont(font);
    window.draw(theText);
}
