#include "DLLCodeBlock.h"

DLLscreenCodeBlock::DLLscreenCodeBlock() {
    std::string insertCodeString = "Node cur = head\n"
                                   "for (k = 0; k < i-1; k++)\n"
                                   "    cur = cur.next\n"
                                   "Node aft = cur.next\n"
                                   "Node vtx = new Node(v)\n"
                                   "vtx->next = aft, aft->prev = vtx\n"
                                   "pre->next = vtx, vtx->prev = pre\n";
    std::string deleteCodeString = "Node pre = head\n"
                                   "for (k = 0; k < i-1; k++)\n"
                                   "    pre = pre->next\n"
                                   "Node del = pre->next, aft = del->next\n"
                                   "pre.next = aft, aft.prev = pre\n"
                                   "delete del\n";
    std::string searchCodeString = "Node *cur = head\n"
                                   "for (i = 0; i < n; i++)\n"
                                   "    if (cur->data == searchData)\n"
                                   "        return i\n"
                                   "    cur = cur->nxt\n"
                                   "return -1\n";
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

void DLLscreenCodeBlock::drawInsertCodeBlock(sf::RenderWindow &window) {
    insertCodeBlock.drawCodeBlock(window);
}
void DLLscreenCodeBlock::drawInsertCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    insertCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void DLLscreenCodeBlock::drawInsertCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    insertCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void DLLscreenCodeBlock::drawDeleteCodeBlock(sf::RenderWindow &window) {
    deleteCodeBlock.drawCodeBlock(window);
}
void DLLscreenCodeBlock::drawDeleteCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    deleteCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void DLLscreenCodeBlock::drawDeleteCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    deleteCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void DLLscreenCodeBlock::drawSearchCodeBlock(sf::RenderWindow &window) {
    searchCodeBlock.drawCodeBlock(window);
}
void DLLscreenCodeBlock::drawSearchCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    searchCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void DLLscreenCodeBlock::drawSearchCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    searchCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void DLLscreenCodeBlock::drawUpdateCodeBlock(sf::RenderWindow &window) {
    updateCodeBlock.drawCodeBlock(window);
}
void DLLscreenCodeBlock::drawUpdateCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    updateCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void DLLscreenCodeBlock::drawUpdateCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    updateCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}
