#include "node.h"

Node::Node() {
    data = -1;
    pNext = nullptr;
}

void Node::drawNode(sf::Vector2f nodePosition, int colorCode, sf::RenderWindow &window) {
    if (data < 0)
        return;

    sf::Texture nodeCircle, nodeOutline;
    if (!nodeCircle.loadFromFile("src//include//texture//circle.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    if (!nodeOutline.loadFromFile("src//include//texture//circle-outline.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    
    sf::Sprite nodeCircleSprite(nodeCircle), nodeOutlineSprite(nodeOutline);
    nodeCircleSprite.setPosition(nodePosition);
    nodeOutlineSprite.setPosition(nodePosition);
    switch (colorCode) {
        case 0:
            nodeCircleSprite.setColor(sf::Color::Red);
            break;
        case 1:
            nodeCircleSprite.setColor(sf::Color::Blue);
            break;
        case 2:
            nodeCircleSprite.setColor(sf::Color::Green);
            break;
        case 3:
            nodeCircleSprite.setColor(sf::Color::Yellow);
            break;
    }
    sf::Color nodeColor = nodeCircleSprite.getColor();
    nodeColor.a = 128;
    nodeCircleSprite.setColor(nodeColor);


    


    window.draw(nodeOutlineSprite);
    window.draw(nodeCircleSprite);
}