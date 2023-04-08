#ifndef LLSCREEN_H
#define LLSCREEN_H

#include <cmath>
#include <algorithm>
#include "node.h"

class SLL {
private:
    Node *pHead;
    int numberOfNode;
public:
    SLL ();
    void build(int inputNumberOfNode);
    void insertAtBeginning(int newData);
    void insertAtEnding(int newData);
    void insertAfterIndex(int newData, int idx);
    void deleteAtBeginning();
    void deleteAtEnding();
    void deleteAtIndex(int idx);
    void updateAtIndex(int newData, int idx);
    int searchElement(int searchData);
    void printList();
    void drawList(sf::RenderWindow &window, int opacity, const int &nodeDistance, sf::Vector2f nodePosition);
    void drawListAtInsert(sf::RenderWindow &window, int insertedIndex, int opacity, 
                          sf::Vector2f nodePosition, sf::Vector2f insertNodePosition, int nodePositionXBehindInsert, 
                          int insertNodeOpacity);
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
    static sf::Vector2f firstNodePosition;
    static float moveDuration;
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

void createList(SLL &mySLL);

void insertNodeProcess(SLL &mySLL, int &insertIndex, int &insertData, sf::Vector2f &insertNodePosition, 
                       int &nodePositionXAfterInsert, int &insertedNodeOpacity, int &insertedNodeColor);

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition, int &insertedNodeOpacity);

void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft, sf::Vector2f nodePositionRight, int opacity);

#endif