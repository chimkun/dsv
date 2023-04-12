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
    void drawList(sf::RenderWindow &window, int opacity, const int &nodeDistance);
    void drawListWhenInsert(sf::RenderWindow &window, int insertIndex, 
                            int opacity, int nodePositionXAfterInsert);
    void drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor);
    void drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, 
                        sf::Vector2f insertNodePosition, int insertNodeOpacity);
    void drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity);
    void drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, int nodePositionDiffX, int newArrowOpacity);
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

void createList(SLL &mySLL);

sf::Color getFadeColor(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer);

void insertNodeProcess(SLL &mySLL, int &insertIndex, int &insertData, sf::Vector2f &insertNodePosition, int &gotoIndex, 
                       int &nodePositionXAfterInsert, int &insertNodeOpacity, int &insertNodeColor, sf::Clock &flashTimer);

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase);

void deleteNodeProcess(SLL &mySLL, int &deleteIndex, int &nodeOpacity, int &deleteNodeOpacity,
                       int &nodePositionMoveSpeed, int &newArrowOpacity);

void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft, 
                          sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);

#endif