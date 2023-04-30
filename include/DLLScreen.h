#ifndef DLLSCREEN_H
#define DLLSCREEN_H

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "text.h"
#include "DLLNode.h"
#include "constants.h"

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
    void deleteList();
    int getNumberOfNode();


    void drawList(sf::RenderWindow &window, int opacity);
    void drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor);
    void drawListWhenInsert(sf::RenderWindow &window, int insertIndex, 
                            int opacity, int nodePositionXAfterInsert);
    void drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, sf::Color fadeColor,
                        sf::Vector2f insertNodePosition, int insertNodeOpacity);
                        
    void drawDeleteNodeIndicator(sf::RenderWindow &window, int deleteIndex, int gotoIndex, sf::Color fadeColor);
    void drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity);
    void drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, 
                             int nodePositionDiffX, int newArrowOpacity, sf::Color fadeColor);

    void drawSearchIndicator(sf::RenderWindow &window, int searchIndex, int gotoIndex, sf::Color fadeColor);
    void drawSearchHighlight(sf::RenderWindow &window, int searchIndex, sf::Color fadeColor, 
                             sf::Color textFadeColor, int infoTextOpacity);
    void drawSearchRevert(sf::RenderWindow &window, int searchIndex, sf::Color fadeColor, 
                          sf::Color textFadeColor, int infoTextOpacity);

    void drawUpdateIndicator(sf::RenderWindow &window, int updateIndex, int gotoIndex, sf::Color fadeColor);
    void drawUpdateChangeNum(sf::RenderWindow &window, int updateIndex, int updateData, 
                             int numberOpacity, sf::Color fadeColor);
    void drawUpdateRevert(sf::RenderWindow &window, int updateIndex, 
                          sf::Color fadeOutlineColor, sf::Color fadeNumberColor);
};

#endif