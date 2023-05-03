#ifndef CLLNODE_H
#define CLLNODE_H

#include "constants.h"
#include "arrow.h"
#include "text.h"

class CLLNodeTexture {
private:
    sf::Texture nodeCircleTexture, nodeOutlineTexture;
    textInfo numberText;
    Arrow arrow;
public:
    CLLNodeTexture();
    void drawCLLNode(sf::RenderWindow &window, sf::Vector2f nodePosition, 
                     int data, sf::Color nodeColor = nodeConstants::baseColor, int numberOpacity = 255, int opacity = 255);
    void drawCLLNode2(sf::RenderWindow &window, sf::Vector2f nodePosition, 
                     int data, sf::Color numberColor = nodeConstants::baseColor,
                     sf::Color nodeColor = nodeConstants::baseColor, int numberOpacity = 255, int opacity = 255);
    void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
};

#endif