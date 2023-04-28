#ifndef FADECOLOR_H
#define FADECOLOR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

sf::Color getFadeColor(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer);

#endif