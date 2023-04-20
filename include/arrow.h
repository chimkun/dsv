#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

struct Arrow {
    sf::Texture arrowShaft;
    sf::Texture arrowHead;
    Arrow ();
    void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
};

#endif