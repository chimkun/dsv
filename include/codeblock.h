#ifndef CODEBLOCK_H
#define CODEBLOCK_H

#include <SFML/Graphics.hpp>
#include "codetext.h"

class codeBlock {
private:
    codeText myCodeText;
    std::string codeTextContent;
    sf::RectangleShape baseBlock;
    int numberOfBlock;
    sf::RectangleShape highlightBlock[20];
public:
    codeBlock();
    codeBlock(std::string &codeTextContent);

    void drawCodeBlock(sf::RenderWindow &window);
    void drawHighlight(sf::RenderWindow &window, int l, int r);
};

#endif