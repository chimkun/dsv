#include "arrow.h"
#include <cmath>

Arrow::Arrow () {
    sf::Texture arrowShaftTexture, arrowHeadTexture;
    // 19 x 23
    std::cerr << "here\n";
    if (!arrowShaftTexture.loadFromFile("src//include//texture//arrowShaft.png")) {
        std::cout << "Texture file not found! (arrowShaft)";
        exit(-1);
    }
    std::cerr << "shaft\n";
    if (!arrowHeadTexture.loadFromFile("src//include//texture//arrowHead.png")) {
        std::cout << "Texture file not found! (arrowHead)";
        exit(-1);
    }
    this->arrowShaft = arrowShaftTexture;
    this->arrowHead = arrowHeadTexture;
}

void Arrow::drawArrowBetweenNode(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                              sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    // 19, 23
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