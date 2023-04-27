#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "arrow.h"

struct Node {
    int data, nodeColor;
    Node *pNext;
    sf::Texture outlineTexture;
    sf::Texture circleTexture;
    sf::Texture numberTexture;
    Arrow nodeArrow;
    Node ();
    Node (int data);
    void drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity);
    void drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
                  int innerOpacity, int outlineOpacity, int numberOpacity,
                  sf::Color outlineColor, sf::Color numberColor);
    void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);

};

#endif