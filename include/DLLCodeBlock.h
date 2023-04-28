#ifndef DLLCODEBLOCK_H
#define DLLCODEBLOCK_H

#include <SFML/Graphics.hpp>
#include "codeblock.h"

class DLLscreenCodeBlock{
private:
    codeBlock insertCodeBlock;
    codeBlock deleteCodeBlock;
    codeBlock searchCodeBlock;
    codeBlock updateCodeBlock;
public:
    DLLscreenCodeBlock();
    void drawInsertCodeBlock(sf::RenderWindow &window);
    void drawInsertCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawInsertCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);
    
    void drawDeleteCodeBlock(sf::RenderWindow &window);
    void drawDeleteCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawDeleteCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);

    void drawSearchCodeBlock(sf::RenderWindow &window);
    void drawSearchCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawSearchCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);

    void drawUpdateCodeBlock(sf::RenderWindow &window);
    void drawUpdateCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawUpdateCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);
};

#endif