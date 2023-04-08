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
    if (idx < 0 || idx > numberOfNode)
        return;
    if (idx == 0) {
        insertAtBeginning(newData);
        return;
    }
    Node *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i == idx) {
            if (i == numberOfNode)
                insertAtEnding(newData);
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

int nodeConstants::nodeDistance;
int nodeConstants::firstNodePositionX;
int nodeConstants::initialInsertNodeY;
int nodeConstants::firstNodePositionY;
int nodeConstants::nodePositionSpeedAfterInsert;
int nodeConstants::insertMoveSpeed;
int nodeConstants::fadeSpeed;
int nodeConstants::nodeRadius;
float nodeConstants::moveDuration;
sf::Vector2f nodeConstants::firstNodePosition;

void nodeConstants::initializeConstants() {
    nodeDistance = 174;
    firstNodePositionX = 174;
    initialInsertNodeY = 180;
    firstNodePositionY = 240;
    nodePositionSpeedAfterInsert = 12;
    insertMoveSpeed = 5;
    fadeSpeed = 10;
    nodeRadius = 64;
    moveDuration = 0.5;
    firstNodePosition.x = firstNodePositionX, firstNodePosition.y = firstNodePositionY;
}

int arrowConstants::arrowLengthInit;
int arrowConstants::arrowHeightInit;
sf::Vector2i arrowConstants::arrowHeadSize;
sf::Vector2i arrowConstants::arrowShaftSize;

void arrowConstants::initializeConstants() {
    arrowLengthInit = 52;
    arrowHeightInit = 23;
    arrowHeadSize.x = 19, arrowHeadSize.y = 23;
    arrowShaftSize.x = 97, arrowShaftSize.y = 3;
}

float mathConstants::PI;

void mathConstants::initializeConstants() {
    PI = 3.14159;
}

void SLL::drawList(sf::RenderWindow &window, int opacity, const int &nodeDistance, sf::Vector2f nodePosition) {
    Node *cur = pHead;
    int countColor = 0, countNode = 1;
    // std::cerr << "countNode: " << numberOfNode << '\n';
    while (cur != nullptr) {
        cur->drawNode(nodePosition, window, opacity);
        if (countNode < numberOfNode) {
            // cur->drawArrow(nodePosition, window, nodeDistance/2, opacity);
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeDistance;
            drawArrowBetweenNode(window, nodePosition, nodePositionRight, opacity);
        }
        nodePosition.x += nodeDistance;
        countNode++;
        cur = cur->pNext;
        countColor++;
        countColor %= 4;
    }
}

void SLL::drawListAtInsert(sf::RenderWindow &window, int insertedIndex, int opacity, 
                           sf::Vector2f nodePosition, sf::Vector2f insertNodePosition, int nodePositionXBehindInsert, 
                           int insertNodeOpacity) {
    Node *cur = pHead, *insertedNode = nullptr;
    int countNode = 1, countColor = 0;
    while (cur != nullptr) {
        if (countNode != insertedIndex) {
            cur->drawNode(nodePosition, window, opacity);
        }
        else {
            if (insertedIndex > 1) {
                sf::Vector2f nodePositionLeft = insertNodePosition;
                sf::Vector2f nodePositionRight = nodePosition;
                nodePositionRight.x += nodePositionXBehindInsert;
                // std::cerr << "node L: " << nodePositionLeft.x << " " << nodePositionLeft.y << '\n';
                // std::cerr << "node R: " << nodePositionRight.x << " " << nodePositionRight.y << "\n\n";
                drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, opacity);
            }
            insertedNode = cur;
            nodePosition.x += nodePositionXBehindInsert;
            countNode++;
            cur = cur->pNext;
            continue;
        }
        if (countNode != insertedIndex && countNode != insertedIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            // std::cerr << "here " << countNode << '\n';
            drawArrowBetweenNode(window, nodePosition, nodePositionRight, opacity);
            // cur->drawArrow(nodePosition, window, nodeConstants::nodeDistance/2, opacity);
        }
        else if (countNode == insertedIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionLeft = nodePosition;
            sf::Vector2f nodePositionRight = insertNodePosition;
            drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->pNext;
        countColor++;
        countColor %= 4;
    }
    insertedNode->drawNode(insertNodePosition, window, opacity);
}

void createList(SLL &mySLL) {
    int numberOfNode;
    std::cin >> numberOfNode;
    mySLL.build(numberOfNode);
}

void insertNodeProcess(SLL &mySLL, int &insertIndex, int &insertData, sf::Vector2f &insertNodePosition, 
                       int &nodePositionXAfterInsert, int &insertedNodeOpacity, int &insertedNodeColor) {
    std::cout << "insert index < n and data\n";
    std::cin >> insertIndex >> insertData;
    mySLL.insertAfterIndex(insertData, insertIndex);
    insertIndex++;
    insertNodePosition.x = nodeConstants::firstNodePositionX * insertIndex;
    insertNodePosition.y = nodeConstants::firstNodePositionY + nodeConstants::initialInsertNodeY;
    nodePositionXAfterInsert = 0;
    insertedNodeColor = rand() % 4;
}

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                    int &insertedNodeOpacity) {
    if (nodePositionXAfterInsert < nodeConstants::nodeDistance)
        nodePositionXAfterInsert = std::min(nodeConstants::nodeDistance, nodePositionXAfterInsert + nodeConstants::insertMoveSpeed);
    if (insertNodePosition.y > nodeConstants::firstNodePositionY)
        insertNodePosition.y = std::max((float) insertNodePosition.y - nodeConstants::insertMoveSpeed, (float) nodeConstants::firstNodePositionY);
    if (insertedNodeOpacity < 255)
        insertedNodeOpacity += nodeConstants::fadeSpeed;
}

void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft, sf::Vector2f nodePositionRight, int opacity) {
    sf::Texture arrowShaft, arrowHead;
    // 19, 23
    if (!arrowShaft.loadFromFile("src//include//texture//arrowShaft.png")) {
        std::cout << "Texture file not found! (arrowShaft)";
        exit(-1);
    }
    if (!arrowHead.loadFromFile("src//include//texture//arrowHead.png")) {
        std::cout << "Texture file not found! (arrowHead)";
        exit(-1);
    }
    float diffX = nodePositionRight.x - nodePositionLeft.x, diffY = nodePositionRight.y - nodePositionLeft.y;
    // nodePositionLeft.x += nodeConstants::nodeRadius;
    // nodePositionRight.x -= nodeConstants::nodeRadius;
    // float arrowLength = sqrt(arrowConstants::arrowLengthInit * arrowConstants::arrowLengthInit + diffY * diffY);
    // float arrowScaleFactor = arrowLength / arrowConstants::arrowLengthInit;
    float arrowLength = sqrt(diffX * diffX + diffY * diffY) - 2 * nodeConstants::nodeRadius + 6;
    float arrowScaleFactor = arrowLength / arrowConstants::arrowLengthInit;

    sf::RenderTexture arrowRenderTexture;
    // int textureLength = (int) arrowConstants::arrowLengthInit * arrowScaleFactor + 3;
    int textureLength = arrowLength + 3;
    arrowRenderTexture.create(textureLength + 1, arrowConstants::arrowHeightInit);
    
    sf::Sprite arrowShaftSprite(arrowShaft);
    arrowShaftSprite.setScale(arrowScaleFactor, 1);
    arrowShaftSprite.setOrigin(0, (float) arrowConstants::arrowShaftSize.y/2.0);
    arrowShaftSprite.setPosition(0, (float) arrowConstants::arrowHeightInit/2.0);
    arrowRenderTexture.draw(arrowShaftSprite);
    
    sf::Sprite arrowHeadSprite(arrowHead);
    arrowHeadSprite.setOrigin(0, (float) arrowConstants::arrowHeadSize.y/2);
    arrowHeadSprite.setPosition(textureLength - arrowConstants::arrowHeadSize.x, (float) arrowConstants::arrowHeightInit/2.0);
    arrowRenderTexture.draw(arrowHeadSprite);
    

    sf::Texture arrowTexture = arrowRenderTexture.getTexture();
    sf::Sprite arrowSprite(arrowTexture);
    arrowSprite.setOrigin(0, (float) arrowSprite.getTextureRect().height/2.0);
    float distanceBetweenNode = sqrt(diffX * diffX + diffY * diffY);
    float direction_x = (nodePositionRight.x - nodePositionLeft.x) / distanceBetweenNode;
    float direction_y = (nodePositionRight.y - nodePositionLeft.y) / distanceBetweenNode;
    float intersect_x = nodePositionLeft.x + (nodeConstants::nodeRadius - 3) * direction_x;
    float intersect_y = nodePositionLeft.y + (nodeConstants::nodeRadius - 3) * direction_y;
    // arrowSprite.setPosition(nodePositionLeft.x - 4, nodePositionLeft.y);
    arrowSprite.setPosition(intersect_x, intersect_y);

    float rotateAngle = atan2(nodePositionRight.y - nodePositionLeft.y, nodePositionRight.x - nodePositionLeft.x) * 180 / mathConstants::PI;
    // std::cerr << "angle: " << rotateAngle << '\n';
    arrowSprite.rotate(rotateAngle);
    sf::Color arrowColor = arrowSprite.getColor();
    arrowColor.a = opacity;
    arrowSprite.setColor(arrowColor);

    window.draw(arrowSprite);
}