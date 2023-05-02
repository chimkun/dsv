#include "DLLNode.h"

DLLNode::DLLNode() {
    data = -1;
    nodeColor = rand() % 4;
    this->nxt = nullptr;
    this->prv = nullptr;
}
DLLNode::DLLNode(int data) {
    this->data = data;
    nodeColor = rand() % 4;
    this->nxt = nullptr;
    this->prv = nullptr;
    sf::Texture nodeCircle, nodeOutline;
    if (!nodeCircle.loadFromFile("src//include//texture//circle.png")) {
        std::cout << "Texture file not found! (circle)\n";
        exit(-1);
    }
    if (!nodeOutline.loadFromFile("src//include//texture//circle-outline.png")) {
        std::cout << "Texture file not found! (circle outline)\n";
        exit(-1);
    }
    this->circleTexture = nodeCircle;
    this->outlineTexture = nodeOutline;

    int digit1 = -1, digit2 = -1;
    digit1 = data % 10;
    if (data > 9)
        digit2 = (data / 10) % 10;

    sf::Texture unitDigitImg, tensDigitImg;
    char unitDigitChar = (char)(digit1 + '0'), tensDigitChar = (char)(digit2 + '0');
    std::string unitDigitFile = "default-", tensDigitFile = "default-", pngExtension = ".png";
    unitDigitFile.push_back(unitDigitChar);
    tensDigitFile.push_back(tensDigitChar);
    unitDigitFile += pngExtension;
    tensDigitFile += pngExtension;
    sf::Texture tensDigit;
    sf::Texture unitDigit;
    if (!unitDigit.loadFromFile("src//include//texture//" + unitDigitFile)) {
        std::cout << "Texture file not found! (digit)\n";
        exit(-1);
    }

    sf::Vector2u numberSize = unitDigit.getSize(), nodeSize = nodeCircle.getSize();
    sf::RenderTexture numberOnNode;
    numberOnNode.create(numberSize.x, numberSize.y);

    if (digit2 != -1) {
        if (!tensDigit.loadFromFile("src//include//texture//" + tensDigitFile)) {
            std::cout << "Texture file not found! (digit)";
            exit(-1);
        }
        numberSize.x;
        numberOnNode.create(numberSize.x * 2 - 8, numberSize.y);
        sf::Sprite unitDigitSprite(unitDigit);
        sf::Sprite tensDigitSprite(tensDigit);
        unitDigitSprite.setPosition(numberSize.x - 8, 0);
        int unitSizeY = unitDigit.getSize().y, tensSizeY = tensDigit.getSize().y;
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitSizeY));
        tensDigitSprite.setTextureRect(sf::IntRect(0, tensDigit.getSize().y, tensDigit.getSize().x, -tensSizeY));
        numberOnNode.draw(tensDigitSprite);
        numberOnNode.draw(unitDigitSprite);
    }
    else {
        sf::Sprite unitDigitSprite(unitDigit);
        int unitSizeY = unitDigit.getSize().y;
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitSizeY));
        numberOnNode.draw(unitDigitSprite);
    }
    this->numberTexture = numberOnNode.getTexture();
}

void DLLNode::updateNumberTexture(int data) {
    int digit1 = -1, digit2 = -1;
    digit1 = data % 10;
    if (data > 9)
        digit2 = (data / 10) % 10;

    sf::Texture unitDigitImg, tensDigitImg;
    char unitDigitChar = (char)(digit1 + '0'), tensDigitChar = (char)(digit2 + '0');
    std::string unitDigitFile = "default-", tensDigitFile = "default-", pngExtension = ".png";
    unitDigitFile.push_back(unitDigitChar);
    tensDigitFile.push_back(tensDigitChar);
    unitDigitFile += pngExtension;
    tensDigitFile += pngExtension;
    sf::Texture tensDigit;
    sf::Texture unitDigit;
    if (!unitDigit.loadFromFile("src//include//texture//" + unitDigitFile)) {
        std::cout << "Texture file not found! (digit)\n";
        exit(-1);
    }

    sf::Vector2u numberSize = unitDigit.getSize();
    sf::RenderTexture numberOnNode;
    numberOnNode.create(numberSize.x, numberSize.y);

    if (digit2 != -1) {
        if (!tensDigit.loadFromFile("src//include//texture//" + tensDigitFile)) {
            std::cout << "Texture file not found! (digit)";
            exit(-1);
        }
        numberSize.x;
        numberOnNode.create(numberSize.x * 2 - 8, numberSize.y);
        sf::Sprite unitDigitSprite(unitDigit);
        sf::Sprite tensDigitSprite(tensDigit);
        unitDigitSprite.setPosition(numberSize.x - 8, 0);
        int unitSizeY = unitDigit.getSize().y, tensSizeY = tensDigit.getSize().y;
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitSizeY));
        tensDigitSprite.setTextureRect(sf::IntRect(0, tensDigit.getSize().y, tensDigit.getSize().x, -tensSizeY));
        numberOnNode.draw(tensDigitSprite);
        numberOnNode.draw(unitDigitSprite);
    }
    else {
        sf::Sprite unitDigitSprite(unitDigit);
        int unitSizeY = unitDigit.getSize().y;
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitSizeY));
        numberOnNode.draw(unitDigitSprite);
    }
    this->numberTexture = numberOnNode.getTexture();
}

void DLLNode::drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity) {
    if (data < 0)
        return;
    sf::Sprite nodeCircleSprite(circleTexture), nodeOutlineSprite(outlineTexture);
    // Circle Size: 128 x 128
    nodeCircleSprite.setOrigin(circleTexture.getSize().x / 2, circleTexture.getSize().y / 2);
    nodeCircleSprite.setPosition(nodePosition);
    nodeOutlineSprite.setOrigin(outlineTexture.getSize().x / 2, outlineTexture.getSize().y / 2);
    nodeOutlineSprite.setPosition(nodePosition);

    int colorCode = nodeColor;
    sf::Color lightPurple(151, 42, 179), lightGreen(67, 211, 25), lightBlue(23, 153, 216), lightPink(238, 34, 145);
    switch (colorCode) {
    case 0:
        nodeCircleSprite.setColor(lightPurple);
        break;
    case 1:
        nodeCircleSprite.setColor(lightGreen);
        break;
    case 2:
        nodeCircleSprite.setColor(lightBlue);
        break;
    case 3:
        nodeCircleSprite.setColor(lightPink);
        break;
    }

    int digit1 = -1, digit2 = -1;
    digit1 = data % 10;
    if (data > 9)
        digit2 = (data / 10) % 10;

    sf::Sprite mergedNumberSprite(numberTexture);
    mergedNumberSprite.setOrigin(numberTexture.getSize().x / 2, numberTexture.getSize().y / 2);
    mergedNumberSprite.setPosition(nodePosition);

    sf::Color outlineColor = nodeOutlineSprite.getColor();
    outlineColor.a = opacity;
    sf::Color circleColor = nodeCircleSprite.getColor();
    circleColor.a = opacity;
    sf::Color numberColor = mergedNumberSprite.getColor();
    numberColor.a = opacity;
    nodeOutlineSprite.setColor(outlineColor);
    nodeCircleSprite.setColor(circleColor);
    mergedNumberSprite.setColor(numberColor);
    window.draw(nodeOutlineSprite);
    window.draw(nodeCircleSprite);
    window.draw(mergedNumberSprite);
}

void DLLNode::drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window,
                     int innerOpacity, int outlineOpacity, int numberOpacity,
                     sf::Color outlineColor, sf::Color numberColor) {
    if (data < 0)
        return;

    sf::Sprite nodeCircleSprite(circleTexture), nodeOutlineSprite(outlineTexture);
    // Circle Size: 128 x 128
    nodeCircleSprite.setOrigin(circleTexture.getSize().x / 2, circleTexture.getSize().y / 2);
    nodeCircleSprite.setPosition(nodePosition);
    nodeOutlineSprite.setOrigin(outlineTexture.getSize().x / 2, outlineTexture.getSize().y / 2);
    nodeOutlineSprite.setPosition(nodePosition);

    int colorCode = nodeColor;
    sf::Color lightPurple(151, 42, 179), lightGreen(67, 211, 25), lightBlue(23, 153, 216), lightPink(238, 34, 145);
    switch (colorCode) {
    case 0:
        nodeCircleSprite.setColor(lightPurple);
        break;
    case 1:
        nodeCircleSprite.setColor(lightGreen);
        break;
    case 2:
        nodeCircleSprite.setColor(lightBlue);
        break;
    case 3:
        nodeCircleSprite.setColor(lightPink);
        break;
    }

    int digit1 = -1, digit2 = -1;
    digit1 = data % 10;
    if (data > 9)
        digit2 = (data / 10) % 10;

    sf::Sprite mergedNumberSprite(numberTexture);
    mergedNumberSprite.setOrigin(numberTexture.getSize().x / 2, numberTexture.getSize().y / 2);
    mergedNumberSprite.setPosition(nodePosition);
    mergedNumberSprite.setColor(numberColor);
    nodeOutlineSprite.setColor(outlineColor);

    sf::Color curOutlineColor = nodeOutlineSprite.getColor();
    curOutlineColor.a = outlineOpacity;
    sf::Color curCircleColor = nodeCircleSprite.getColor();
    curCircleColor.a = innerOpacity;
    sf::Color curNumberColor = mergedNumberSprite.getColor();
    curNumberColor.a = numberOpacity;
    nodeOutlineSprite.setColor(curOutlineColor);
    nodeCircleSprite.setColor(curCircleColor);
    mergedNumberSprite.setColor(curNumberColor);
    window.draw(nodeOutlineSprite);
    window.draw(nodeCircleSprite);
    window.draw(mergedNumberSprite);
}

// void DLLNode::drawArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
//                                    sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
//     sf::Vector2f fwArrowLeft = nodePositionLeft, fwArrowRight = nodePositionRight;
//     fwArrowLeft.x -= 5, fwArrowLeft.y -= 18;
//     fwArrowRight.x += 5, fwArrowRight.y -= 17;
//     fwArrow.drawArrowBetweenNode(window, fwArrowLeft, fwArrowRight, arrowColor, opacity);
//     sf::Vector2f bwArrowLeft = nodePositionLeft, bwArrowRight = nodePositionRight;
//     bwArrowLeft.x -= 5, bwArrowLeft.y += 17;
//     bwArrowRight.x += 5, bwArrowRight.y += 18;
//     bwArrow.drawArrowBetweenNode(window, bwArrowRight, bwArrowLeft, arrowColor, opacity);
// }

// void DLLNode::drawFwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
//                                      sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
//     sf::Vector2f fwArrowLeft = nodePositionLeft, fwArrowRight = nodePositionRight;
//     fwArrowLeft.x -= 5, fwArrowLeft.y -= 18;
//     fwArrowRight.x += 5, fwArrowRight.y -= 17;
//     fwArrow.drawArrowBetweenNode(window, fwArrowLeft, fwArrowRight, arrowColor, opacity);
// }

// void DLLNode::drawBwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
//                                      sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
//     sf::Vector2f bwArrowLeft = nodePositionLeft, bwArrowRight = nodePositionRight;
//     bwArrowLeft.x -= 5, bwArrowLeft.y += 17;
//     bwArrowRight.x += 5, bwArrowRight.y += 18;
//     bwArrow.drawArrowBetweenNode(window, bwArrowRight, bwArrowLeft, arrowColor, opacity);;
// }

void DLLNode::drawArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                   sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    // sf::Vector2f fwArrowLeft = nodePositionLeft, fwArrowRight = nodePositionRight;
    // fwArrowLeft.x -= 5, fwArrowLeft.y -= 18;
    // fwArrowRight.x += 5, fwArrowRight.y -= 17;
    // fwArrow.drawArrowBetweenNode(window, fwArrowLeft, fwArrowRight, arrowColor, opacity);
    // sf::Vector2f bwArrowLeft = nodePositionLeft, bwArrowRight = nodePositionRight;
    // bwArrowLeft.x -= 5, bwArrowLeft.y += 17;
    // bwArrowRight.x += 5, bwArrowRight.y += 18;
    // // std::cerr << "what it was: " << fwArrowLeft.x << " " << fwArrowLeft.y << "    " << fwArrowLeft
    // bwArrow.drawArrowBetweenNode(window, bwArrowRight, bwArrowLeft, arrowColor, opacity);
    drawFwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, arrowColor, opacity);
    drawBwArrowBetweenNode(window, nodePositionLeft, nodePositionRight, arrowColor, opacity);
}

void DLLNode::drawFwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                     sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    float rotateAngleL = atan2(-nodePositionRight.y + nodePositionLeft.y, nodePositionRight.x - nodePositionLeft.x);
    float rotateAngleR = (mathConstants::PI + rotateAngleL) - mathConstants::PI / 12;
    rotateAngleL += mathConstants::PI / 12;
    float newLeftX = nodePositionLeft.x + cos(rotateAngleL) * (nodeConstants::nodeRadius - 5);
    float newLeftY = nodePositionLeft.y - sin(rotateAngleL) * nodeConstants::nodeRadius;
    float newRightX = nodePositionRight.x + cos(rotateAngleR) * (nodeConstants::nodeRadius + 5);
    float newRightY = nodePositionRight.y - sin(rotateAngleR) * nodeConstants::nodeRadius;

    sf::Vector2f fwArrowLeft = sf::Vector2f(newLeftX, newLeftY), fwArrowRight = sf::Vector2f(newRightX, newRightY);
    // if (nodePositionLeft.y != nodePositionRight.y) {
        // std::cerr << "angle: " << rotateAngleL << ' ' << rotateAngleR << '\n';
        // std::cerr << "init: " << nodePositionLeft.x << " " << nodePositionLeft.y << '\n';
        // std::cerr << "new: " << newLeftX << " " << newLeftY << "\n";
        // std::cerr << "right: " << nodePositionRight.x << " " << nodePositionRight.y << '\n';
        // std::cerr << "new right: " << newRightX << " " << newRightY << '\n' << '\n';
    // }
    // fwArrowLeft.x -= 5, fwArrowLeft.y -= 18;
    // fwArrowRight.x += 5, fwArrowRight.y -= 17;
    fwArrow.drawArrowDLLNode(window, fwArrowLeft, fwArrowRight, arrowColor, opacity);
}

void DLLNode::drawBwArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
                                     sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    float rotateAngleL = atan2(-nodePositionRight.y + nodePositionLeft.y, nodePositionRight.x - nodePositionLeft.x);
    float rotateAngleR = (mathConstants::PI + rotateAngleL) + mathConstants::PI / 12;
    rotateAngleL -= mathConstants::PI / 12;
    float newLeftX = nodePositionLeft.x + cos(rotateAngleL) * (nodeConstants::nodeRadius + 5);
    float newLeftY = nodePositionLeft.y - sin(rotateAngleL) * nodeConstants::nodeRadius;
    float newRightX = nodePositionRight.x + cos(rotateAngleR) * (nodeConstants::nodeRadius - 5);
    float newRightY = nodePositionRight.y - sin(rotateAngleR) * nodeConstants::nodeRadius;

    // if (nodePositionLeft.y != nodePositionRight.y) {
        // std::cerr << "angle REV: " << rotateAngleL << " " << rotateAngleR << '\n';
        // std::cerr << "init: " << nodePositionLeft.x << " " << nodePositionLeft.y << '\n';
        // std::cerr << "new: " << newLeftX << " " << newLeftY << "\n";
        // std::cerr << "right: " << nodePositionRight.x << " " << nodePositionRight.y << '\n';
        // std::cerr << "new right: " << newRightX << " " << newRightY << '\n' << '\n';
    // }
    sf::Vector2f fwArrowLeft = sf::Vector2f(newLeftX, newLeftY), fwArrowRight = sf::Vector2f(newRightX, newRightY);
    bwArrow.drawArrowDLLNode(window, fwArrowRight, fwArrowLeft, arrowColor, opacity);;
}