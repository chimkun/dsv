#include "LLscreen.h"
#include "button.h"
#include <iostream>

SLL::SLL () {
    numberOfNode = 0;
}

void SLL::build(int inputNumberOfNode) {
    Node *cur = pHead;
    for (int countElement = 1; countElement <= inputNumberOfNode; countElement++) {
        int curElement;
        std::cin >> curElement;
        if (curElement < 0 || curElement > 99) {
            std::cout << "Please input integer in range[0, 99]" << '\n';
            countElement--;
        }
        if (countElement == 1) {
            pHead = new Node;
            cur = pHead;
            pHead->pNext = nullptr;
        }
        else {
            pHead->pNext = new Node;
            pHead = pHead->pNext;
        }
        pHead->data = curElement;
        pHead->pNext = nullptr;
    }
    numberOfNode = inputNumberOfNode;
    pHead = cur;
}

void SLL::insertAtBeginning(int newData) {
    numberOfNode++;
    if (pHead == nullptr) {
        pHead = new Node;
        pHead->data = newData;
        pHead->pNext = nullptr;
        return;
    }
    Node *newHead = new Node;
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
    pHead->pNext = new Node;
    pHead->pNext->data = newData;
    pHead->pNext->pNext = nullptr;
    pHead = cur;
    return;
}

void SLL::insertAfterIndex(int newData, int idx) {
    if (idx < 1 || idx > numberOfNode)
        return;
    Node *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i == idx) {
            if (i == numberOfNode)
                insertAtEnding(newData);
            else if (i == 1)
                insertAtBeginning(newData);
            else {
                Node *leftNode = cur;
                Node *rightNode = cur->pNext;
                Node *newNode = new Node;
                newNode->data = newData;
                newNode->pNext = rightNode;
                leftNode->pNext = newNode;
            }
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
    Node *newNode = pHead->pNext;
    delete(pHead);
    pHead = newNode;
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

void SLL::printList() {
    Node *cur = pHead;
    while (pHead != nullptr) {
        std::cout << pHead->data << " ";
        pHead = pHead->pNext;
    }
    std::cout << '\n';
    pHead = cur;
}

void SLL::drawList(sf::RenderWindow &window, int opacity, const int &nodeDistance) {
    Node *cur = pHead;
    int countColor = 0, countNode = 1;
    sf::Vector2f nodePosition(0, 240.0);
    while (cur != nullptr) {
        if (countNode > 1)
            cur->drawArrow(nodePosition, window, nodeDistance/2, opacity);
        nodePosition.x += nodeDistance;
        cur->drawNode(nodePosition, countColor, window, opacity);
        countNode++;
        cur = cur->pNext;
        countColor++;
        countColor %= 4;
    }
}

void SLL::drawListAtInsert(sf::RenderWindow &window, int insertedIndex, int opacity, const int &nodeDistance, int insertedNodeDistanceDifference) {
    Node *cur = pHead, *insertedNode = nullptr;
    int countNode = 1, countColor = 0;
    sf::Vector2f nodePosition(0, 476.0), insertedNodePosition;
    while (cur != nullptr) {
        if (countNode > 1 && countNode != insertedIndex && countNode != insertedIndex + 1) {
            cur->drawArrow(nodePosition, window, nodeDistance/2, opacity);
        }
        nodePosition.x += nodeDistance;
        if (countNode != insertedIndex)
            cur->drawNode(nodePosition, countColor, window, opacity);
        else {
            insertedNodePosition = nodePosition;
            insertedNodePosition.y += 300 - insertedNodeDistanceDifference;
            insertedNode = cur;
        }
        countNode++;
        cur = cur->pNext;
        countColor++;
        countColor %= 4;
    }

    int insertedNodeColor = rand() % 4;
    insertedNode->drawNode(insertedNodePosition, insertedNodeColor, window, opacity);
}

void createList(SLL &mySLL) {
    int numberOfNode;
    std::cin >> numberOfNode;
    mySLL.build(numberOfNode);
}
