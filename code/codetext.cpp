#include "codetext.h"

codeText::codeText() {
    codeTextInfo = textInfo(3);
}
codeText::codeText(std::string &codeTextContent) {
    codeTextInfo = textInfo(3);
    this->codeTextContent = codeTextContent;
    this->textPosition = codeTextConstants::textPosition;
}

void codeText::drawText(sf::RenderWindow &window) {
    sf::Vector2f textOrigin = sf::Vector2f(0, 0);
    codeTextInfo.drawOptionalTextSize(window, this->codeTextContent, textOrigin,
                                      this->textPosition, 255, codeTextConstants::textSize);
}