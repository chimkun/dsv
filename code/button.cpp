#include <iostream>
#include "button.h"

button::button(int moveSpeed, int maxLength) {
    lengthDiff = 0;
    this->moveSpeed = moveSpeed;
    this->maxLength = maxLength;
}

void button::initButton(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string &buttonTextContent) {
    buttonText.setFont(1);
    buttonSprite.setOrigin(0, 0);
    buttonSprite.setPosition(buttonPosition);
    buttonInitialPosition = buttonPosition;
    this->buttonTexture = buttonTexture;
    this->buttonTextContent = buttonTextContent;
}
void button::drawButton(sf::RenderWindow &window, float xFactor, float yFactor, int textSize) {
    buttonSprite.setTexture(this->buttonTexture);
    window.draw(buttonSprite);

    sf::IntRect buttonBound = buttonSprite.getTextureRect();
    sf::FloatRect globalBound = buttonSprite.getGlobalBounds();
    sf::Vector2f textOrigin(0, 0);
    sf::Vector2f textPosition(globalBound.left + (int) buttonBound.width * xFactor, globalBound.top + (int) buttonBound.height * yFactor);
    buttonText.drawOptionalTextSize(window, buttonTextContent, textOrigin, textPosition, 255, textSize);
}

bool button::buttonIsClick(sf::RenderWindow &window) {
    sf::FloatRect buttonBounds = getButtonBounds();
    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonBounds.contains(mousePosition))
        return true;
    return false;
}
bool button::buttonIsHover(sf::RenderWindow &window) {
    sf::FloatRect buttonBounds = getButtonBounds();
    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
    if (buttonBounds.contains(mousePosition))
        return true;
    return false;
}
void button::moveButtonWhenHover(sf::RenderWindow &window) {
    if (buttonIsHover(window)) {
        sf::Vector2f buttonSpritePosition = buttonSprite.getPosition();
        buttonSpritePosition.x = std::min(buttonInitialPosition.x + maxLength, buttonSpritePosition.x + moveSpeed);
        buttonSprite.setPosition(buttonSpritePosition);
    }
    else {
        sf::Vector2f buttonSpritePosition = buttonSprite.getPosition();
        buttonSpritePosition.x = std::max(buttonInitialPosition.x, buttonSpritePosition.x - moveSpeed);
        buttonSprite.setPosition(buttonSpritePosition);
    }
}

void button::flipChoose() {
    isChoose = !isChoose;
}

sf::FloatRect button::getButtonBounds()  {
    return buttonSprite.getGlobalBounds();
}
