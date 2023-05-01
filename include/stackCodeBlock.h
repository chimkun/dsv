#ifndef STACKCODEBLOCK_H
#define STACKCODEBLOCK_H

#include "codeblock.h"

class stackScreenCodeBlock{
private:
    codeBlock peekCodeBlock;
    codeBlock pushCodeBlock;
    codeBlock popCodeBlock;
    codeBlock clearCodeBlock;
public:
    stackScreenCodeBlock();
    void drawPeekCodeBlock(sf::RenderWindow &window);
    void drawPeekCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    
    void drawPushCodeBlock(sf::RenderWindow &window);
    void drawPushCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);

    void drawPopCodeBlock(sf::RenderWindow &window);
    void drawPopCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);

    void drawClearCodeBlock(sf::RenderWindow &window);
    void drawClearCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
};


#endif