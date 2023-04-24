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
    std::string searchCodeString = "Node cur = head\n"
                                   "for (i = 0; i < n; i++) \n"
                                   "    if cur->data = searchValue\n"
                                   "        return i\n"
                                   "    cur = cur->next\n"
                                   "return NOT_FOUND\n";
    std::string updateCodeString = "Node cur = head\n"
                                   "for (i = 0; i < n; i++)\n"
                                   "    if (i = updateIndex)\n"
                                   "        cur->data = newData\n"
                                   "        break\n"
                                   "    cur = cur->next";
    insertCodeBlock = codeBlock(insertCodeString);
    deleteCodeBlock = codeBlock(deleteCodeString);
    searchCodeBlock = codeBlock(searchCodeString);
    updateCodeBlock = codeBlock(updateCodeString);
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

void LLscreenCodeBlock::drawSearchCodeBlock(sf::RenderWindow &window) {
    searchCodeBlock.drawCodeBlock(window);
}
void LLscreenCodeBlock::drawSearchCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    searchCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void LLscreenCodeBlock::drawSearchCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    searchCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void LLscreenCodeBlock::drawUpdateCodeBlock(sf::RenderWindow &window) {
    updateCodeBlock.drawCodeBlock(window);
}
void LLscreenCodeBlock::drawUpdateCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    updateCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void LLscreenCodeBlock::drawUpdateCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    updateCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}
