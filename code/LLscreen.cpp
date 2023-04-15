#include "constants.h"
#include "LLscreen.h"
#include "arrow.h"
#include <iostream>

SLL::SLL () {
    numberOfNode = 0;
    int *a = new int(0);
    pHead = nullptr;
}

void SLL::build(int inputNumberOfNode, int *a) {
    Node *cur = pHead;
    for (int countElement = 1; countElement <= inputNumberOfNode; countElement++) {
        int curElement = a[countElement - 1];
        if (countElement == 1) {
            pHead = new Node(curElement);
            cur = pHead;
            pHead->pNext = nullptr;
        }
        else {
            pHead->pNext = new Node(curElement);
            pHead = pHead->pNext;
        }
        pHead->pNext = nullptr;
    }
    numberOfNode = inputNumberOfNode;
    pHead = cur;
}

void SLL::insertAtBeginning(int newData) {
    numberOfNode++;
    if (pHead == nullptr) {
        pHead = new Node(newData);
        pHead->data = newData;
        pHead->pNext = nullptr;
        return;
    }
    Node *newHead = new Node(newData);
    newHead->data = newData;
    newHead->pNext = pHead;
    pHead = newHead;
    return;
}

void SLL::insertAtEnding(int newData) {
    numberOfNode++;
    Node *cur = pHead;
    while (pHead->pNext != nullptr) {
        pHead = pHead->pNext;
    }
    pHead->pNext = new Node(newData);
    pHead->pNext->data = newData;
    pHead->pNext->pNext = nullptr;
    pHead = cur;
    return;
}

void SLL::insertAfterIndex(int newData, int idx) {
    if (idx < 0 || idx > numberOfNode)
        return;
    if (idx == 0) {
        insertAtBeginning(newData);
        return;
    }
    if (idx == numberOfNode) {
        insertAtEnding(newData);
        return;
    }
    Node *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i == idx) {
            Node *leftNode = cur;
            Node *rightNode = cur->pNext;
            Node *newNode = new Node(newData);
            newNode->data = newData;
            newNode->pNext = rightNode;
            leftNode->pNext = newNode;
            break;
        }
        cur = cur->pNext;
    }
    numberOfNode++;
}

void SLL::deleteAtBeginning() {
    if (pHead == nullptr)
        return;
    numberOfNode--;
    if (pHead->pNext == nullptr) {
        delete(pHead);
        pHead = nullptr;
        return;
    }
    Node *temp = pHead; 
    pHead = pHead->pNext;
    delete(temp);
    return;
}

void SLL::deleteAtEnding() {
    if (pHead == nullptr)
        return;
    numberOfNode--;
    if (pHead->pNext == nullptr) {
        delete pHead;
        pHead = nullptr;
        return;
    }
    Node *cur = pHead;
    while (cur->pNext != nullptr && cur->pNext->pNext != nullptr) {
        cur = cur->pNext;
    }
    delete cur->pNext;
    cur->pNext = nullptr;
    return;
}

void SLL::deleteAtIndex(int idx) {
    if (idx < 1 || idx > numberOfNode)
        return;
    if (pHead == nullptr)
        return;
    Node *cur = pHead;
    if (idx == 1) {
        deleteAtBeginning();
        return;
    }
    if (idx == numberOfNode) {
        deleteAtEnding();
        return;
    }
    for (int i = 1; i < numberOfNode; i++) {
        if (i + 1 == idx) {
            Node *leftNode = cur;
            Node *deleteNode = cur->pNext;
            Node *rightNode = deleteNode->pNext;
            leftNode->pNext = rightNode;
            delete(deleteNode);
            deleteNode = nullptr;
            break;
        }
        cur = cur->pNext;
    }
    numberOfNode--;
    return;
}

void SLL::updateAtIndex(int newData, int idx) {
    if (idx < 1 || idx > numberOfNode)
        return;
    Node *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i == idx) {
            cur->data = newData;
            break;
        }
        cur = cur->pNext;
    }
    return;
}

int SLL::searchElement(int searchData) {
    Node *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (cur->data == searchData)
            return i;
        cur = cur->pNext;
    }
    return -1;
}

void SLL::deleteList() {
    while (numberOfNode > 1)
        deleteAtEnding();
    pHead = nullptr;
}

int SLL::getNumberOfNode() {
    return numberOfNode;
}

void SLL::printList() {
    Node *cur = pHead;
    while (pHead != nullptr) {
        std::cout << pHead->data << " ";
        pHead = pHead->pNext;
    }
    std::cout << '\n';
    pHead = cur;
}

void SLL::drawList(sf::RenderWindow &window, int opacity) {
    Node *cur = pHead;
    int countNode = 1;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        cur->drawNode(nodePosition, window, opacity);
        if (countNode == 1) {
            if (numberOfNode == 1)
                cur->drawText(window, nodePosition, textConstants::typeHeadAndTail, nodeConstants::textOpacity);
            else 
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
        }
        else if (countNode == numberOfNode) {
            cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
        }

        if (countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            cur->drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->pNext;
    }
}

void SLL::drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor) {
    Node *cur = pHead;
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
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            else if (i == numberOfNode)
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
        }
        else {
            if (i == 1) {
                if (numberOfNode == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndTail, nodeConstants::textOpacity);
                else if (i == gotoIndex)
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else 
                    cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (i == numberOfNode) {
                if (i == gotoIndex)
                    cur->drawText(window, nodePosition, textConstants::typeTailAndCur, nodeConstants::textOpacity);
                else if (numberOfNode > 1)
                    cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
            else if (i == gotoIndex) {
                cur->drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
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
        cur = cur->pNext;
    }
}

void SLL::drawListWhenInsert(sf::RenderWindow &window, int insertIndex, 
                             int opacity, int nodePositionXAfterInsert) {
    Node *cur = pHead, *insertedNode = nullptr;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < insertIndex) {
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, nodeConstants::flashColor, nodeConstants::baseColor);
        }
        else if (countNode == insertIndex) {
            nodePosition.x += nodePositionXAfterInsert;
            countNode++;
            cur = cur->pNext;
            continue;
        }
        else {
            cur->drawNode(nodePosition, window, opacity);
        }

        if (insertIndex == 1) {
            if (countNode == insertIndex + 1) {
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }
        else {
            if (countNode == insertIndex - 1) {
                if (countNode == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else if (countNode == numberOfNode - 1)
                    cur->drawText(window, nodePosition, textConstants::typeTailAndCur, nodeConstants::textOpacity);
                else 
                    cur->drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == 1) {
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }
        
        if (countNode != insertIndex && countNode != insertIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            if (countNode >= insertIndex)
                cur->drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            else 
                cur->drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::flashColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->pNext;
    }
}

void SLL::drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, sf::Color fadeColor,
                         sf::Vector2f insertNodePosition, int insertNodeOpacity) {
    Node *cur = pHead;
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
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            else if (countNode == numberOfNode)
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
        }
        else {
            if (countNode == insertIndex - 1) {
                if (countNode == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else if (countNode == numberOfNode - 1)
                    cur->drawText(window, nodePosition, textConstants::typeTailAndCur, nodeConstants::textOpacity);
                else 
                    cur->drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == 1) {
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode - 1 && insertIndex == numberOfNode) {
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode && insertIndex != numberOfNode) {
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }

        if (countNode != insertIndex && countNode != insertIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            if (countNode > insertIndex)
                cur->drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            else 
                cur->drawArrowBetweenNode(window, nodePosition, nodePositionRight, fadeColor, opacity);
        }
        else if (countNode == insertIndex - 1 && insertIndex > 1) {
            sf::Vector2f nodePositionLeft = nodePosition;
            sf::Vector2f nodePositionRight = insertNodePosition;
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, insertNodeOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->pNext;
    }
}

void SLL::drawDeleteNodeIndicator(sf::RenderWindow &window, int deleteIndex, int gotoIndex, sf::Color fadeColor) {
    // std::cerr << "delete index, goto index: " << deleteIndex << " " << gotoIndex << "\n";
    Node *cur = pHead;
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
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            else {
                if (i == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
                else if (i == 2) {
                    cur->drawText(window, nodePosition, textConstants::typeTemp, nodeConstants::textOpacity);
                }
                else if (i == numberOfNode) {
                    cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
                }
            }
        }
        else {
            if (gotoIndex == 1) {
                if (i == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else if (i == numberOfNode)
                    cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
            else {
                if (i == gotoIndex - 1) {
                    if (i == 1)
                        cur->drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                    else 
                        cur->drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
                }
                else if (i == gotoIndex) {
                    if (i == numberOfNode)
                        cur->drawText(window, nodePosition, textConstants::typeTailAndNext, nodeConstants::textOpacity);
                    else 
                        cur->drawText(window, nodePosition, textConstants::typeNext, nodeConstants::textOpacity);
                }
                else if (i == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
                else if (i == numberOfNode) 
                    cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
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
        cur = cur->pNext;
    }
}

void SLL::drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity) {
    Node *cur = pHead;
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
                cur->drawText(window, nodePosition, textConstants::typeHead, deleteNodeOpacity);
            else if (countNode == 2)
                cur->drawText(window, nodePosition, textConstants::typeTemp, nodeConstants::textOpacity);
            else if (countNode == numberOfNode)
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
        }
        else {
            if (countNode == removeIndex - 1) {
                if (countNode == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else 
                    cur->drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == removeIndex) {
                cur->drawText(window, nodePosition, textConstants::typeNext, deleteNodeOpacity);
            }
            else if (countNode == 1) {
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;    
        nodePositionRight.x += nodeConstants::nodeDistance;
        if (countNode == 1 && removeIndex == 1) {
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode == removeIndex - 1 && removeIndex - 1 > 0) {
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, deleteNodeOpacity);
        }
        else if (countNode == removeIndex && removeIndex < numberOfNode) {
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode < removeIndex - 1 && countNode < numberOfNode) {
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, opacity);
        }
        else if (countNode > removeIndex && countNode < numberOfNode) {
            cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->pNext;
        countNode++;
    }
}

void SLL::drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, 
                             int nodePositionDiffX, int newArrowOpacity, sf::Color fadeColor) {
                            
    Node *cur = pHead;
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
                    cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
                else 
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndTail, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }
        else {
            if (countNode == removeIndex - 1) {
                if (countNode == 1)
                    cur->drawText(window, nodePosition, textConstants::typeHeadAndCur, nodeConstants::textOpacity);
                else 
                    cur->drawText(window, nodePosition, textConstants::typeCur, nodeConstants::textOpacity);
            }
            else if (countNode == 1) {
                cur->drawText(window, nodePosition, textConstants::typeHead, nodeConstants::textOpacity);
            }
            else if (countNode == numberOfNode) {
                cur->drawText(window, nodePosition, textConstants::typeTail, nodeConstants::textOpacity);
            }
        }

        sf::Vector2f nodePositionLeft = nodePosition;
        if (countNode == removeIndex - 1)
            nodePosition.x += nodePositionDiffX;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;    
        if (countNode < numberOfNode) {
            if (countNode == removeIndex - 1)
                cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, newArrowOpacity);
            else if (countNode < removeIndex)
                cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, nodeOpacity);
            else 
                cur->drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, nodeOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->pNext;
        countNode++;
    }
}

void SLL::drawSearchIndicator(sf::RenderWindow &window, int searchIndex, int gotoIndex, sf::Color fadeColor) {
    drawDeleteNodeIndicator(window, searchIndex, gotoIndex, fadeColor);
}

void createList(SLL &mySLL) {
    int numberOfNode;
    std::cin >> numberOfNode;
    int *a = new int(numberOfNode);
    for (int i = 0; i < numberOfNode; i++) {
        std::cin >> a[i];
        if (a[i] < 0 || a[i] > 99) {
            std::cout << "input integer in range [0..99]\n";
            i--;
        }
    }
    mySLL.build(numberOfNode, a);
}

sf::Color getFadeColor(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer) {
    sf::Time elapsedTime = flashTimer.getElapsedTime();
    float completionPercentage = elapsedTime.asSeconds() / nodeConstants::flashDuration.asSeconds();
    completionPercentage = std::min(completionPercentage, 1.0f);
    sf::Color curColor = sf::Color(startColor.r + (endColor.r - startColor.r) * completionPercentage,
                                   startColor.g + (endColor.g - startColor.g) * completionPercentage,
                                   startColor.b + (endColor.b - startColor.b) * completionPercentage);
    return curColor;
}

void insertNodeProcess(SLL &mySLL, int &insertIndex, int &insertData, sf::Vector2f &insertNodePosition, int &gotoIndex,
                       int &nodePositionXAfterInsert, int &insertNodeOpacity, int &insertNodeColor, sf::Clock &flashTimer) {
    std::cout << "insert index <= n and data to add\n";
    std::cin >> insertIndex >> insertData;
    insertNodePosition.x = nodeConstants::firstNodePositionX * (insertIndex + 1);
    insertNodePosition.y = nodeConstants::firstNodePositionY + nodeConstants::initialInsertNodeY;
    gotoIndex = 1;
    nodePositionXAfterInsert = 0;
    insertNodeOpacity = 0;
    insertNodeColor = rand() % 4;
    flashTimer.restart();
}

void deleteNodeProcess(SLL &mySLL, int &deleteIndex, int &nodeOpacity, int &deleteNodeOpacity, int &gotoIndex,
                       int &nodePositionDiffX, int &newArrowOpacity, sf::Clock &flashTimer) {
    std::cout << "insert index [1..n] to delete: ";
    std::cin >> deleteIndex;
    nodeOpacity = deleteNodeOpacity = 255;
    nodePositionDiffX = nodeConstants::nodeDistance;
    newArrowOpacity = 0;
    gotoIndex = 1;
    flashTimer.restart();
}

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase) {
    if (nodePositionXAfterInsert < nodeConstants::nodeDistance)
        nodePositionXAfterInsert = std::min(nodeConstants::nodeDistance, nodePositionXAfterInsert + nodeConstants::insertMoveSpeed);
    if (insertPhase == 2)
        insertNodeOpacity = std::min(insertNodeOpacity + nodeConstants::fadeSpeed, 255);
    if (insertPhase == 2 && insertNodePosition.y > nodeConstants::firstNodePositionY && insertNodeOpacity == 255)
        insertNodePosition.y = std::max((float) insertNodePosition.y - nodeConstants::insertMoveSpeed, (float) nodeConstants::firstNodePositionY);
}