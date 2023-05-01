#include "node.h"

Node::Node() {
    data = -1;
    // nodeColor = rand() % 4;
    pNext = nullptr;
}
Node::Node(int data) {
    this->data = data;
    // nodeColor = rand() % 4;
    pNext = nullptr;
    // sf::Texture nodeCircle, nodeOutline;
    // if (!nodeCircle.loadFromFile("src//include//texture//circle.png")) {
    //     std::cout << "Texture file not found! (circle)\n";
    //     exit(-1);
    // }
    // if (!nodeOutline.loadFromFile("src//include//texture//circle-outline.png")) {
    //     std::cout << "Texture file not found! (circle outline)\n";
    //     exit(-1);
    // }
    // this->circleTexture = nodeCircle;
    // this->outlineTexture = nodeOutline;

    // int digit1 = -1, digit2 = -1;
    // digit1 = data % 10;
    // if (data > 9)
    //     digit2 = (data / 10) % 10;

    // sf::Texture unitDigitImg, tensDigitImg;
    // char unitDigitChar = (char)(digit1 + '0'), tensDigitChar = (char)(digit2 + '0');
    // std::string unitDigitFile = "default-", tensDigitFile = "default-", pngExtension = ".png";
    // unitDigitFile.push_back(unitDigitChar);
    // tensDigitFile.push_back(tensDigitChar);
    // unitDigitFile += pngExtension;
    // tensDigitFile += pngExtension;
    // sf::Texture tensDigit;
    // sf::Texture unitDigit;
    // // std::cerr << "char: " << unitDigitFile << " " << tensDigitFile << '\n';
    // if (!unitDigit.loadFromFile("src//include//texture//" + unitDigitFile)) {
    //     std::cout << "Texture file not found! (digit)\n";
    //     exit(-1);
    // }

    // sf::Vector2u numberSize = unitDigit.getSize(), nodeSize = nodeCircle.getSize();
    // // std::cerr << "size: " << nodeSize.x << " " << nodeSize.y << '\n';
    // sf::RenderTexture numberOnNode;
    // numberOnNode.create(numberSize.x, numberSize.y);

    // if (digit2 != -1) {
    //     if (!tensDigit.loadFromFile("src//include//texture//" + tensDigitFile)) {
    //         std::cout << "Texture file not found! (digit)";
    //         exit(-1);
    //     }
    //     numberSize.x;
    //     numberOnNode.create(numberSize.x * 2 - 8, numberSize.y);
    //     sf::Sprite unitDigitSprite(unitDigit);
    //     sf::Sprite tensDigitSprite(tensDigit);
    //     unitDigitSprite.setPosition(numberSize.x - 8, 0);
    //     int unitSizeY = unitDigit.getSize().y, tensSizeY = tensDigit.getSize().y;
    //     unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitSizeY));
    //     tensDigitSprite.setTextureRect(sf::IntRect(0, tensDigit.getSize().y, tensDigit.getSize().x, -tensSizeY));
    //     numberOnNode.draw(tensDigitSprite);
    //     numberOnNode.draw(unitDigitSprite);
    // }
    // else {
    //     sf::Sprite unitDigitSprite(unitDigit);
    //     int unitSizeY = unitDigit.getSize().y;
    //     unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitSizeY));
    //     numberOnNode.draw(unitDigitSprite);
    // }
    // this->numberTexture = numberOnNode.getTexture();
}

drawListNode::drawListNode() {}
void drawListNode::initTexture() {
    // sf::Texture tempCircle, tempOutline;
    // if (!tempCircle.loadFromFile("src//include//texture//circle.png")) {
    //     std::cout << "Texture file not found! (circle)\n";
    //     exit(-1);
    // }
    // if (!tempOutline.loadFromFile("src//include//texture//circle-outline.png")) {
    //     std::cout << "Texture file not found! (circle outline)\n";
    //     exit(-1);
    // }
    // this->circleTexture = tempCircle;
    // this->outlineTexture = tempOutline;
    // // std::cerr << "texture size INIT: " << tempCircle.getSize().x << " " << tempCircle.getSize().y << '\n';
    // std::string digitFile = "default-";
    // for (int i = 0; i < 10; i++) {
    //     std::string curFile = digitFile + std::to_string(i) + ".png";
    //     if (!outlineTexture.loadFromFile("src//include//texture//" + curFile)) {
    //         std::cout << "Texture file not found! (digit)\n";
    //         exit(-1);
    //     }
    // }
}
void drawListNode::drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity, int data) {
    if (data < 0)
        return;
    //std::cerr << "data, pos.x: " << data << " " << nodePosition.x << '\n';
    //sf::Texture nodeCircle = circleTexture, nodeOutline = outlineTexture;
    //sf::Sprite nodeCircleSprite(nodeCircle), nodeOutlineSprite(nodeOutline);
    sf::Texture baseTexture = NodeTexture.getBaseTexture();
    // sf::Texture outlineTexture;
    sf::Texture outlineTexture = NodeTexture.getOutlineTexture();
    sf::Sprite nodeCircleSprite(baseTexture), nodeOutlineSprite(outlineTexture);
    // Circle Size: 128 x 128
    std::cerr << "texture size: " << baseTexture.getSize().x << " " << baseTexture.getSize().y << '\n';
    nodeCircleSprite.setOrigin(baseTexture.getSize().x / 2, baseTexture.getSize().y / 2);
    nodeCircleSprite.setPosition(nodePosition);
    nodeOutlineSprite.setOrigin(outlineTexture.getSize().x / 2, outlineTexture.getSize().y / 2);
    nodeOutlineSprite.setPosition(nodePosition);

    int colorCode = data % 4;
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

    sf::Texture unitDigit = NodeTexture.getDigitTexture(digit1);
    sf::Vector2u numberSize = unitDigit.getSize(), nodeSize = baseTexture.getSize();
    sf::RenderTexture numberOnNode;
    numberOnNode.create(numberSize.x, numberSize.y);

    if (digit2 != -1) {
        sf::Texture tensDigit = NodeTexture.getDigitTexture(digit2);
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

    sf::Texture numberTexture = numberOnNode.getTexture();

    //sf::Texture mergedNumber = numberTexture;
    sf::Sprite mergedNumberSprite(numberTexture);
    mergedNumberSprite.setOrigin(numberTexture.getSize().x / 2, numberTexture.getSize().y / 2);
    //std::cerr << "numpos: " << 
    mergedNumberSprite.setPosition(nodePosition);

    // std::cerr << "col no circle\n";
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

void drawListNode::drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window,
                     int innerOpacity, int outlineOpacity, int numberOpacity,
                     sf::Color outlineColor, sf::Color numberColor, int data) {
    if (data < 0)
        return;

    sf::Texture circleTexture = NodeTexture.getBaseTexture();
    sf::Texture outlineTexture = NodeTexture.getOutlineTexture();
    sf::Sprite nodeCircleSprite(circleTexture), nodeOutlineSprite(outlineTexture);
    // Circle Size: 128 x 128
    nodeCircleSprite.setOrigin(circleTexture.getSize().x / 2, circleTexture.getSize().y / 2);
    nodeCircleSprite.setPosition(nodePosition);
    nodeOutlineSprite.setOrigin(outlineTexture.getSize().x / 2, outlineTexture.getSize().y / 2);
    nodeOutlineSprite.setPosition(nodePosition);

    int colorCode = data % 4;
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

    sf::Texture unitDigit = NodeTexture.getDigitTexture(digit1);
    sf::Vector2u numberSize = unitDigit.getSize(), nodeSize = circleTexture.getSize();
    sf::RenderTexture numberOnNode;
    numberOnNode.create(numberSize.x, numberSize.y);

    if (digit2 != -1) {
        sf::Texture tensDigit = NodeTexture.getDigitTexture(digit2);
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

    sf::Texture numberTexture = numberOnNode.getTexture();

    //sf::Texture mergedNumber = numberTexture;
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

void drawListNode::drawArrowBetweenNode(sf::RenderWindow& window, sf::Vector2f nodePositionLeft,
    sf::Vector2f nodePositionRight, sf::Color arrowColor, int opacity) {
    nodeArrow.drawArrowBetweenNode(window, nodePositionLeft, nodePositionRight, arrowColor, opacity);
}
