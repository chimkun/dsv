#include "codeblock.h"

codeBlock::codeBlock() {}
codeBlock::codeBlock(std::string &codeTextContent) {
    this->codeTextContent = codeTextContent;
    myCodeText = codeText(codeTextContent);
    sf::Color baseColor = sf::Color(55, 55, 55, 110);
    baseBlock = sf::RectangleShape(sf::Vector2f(codeTextConstants::baseWidth, codeTextConstants::baseHeight));
    baseBlock.setFillColor(baseColor);
    baseBlock.setPosition(codeTextConstants::blockPosition);
    this->numberOfBlock = 20;
    for (int i = 0; i < numberOfBlock; i++) {
        highlightBlock[i] = sf::RectangleShape(sf::Vector2f(codeTextConstants::highlightWidth, codeTextConstants::highlightHeight));
        sf::Color highlightColor = sf::Color(222, 222, 24, 130);
        highlightColor.a = 50;
        highlightBlock[i].setFillColor(highlightColor);
        highlightBlock[i].setPosition(codeTextConstants::highlightPosition + sf::Vector2f(0, codeTextConstants::highlightHeight * i));
    }
}

void codeBlock::drawCodeBlock(sf::RenderWindow &window) {
    window.draw(baseBlock);
    myCodeText.drawText(window);
}
void codeBlock::drawHighlight(sf::RenderWindow &window, int l, int r) {
    for (int i = l; i <= r; i++) 
        window.draw(highlightBlock[i]);
}
