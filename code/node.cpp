#include "node.h"

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

void Node::drawArrow(sf::Vector2f nodePosition, sf::RenderWindow &window, int middleOfNodes, int opacity) {
    sf::Texture arrow;
    if (!arrow.loadFromFile("src//include//texture//arrow.png")) {
        std::cout << "Texture file not found! (arrow)";
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