#ifndef ARRAYNODE_H
#define ARRAYNODE_H

#include "constants.h"
#include "text.h"

class arrayNode {
private:
    sf::Texture nodeCircleTexture, nodeOutlineTexture;
    textInfo numberText;
public:
    arrayNode();
    void drawArrayNode(sf::RenderWindow &window, sf::Vector2f nodePosition, int data, 
                       int opacity = 255, sf::Color nodeColor = sf::Color::White,
                       int innerOpacity = 255);
    void drawUnusedNode(sf::RenderWindow &window, sf::Vector2f nodePosition, int data = -1,
                        int numberOpacity = 255, sf::Color nodeColor = sf::Color::White);
};

#endif