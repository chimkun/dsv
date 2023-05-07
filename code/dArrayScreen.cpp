#include "dArrayScreen.h"

DynamicArray::DynamicArray() {
    arrayLength = 0;
}

void DynamicArray::build(std::vector <int> &input) {
    DArray = input;
    arrayLength = (int) input.size();
}
void DynamicArray::printArray() {
    for (int i = 0; i < (int) DArray.size(); i++)
        std::cout << DArray[i] << " ";
    std::cout << '\n';
}

void DynamicArray::insertAtBeginning(int data) {
    DArray.push_back(data);
    for (int i = (int) DArray.size() - 1; i > 0; i--) {
        std::swap(DArray[i], DArray[i - 1]);
    }
}
void DynamicArray::insertAtEnding(int data) {
    DArray.push_back(data);
}
void DynamicArray::insertAtMiddle(int index, int data) {
    if (index == 0) {
        insertAtBeginning(data);
        return;
    }
    if (index == (int) DArray.size()) {
        insertAtEnding(data);
        return;
    }
    DArray.push_back(data);
    for (int i = (int) DArray.size() - 1; i > index; i--) {
        std::swap(DArray[i], DArray[i - 1]);
    }
}

void DynamicArray::deleteAtBeginning() {
    if (DArray.empty()) 
        return;
    for (int i = 0; i < (int) DArray.size() - 1; i++) {
        std::swap(DArray[i], DArray[i + 1]);
    }
    DArray.pop_back();
}
void DynamicArray::deleteAtEnding() {
    if (DArray.empty())
        return;
    DArray.pop_back();
}
void DynamicArray::deleteAtMiddle(int index) {
    if (DArray.empty())
        return;
    if (index == 0) {
        deleteAtBeginning();
        return;
    }
    if (index == (int) DArray.size() - 1) {
        deleteAtEnding();
        return;
    }
    for (int i = index; i < (int) DArray.size() - 1; i++) {
        std::swap(DArray[i], DArray[i + 1]);
    }
    DArray.pop_back();
}

void DynamicArray::updateIndex(int index, int newElement) {
    if (index < 0 || index >= (int) DArray.size())
        return;
    DArray[index] = newElement;
}
int DynamicArray::accessIndex(int index) {
    if (index < 0 || index >= (int) DArray.size())
        return -1;
    return DArray[index];
}
int DynamicArray::searchValue(int value) {
    for (int i = 0; i < (int) DArray.size(); i++) 
        if (DArray[i] == value)
            return i;
    return -1;
}

int DynamicArray::getArrayLength() {
    return DArray.size();
}

void DynamicArray::drawArray(sf::RenderWindow &window, int opacity) {
    for (int i = 0; i < (int) DArray.size(); i++) {
        sf::Vector2f nodePosition = arrayConstants::leftArray;
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        node.drawArrayNode(window, nodePosition, DArray[i], opacity, sf::Color::White, opacity);
    }
    for (int i = (int) DArray.size(); i < arrayLength; i++) {    
        sf::Vector2f nodePosition = arrayConstants::leftArray;    
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        node.drawUnusedNode(window, nodePosition);
    }
    drawArrayIndex(window, opacity);
}
void DynamicArray::drawArrayIndex(sf::RenderWindow &window, int opacity) {
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    nodePosition.y += 85;
    for (int i = 0; i < arrayLength; i++) {
        std::string curIndex = std::to_string(i);
        arrayText.drawOptionalTextMid(window, curIndex, nodePosition, opacity, 44);
        nodePosition.x += arrayConstants::xDistance;
    }
    sf::Vector2f indexTextPosition = arrayConstants::leftArray + sf::Vector2f(-100, 82);
    std::string indexString = "index:";
    arrayText.drawOptionalTextMid(window, indexString, indexTextPosition, opacity, 42);
}

void DynamicArray::drawInsertNodeIndicator(sf::RenderWindow &window, sf::Color newNodeColor, int insertNumberOpacity, int insertData) {
    for (int i = 0; i <= (int) DArray.size(); i++) {
        sf::Vector2f nodePosition = arrayConstants::leftArray;
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        if (i < (int) DArray.size())
            node.drawArrayNode(window, nodePosition, DArray[i]);
        else 
            node.drawArrayNode(window, nodePosition, insertData, 255, newNodeColor);
    }
    drawArrayIndex(window, 255);
}
void DynamicArray::drawInsertNodeSwap(sf::RenderWindow &window, int swapIndex, int insertData, int insertDistance) {
    int dataIndex = 0;
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) DArray.size(); i++) {
        if (i == swapIndex) {
            continue;
        }
        if (i == swapIndex + 1) {
            nodePosition += sf::Vector2f(arrayConstants::xDistance * 2, 0);
            dataIndex++;
        }
        node.drawArrayNode(window, nodePosition, DArray[dataIndex]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance, 0);
        dataIndex++;
    }
    sf::Vector2f nodePositionL = arrayConstants::leftArray;
    nodePositionL += sf::Vector2f(arrayConstants::xDistance * swapIndex + insertDistance, 0);
    node.drawArrayNode(window, nodePositionL, DArray[swapIndex]);
    sf::Vector2f nodePositionR = arrayConstants::leftArray;
    nodePositionR += sf::Vector2f(arrayConstants::xDistance * (swapIndex + 1) - insertDistance, 0);
    node.drawArrayNode(window, nodePositionR, insertData);
    drawArrayIndex(window, 255);
}

void DynamicArray::drawDeleteNodeIndicator(sf::RenderWindow &window, sf::Color fadeColor, int deleteIndex, int numberOpacity) {
    for (int i = 0; i < (int) DArray.size(); i++) {
        sf::Vector2f nodePosition = arrayConstants::leftArray;
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        if (i == deleteIndex)
            node.drawUnusedNode(window, nodePosition, DArray[i], numberOpacity);
        else
            node.drawArrayNode(window, nodePosition, DArray[i]);
    }
    drawArrayIndex(window, 255);
}
void DynamicArray::drawDeleteNodeSwap(sf::RenderWindow &window, int deleteIndex, int swapIndex, int swapDistance) {
    int dataIndex = 0;
    if (swapIndex == (int) DArray.size() || swapIndex == 0)
        return;
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) DArray.size(); i++) {
        if (i == deleteIndex) {
            dataIndex++;
            continue;
        }
        if (i == swapIndex) {
            nodePosition.x += arrayConstants::xDistance * 2;
            dataIndex++;
            continue;
        }
        node.drawArrayNode(window, nodePosition, DArray[dataIndex]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance, 0);
        dataIndex++;
    }
    sf::Vector2f nodePositionL = arrayConstants::leftArray;
    nodePositionL += sf::Vector2f(arrayConstants::xDistance * (swapIndex - 1) + swapDistance, 0);
    node.drawUnusedNode(window, nodePositionL);
    sf::Vector2f nodePositionR = arrayConstants::leftArray;
    nodePositionR += sf::Vector2f(arrayConstants::xDistance * swapIndex - swapDistance, 0);
    node.drawArrayNode(window, nodePositionR, DArray[swapIndex]);
    drawArrayIndex(window, 255);
}


void DynamicArray::drawSearchIndicator(sf::RenderWindow &window, sf::Color fadeColor, int searchIndex) {
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) DArray.size(); i++) {
        if (i < searchIndex)
            node.drawArrayNode(window, nodePosition, DArray[i], 255, nodeConstants::flashColor);
        else if (i == searchIndex)
            node.drawArrayNode(window, nodePosition, DArray[i], 255, fadeColor);
        else
            node.drawArrayNode(window, nodePosition, DArray[i]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance, 0);
    }
    drawArrayIndex(window, 255);
}
void DynamicArray::drawSearchRevert(sf::RenderWindow &window, sf::Color fadeColor, sf::Color foundNodeColor, int searchIndex) {
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) DArray.size(); i++) {
        if (i < searchIndex)
            node.drawArrayNode(window, nodePosition, DArray[i], 255, fadeColor);
        else if (i == searchIndex)
            node.drawArrayNode(window, nodePosition, DArray[i], 255, foundNodeColor);
        else
            node.drawArrayNode(window, nodePosition, DArray[i]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance, 0);
    }
    drawArrayIndex(window, 255);
}

void DynamicArray::drawUpdateIndicator(sf::RenderWindow &window, sf::Color fadeColor, int updateIndex, int updateOpacity) {
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) DArray.size(); i++) {
        if (i == updateIndex)
            node.drawArrayNode(window, nodePosition, DArray[i], 255, fadeColor, updateOpacity);
        else
            node.drawArrayNode(window, nodePosition, DArray[i]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance, 0);
    }
    drawArrayIndex(window, 255);
}
void DynamicArray::drawUpdateRevert(sf::RenderWindow &window, sf::Color fadeColor, int updateIndex) {
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) DArray.size(); i++) {
        if (i == updateIndex)
            node.drawArrayNode(window, nodePosition, DArray[i], 255, fadeColor);
        else
            node.drawArrayNode(window, nodePosition, DArray[i]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance, 0);
    }
    drawArrayIndex(window, 255);
}