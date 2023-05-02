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
    for (int i = 0; i < (int) Queue.size() - 1; i++) {
        std::swap(Queue[i], Queue[i + 1]);
    }
    Queue.pop_back();
}
void queueClass::pushQueue(int data) {
    Queue.push_back(data);
    for (int i = 0; i < (int) Queue.size() - 1; i++) {
        std::swap(Queue[i], Queue[i + 1]);
    }}
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
    }
}
void queueClass::drawQueuePeek(sf::RenderWindow &window, sf::Color peekColor) {
    if (Queue.empty())
        return;
    for (int i = 0; i < (int) Queue.size() - 1; i++) {
        sf::Vector2f nodePosition = queueConstants::leftQueue;
        nodePosition += sf::Vector2f(queueConstants::xDistance * i, 0);
        node.drawQueueNode(window, nodePosition, Queue[i]);
    }
    sf::Vector2f addPosition = queueConstants::leftQueue;
    addPosition += sf::Vector2f(queueConstants::xDistance * ((int) Queue.size() - 1), 0);
    node.drawQueueNode(window, addPosition, Queue[(int) Queue.size() - 1], 255, peekColor);
}
void queueClass::drawQueuePush(sf::RenderWindow &window, int extraXDistance, int opacity) {
    for (int i = 0; i < (int) Queue.size() - 1; i++) {
        sf::Vector2f nodePosition = queueConstants::leftQueue;
        nodePosition += sf::Vector2f(queueConstants::xDistance * i - extraXDistance, 0);
        node.drawQueueNode(window, nodePosition, Queue[i]);
    }
    sf::Vector2f addPosition = queueConstants::leftQueue;
    addPosition += sf::Vector2f(queueConstants::xDistance * ((int) Queue.size() - 1) - extraXDistance, 0);
    node.drawQueueNode(window, addPosition, Queue[(int) Queue.size() - 1], opacity);
}
void queueClass::drawQueuePop(sf::RenderWindow &window, int popNodeOpacity) {
    for (int i = 0; i < (int) Queue.size() - 1; i++) {
        sf::Vector2f nodePosition = queueConstants::leftQueue;
        nodePosition += sf::Vector2f(queueConstants::xDistance * i, 0);
        node.drawQueueNode(window, nodePosition, Queue[i]);
    }
    sf::Vector2f addPosition = queueConstants::leftQueue;
    addPosition += sf::Vector2f(queueConstants::xDistance * ((int) Queue.size() - 1), 0);
    node.drawQueueNode(window, addPosition, Queue[(int) Queue.size() - 1], popNodeOpacity);
}