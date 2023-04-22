#include "LLscreenCodeBlock.h"

LLscreenCodeBlock::LLscreenCodeBlock() {
    std::string insertCodeString = "Node cur = head\n"
                                    "for (k = 0; k < i; k++)\n"
                                    "    cur = cur->next\n"
                                    "Node rightNode = cur->next\n"
                                    "Node newNode = new Node(data)\n"
                                    "cur->next = newNode\n"
                                    "newNode->next = rightNode\n";
    std::string deleteCodeString = "Node cur = head\n"
                                   "for (k = 0; k < i-1; k++)\n"
                                   "   cur = cur->next\n"
                                   "Node del = cur->next, rightNode = del->next\n"
                                   "delete del\n"
                                   "cur->next = rightNode\n";
    insertCodeBlock = codeBlock(insertCodeString);
    deleteCodeBlock = codeBlock(deleteCodeString);
}

void LLscreenCodeBlock::drawInsertCodeBlock(sf::RenderWindow &window) {
    insertCodeBlock.drawCodeBlock(window);
}
void LLscreenCodeBlock::drawInsertCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    insertCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void LLscreenCodeBlock::drawInsertCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    insertCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void LLscreenCodeBlock::drawDeleteCodeBlock(sf::RenderWindow &window) {
    deleteCodeBlock.drawCodeBlock(window);
}
void LLscreenCodeBlock::drawDeleteCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    deleteCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void LLscreenCodeBlock::drawDeleteCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    deleteCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}
