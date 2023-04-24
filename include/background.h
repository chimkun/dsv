#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

class background {
private:
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    int bgCode;
public:
    background();
    void setBackground();
    void drawBackground(sf::RenderWindow &window, int bgOpacity = 50);
};

#endif