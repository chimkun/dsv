#ifndef LLSCREEN_H
#define LLSCREEN_H

#include <cmath>
#include <algorithm>
#include "node.h"
#include "text.h"

class SLL {
private:
    Node *pHead;
    int numberOfNode;
public:
    SLL ();
    void build(int inputNumberOfNode, int *a);
    void insertAtBeginning(int newData);
    void insertAtEnding(int newData);
    void insertAfterIndex(int newData, int idx);
    void deleteAtBeginning();
    void deleteAtEnding();
    void deleteAtIndex(int idx);
    void updateAtIndex(int newData, int idx);
    int searchElement(int searchData);
    void deleteList();
    int getNumberOfNode();
    void printList();
    void drawList(sf::RenderWindow &window, int opacity, textInfo &nodeText);
    void drawListWhenInsert(sf::RenderWindow &window, int insertIndex, 
                            int opacity, int nodePositionXAfterInsert, textInfo &nodeText);
    void drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor, textInfo &nodeText);
    void drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, sf::Color fadeColor,
                        sf::Vector2f insertNodePosition, int insertNodeOpacity, textInfo &nodeText);
    void drawDeleteNodeIndicator(sf::RenderWindow &window, int deleteIndex, int gotoIndex, sf::Color fadeColor, textInfo &nodeText);
    void drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity, textInfo &nodeText);
    void drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, 
                             int nodePositionDiffX, int newArrowOpacity, sf::Color fadeColor, textInfo &nodeText);
    void drawSearchIndicator(sf::RenderWindow &window, int searchIndex, int gotoIndex, sf::Color fadeColor, textInfo &nodeText);
};

void createList(SLL &mySLL);

sf::Color getFadeColor(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer);

void insertNodeProcess(SLL &mySLL, int &insertIndex, int &insertData, sf::Vector2f &insertNodePosition, int &gotoIndex, 
                       int &nodePositionXAfterInsert, int &insertNodeOpacity, int &insertNodeColor, sf::Clock &flashTimer);

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase);

void deleteNodeProcess(SLL &mySLL, int &deleteIndex, int &nodeOpacity, int &deleteNodeOpacity, int &gotoIndex,
                       int &nodePositionDiffX, int &newArrowOpacity, sf::Clock &flashTimer);

#endif