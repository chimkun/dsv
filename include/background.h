#ifndef BACKGROUND_H
#define BACKGROUND_H

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
    void drawBackground(sf::RenderWindow &window, int bgOpacity = 40);
};

#endif