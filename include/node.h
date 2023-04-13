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
    void drawText(sf::RenderWindow &window, sf::Vector2f nodePosition, int textType, int opacity);
};

class nodeConstants {
public:
    static int nodeDistance;
    static int firstNodePositionX;
    static int initialInsertNodeY;
    static int firstNodePositionY;
    static int nodePositionSpeedAfterInsert;
    static int insertMoveSpeed;
    static int fadeSpeed;
    static int nodeRadius;
    static int textOpacity;
    static sf::Vector2f firstNodePosition;
    static sf::Color flashColor;
    static sf::Color baseColor;
    static float moveDuration;
    static sf::Time flashDuration;
    static void initializeConstants();
};

class arrowConstants {
public:
    static int arrowLengthInit;
    static int arrowHeightInit;
    static sf::Vector2i arrowHeadSize;
    static sf::Vector2i arrowShaftSize;
    static void initializeConstants();
};

class mathConstants {
public:
    static float PI;
    static void initializeConstants();
};

class textConstants {
public:
    static int typeHead;
    static int typeCur;
    static int typeTail;
    static int typeHeadAndTail;
    static int typeHeadAndCur;
    static int typeTailAndCur;
    static int typeTemp;
    static int typeNext;
    static int typeDel;
    static int typeHeadAndTemp;
    static int typeTailAndNext;
    static void initializeConstants();
};

#endif