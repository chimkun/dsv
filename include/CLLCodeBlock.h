#ifndef CLLCODEBLOCK_H
#define CLLCODEBLOCK_H

#include "codeblock.h"

class CLLscreenCodeBlock {
private:
    codeBlock insertCodeBlock;
    codeBlock deleteCodeBlock;
    codeBlock searchCodeBlock;
    codeBlock updateCodeBlock;

    codeBlock insertBeginBlock;
    codeBlock deleteBeginBlock;
public:
    CLLscreenCodeBlock();
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

    void drawInsertBeginCodeBlock(sf::RenderWindow &window);
    void drawInsertBeginCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawInsertBeginCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);
    
    void drawDeleteBeginCodeBlock(sf::RenderWindow &window);
    void drawDeleteBeginCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber);
    void drawDeleteBeginCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh);
};

#endif