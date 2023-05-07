#ifndef ARRAYCODEBLOCK_H
#define ARRAYCODEBLOCK_H

#include "codeblock.h"

class arrayScreenCodeBlock {
private:
    codeBlock insertCodeBlock;
    codeBlock deleteCodeBlock;
    codeBlock updateCodeBlock;
    codeBlock searchCodeBlock;
public:
    arrayScreenCodeBlock();
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
};

#endif