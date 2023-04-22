#ifndef LLSCREENCODEBLOCK_H
#define LLSCREENCODEBLOCK_H

#include <SFML/Graphics.hpp>
#include "codeblock.h"

class LLscreenCodeBlock{
private:
    codeBlock insertCodeBlock;
    codeBlock deleteCodeBlock;
    codeBlock searchCodeBlock;
    codeBlock updateCodeBlock;
public:
    LLscreenCodeBlock();
    void drawInsertCodeBlock(sf::RenderWindow &window);
    void drawInsertCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawInsertCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);
    
    void drawDeleteCodeBlock(sf::RenderWindow &window);
    void drawDeleteCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawDeleteCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);
};

#endif