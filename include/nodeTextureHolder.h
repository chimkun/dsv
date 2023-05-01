#ifndef NODETEXTUREHOLDER_H
#define NODETEXTUREHOLDER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "constants.h"

class nodeTexture {
private:
    sf::Texture baseTexture, outlineTexture;
    sf::Texture digitTexture[10];
public:
    nodeTexture();
    void initNodeTexture();
    sf::Texture getBaseTexture();
    sf::Texture getOutlineTexture();
    sf::Texture getDigitTexture(int digit);
};

#endif