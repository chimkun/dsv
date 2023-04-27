#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "text.h"

struct button {
    textInfo buttonText;
    sf::Sprite buttonSprite;
    sf::Texture buttonTexture;
    std::string buttonTextContent;
    sf::Vector2f buttonInitialPosition;
    float maxLength, moveSpeed;
    float opacity, fadeSpeed;
    bool isChoose;

    button(int moveSpeed = buttonConstants::moveSpeed, int maxLength = buttonConstants::moveLength);
    button(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string &buttonTextContent,
           int moveSpeed = buttonConstants::moveSpeed, int maxLength = buttonConstants::moveLength);

    void initButton(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string &buttonTextContent);
    void drawButton(sf::RenderWindow &window, float xFactor = 0.31, float yFactor = 0.17, int textSize = 33);
    void drawButtonOptional(sf::RenderWindow &window, float xFactor = 0.31, float yFactor = 0.17, int textSize = 33, int buttonOpacity = 255);
    bool buttonIsClick(sf::RenderWindow &window);
    bool buttonIsHover(sf::RenderWindow &window);
    
    void flipChoose();
    void offButton();
    void onButton();
    bool isChosen();


    void moveButtonWhenHover(sf::RenderWindow &window);
    sf::FloatRect getButtonBounds();
};

#endif