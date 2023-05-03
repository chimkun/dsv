#ifndef CLLSCREEN_H
#define CLLSCREEN_H

#include <cmath>
#include <algorithm>
#include <vector>
#include "CLLNode.h"
#include "text.h"

struct CLLNode {
    int data;
    CLLNode *nxt;
    CLLNode();
    CLLNode(int data);
};

class CLL {
private:
    CLLNode *pHead, *pTail;
    int numberOfNode;
    CLLNodeTexture NodeTexture;
    textInfo nodeText;
public:
    CLL();
    void build(std::vector <int> input);
    void printList();
    void deleteList();
    int getNumberOfNode();

    void insertAtBeginning(int data);
    void insertAtEnding(int data);
    void insertAtMiddle(int index, int data);

    void deleteAtBeginning();
    void deleteAtEnding();
    void deleteAtMiddle(int index);

    void updateIndex(int index, int newElement);
    int searchValue(int value);

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