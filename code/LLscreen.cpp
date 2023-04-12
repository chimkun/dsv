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
    if (idx == numberOfNode) {
        insertAtEnding(newData);
        return;
    }
    Node *cur = pHead;
    for (int i = 1; i <= numberOfNode; i++) {
        if (i == idx) {
            Node *leftNode = cur;
            Node *rightNode = cur->pNext;
            Node *newNode = new Node;
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
sf::Time nodeConstants::flashDuration;
sf::Vector2f nodeConstants::firstNodePosition;
sf::Color nodeConstants::flashColor;
sf::Color nodeConstants::baseColor;

void nodeConstants::initializeConstants() {
    nodeDistance = 174;
    firstNodePositionX = 174;
    initialInsertNodeY = 180;
    firstNodePositionY = 240;
    nodePositionSpeedAfterInsert = 22;
    insertMoveSpeed = 12;
    fadeSpeed = 26;
    nodeRadius = 64;
    moveDuration = 0.5;
    flashDuration = sf::seconds(1.0f);
    firstNodePosition.x = firstNodePositionX, firstNodePosition.y = firstNodePositionY;
    flashColor = sf::Color::Red;
    baseColor = sf::Color::White;
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

void SLL::drawList(sf::RenderWindow &window, int opacity, const int &nodeDistance) {
    Node *cur = pHead;
    int countNode = 1;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        cur->drawNode(nodePosition, window, opacity);
        if (countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeDistance;
            drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeDistance;
        countNode++;
        cur = cur->pNext;
    }
}

void SLL::drawInsertNodeIndicator(sf::RenderWindow &window, int insertIndex, int gotoIndex, sf::Color fadeColor) {
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
        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;
        if (i < gotoIndex - 1 && i < numberOfNode)
            drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, maxOpacity);
        else if (i > gotoIndex - 1 && i < numberOfNode) 
            drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, maxOpacity);
        else if (i == gotoIndex - 1 && i < numberOfNode)
            drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, fadeColor, maxOpacity);
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
        if (countNode != insertIndex && countNode != insertIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            if (countNode >= insertIndex)
                drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            else 
                drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::flashColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->pNext;
    }
}

void SLL::drawInsertNode(sf::RenderWindow &window, int insertIndex, int opacity, 
                         sf::Vector2f insertNodePosition, int insertNodeOpacity) {
    Node *cur = pHead;
    int countNode = 1, maxOpacity = 255;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode < insertIndex) {
            cur->drawNode2(nodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           nodeConstants::flashColor, nodeConstants::baseColor);
        }
        else if (countNode > insertIndex)
            cur->drawNode(nodePosition, window, opacity);
        else {
            cur->drawNode2(insertNodePosition, window, maxOpacity, maxOpacity, maxOpacity, 
                           nodeConstants::flashColor, nodeConstants::baseColor);
            if (insertIndex < numberOfNode) {
                sf::Vector2f nodePositionLeft = insertNodePosition;
                sf::Vector2f nodePositionRight = nodePosition;
                nodePositionRight.x += nodeConstants::nodeDistance;
                drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, insertNodeOpacity);
            }
        }
        if (countNode != insertIndex && countNode != insertIndex - 1 && countNode < numberOfNode) {
            sf::Vector2f nodePositionRight = nodePosition;
            nodePositionRight.x += nodeConstants::nodeDistance;
            if (countNode > insertIndex)
                drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::baseColor, opacity);
            else 
                drawArrowBetweenNode(window, nodePosition, nodePositionRight, nodeConstants::flashColor, opacity);
        }
        else if (countNode == insertIndex - 1 && insertIndex > 1) {
            sf::Vector2f nodePositionLeft = nodePosition;
            sf::Vector2f nodePositionRight = insertNodePosition;
            drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::flashColor, insertNodeOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        countNode++;
        cur = cur->pNext;
    }
}

void SLL::drawDeleteNode(sf::RenderWindow &window, int removeIndex, int opacity, int deleteNodeOpacity) {
    Node *cur = pHead;
    int countNode = 1;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        if (countNode != removeIndex) {
            cur->drawNode(nodePosition, window, opacity);
        }
        else {
            cur->drawNode(nodePosition, window, deleteNodeOpacity);
        }
        sf::Vector2f nodePositionLeft = nodePosition;
        sf::Vector2f nodePositionRight = nodePosition;    
        nodePositionRight.x += nodeConstants::nodeDistance;
        if ((countNode == removeIndex - 1 && removeIndex - 1 > 0) || (countNode == removeIndex && removeIndex < numberOfNode)) {
            drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, deleteNodeOpacity);
        }
        else if (countNode < numberOfNode) {
            drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, opacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->pNext;
        countNode++;
    }
}

void SLL::drawDeleteNodeMove(sf::RenderWindow &window, int removeIndex, int nodeOpacity, int nodePositionDiffX, int newArrowOpacity) {
    Node *cur = pHead;
    int countNode = 1;
    sf::Vector2f nodePosition = nodeConstants::firstNodePosition;
    while (cur != nullptr) {
        cur->drawNode(nodePosition, window, nodeOpacity);
        sf::Vector2f nodePositionLeft = nodePosition;
        if (countNode == removeIndex - 1)
            nodePosition.x += nodePositionDiffX;
        sf::Vector2f nodePositionRight = nodePosition;
        nodePositionRight.x += nodeConstants::nodeDistance;    
        if (countNode < numberOfNode) {
            if (countNode == removeIndex - 1)
                drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, newArrowOpacity);
            else
                drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, nodeConstants::baseColor, nodeOpacity);
        }
        nodePosition.x += nodeConstants::nodeDistance;
        cur = cur->pNext;
        countNode++;
    }
}

void createList(SLL &mySLL) {
    int numberOfNode;
    std::cin >> numberOfNode;
    mySLL.build(numberOfNode);
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

void deleteNodeProcess(SLL &mySLL, int &deleteIndex, int &nodeOpacity, int &deleteNodeOpacity, 
                       int &nodePositionDiffX, int &newArrowOpacity) {
    std::cout << "insert index [1..n] to delete: ";
    std::cin >> deleteIndex;
    nodeOpacity = deleteNodeOpacity = 255;
    nodePositionDiffX = nodeConstants::nodeDistance;
    newArrowOpacity = 0;
}

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                    int &insertNodeOpacity, int insertPhase) {
    if (nodePositionXAfterInsert < nodeConstants::nodeDistance)
        nodePositionXAfterInsert = std::min(nodeConstants::nodeDistance, nodePositionXAfterInsert + nodeConstants::insertMoveSpeed);
    if (insertPhase == 2 && insertNodePosition.y > nodeConstants::firstNodePositionY)
        insertNodePosition.y = std::max((float) insertNodePosition.y - nodeConstants::insertMoveSpeed, (float) nodeConstants::firstNodePositionY);
    if (insertPhase == 2)
        insertNodeOpacity = std::min(insertNodeOpacity + nodeConstants::fadeSpeed, 255);
}

void drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft, 
                          sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
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
    float arrowLength = sqrt(diffX * diffX + diffY * diffY) - 2 * nodeConstants::nodeRadius + 6;
    float arrowScaleFactor = arrowLength / arrowConstants::arrowLengthInit;

    sf::RenderTexture arrowRenderTexture;
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
    arrowSprite.setPosition(intersect_x, intersect_y);

    float rotateAngle = atan2(nodePositionRight.y - nodePositionLeft.y, nodePositionRight.x - nodePositionLeft.x) * 180 / mathConstants::PI;
    arrowSprite.rotate(rotateAngle);
    arrowSprite.setColor(arrowColor);
    sf::Color curArrowColor = arrowSprite.getColor();
    curArrowColor.a = opacity;
    arrowSprite.setColor(curArrowColor);

    window.draw(arrowSprite);
}