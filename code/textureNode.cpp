#include "textureNode.h"

TextureNode::TextureNode() {
    if (!nodeCircleTexture.loadFromFile("src//include//texture//circle.png")) {
        std::cout << "texture file not found (circle)\n";
        exit(-1);
    }
    if (!nodeOutlineTexture.loadFromFile("src//include//texture//circle-outline.png")) {
        std::cout << "texture file not found (circle outline)\n";
        exit(-1);
    }

    numberText.setFont(0);
}    
void TextureNode::drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity, int data) {
    sf::Sprite circleSprite(nodeCircleTexture), outlineSprite(nodeOutlineTexture);
    sf::IntRect circleBound = circleSprite.getTextureRect(), outlineBound = outlineSprite.getTextureRect();

    int colorCode = data % 4;
    sf::Color lightPurple(151, 42, 179), lightGreen(67, 211, 25), lightBlue(23, 153, 216), lightPink(238, 34, 145);
    switch (colorCode) {
    case 0:
        circleSprite.setColor(lightPurple);
        break;
    case 1:
        circleSprite.setColor(lightGreen);
        break;
    case 2:
        circleSprite.setColor(lightBlue);
        break;
    case 3:
        circleSprite.setColor(lightPink);
        break;
    }

    circleSprite.setOrigin(circleBound.width/2, circleBound.height/2);
    outlineSprite.setOrigin(outlineBound.width/2, outlineBound.height/2);
    circleSprite.setPosition(nodePosition);
    outlineSprite.setPosition(nodePosition);
    sf::Color circleCol = circleSprite.getColor(), outlineCol = outlineSprite.getColor();
    int numberOpacity = 255;
    circleCol.a = opacity, outlineCol.a = opacity;
    circleSprite.setColor(circleCol);
    outlineSprite.setColor(outlineCol);

    window.draw(circleSprite);
    window.draw(outlineSprite);
    std::string dataString = std::to_string(data);
    numberText.drawOptionalTextMid(window, dataString, nodePosition, numberOpacity);
}
void TextureNode::drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
                         int innerOpacity, int outlineOpacity, int numberOpacity,
                         sf::Color outlineColor, sf::Color numberColor, int data) {
    sf::Sprite circleSprite(nodeCircleTexture), outlineSprite(nodeOutlineTexture);
    sf::IntRect circleBound = circleSprite.getTextureRect(), outlineBound = outlineSprite.getTextureRect();

    int colorCode = data % 4;
    sf::Color lightPurple(151, 42, 179), lightGreen(67, 211, 25), lightBlue(23, 153, 216), lightPink(238, 34, 145);
    switch (colorCode) {
    case 0:
        circleSprite.setColor(lightPurple);
        break;
    case 1:
        circleSprite.setColor(lightGreen);
        break;
    case 2:
        circleSprite.setColor(lightBlue);
        break;
    case 3:
        circleSprite.setColor(lightPink);
        break;
    }

    circleSprite.setOrigin(circleBound.width/2, circleBound.height/2);
    outlineSprite.setOrigin(outlineBound.width/2, outlineBound.height/2);
    circleSprite.setPosition(nodePosition);
    outlineSprite.setPosition(nodePosition);
    outlineSprite.setColor(outlineColor);
    sf::Color circleCol = circleSprite.getColor(), outlineCol = outlineSprite.getColor();
    circleCol.a = innerOpacity, outlineCol.a = outlineOpacity;
    circleCol.a = innerOpacity;
    circleSprite.setColor(circleCol);
    outlineSprite.setColor(outlineCol);

    window.draw(circleSprite);
    window.draw(outlineSprite);
    std::string dataString = std::to_string(data);
    numberText.drawOptionalTextMid(window, dataString, nodePosition, numberOpacity);  
}


void TextureNode::drawArrowBetweenNodeSLL(sf::RenderWindow &window, sf::Vector2f nodePositionLeft,
                                 sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    fwArrow.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, arrowColor, opacity);
}
void TextureNode::drawArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                   sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, arrowColor, opacity);
    drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, arrowColor, opacity);
}
void TextureNode::drawFwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                     sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    float rotateAngleL = atan2(-nodePositionRight.y + nodePositionLeft.y, nodePositionRight.x - nodePositionLeft.x);
    float rotateAngleR = (mathConstants::PI + rotateAngleL) - mathConstants::PI / 12;
    rotateAngleL += mathConstants::PI / 12;
    float newLeftX = nodePositionLeft.x + cos(rotateAngleL) * (nodeConstants::nodeRadius - 5);
    float newLeftY = nodePositionLeft.y - sin(rotateAngleL) * nodeConstants::nodeRadius;
    float newRightX = nodePositionRight.x + cos(rotateAngleR) * (nodeConstants::nodeRadius + 5);
    float newRightY = nodePositionRight.y - sin(rotateAngleR) * nodeConstants::nodeRadius;

    sf::Vector2f fwArrowLeft = sf::Vector2f(newLeftX, newLeftY), fwArrowRight = sf::Vector2f(newRightX, newRightY);
    fwArrow.drawArrowDLLNode(window, fwArrowLeft, fwArrowRight, arrowColor, opacity);
}
void TextureNode::drawBwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                     sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    float rotateAngleL = atan2(-nodePositionRight.y + nodePositionLeft.y, nodePositionRight.x - nodePositionLeft.x);
    float rotateAngleR = (mathConstants::PI + rotateAngleL) + mathConstants::PI / 12;
    rotateAngleL -= mathConstants::PI / 12;
    float newLeftX = nodePositionLeft.x + cos(rotateAngleL) * (nodeConstants::nodeRadius + 5);
    float newLeftY = nodePositionLeft.y - sin(rotateAngleL) * nodeConstants::nodeRadius;
    float newRightX = nodePositionRight.x + cos(rotateAngleR) * (nodeConstants::nodeRadius - 5);
    float newRightY = nodePositionRight.y - sin(rotateAngleR) * nodeConstants::nodeRadius;
    sf::Vector2f fwArrowLeft = sf::Vector2f(newLeftX, newLeftY), fwArrowRight = sf::Vector2f(newRightX, newRightY);
    bwArrow.drawArrowDLLNode(window, fwArrowRight, fwArrowLeft, arrowColor, opacity);;
}