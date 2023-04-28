#include "DLLScreen.h"

DLL::DLL() {
    pHead = nullptr;
    numberOfNode = 0;
    nodeText.setFont(0);
}

void DLL::build(std::vector <int> &inputValue) {
    DLLNode *cur = pHead;
    numberOfNode = (int) inputValue.size();
    for (int i = 0; i < (int) inputValue.size(); i++) {
        int t = inputValue[i];
        if (pHead == nullptr) {
            pHead = new DLLNode(t);
            cur = pHead;
            pHead->prv = nullptr;
        }
        else {
            cur->nxt = new DLLNode(t);
            cur->nxt->prv = cur;
            cur = cur->nxt;
        }
        cur->nxt = nullptr;
    }
}

void DLL::insertAtBeginning(int value) {
    DLLNode *newNode = new DLLNode(value);
    newNode->nxt = pHead;
    if (pHead != nullptr)
        pHead->prv = newNode;
    pHead = newNode;
    numberOfNode++;
}
void DLL::insertAtEnding(int value) {
    DLLNode *newNode = new DLLNode(value);
    if (pHead == nullptr)
        pHead = newNode;
    else {
        DLLNode *cur = pHead;
        while (cur->nxt != nullptr) {
            cur = cur->nxt;
        }
        cur->nxt = newNode;
        newNode->prv = cur;
    }
    numberOfNode++;
}
void DLL::insertAfterIndex(int index, int value) {
    if (index == 0) {
        insertAtBeginning(value);
        return;
    }
    if (index == numberOfNode) {
        insertAtEnding(value);
        return;
    }
    DLLNode *cur = pHead;
    for (int i = 0; i < index - 1; i++) {
        cur = cur->nxt;
    }
    DLLNode *aft = cur->nxt;
    DLLNode *newNode = new DLLNode(value);
    newNode->nxt = aft;
    aft->prv = newNode;
    cur->nxt = newNode;
    newNode->prv = cur;
    numberOfNode++;
}

void DLL::deleteAtBeginning() {
    if (pHead == nullptr)
        return;
    DLLNode *tmp = pHead;
    pHead = pHead->nxt;
    delete(tmp);
    if (pHead != nullptr)
        pHead->prv = nullptr;
    numberOfNode--;
}
void DLL::deleteAtEnding() {
    if (pHead == nullptr)
        return;
    DLLNode *tmp = pHead;
    while (tmp->nxt != nullptr)
        tmp = tmp->nxt;
    DLLNode *prvNode = tmp->prv;
    if (prvNode != nullptr)
        prvNode->nxt = nullptr;
    delete tmp;
    numberOfNode--;
}
void DLL::deleteAtIndex(int index) {
    if (index > numberOfNode)
        return;
    if (pHead == nullptr)
        return;
    if (index == 1) {
        deleteAtBeginning();
        return;
    }
    if (index == numberOfNode) {
        deleteAtEnding();
        return;
    }
    DLLNode *lft = pHead;
    for (int i = 1; i < index - 1; i++)
        lft = lft->nxt;
    DLLNode *del = lft->nxt;
    DLLNode *rt = del->nxt;
    lft->nxt = rt;
    rt->prv = lft;
    numberOfNode--;
    delete(del);
}


void DLL::updateAtIndex(int index, int element) {
    DLLNode *cur = pHead;
    for (int i = 1; i < index; i++) {
        cur = cur->nxt;
    }
    cur->data = element;
    cur->updateNumberTexture(element);
}

int DLL::searchElement(int element) {
    DLLNode *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (cur->data == element)
            return i;
        cur = cur->nxt;
    }
    return -1;
}

void DLL::printList() {
    DLLNode *cur = pHead;
    while (cur != nullptr) {
        std::cout << cur->data << " ";
        cur = cur->nxt;
    }
    std::cout << "\n\n";
}
void DLL::deleteList() {
    DLLNode *cur = pHead;
    while (cur != nullptr) {
        DLLNode *tmp = cur;
        cur = cur->nxt;
        delete tmp;
    }
    pHead = nullptr;
    numberOfNode = 0;
}
int DLL::getNumberOfNode() {
    return numberOfNode;
}


void DLL::drawList(sf::RenderWindow &window, int opacity) {
    DLLNode *cur = pHead;
    int countNode = 0;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        cur->drawNode(nodePosition, window, opacity);
        
        if (countNode == 0) {
            if (numberOfNode == 1) {
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndTail, opacity);
            }
            else {
                nodeText.drawText(window, nodePosition, textConstants::typeHead, opacity);
            }
        }
        else if (countNode == numberOfNode - 1) {
            nodeText.drawText(window, nodePosition, textConstants::typeTail, opacity);
        }

        if (countNode < numberOfNode - 1) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            cur->drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->nxt;
    }
}

void DLL::drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor) {
    DLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255;
    gotoIndex = std::min(gotoIndex, insertIndex);
    for (int i = 1; i <= numberOfNode; i++) {
        if (i < gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::flashColor, sf::Color::White);
        else if (i == gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, fadeColor, nodeConstants::baseColor);
        else 
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::baseColor, nodeConstants::baseColor);
        
        if (insertIndex == 0) {
            if (i == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            else if (i == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
        }
        else {
            if (i == 1) {
                if (numberOfNode == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndTail, nodeConstants::textOpacity);
                else if (i == gotoIndex)
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else 
                    nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (i == numberOfNode) {
                if (i == gotoIndex)
                    nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, nodeConstants::textOpacity);
                else if (numberOfNode > 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
            else if (i == gotoIndex) {
                nodeText.drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;
        if (i < gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i > gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i == gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
}

void DLL::drawListWhenInsert(sf::RenderWindow &window, int insertIndex, 
                             int opacity, int nodePositionXAfterInsert) {
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < insertIndex) {
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::flashColor, nodeConstants::baseColor);
        }
        else if (countNode == insertIndex) {
            nodePosition.x += nodePositionXAfterInsert;
            countNode++;
            cur = cur->nxt;
            continue;
        }
        else {
            cur->drawNode(nodePosition, window, opacity);
        }

        if (insertIndex == 1) {
            if (countNode == insertIndex + 1) {
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }
        else {
            if (countNode == insertIndex - 1) {
                if (countNode == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else if (countNode == numberOfNode - 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, nodeConstants::textOpacity);
                else 
                    nodeText.drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == 1) {
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }
        
        if (countNode != insertIndex && countNode != insertIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            if (countNode >= insertIndex) {
                cur->drawFwArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
                cur->drawBwArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            }
            else {
                cur->drawFwArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::flashColor, opacity);
                cur->drawBwArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            }
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->nxt;
    }
}

void DLL::drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, sf::Color fadeColor,
                         sf::Vector2f insertNodePosition, int insertNodeOpacity) {
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < insertIndex) {
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           fadeColor, nodeConstants::baseColor);
        }
        else if (countNode > insertIndex)
            cur->drawNode(nodePosition, window, opacity);
        else {
            cur->drawNode2(insertNodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           fadeColor, nodeConstants::baseColor);
            if (insertIndex < numberOfNode) {
                sf::Vector2f nodePositionLeft = insertNodePosition;
                sf::Vector2f nodePositionRight = nodePosition;
                nodePositionRight.x += nodeConstants::nodeDistance;
                cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, insertNodeOpacity);
            }
        }

        if (insertIndex == 1) {
            if (countNode == insertIndex + 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            else if (countNode == numberOfNode && numberOfNode > 1)
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
        }
        else {
            if (countNode == insertIndex - 1) {
                if (countNode == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else if (countNode == numberOfNode - 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, nodeConstants::textOpacity);
                else 
                    nodeText.drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == 1) {
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode - 1 && insertIndex == numberOfNode) {
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode && insertIndex != numberOfNode) {
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }

        if (countNode != insertIndex && countNode != insertIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            if (countNode > insertIndex) {
                cur->drawFwArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
                cur->drawBwArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            }
            else {
                cur->drawFwArrowBetweenNode(window, nodePosition, nodePositionRight, fadeColor, opacity);
                cur->drawBwArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            }
        }
        else if (countNode == insertIndex - 1 && insertIndex > 1) {
            sf::Vector2f nodePositionLeft = nodePosition;
            sf::Vector2f nodePositionRight = insertNodePosition;
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, insertNodeOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->nxt;
    }
}


void DLL::drawDeleteNodeIndicator(sf::RenderWindow &window, int deleteIndex, int gotoIndex, sf::Color fadeColor) {
    // std::cerr << "delete index, goto index: " << deleteIndex << " " << gotoIndex << "\n";
    DLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i < gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::flashColor, sf::Color::White);
        else if (i == gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, fadeColor, nodeConstants::baseColor);
        else 
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::baseColor, nodeConstants::baseColor);
        
        if (deleteIndex == 1) {
            if (numberOfNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            else {
                if (i == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
                else if (i == 2) {
                    nodeText.drawText(window, nodePosition, textConstants::typeTemp, nodeConstants::textOpacity);
                }
                else if (i == numberOfNode) {
                    nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
                }
            }
        }
        else {
            if (gotoIndex == 1) {
                if (i == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else if (i == numberOfNode)
                    nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
            else {
                if (i == gotoIndex - 1) {
                    if (i == 1)
                        nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                    else 
                        nodeText.drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
                }
                else if (i == gotoIndex) {
                    if (i == numberOfNode)
                        nodeText.drawText(window, nodePosition, textConstants::typeTailAndNext, nodeConstants::textOpacity);
                    else 
                        nodeText.drawText(window, nodePosition, textConstants::typeNext, nodeConstants::textOpacity);
                }
                else if (i == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
                else if (i == numberOfNode) 
                    nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }
        
        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;
        if (i < gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i > gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i == gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
}

void DLL::drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity) {
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < removeIndex) {
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           nodeConstants::flashColor, nodeConstants::baseColor);
        }
        else if (countNode > removeIndex) {
            cur->drawNode(nodePosition, window, opacity);
        }
        else {
            cur->drawNode2(nodePosition, window, deleteNodeOpacity, deleteNodeOpacity, deleteNodeOpacity, 
                           nodeConstants::flashColor, nodeConstants::baseColor);
        }

        if (removeIndex == 1) {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, deleteNodeOpacity);
            else if (countNode == 2)
                nodeText.drawText(window, nodePosition, textConstants::typeTemp, nodeConstants::textOpacity);
            else if (countNode == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
        }
        else {
            if (countNode == removeIndex - 1) {
                if (countNode == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else 
                    nodeText.drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == removeIndex) {
                nodeText.drawText(window, nodePosition, textConstants::typeNext, deleteNodeOpacity);
            }
            else if (countNode == 1) {
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;    
        nodePositionRight.x += nodeConstants::nodeDistance;
        if (countNode == 1 && removeIndex == 1) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode == removeIndex - 1 && removeIndex - 1 > 0 && countNode < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, deleteNodeOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode == removeIndex && removeIndex < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode < removeIndex - 1 && countNode < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, opacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        else if (countNode > removeIndex && countNode < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, opacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
        countNode++;
    }
}

void DLL::drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, 
                             int nodePositionDiffX, int newArrowOpacity, sf::Color fadeColor) {
                            
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    if (removeIndex == 1)
        nodePosition.x += nodePositionDiffX;
    while (cur != nullptr) {
        if (countNode < removeIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity,
                           fadeColor, nodeConstants::baseColor);
        else 
            cur->drawNode(nodePosition, window, nodeOpacity);

        if (removeIndex == 1) {
            if (countNode == 1) {
                if (numberOfNode > 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
                else 
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndTail, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }
        else {
            if (countNode == removeIndex - 1) {
                if (countNode == 1)
                    nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else 
                    nodeText.drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == 1) {
                nodeText.drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                nodeText.drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        if (countNode == removeIndex - 1)
            nodePosition.x += nodePositionDiffX;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;    
        if (countNode < numberOfNode) {
            if (countNode == removeIndex - 1) {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, newArrowOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, newArrowOpacity);
            }
            else if (countNode < removeIndex) {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, nodeOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, nodeOpacity);
            }
            else { 
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, nodeOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, nodeOpacity);
            }
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
        countNode++;
    }
}


void DLL::drawSearchIndicator(sf::RenderWindow &window, int searchIndex, int gotoIndex, sf::Color fadeColor) {
    // drawDeleteNodeIndicator(window, searchIndex, gotoIndex, fadeColor, nodeText);
    DLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255, tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = numberOfNode;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i < gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::flashColor, sf::Color::White);
        else if (i == gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, fadeColor, nodeConstants::baseColor);
        else 
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::baseColor, nodeConstants::baseColor);
        
        if (i == gotoIndex) {
            if (gotoIndex == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, maxOpacity);
            else if (gotoIndex == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, maxOpacity);
            else 
                nodeText.drawText(window, nodePosition, textConstants::typeCur, maxOpacity);
        }
        else if (i == 1)
            nodeText.drawText(window, nodePosition, textConstants::typeHead, maxOpacity);
        else if (i == numberOfNode)
            nodeText.drawText(window, nodePosition, textConstants::typeTail, maxOpacity);
        
        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;
        if (i < gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i > gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i == gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
}
void DLL::drawSearchHighlight(sf::RenderWindow &window, int searchIndex, sf::Color fadeColor, 
                             sf::Color textFadeColor, int infoTextOpacity) {
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = numberOfNode;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < tempSearchIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           nodeConstants::flashColor, nodeConstants::baseColor);
        else if (countNode > tempSearchIndex)
            cur->drawNode(nodePosition, window, maxOpacity);
        else {
            if (searchIndex == -1)
                cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity,
                               nodeConstants::flashColor, nodeConstants::baseColor);
            else 
                cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity,
                               fadeColor, textFadeColor);
        }

        if (countNode == tempSearchIndex) {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, maxOpacity);
            else if (countNode == numberOfNode) 
                nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, maxOpacity);
            else 
                nodeText.drawText(window, nodePosition, textConstants::typeCur, maxOpacity);
        }
        else {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, maxOpacity);
            else if (countNode == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTail, maxOpacity);
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;

        if (countNode < numberOfNode) {
            if (countNode < tempSearchIndex) {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            }
            else {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);     
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            }
        }

        countNode++;
        cur = cur->nxt;
        nodePosition.x += nodeConstants::nodeDistance;
    }
}
void DLL::drawSearchRevert(sf::RenderWindow &window, int searchIndex, 
                           sf::Color fadeColor, sf::Color textFadeColor, int infoTextOpacity) {
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = numberOfNode;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < tempSearchIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           fadeColor, nodeConstants::baseColor);
        else if (countNode > tempSearchIndex)
            cur->drawNode(nodePosition, window, maxOpacity);
        else {
            if (searchIndex == -1)
                cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity,
                               fadeColor, nodeConstants::baseColor);
            else 
                cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity,
                               textFadeColor, textFadeColor);
        }

        if (countNode == tempSearchIndex) {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, maxOpacity);
            else if (countNode == numberOfNode) 
                nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, maxOpacity);
            else 
                nodeText.drawText(window, nodePosition, textConstants::typeCur, maxOpacity);
        }
        else {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, maxOpacity);
            else if (countNode == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTail, maxOpacity);
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;

        if (countNode < numberOfNode) {
            if (countNode < tempSearchIndex) {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
                
            }
            else { 
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            }
        }

        countNode++;
        cur = cur->nxt;
        nodePosition.x += nodeConstants::nodeDistance;
    }
}



void DLL::drawUpdateIndicator(sf::RenderWindow &window, int updateIndex, 
                              int gotoIndex, sf::Color fadeColor) {
    DLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i < gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::flashColor, sf::Color::White);
        else if (i == gotoIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, fadeColor, nodeConstants::baseColor);
        else 
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::baseColor, nodeConstants::baseColor);
        
        if (i == gotoIndex) {
            if (gotoIndex == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, maxOpacity);
            else if (gotoIndex == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, maxOpacity);
            else 
                nodeText.drawText(window, nodePosition, textConstants::typeCur, maxOpacity);
        }
        else if (i == 1)
            nodeText.drawText(window, nodePosition, textConstants::typeHead, maxOpacity);
        else if (i == numberOfNode)
            nodeText.drawText(window, nodePosition, textConstants::typeTail, maxOpacity);
        
        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;
        if (i < gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i > gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        else if (i == gotoIndex - 1 && i < numberOfNode) {
            cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
            cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
}
void DLL::drawUpdateChangeNum(sf::RenderWindow &window, int updateIndex, int updateData, 
                              int numberOpacity, sf::Color fadeColor) {
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < updateIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           nodeConstants::flashColor, nodeConstants::baseColor);
        else if (countNode > updateIndex)
            cur->drawNode(nodePosition, window, maxOpacity);
        else {
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, numberOpacity,
                           nodeConstants::flashColor, fadeColor);
        }

        if (countNode == updateIndex) {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, maxOpacity);
            else if (countNode == numberOfNode) 
                nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, maxOpacity);
            else 
                nodeText.drawText(window, nodePosition, textConstants::typeCur, maxOpacity);
        }
        else {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, maxOpacity);
            else if (countNode == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTail, maxOpacity);
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;

        if (countNode < numberOfNode) {
            if (countNode < updateIndex) {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            }
            else {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            }
        }

        countNode++;
        cur = cur->nxt;   
        nodePosition.x += nodeConstants::nodeDistance;
    }
}
void DLL::drawUpdateRevert(sf::RenderWindow &window, int updateIndex, 
                           sf::Color fadeOutlineColor, sf::Color fadeNumberColor) {
    DLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < updateIndex)
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           fadeOutlineColor, nodeConstants::baseColor);
        else if (countNode > updateIndex)
            cur->drawNode(nodePosition, window, maxOpacity);
        else {
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity,
                           fadeOutlineColor, fadeNumberColor);
        }

        if (countNode == updateIndex) {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndCur, maxOpacity);
            else if (countNode == numberOfNode) 
                nodeText.drawText(window, nodePosition, textConstants::typeTailAndCur, maxOpacity);
            else 
                nodeText.drawText(window, nodePosition, textConstants::typeCur, maxOpacity);
        }
        else {
            if (countNode == 1)
                nodeText.drawText(window, nodePosition, textConstants::typeHead, maxOpacity);
            else if (countNode == numberOfNode)
                nodeText.drawText(window, nodePosition, textConstants::typeTail, maxOpacity);
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;

        if (countNode < numberOfNode) {
            if (countNode < updateIndex) {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeOutlineColor, maxOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            }
            else {
                cur->drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
                cur->drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
            }
        }

        countNode++;
        cur = cur->nxt;
        nodePosition.x += nodeConstants::nodeDistance;
    }
}