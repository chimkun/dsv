#ifndef QUEUESCREEN_H
#define QUEUESCREEN_H

#include <vector>
#include "constants.h"
#include "queueNode.h"

class queueClass {
private:
    std::vector <int> Queue;
    queueNode node;    
public:
    queueClass();

    void createQueue(std::vector <int> &input);
    int peekQueue();
    void pushQueue(int data);
    void popQueue();
    void clearQueue();
    int getQueueSize();

    std::vector <int> getQueue();

    void drawQueue(sf::RenderWindow &window, int opacity);
    void drawQueuePeek(sf::RenderWindow &window, sf::Color peekColor);
    void drawQueuePush(sf::RenderWindow &window, int extraXDistance, int opacity);
    void drawQueuePop(sf::RenderWindow &window, int popNodeOpacity);
};

#endif