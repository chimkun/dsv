#ifndef ARROW_H
#define ARROW_H

#include <iostream>
#include <cmath>
#include "constants.h"

struct Arrow {
    sf::Texture arrowShaft;
    sf::Texture arrowHead;
    sf::RectangleShape ArrowShaft;
    Arrow ();
    void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
    void drawArrowDLLNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
};

#endif