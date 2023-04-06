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
    void drawArrow(sf::Vector2f nodePosition, sf::RenderWindow &window, int middleOfNodes, int opacity);
};

#endif