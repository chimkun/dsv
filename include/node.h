#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

struct Node {
    int data, nodeColor;
    Node *pNext;
    Node ();
    void drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity);
    void drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
                  int innerOpacity, int outlineOpacity, int numberOpacity,
                  sf::Color outlineColor, sf::Color numberColor);
    void drawArrow(sf::Vector2f nodePosition, sf::RenderWindow &window, int middleOfNodes, int opacity);
};

#endif