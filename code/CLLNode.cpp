#include "CLLNode.h"

CLLNodeTexture::CLLNodeTexture() {
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

void CLLNodeTexture::drawCLLNode(sf::RenderWindow &window, sf::Vector2f nodePosition, 
                                 int data, sf::Color nodeColor, int numberOpacity, int opacity) {
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
    outlineSprite.setColor(nodeColor);
    sf::Color circleCol = circleSprite.getColor(), outlineCol = outlineSprite.getColor();
    circleCol.a = opacity, outlineCol.a = opacity;
    circleSprite.setColor(circleCol);
    outlineSprite.setColor(outlineCol);

    window.draw(circleSprite);
    window.draw(outlineSprite);
    std::string dataString = std::to_string(data);
    numberText.drawOptionalTextMid(window, dataString, nodePosition, numberOpacity);
}

void CLLNodeTexture::drawCLLNode2(sf::RenderWindow &window, sf::Vector2f nodePosition, 
                                  int data, sf::Color numberColor, sf::Color nodeColor, 
                                  int numberOpacity, int opacity) {
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
    outlineSprite.setColor(nodeColor);
    sf::Color circleCol = circleSprite.getColor(), outlineCol = outlineSprite.getColor();
    circleCol.a = opacity, outlineCol.a = opacity;
    circleSprite.setColor(circleCol);
    outlineSprite.setColor(outlineCol);

    window.draw(circleSprite);
    window.draw(outlineSprite);
    std::string dataString = std::to_string(data);
    numberText.drawOptionalTextMidCol(window, dataString, nodePosition, numberColor, numberOpacity);
}

void CLLNodeTexture::drawArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                   sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    nodePositionRight.y += 1;
    arrow.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, arrowColor, opacity);
}