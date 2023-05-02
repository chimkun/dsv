#include "queueCodeBlock.h"

queueScreenCodeBlock::queueScreenCodeBlock() {
    std::string peekCodeString = "if (queue.isEmpty)\n"
                                 "    return STACK_EMPTY\n"
                                 "return queue.front";
    std::string pushCodeString = "queue.push(data)";
    std::string popCodeString = "if (queue.isEmpty == false)\n"
                                "    queue.pop";
    std::string clearCodeString = "while (queue.isEmpty == false)\n"
                                  "    queue.pop\n";
    peekCodeBlock = codeBlock(peekCodeString);
    pushCodeBlock = codeBlock(pushCodeString);
    popCodeBlock = codeBlock(popCodeString);
    clearCodeBlock = codeBlock(clearCodeString);
}

void queueScreenCodeBlock::drawPeekCodeBlock(sf::RenderWindow &window) {
    peekCodeBlock.drawCodeBlock(window);
}
void queueScreenCodeBlock::drawPeekCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    peekCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}

void queueScreenCodeBlock::drawPushCodeBlock(sf::RenderWindow &window) {
    pushCodeBlock.drawCodeBlock(window);
}
void queueScreenCodeBlock::drawPushCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    pushCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}

void queueScreenCodeBlock::drawPopCodeBlock(sf::RenderWindow &window) {
    popCodeBlock.drawCodeBlock(window);
}
void queueScreenCodeBlock::drawPopCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    popCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}

void queueScreenCodeBlock::drawClearCodeBlock(sf::RenderWindow &window) {
    clearCodeBlock.drawCodeBlock(window);
}
void queueScreenCodeBlock::drawClearCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    clearCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}