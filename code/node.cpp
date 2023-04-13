#include "node.h"

int nodeConstants::nodeDistance;
int nodeConstants::firstNodePositionX;
int nodeConstants::initialInsertNodeY;
int nodeConstants::firstNodePositionY;
int nodeConstants::nodePositionSpeedAfterInsert;
int nodeConstants::insertMoveSpeed;
int nodeConstants::fadeSpeed;
int nodeConstants::nodeRadius;
int nodeConstants::textOpacity;
float nodeConstants::moveDuration;
sf::Time nodeConstants::flashDuration;
sf::Vector2f nodeConstants::firstNodePosition;
sf::Color nodeConstants::flashColor;
sf::Color nodeConstants::baseColor;

void nodeConstants::initializeConstants() {
    nodeDistance = 174;
    firstNodePositionX = 174;
    initialInsertNodeY = 180;
    firstNodePositionY = 240;
    nodePositionSpeedAfterInsert = 22;
    insertMoveSpeed = 12;
    fadeSpeed = 25;
    nodeRadius = 64;
    moveDuration = 0.5;
    textOpacity = 200;
    flashDuration = sf::seconds(1.0f);
    firstNodePosition.x = firstNodePositionX, firstNodePosition.y = firstNodePositionY;
    flashColor = sf::Color::Red;
    baseColor = sf::Color::White;
}

int arrowConstants::arrowLengthInit;
int arrowConstants::arrowHeightInit;
sf::Vector2i arrowConstants::arrowHeadSize;
sf::Vector2i arrowConstants::arrowShaftSize;

void arrowConstants::initializeConstants() {
    arrowLengthInit = 52;
    arrowHeightInit = 23;
    arrowHeadSize.x = 19, arrowHeadSize.y = 23;
    arrowShaftSize.x = 97, arrowShaftSize.y = 3;
}

float mathConstants::PI;

void mathConstants::initializeConstants() {
    PI = 3.14159;
}

int textConstants::typeHead;
int textConstants::typeCur;
int textConstants::typeTail;
int textConstants::typeHeadAndTail;
int textConstants::typeHeadAndCur;
int textConstants::typeTailAndCur;
int textConstants::typeTemp;
int textConstants::typeNext;
int textConstants::typeDel;
int textConstants::typeHeadAndTemp;
int textConstants::typeTailAndNext;

void textConstants::initializeConstants() {
    typeHead = 1, typeCur = 2, typeTail = 3, typeHeadAndTail = 4, typeHeadAndCur = 5, typeTailAndCur = 6;
    typeTemp = 7, typeNext = 8, typeDel = 9, typeHeadAndTemp = 10, typeTailAndNext = 11;
}

Node::Node() {
    data = -1;
    nodeColor = rand() % 4;
    pNext = nullptr;
}

void Node::drawNode(sf::Vector2f nodePosition, sf::RenderWindow &window, int opacity) {
    if (data < 0)
        return;

    sf::Texture nodeCircle, nodeOutline;
    if (!nodeCircle.loadFromFile("src//include//texture//circle.png")) {
        std::cout << "Texture file not found! (circle)\n";
        exit(-1);
    }
    if (!nodeOutline.loadFromFile("src//include//texture//circle-outline.png")) {
        std::cout << "Texture file not found! (circle outline)\n";
        exit(-1);
    }
    
    sf::Sprite nodeCircleSprite(nodeCircle), nodeOutlineSprite(nodeOutline);
    // Circle Size: 128 x 128
    nodeCircleSprite.setOrigin(nodeCircle.getSize().x/2, nodeCircle.getSize().y/2);
    nodeCircleSprite.setPosition(nodePosition);
    nodeOutlineSprite.setOrigin(nodeOutline.getSize().x/2, nodeOutline.getSize().y/2);
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
        digit2 = (data/10) % 10;

    sf::Texture unitDigitImg, tensDigitImg;
    char unitDigitChar = (char) (digit1 + '0'), tensDigitChar = (char) (digit2 + '0');
    std::string unitDigitFile = "default-", tensDigitFile = "default-", pngExtension = ".png";
    unitDigitFile.push_back(unitDigitChar);
    tensDigitFile.push_back(tensDigitChar);
    unitDigitFile += pngExtension;
    tensDigitFile += pngExtension;
    sf::Texture tensDigit;
    sf::Texture unitDigit;
    // std::cerr << "char: " << unitDigitFile << " " << tensDigitFile << '\n';
    if (!unitDigit.loadFromFile("src//include//texture//" + unitDigitFile)) {
        std::cout << "Texture file not found! (digit)\n";
        exit(-1);
    }

    sf::Vector2u numberSize = unitDigit.getSize(), nodeSize = nodeCircle.getSize();
    // std::cerr << "size: " << nodeSize.x << " " << nodeSize.y << '\n';
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
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitDigit.getSize().y));
        tensDigitSprite.setTextureRect(sf::IntRect(0, tensDigit.getSize().y, tensDigit.getSize().x, -tensDigit.getSize().y));
        numberOnNode.draw(tensDigitSprite);
        numberOnNode.draw(unitDigitSprite);
    }
    else {
        sf::Sprite unitDigitSprite(unitDigit);
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitDigit.getSize().y));
        numberOnNode.draw(unitDigitSprite); 
    }
    sf::Texture mergedNumber = numberOnNode.getTexture();
    sf::Sprite mergedNumberSprite(mergedNumber);
    mergedNumberSprite.setOrigin(mergedNumber.getSize().x / 2, mergedNumber.getSize().y / 2);
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

void Node::drawNode2(sf::Vector2f nodePosition, sf::RenderWindow &window, 
                  int innerOpacity, int outlineOpacity, int numberOpacity,
                  sf::Color outlineColor, sf::Color numberColor) {
    if (data < 0)
        return;

    sf::Texture nodeCircle, nodeOutline;
    if (!nodeCircle.loadFromFile("src//include//texture//circle.png")) {
        std::cout << "Texture file not found! (circle)\n";
        exit(-1);
    }
    if (!nodeOutline.loadFromFile("src//include//texture//circle-outline.png")) {
        std::cout << "Texture file not found! (circle outline)\n";
        exit(-1);
    }
    
    sf::Sprite nodeCircleSprite(nodeCircle), nodeOutlineSprite(nodeOutline);
    // Circle Size: 128 x 128
    nodeCircleSprite.setOrigin(nodeCircle.getSize().x/2, nodeCircle.getSize().y/2);
    nodeCircleSprite.setPosition(nodePosition);
    nodeOutlineSprite.setOrigin(nodeOutline.getSize().x/2, nodeOutline.getSize().y/2);
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
        digit2 = (data/10) % 10;

    sf::Texture unitDigitImg, tensDigitImg;
    char unitDigitChar = (char) (digit1 + '0'), tensDigitChar = (char) (digit2 + '0');
    std::string unitDigitFile = "default-", tensDigitFile = "default-", pngExtension = ".png";
    unitDigitFile.push_back(unitDigitChar);
    tensDigitFile.push_back(tensDigitChar);
    unitDigitFile += pngExtension;
    tensDigitFile += pngExtension;
    sf::Texture tensDigit;
    sf::Texture unitDigit;
    // std::cerr << "char: " << unitDigitFile << " " << tensDigitFile << '\n';
    if (!unitDigit.loadFromFile("src//include//texture//" + unitDigitFile)) {
        std::cout << "Texture file not found! (digit)\n";
        exit(-1);
    }

    sf::Vector2u numberSize = unitDigit.getSize(), nodeSize = nodeCircle.getSize();
    // std::cerr << "size: " << nodeSize.x << " " << nodeSize.y << '\n';
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
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitDigit.getSize().y));
        tensDigitSprite.setTextureRect(sf::IntRect(0, tensDigit.getSize().y, tensDigit.getSize().x, -tensDigit.getSize().y));
        numberOnNode.draw(tensDigitSprite);
        numberOnNode.draw(unitDigitSprite);
    }
    else {
        sf::Sprite unitDigitSprite(unitDigit);
        unitDigitSprite.setTextureRect(sf::IntRect(0, unitDigit.getSize().y, unitDigit.getSize().x, -unitDigit.getSize().y));
        numberOnNode.draw(unitDigitSprite); 
    }
    sf::Texture mergedNumber = numberOnNode.getTexture();
    sf::Sprite mergedNumberSprite(mergedNumber);
    mergedNumberSprite.setOrigin(mergedNumber.getSize().x / 2, mergedNumber.getSize().y / 2);
    mergedNumberSprite.setPosition(nodePosition);

    nodeOutlineSprite.setColor(outlineColor);
    mergedNumberSprite.setColor(numberColor);
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

void Node::drawArrow(sf::Vector2f nodePosition, sf::RenderWindow &window, int middleOfNodes, int opacity) {
    sf::Texture arrow;
    if (!arrow.loadFromFile("src//include//texture//arrow.png")) {
        std::cout << "Texture file not found! (arrow)\n";
        exit(-1);
    }
    sf::Sprite arrowSprite(arrow);
    arrowSprite.setOrigin(arrow.getSize().x / 2, arrow.getSize().y / 2);
    arrowSprite.setPosition(nodePosition.x + middleOfNodes, nodePosition.y);
    sf::Color arrowColor = arrowSprite.getColor();
    arrowColor.a = opacity;
    arrowSprite.setColor(arrowColor);
    
    window.draw(arrowSprite);
}

void Node::drawText(sf::RenderWindow &window, sf::Vector2f nodePosition, int textType, int opacity) {
    sf::Font textFont;
    if (!textFont.loadFromFile("src//font//Aller_Bd.ttf")) {
        std::cout << "Font not found!\n";
        exit(-1);
    }
    sf::Text textContent;
    // 1 - head
    // 2 - cur
    // 3 - tail
    // 4 - head/tail
    // 5 - head/cur
    // 6 - tail/cur
    // 7 - temp
    // 8 - next
    // 9 - del
    // 10 - head/temp
    // 11 - tail/temp
    switch (textType) {
        case 1:
            textContent.setString("head");
            break;
        case 2:
            textContent.setString("cur");
            break;
        case 3:
            textContent.setString("tail");
            break;
        case 4:
            textContent.setString("head/tail");
            break;
        case 5:
            textContent.setString("head/cur");
            break;
        case 6:
            textContent.setString("tail/cur");
            break;
        case 7:
            textContent.setString("temp");
            break;
        case 8:
            textContent.setString("next");
            break;
        case 9:
            textContent.setString("del");
            break;
        case 10:
            textContent.setString("head/temp");
        case 11:
            textContent.setString("tail/next");
    }
    int extraHeight = 0;
    std::string textString = textContent.getString();
    for (int i = 0; i < (int) textString.size(); i++) {
        if (textString[i] == 'g' || textString[i] == 'j' || textString[i] == 'p' || textString[i] == 'q' || textString[i] == 'y')
            extraHeight = 10;
    }
    textContent.setFont(textFont);
    textContent.setCharacterSize(44);
    sf::Color textColor = sf::Color::White;
    textColor.a = opacity;
    textContent.setFillColor(textColor);
    sf::FloatRect textRect = textContent.getLocalBounds();
    textContent.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height);
    sf::Vector2f textPosition = nodePosition;
    textPosition.y += nodeConstants::nodeRadius + 40 + extraHeight;
    textContent.setPosition(textPosition);

    window.draw(textContent);
}