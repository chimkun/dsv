#include "arrayCodeBlock.h"

arrayScreenCodeBlock::arrayScreenCodeBlock() {
    std::string insertCodeString = "if (cur_length > fixed_length)\n"
                                   "    arr[cur_length] = data\n"
                                   "    cur_length = cur_length + 1\n"
                                   "    for (k = cur_length - 1; k > index; k--)\n"
                                   "        swap(arr[k], arr[k - 1]\n";
    std::string deleteCodeString = "for (k = index; k < cur_length - 1; k++)\n"
                                   "    swap(arr[k], arr[k + 1])\n"
                                   "cur_length = cur_length - 1\n";
    std::string searchCodeString = "for (i = 0; i < n; i++)\n"
                                   "    if (arr[i] == searchData)\n"
                                   "        return i\n"
                                   "return -1\n";
    std::string updateCodeString = "arr[i] = data\n";
    insertCodeBlock = codeBlock(insertCodeString);
    deleteCodeBlock = codeBlock(deleteCodeString);
    searchCodeBlock = codeBlock(searchCodeString);
    updateCodeBlock = codeBlock(updateCodeString);
}

void arrayScreenCodeBlock::drawInsertCodeBlock(sf::RenderWindow &window) {
    insertCodeBlock.drawCodeBlock(window);
}
void arrayScreenCodeBlock::drawInsertCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    insertCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void arrayScreenCodeBlock::drawInsertCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    insertCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void arrayScreenCodeBlock::drawDeleteCodeBlock(sf::RenderWindow &window) {
    deleteCodeBlock.drawCodeBlock(window);
}
void arrayScreenCodeBlock::drawDeleteCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    deleteCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void arrayScreenCodeBlock::drawDeleteCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    deleteCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void arrayScreenCodeBlock::drawSearchCodeBlock(sf::RenderWindow &window) {
    searchCodeBlock.drawCodeBlock(window);
}
void arrayScreenCodeBlock::drawSearchCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    searchCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void arrayScreenCodeBlock::drawSearchCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    searchCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void arrayScreenCodeBlock::drawUpdateCodeBlock(sf::RenderWindow &window) {
    updateCodeBlock.drawCodeBlock(window);
}
void arrayScreenCodeBlock::drawUpdateCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    updateCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}