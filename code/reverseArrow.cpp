#include "reverseArrow.h"

reverseArrow::reverseArrow() {
    AB.setSize(sf::Vector2f(3, nodeConstants::nodeRadius + 5));
    BC.setSize(sf::Vector2f(nodeConstants::nodeRadius * 2, 3));
    CD.setSize(sf::Vector2f(3, nodeConstants::nodeRadius * 2));
    DE.setSize(sf::Vector2f(nodeConstants::nodeRadius - 5, 3));

    if (!arrowHead.loadFromFile("src//include//texture//arrowHead.png")) {
        std::cout << "texture file not found! (arrow head)\n";
        exit(-1);
    }
}

void reverseArrow::drawReverseArrow(sf::RenderWindow &window, sf::Vector2f firstNode, sf::Vector2f lastNode, 
                                    sf::Color arrowColor, int opacity) {
    float scaleFactorAB = (lastNode.y - nodeConstants::firstNodePositionY + nodeConstants::nodeRadius + 5) / (nodeConstants::nodeRadius + 5);
    AB.setScale(1.0, scaleFactorAB);
    AB.setOrigin(AB.getLocalBounds().width / 2.0, AB.getLocalBounds().height);
    AB.setPosition(lastNode + sf::Vector2f(0, -nodeConstants::nodeRadius + 5));
    
    float scaleFactorBC = (lastNode.x - firstNode.x + nodeConstants::nodeRadius * 2) / (nodeConstants::nodeRadius * 2);
    BC.setScale(scaleFactorBC, 1.0);
    BC.setOrigin(0, 0);
    BC.setPosition(nodeConstants::firstNodePosition + sf::Vector2f(-nodeConstants::nodeRadius * 2, -nodeConstants::nodeRadius * 2));

    float scaleFactorCD = (firstNode.y - nodeConstants::firstNodePositionY + nodeConstants::nodeRadius * 2) / (nodeConstants::nodeRadius * 2);
    CD.setScale(1.0, scaleFactorCD);
    CD.setOrigin(0, 0);
    CD.setPosition(nodeConstants::firstNodePosition + sf::Vector2f(-nodeConstants::nodeRadius * 2, -nodeConstants::nodeRadius * 2));
    
    DE.setOrigin(0, 0);
    DE.setPosition(firstNode + sf::Vector2f(-nodeConstants::nodeRadius * 2 + 3, -1.5));

    sf::Sprite arrowHeadSprite(arrowHead);
    arrowHeadSprite.setOrigin(arrowHeadSprite.getLocalBounds().width, arrowHeadSprite.getLocalBounds().height/2.0);
    arrowHeadSprite.setPosition(firstNode.x - nodeConstants::nodeRadius, firstNode.y);
    
    arrowColor.a = opacity;
    AB.setFillColor(arrowColor);
    BC.setFillColor(arrowColor);
    CD.setFillColor(arrowColor);
    DE.setFillColor(arrowColor);
    arrowHeadSprite.setColor(arrowColor);

    window.draw(AB);
    window.draw(BC);
    window.draw(CD);
    window.draw(DE);
    window.draw(arrowHeadSprite);
}