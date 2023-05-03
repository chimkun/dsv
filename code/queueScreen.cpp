#include "queueScreen.h"

queueClass::queueClass() {
    int n = rand() % 5 + 3;
    Queue.clear();
    for (int i = 0; i < n; i++) {
        int u = rand() % 100;
        Queue.push_back(u);
    }
}

void queueClass::createQueue(std::vector <int> &input) {
    Queue = input;
}
int queueClass::peekQueue() {
    if (!Queue.empty())
        return Queue[(int) Queue.size() - 1];
    return -1;
}
void queueClass::popQueue() {
    Queue.pop_back();
}
void queueClass::pushQueue(int data) {
    Queue.push_back(data);
    for (int i = (int) Queue.size() - 1; i >= 1; i--) {
        std::swap(Queue[i], Queue[i - 1]);
    }
}
void queueClass::clearQueue() {
    Queue.clear();
}
int queueClass::getQueueSize() {
    return (int) Queue.size();
}

std::vector <int> queueClass::getQueue() {
    return Queue;
}

void queueClass::drawQueue(sf::RenderWindow &window, int opacity) {
    for (int i = 0; i < (int) Queue.size(); i++) {
        sf::Vector2f nodePosition = queueConstants::leftQueue;
        nodePosition += sf::Vector2f(queueConstants::xDistance * i, 0);
        node.drawQueueNode(window, nodePosition, Queue[i], opacity);
        sf::Vector2f textPosition = nodePosition + sf::Vector2f(0, nodeConstants::nodeRadius + 20);
        if (i == 0) {
            if ((int) Queue.size() == 1) {
                std::string frontBack = "front/back";
                nodeText.drawOptionalTextMid(window, frontBack, textPosition, 255, 44);
            }
            else {
                std::string back = "back";
                nodeText.drawOptionalTextMid(window, back, textPosition, 255, 44);
            }
        }
        else if (i == (int) Queue.size() - 1) {
            std::string front = "front";
            nodeText.drawOptionalTextMid(window, front, textPosition, 255, 44);
        }
    }
}
void queueClass::drawQueuePeek(sf::RenderWindow &window, sf::Color peekColor) {
    if (Queue.empty())
        return;
    for (int i = 0; i < (int) Queue.size(); i++) {
        sf::Vector2f nodePosition = queueConstants::leftQueue;
        nodePosition += sf::Vector2f(queueConstants::xDistance * i, 0);
        if (i < (int) Queue.size() - 1)
            node.drawQueueNode(window, nodePosition, Queue[i]);
        sf::Vector2f textPosition = nodePosition + sf::Vector2f(0, nodeConstants::nodeRadius + 20);
        if (i == 0) {
            if ((int) Queue.size() == 1) {
                std::string frontBack = "front/back";
                nodeText.drawOptionalTextMid(window, frontBack, textPosition, 255, 44);
            }
            else {
                std::string back = "back";
                nodeText.drawOptionalTextMid(window, back, textPosition, 255, 44);
            }
        }
        else if (i == (int) Queue.size() - 1) {
            std::string front = "front";
            nodeText.drawOptionalTextMid(window, front, textPosition, 255, 44);
        }
    }
    sf::Vector2f addPosition = queueConstants::leftQueue;
    addPosition += sf::Vector2f(queueConstants::xDistance * ((int) Queue.size() - 1), 0);
    node.drawQueueNode(window, addPosition, Queue[(int) Queue.size() - 1], 255, peekColor);
}
void queueClass::drawQueuePush(sf::RenderWindow &window, int extraXDistance, int opacity) {
    for (int i = 0; i < (int) Queue.size(); i++) {
        sf::Vector2f nodePosition = queueConstants::leftQueue;
        nodePosition += sf::Vector2f(queueConstants::xDistance * i - extraXDistance, 0);
        if (i > 0)
            node.drawQueueNode(window, nodePosition, Queue[i]);
        sf::Vector2f textPosition = nodePosition + sf::Vector2f(0, nodeConstants::nodeRadius + 20);
        if (i == 0) {
            if ((int) Queue.size() == 1) {
                std::string frontBack = "front/back";
                nodeText.drawOptionalTextMid(window, frontBack, textPosition, opacity, 44);
            }
            else {
                std::string back = "back";
                nodeText.drawOptionalTextMid(window, back, textPosition, opacity, 44);
            }
        }
        else if (i == (int) Queue.size() - 1) {
            std::string front = "front";
            nodeText.drawOptionalTextMid(window, front, textPosition, 255, 44);
        }
    }
    sf::Vector2f addPosition = queueConstants::leftQueue;
    addPosition += sf::Vector2f(-extraXDistance, 0);
    node.drawQueueNode(window, addPosition, Queue[0], opacity);
}
void queueClass::drawQueuePop(sf::RenderWindow &window, int popNodeOpacity) {
    for (int i = 0; i < (int) Queue.size(); i++) {
        sf::Vector2f nodePosition = queueConstants::leftQueue;
        nodePosition += sf::Vector2f(queueConstants::xDistance * i, 0);
        if (i < (int) Queue.size() - 1)
            node.drawQueueNode(window, nodePosition, Queue[i]);
        sf::Vector2f textPosition = nodePosition + sf::Vector2f(0, nodeConstants::nodeRadius + 20);
        if (i == 0) {
            if ((int) Queue.size() == 1) {
                std::string frontBack = "front/back";
                nodeText.drawOptionalTextMid(window, frontBack, textPosition, popNodeOpacity, 44);
            }
            else {
                std::string back = "back";
                nodeText.drawOptionalTextMid(window, back, textPosition, 255, 44);
            }
        }
        else if (i == (int) Queue.size() - 1) {
            std::string front = "front";
            nodeText.drawOptionalTextMid(window, front, textPosition, popNodeOpacity, 44);
        }
    }
    sf::Vector2f addPosition = queueConstants::leftQueue;
    addPosition += sf::Vector2f(queueConstants::xDistance * ((int) Queue.size() - 1), 0);
    node.drawQueueNode(window, addPosition, Queue[(int) Queue.size() - 1], popNodeOpacity);
}