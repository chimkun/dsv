#ifndef LLSCREEN_H
#define LLSCREEN_H

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
    void drawListAtInsert(sf::RenderWindow &window, int insertedIndex, int opacity, const int &nodeDistance, int insertedNodeDistancDifference);
};

void createList(SLL &mySLL);

#endif