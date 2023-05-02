#ifndef QUEUENODE_H
#define QUEUENODE_H

#include "constants.h"
#include "text.h"

class queueNode {
private:
    sf::Texture nodeCircleTexture, nodeOutlineTexture;
    textInfo numberText;
public:
    queueNode();
    void drawQueueNode(sf::RenderWindow &window, sf::Vector2f nodePosition, int data, int opacity = 255, sf::Color nodeColor = sf::Color::White);
};


#endif