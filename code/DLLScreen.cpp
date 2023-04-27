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
    if (pHead == nullptr)
        return;
    if (index == 0) {
        deleteAtBeginning();
        return;
    }
    if (index == numberOfNode - 1) {
        deleteAtEnding();
        return;
    }
    numberOfNode--;
    DLLNode *lft = pHead;
    for (int i = 0; i < index - 1; i++)
        lft = lft->nxt;
    DLLNode *del = lft->nxt;
    DLLNode *rt = del->nxt;
    lft->nxt = rt;
    rt->prv = lft;
    delete(del);
}


void DLL::updateAtIndex(int index, int element) {
    DLLNode *cur = pHead;
    for (int i = 0; i < index; i++) {
        cur = cur->nxt;
    }
    cur->data = element;
}

int DLL::searchElement(int element) {
    DLLNode *cur = pHead;
    for (int i = 0; i < numberOfNode; i++) {
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
        if (i < gotoIndex - 1 && i < numberOfNode)
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
        else if (i > gotoIndex - 1 && i < numberOfNode) 
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        else if (i == gotoIndex - 1 && i < numberOfNode)
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->nxt;
    }
}