#ifndef DLLSCREEN_H
#define DLLSCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "text.h"
#include "DLLNode.h"

class DLL {
private:
    DLLNode *pHead;
    int numberOfNode;
    textInfo nodeText;
public:
    DLL();
    void build(std::vector <int> &inputValue);
    void insertAtBeginning(int value);
    void insertAtEnding(int value);
    void insertAfterIndex(int index, int value);

    void deleteAtBeginning();
    void deleteAtEnding();
    void deleteAtIndex(int index);

    void updateAtIndex(int index, int element);
    int searchElement(int element);
    void printList();


    void drawList(sf::RenderWindow &window, int opacity);
    void drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor);
};

#endif