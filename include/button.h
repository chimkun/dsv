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
    void initButton(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string &buttonTextContent);
    void drawButton(sf::RenderWindow &window, float xFactor = 0.33, float yFactor = 0.17, int textSize = 33);
    bool buttonIsClick(sf::RenderWindow &window);
    sf::FloatRect getButtonBounds();
};

#endif