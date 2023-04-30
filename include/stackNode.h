#ifndef STACKNODE_H
#define STACKNODE_H

#include "constants.h"
#include "text.h"

class stackNode {
private:
    sf::Texture nodeCircleTexture, nodeOutlineTexture;
    textInfo numberText;
public:
    stackNode();
    void drawStackNode(sf::RenderWindow &window, sf::Vector2f nodePosition, int data, int opacity = 255, sf::Color nodeColor = sf::Color::White);
};

#endif