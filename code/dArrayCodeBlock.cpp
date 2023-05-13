#include "dArrayCodeBlock.h"

dArrayScreenCodeBlock::dArrayScreenCodeBlock() {
    std::string insertCodeString = "newArr = new array (n + 1)\n"
                                   "for (int i = 0; i < n; i++)\n"
                                   "    newArr[i] = arr[i]\n"
                                   "newArr[n] = newData\n"
                                   "delete arr, arr = newArr\n"
                                   "for (i = n - 1; i > insertIndex; i--)\n"
                                   "    swap(newArr[i - 1], newArr[i])";
    std::string deleteCodeString = "newArr = new array (n - 1)\n"
                                   "newIndex = 0\n"
                                   "for (int i = 0; i < n; i++)\n" 
                                   "    if (i != deleteIndex)\n"
                                   "        newArr[newIndex] = arr[i], newIndex++\n"
                                   "delete arr, arr = newArr";
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

void dArrayScreenCodeBlock::drawInsertCodeBlock(sf::RenderWindow &window) {
    insertCodeBlock.drawCodeBlock(window);
}
void dArrayScreenCodeBlock::drawInsertCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    insertCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void dArrayScreenCodeBlock::drawInsertCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    insertCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void dArrayScreenCodeBlock::drawDeleteCodeBlock(sf::RenderWindow &window) {
    deleteCodeBlock.drawCodeBlock(window);
}
void dArrayScreenCodeBlock::drawDeleteCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    deleteCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void dArrayScreenCodeBlock::drawDeleteCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    deleteCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void dArrayScreenCodeBlock::drawSearchCodeBlock(sf::RenderWindow &window) {
    searchCodeBlock.drawCodeBlock(window);
}
void dArrayScreenCodeBlock::drawSearchCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    searchCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}
void dArrayScreenCodeBlock::drawSearchCodeBlockMultiLine(sf::RenderWindow &window, int lineNumberLow, int lineNumberHigh) {
    searchCodeBlock.drawHighlight(window, lineNumberLow, lineNumberHigh);
}

void dArrayScreenCodeBlock::drawUpdateCodeBlock(sf::RenderWindow &window) {
    updateCodeBlock.drawCodeBlock(window);
}
void dArrayScreenCodeBlock::drawUpdateCodeBlockSingleLine(sf::RenderWindow &window, int lineNumber) {
    updateCodeBlock.drawHighlight(window, lineNumber, lineNumber);
}