#include "CLLCodeBlock.h"

CLLscreenCodeBlock::CLLscreenCodeBlock() {
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
                                   "    cur = cur->next\n"
                                   "return -1\n";
    std::string updateCodeString = "Node cur = head\n"
                                   "for (i = 0; i < n; i++)\n"
                                   "    if (i = updateIndex)\n"
                                   "        cur->data = newData\n"
                                   "        break\n"
                                   "    cur = cur->next";
    std::string insertBeginString = "if (head = null)\n"
                                    "    head = new Node(data)\n"
                                    "    pTail = head->nxt = head\n"
                                    "else if (head != null)\n"
                                    "    Node temp = new Node(data)\n"
                                    "    temp->nxt = head, head = tail->nxt = temp";
    std::string deleteBeginString = "if (head = null)\n"
                                   "    do nothing\n"
                                   "else if (head != null)\n"
                                   "    temp = head, head = head->nxt, tail->nxt = head\n"
                                   "    delete temp";
    insertCodeBlock = codeBlock(insertCodeString);
    deleteCodeBlock = codeBlock(deleteCodeString);
    searchCodeBlock = codeBlock(searchCodeString);
    updateCodeBlock = codeBlock(updateCodeString);
    insertBeginBlock = codeBlock(insertBeginString);
    deleteBeginBlock = codeBlock(deleteBeginString);
}

void CLLscreenCodeBlock::drawInsertCodeBlock(sf::RenderWindow &window) {
    insertCodeBlock.drawCodeBlock(window);
}
void CLLscreenCodeBlock::drawInsertCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    insertCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void CLLscreenCodeBlock::drawInsertCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    insertCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void CLLscreenCodeBlock::drawDeleteCodeBlock(sf::RenderWindow &window) {
    deleteCodeBlock.drawCodeBlock(window);
}
void CLLscreenCodeBlock::drawDeleteCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    deleteCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void CLLscreenCodeBlock::drawDeleteCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    deleteCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void CLLscreenCodeBlock::drawSearchCodeBlock(sf::RenderWindow &window) {
    searchCodeBlock.drawCodeBlock(window);
}
void CLLscreenCodeBlock::drawSearchCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    searchCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void CLLscreenCodeBlock::drawSearchCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    searchCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void CLLscreenCodeBlock::drawUpdateCodeBlock(sf::RenderWindow &window) {
    updateCodeBlock.drawCodeBlock(window);
}
void CLLscreenCodeBlock::drawUpdateCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    updateCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void CLLscreenCodeBlock::drawUpdateCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    updateCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void CLLscreenCodeBlock::drawInsertBeginCodeBlock(sf::RenderWindow &window) {
    insertBeginBlock.drawCodeBlock(window);
}
void CLLscreenCodeBlock::drawInsertBeginCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    insertBeginBlock.drawHighlight(window, lineNumber, lineNumber);
}
void CLLscreenCodeBlock::drawInsertBeginCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    insertBeginBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void CLLscreenCodeBlock::drawDeleteBeginCodeBlock(sf::RenderWindow &window) {
    deleteBeginBlock.drawCodeBlock(window);
}
void CLLscreenCodeBlock::drawDeleteBeginCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    deleteBeginBlock.drawHighlight(window, lineNumber, lineNumber);
}
void CLLscreenCodeBlock::drawDeleteBeginCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    deleteBeginBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}