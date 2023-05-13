#ifndef TEXTURENODE_H
#define TEXTURENODE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "arrow.h"
#include "text.h"

class TextureNode {
private:
    sf::Texture nodeCircleTexture, nodeOutlineTexture;
    textInfo numberText;
    Arrow fwArrow, bwArrow;
public:
    TextureNode();
    void drawArrayNode(sf::RenderWindow &window, sf::Vector2f nodePosition, int data, 
                       int opacity = 255, sf::Color nodeColor = sf::Color::White,
                       int innerOpacity = 255);

    void drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity, int data);
    void drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
                  int innerOpacity, int outlineOpacity, int numberOpacity,
                  sf::Color outlineColor, sf::Color numberColor, int data);
    void drawArrowBetweenNodeSLL(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                                 sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
    void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
    void drawFwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
    void drawBwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
};

#endif