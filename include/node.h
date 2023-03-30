#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <iostream>

struct Node {
    int data;
    Node *pNext;
    Node ();
    void drawNode(sf::Vector2f nodePosition, int colorCode, sf::RenderWindow &window);
};

#endif