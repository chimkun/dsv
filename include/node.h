#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "nodeTextureHolder.h"
#include "arrow.h"

struct Node {
    int data;
    Node *pNext;
    // sf::Texture outlineTexture;
    // sf::Texture circleTexture;
    // sf::Texture numberTexture;
    // nodeTexture NodeTexture;
    // Arrow nodeArrow;
    Node ();
    Node (int data);
    // void drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity);
    // void drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
    //               int innerOpacity, int outlineOpacity, int numberOpacity,
    //               sf::Color outlineColor, sf::Color numberColor);
    // void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
    //                           sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
};

class drawListNode {
private:
    nodeTexture NodeTexture;
    // sf::Texture circleTexture, outlineTexture;
    // sf::Texture digitTexture[10];
    
    Arrow nodeArrow;
public:
    drawListNode();
    void initTexture();
    void getTexture();

    void drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity, int data);

    void drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
                  int innerOpacity, int outlineOpacity, int numberOpacity,
                  sf::Color outlineColor, sf::Color numberColor, int data);

    void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);
};

#endif