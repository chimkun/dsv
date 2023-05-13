#ifndef DARRAYCODEBLOCK_H
#define DARRAYCODEBLOCK_H

#include "codeblock.h"

class dArrayScreenCodeBlock {
private:
    codeBlock insertCodeBlock;
    codeBlock deleteCodeBlock;
    codeBlock updateCodeBlock;
    codeBlock searchCodeBlock;
public:
    dArrayScreenCodeBlock();
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