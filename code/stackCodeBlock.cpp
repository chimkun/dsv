#include "stackCodeBlock.h"

stackScreenCodeBlock::stackScreenCodeBlock() {
    std::string peekCodeString = "if (stack.isEmpty)\n"
                                 "    return STACK_EMPTY\n"
                                 "return stack.top";
    std::string pushCodeString = "stack.push(data)";
    std::string popCodeString = "if (stack.isEmpty == false)\n"
                                "    stack.pop";
    std::string clearCodeString = "while (stack.isEmpty == false)\n"
                                  "    stack.pop\n";
    peekCodeBlock = codeBlock(peekCodeString);
    pushCodeBlock = codeBlock(pushCodeString);
    popCodeBlock = codeBlock(popCodeString);
    clearCodeBlock = codeBlock(clearCodeString);
}

void stackScreenCodeBlock::drawPeekCodeBlock(sf::RenderWindow &window) {
    peekCodeBlock.drawCodeBlock(window);
}
void stackScreenCodeBlock::drawPeekCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    peekCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}

void stackScreenCodeBlock::drawPushCodeBlock(sf::RenderWindow &window) {
    pushCodeBlock.drawCodeBlock(window);
}
void stackScreenCodeBlock::drawPushCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    pushCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}

void stackScreenCodeBlock::drawPopCodeBlock(sf::RenderWindow &window) {
    popCodeBlock.drawCodeBlock(window);
}
void stackScreenCodeBlock::drawPopCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    popCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}

void stackScreenCodeBlock::drawClearCodeBlock(sf::RenderWindow &window) {
    clearCodeBlock.drawCodeBlock(window);
}
void stackScreenCodeBlock::drawClearCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    clearCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}