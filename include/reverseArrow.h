#ifndef REVERSEARROW_H
#define REVERSEARROW_H

#include <iostream>
#include <cmath>
#include "constants.h"

class reverseArrow {
private:
    sf::RectangleShape AB, BC, CD, DE;
    sf::Texture arrowHead;
public:
    reverseArrow();
    void drawReverseArrow(sf::RenderWindow &window, sf::Vector2f firstNode, sf::Vector2f lastNode, 
                          sf::Color arrowColor = sf::Color::White, int opacity = 255);
};

#endif