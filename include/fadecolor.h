#ifndef FADECOLOR_H
#define FADECOLOR_H

#include <iostream>
#include "constants.h"

sf::Color getFadeColor(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer);
sf::Color getFadeColorOptionalDuration(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer, 
                                       sf::Time effectDuration = nodeConstants::flashDuration);

#endif