#include "CLLScreen.h"

CLLNode::CLLNode() {
    data = -1;
    nxt = nullptr;
}
CLLNode::CLLNode(int data) {
    this->data = data;
}
CLL::CLL() {
    pHead = nullptr;
    numberOfNode = 0;
}
void CLL::build(std::vector <int> input) {
    CLLNode *cur = nullptr;
    for (int i = 0; i < (int) input.size(); i++) {
        int data = input[i];
        if (i == 0) {
            pHead = new CLLNode(data);
            cur = pHead;
        }
        else {
            cur->nxt = new CLLNode(data);
            cur = cur->nxt;
        }
        pTail = cur;
        cur->nxt = nullptr;
    }
    pTail->nxt = pHead;
    numberOfNode = (int) input.size();
}
void CLL::printList() {
    CLLNode *cur = pHead;
    do {
        std::cout << cur->data << " ";
        cur = cur->nxt;
    } while (cur != pHead);
    // std::cerr << "head: " << pHead->data << '\n';
    // std::cerr << "tail: " << pTail->data << '\n';
    std::cout << "\n\n";
}
void CLL::deleteList() {
    while (pHead != nullptr)
        deleteAtBeginning();
}
int CLL::getNumberOfNode() {
    return numberOfNode;
}

void CLL::insertAtBeginning(int data) {
    numberOfNode++;
    CLLNode *newNode = new CLLNode(data);
    if (pHead == nullptr) {
        pHead = pTail = newNode;
        pHead->nxt = pHead;
        return;
    }
    newNode->nxt = pHead;
    pTail->nxt = newNode;
    pHead = newNode;
}
void CLL::insertAtEnding(int data) {
    numberOfNode++;
    CLLNode *newNode = new CLLNode(data);
    if (pHead == nullptr) {
        pHead = pTail = newNode;
        pHead->nxt = pHead;
        return;
    }
    pTail->nxt = newNode;
    newNode->nxt = pHead;
    pTail = newNode;
}
void CLL::insertAtMiddle(int index, int data) {
    if (index == 1) {
        insertAtBeginning(data);
        return;
    }
    if (index == numberOfNode) {
        insertAtEnding(data);
        return;
    }
    numberOfNode++;
    CLLNode *cur = pHead;
    for (int i = 1; i < index - 1; i++) {
        cur = cur->nxt;
    }
    CLLNode *newNode = new CLLNode(data);
    newNode->nxt = cur->nxt;
    cur->nxt = newNode;
}

void CLL::deleteAtBeginning() {
    if (pHead == nullptr)
        return;
    if (pHead->nxt == pHead) {
        delete pHead;
        pHead = pTail = nullptr;
        numberOfNode--;
        return;
    }
    numberOfNode--;
    CLLNode *temp = pHead;
    pHead = pHead->nxt;
    delete temp;
    pTail->nxt = pHead;
}
void CLL::deleteAtEnding() {
    if (pHead == nullptr)
        return;
    if (pHead->nxt == pHead) {
        delete pHead;
        pHead = nullptr;
        numberOfNode--;
        return;
    }
    numberOfNode--;
    CLLNode *cur = pHead;
    while (cur->nxt != pTail)
        cur = cur->nxt;
    cur->nxt = pHead;
    CLLNode *temp = pTail;
    pTail = cur;
    delete temp;
}
void CLL::deleteAtMiddle(int index) {
    if (index == 1) {
        deleteAtBeginning();
        return;
    }
    if (index == numberOfNode) {
        deleteAtEnding();
        return;
    }
    numberOfNode--;
    CLLNode *cur = pHead;
    for (int i = 1; i < index - 1; i++) {
        cur = cur->nxt;
    }
    CLLNode *temp = cur->nxt;
    CLLNode *aft = temp->nxt;
    cur->nxt = aft;
    delete temp;
}

void CLL::updateIndex(int index, int newElement) {
    CLLNode *cur = pHead;
    for (int i = 1; i < index; i++) {
        cur = cur->nxt;
    }
    cur->data = newElement;
}
int CLL::searchValue(int value) {
    CLLNode *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (cur->data == value)
            return i;
        cur = cur->nxt;
    }
    return -1;
}
void CLL::drawList(sf::RenderWindow &window, int opacity) {
    if (pHead == nullptr)
        return;
    CLLNode *cur = pHead;
    int countNode = 1;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        
        if (countNode == 1) {
            if (numberOfNode == 1) {
                nodeText.drawText(window, nodePosition, textConstants::typeHeadAndTail, opacity);
            }
            else {
                nodeText.drawText(window, nodePosition, textConstants::typeHead, opacity);
            }
        }
        else if (countNode == numberOfNode) {
            nodeText.drawText(window, nodePosition, textConstants::typeTail, opacity);
        }

        if (countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            NodeTexture.drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->nxt;
    } while (cur != pHead);
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos, sf::Color::White, opacity);
}

void CLL::drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor) {
    CLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255;
    gotoIndex = std::min(gotoIndex, insertIndex);
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    for (int i = 1; i <= numberOfNode; i++) {
        pTailPos = nodePosition;
        if (i < gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
        else if (i == gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
        else
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        
        if (insertIndex == 0 || insertIndex == numberOfNode) {
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
        if (i < gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
        else if (i > gotoIndex - 1 && i < numberOfNode) 
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        else if (i == gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);
}

void CLL::drawListWhenInsert(sf::RenderWindow &window, int insertIndex, 
                             int opacity, int nodePositionXAfterInsert) {
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        if (countNode < insertIndex) {
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
        }
        else if (countNode == insertIndex) {
            nodePosition.x += nodePositionXAfterInsert;
            countNode++;
            cur = cur->nxt;
            continue;
        }
        else {
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::baseColor, opacity, opacity);
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
            if (countNode >= insertIndex)
                NodeTexture.drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            else 
                NodeTexture.drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::flashColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->nxt;
    } while (cur != pHead);
    if (insertIndex != numberOfNode && insertIndex != 1)
        NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);
    // else 
    //     NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos, sf::Color::White, );
}

void CLL::drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, sf::Color fadeColor,
                         sf::Vector2f insertNodePosition, int insertNodeOpacity) {
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    if (insertIndex == 1)
        pHeadPos = insertNodePosition;
    do {
        pTailPos = nodePosition;
        if (countNode < insertIndex) {
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
        }
        else if (countNode > insertIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::baseColor, 255, opacity);
        else {
            NodeTexture.drawCLLNode(window, insertNodePosition, cur->data, fadeColor);
            if (insertIndex < numberOfNode) {
                sf::Vector2f nodePositionLeft = insertNodePosition;
                sf::Vector2f nodePositionRight = nodePosition;
                nodePositionRight.x += nodeConstants::nodeDistance;
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, insertNodeOpacity);
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
            if (countNode > insertIndex)
                NodeTexture.drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            else 
                NodeTexture.drawArrowBetweenNode(window, nodePosition, nodePositionRight, fadeColor, opacity);
        }
        else if (countNode == insertIndex - 1 && insertIndex > 1) {
            sf::Vector2f nodePositionLeft = nodePosition;
            sf::Vector2f nodePositionRight = insertNodePosition;
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, insertNodeOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->nxt;
    } while (cur != pHead);
    if (insertIndex != numberOfNode)
        NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);
    else if (insertIndex == 1)
        NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos, fadeColor, insertNodeOpacity);
    else if (insertIndex != 1)
        NodeTexture.drawReverseArrow(window, pHeadPos, insertNodePosition);
}

void CLL::drawDeleteNodeIndicator(sf::RenderWindow &window, int deleteIndex, int gotoIndex, sf::Color fadeColor) {
    // std::cerr << "delete index, goto index: " << deleteIndex << " " << gotoIndex << "\n";
    CLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    for (int i = 1; i <= numberOfNode; i++) {
        pTailPos = nodePosition;
        if (i < gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
        else if (i == gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
        else 
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::baseColor);
        
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
        if (i < gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
        else if (i > gotoIndex - 1 && i < numberOfNode) 
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        else if (i == gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);
}

void CLL::drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity) {
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        if (countNode < removeIndex) {
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
        }
        else if (countNode > removeIndex) {
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        }
        else {
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor, deleteNodeOpacity, deleteNodeOpacity);
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
        if (countNode == 1 && removeIndex == 1 && countNode < numberOfNode) {
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode == removeIndex - 1 && removeIndex - 1 > 0 && countNode < numberOfNode) {
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, deleteNodeOpacity);
        }
        else if (countNode == removeIndex && removeIndex < numberOfNode) {
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode < removeIndex - 1 && countNode < numberOfNode) {
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, opacity);
        }
        else if (countNode > removeIndex && countNode < numberOfNode) {
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
        countNode++;
    } while (cur != pHead);
    if (removeIndex == numberOfNode || removeIndex == 1) 
        NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos, sf::Color::White, deleteNodeOpacity);
    else     
        NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);
}

void CLL::drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, 
                             int nodePositionDiffX, int newArrowOpacity, sf::Color fadeColor) { 
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    if (removeIndex == 1)
        nodePosition.x += nodePositionDiffX;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        if (countNode < removeIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
        else 
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);

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
            if (countNode == removeIndex - 1)
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, newArrowOpacity);
            else if (countNode < removeIndex)
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, nodeOpacity);
            else 
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, nodeOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
        countNode++;
    } while (cur != pHead);
    if (removeIndex == numberOfNode + 1 || removeIndex == 1)
        NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos, sf::Color::White, newArrowOpacity);
    else 
        NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);    
}

void CLL::drawSearchIndicator(sf::RenderWindow &window, int searchIndex, int gotoIndex, sf::Color fadeColor) {
    // drawDeleteNodeIndicator(window, searchIndex, gotoIndex, fadeColor, nodeText);
    CLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255, tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = numberOfNode;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    for (int i = 1; i <= numberOfNode; i++) {
        pTailPos = nodePosition;
        if (i < gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
        else if (i == gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
        else 
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        
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
        if (i < gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
        else if (i > gotoIndex - 1 && i < numberOfNode) 
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        else if (i == gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);  
}
void CLL::drawSearchHighlight(sf::RenderWindow &window, int searchIndex, sf::Color fadeColor, 
                             sf::Color textFadeColor, int infoTextOpacity) {
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = numberOfNode;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        if (countNode < tempSearchIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
        else if (countNode > tempSearchIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        else {
            if (searchIndex == -1)
                NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
            else
                NodeTexture.drawCLLNode2(window, nodePosition, cur->data, textFadeColor, fadeColor);
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
            if (countNode < tempSearchIndex)
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
            else 
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }

        countNode++;
        cur = cur->nxt;
        nodePosition.x += nodeConstants::nodeDistance;
    } while (cur != pHead);
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);  
}
void CLL::drawSearchRevert(sf::RenderWindow &window, int searchIndex, 
                           sf::Color fadeColor, sf::Color textFadeColor, int infoTextOpacity) {
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = numberOfNode;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        if (countNode < tempSearchIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
        else if (countNode > tempSearchIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        else {
            if (searchIndex == -1)
                NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
            else 
                NodeTexture.drawCLLNode2(window, nodePosition, cur->data, textFadeColor, textFadeColor);
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
            if (countNode < tempSearchIndex)
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
            else 
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }

        countNode++;
        cur = cur->nxt;
        nodePosition.x += nodeConstants::nodeDistance;
    } while (cur != pHead);
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);  
}
void CLL::drawUpdateIndicator(sf::RenderWindow &window, int updateIndex, 
                              int gotoIndex, sf::Color fadeColor) {
    CLLNode *cur = pHead;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    int maxOpacity = 255;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    for (int i = 1; i <= numberOfNode; i++) {
        pTailPos = nodePosition;
        if (i < gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
            // cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::flashColor, sf::Color::White);
        else if (i == gotoIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeColor);
        else 
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        
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
        if (i < gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
        else if (i > gotoIndex - 1 && i < numberOfNode) 
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        else if (i == gotoIndex - 1 && i < numberOfNode)
            NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);  
}
void CLL::drawUpdateChangeNum(sf::RenderWindow &window, int updateIndex, int updateData, 
                              int numberOpacity, sf::Color fadeColor) {
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        if (countNode < updateIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, nodeConstants::flashColor);
        else if (countNode > updateIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        else {
            NodeTexture.drawCLLNode2(window, nodePosition, cur->data, fadeColor, nodeConstants::flashColor, numberOpacity, 255);
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
            if (countNode < updateIndex)
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
            else 
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }

        countNode++;
        cur = cur->nxt;   
        nodePosition.x += nodeConstants::nodeDistance;
    } while (cur != pHead);
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);  
}
void CLL::drawUpdateRevert(sf::RenderWindow &window, int updateIndex, 
                           sf::Color fadeOutlineColor, sf::Color fadeNumberColor) {
    CLLNode *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    sf::Vector2f pHeadPos = nodePosition, pTailPos;
    do {
        pTailPos = nodePosition;
        if (countNode < updateIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data, fadeOutlineColor);
        else if (countNode > updateIndex)
            NodeTexture.drawCLLNode(window, nodePosition, cur->data);
        else {
            NodeTexture.drawCLLNode2(window, nodePosition, cur->data, fadeNumberColor, fadeOutlineColor);
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
            if (countNode < updateIndex)
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeOutlineColor, maxOpacity);
            else 
                NodeTexture.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        }

        countNode++;
        cur = cur->nxt;
        nodePosition.x += nodeConstants::nodeDistance;
    } while (cur != pHead);
    NodeTexture.drawReverseArrow(window, pHeadPos, pTailPos);  
}