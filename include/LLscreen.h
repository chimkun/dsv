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
    void drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, sf::Color fadeColor,
                        sf::Vector2f insertNodePosition, int insertNodeOpacity);
    void drawDeleteNodeIndicator(sf::RenderWindow &window, int deleteIndex, int gotoIndex, sf::Color fadeColor);
    void drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity);
    void drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, 
                             int nodePositionDiffX, int newArrowOpacity, sf::Color fadeColor);
};

void createList(SLL &mySLL);

sf::Color getFadeColor(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer);

void insertNodeProcess(SLL &mySLL, int &insertIndex, int &insertData, sf::Vector2f &insertNodePosition, int &gotoIndex, 
                       int &nodePositionXAfterInsert, int &insertNodeOpacity, int &insertNodeColor, sf::Clock &flashTimer);

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase);

void deleteNodeProcess(SLL &mySLL, int &deleteIndex, int &nodeOpacity, int &deleteNodeOpacity, int &gotoIndex,
                       int &nodePositionDiffX, int &newArrowOpacity, sf::Clock &flashTimer);

void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft, 
                          sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity);

#endif