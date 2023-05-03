#ifndef REVERSEARROW_H
#define REVERSEARROW_H

#include <iostream>
#include <cmath>
#include "constants.h"

class reverseArrow {
private:
    sf::Texture arrowShaft, arrowLeft, arrowRight;
public:
    reverseArrow();
    void drawReverseArrow();
};

#endif