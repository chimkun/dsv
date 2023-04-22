#ifndef CODETEXT_H
#define CODETEXT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "constants.h"
#include "text.h"

class codeText {
private:
    textInfo codeTextInfo;
    std::string codeTextContent;
    sf::Vector2f textPosition;
public:
    codeText();
    codeText(std::string &textContent);
    void drawText(sf::RenderWindow &window);
};

#endif
