#ifndef DLLNODE_H
#define DLLNODE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "arrow.h"

struct DLLNode {
    int data, nodeColor;
    DLLNode *nxt, *prv;
    sf::Texture outlineTexture;
    sf::Texture circleTexture;
    sf::Texture numberTexture;

    Arrow fwArrow, bwArrow;

    DLLNode ();
    DLLNode (int data);
    void updateNumberTexture(int data);
    void drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity);
    void drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
                  int innerOpacity, int outlineOpacity, int numberOpacity,
                  sf::Color outlineColor, sf::Color numberColor);
    void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
    void drawFwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                     sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
    void drawBwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                     sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
};

#endif