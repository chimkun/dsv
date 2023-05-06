#include "arrayScreen.h"

StaticArray::StaticArray() {
    arrayLength = 0;
}

void StaticArray::build(std::vector <int> &input) {
    SArray = input;
    arrayLength = (int) input.size();
}
void StaticArray::printArray() {
    for (int i = 0; i < (int) SArray.size(); i++)
        std::cout << SArray[i] << " ";
    std::cout << '\n';
}

void StaticArray::insertAtBeginning(int data) {
    if ((int) SArray.size() >= arrayLength)
        return;
    SArray.push_back(data);
    for (int i = (int) SArray.size() - 1; i > 0; i--) {
        std::swap(SArray[i], SArray[i - 1]);
    }
}
void StaticArray::insertAtEnding(int data) {
    if ((int) SArray.size() >= arrayLength)
        return;
    SArray.push_back(data);
}
void StaticArray::insertAtMiddle(int index, int data) {
    if ((int) SArray.size() >= arrayLength) 
        return;
    if (index == 0) {
        insertAtBeginning(data);
        return;
    }
    if (index == (int) SArray.size()) {
        insertAtEnding(data);
        return;
    }
    SArray.push_back(data);
    for (int i = (int) SArray.size() - 1; i >= index; i--) {
        std::swap(SArray[i], SArray[i - 1]);
    }
}

void StaticArray::deleteAtBeginning() {
    if (SArray.empty()) 
        return;
    for (int i = 0; i < (int) SArray.size() - 1; i++) {
        std::swap(SArray[i], SArray[i + 1]);
    }
    SArray.pop_back();
}
void StaticArray::deleteAtEnding() {
    if (SArray.empty())
        return;
    SArray.pop_back();
}
void StaticArray::deleteAtMiddle(int index) {
    if (SArray.empty())
        return;
    if (index == 0) {
        deleteAtBeginning();
        return;
    }
    if (index == (int) SArray.size() - 1) {
        deleteAtEnding();
        return;
    }
    for (int i = index; i < (int) SArray.size() - 1; i++) {
        std::swap(SArray[i], SArray[i + 1]);
    }
    SArray.pop_back();
}

void StaticArray::updateIndex(int index, int newElement) {
    if (index < 0 || index >= (int) SArray.size())
        return;
    SArray[index] = newElement;
}
int StaticArray::accessIndex(int index) {
    if (index < 0 || index >= (int) SArray.size())
        return -1;
    return SArray[index];
}
int StaticArray::searchValue(int value) {
    for (int i = 0; i < (int) SArray.size(); i++) 
        if (SArray[i] == value)
            return i;
    return -1;
}

int StaticArray::getArrayLength() {
    return SArray.size();
}
int StaticArray::getFixedLength() {
    return arrayLength;
}

void StaticArray::drawArray(sf::RenderWindow &window, int opacity) {
    for (int i = 0; i < (int) SArray.size(); i++) {
        sf::Vector2f nodePosition = arrayConstants::leftArray;
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        node.drawArrayNode(window, nodePosition, SArray[i], opacity);
    }
    for (int i = (int) SArray.size(); i < arrayLength; i++) {    
        sf::Vector2f nodePosition = arrayConstants::leftArray;    
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        node.drawUnusedNode(window, nodePosition);
    }
}

void StaticArray::drawInsertNodeIndicator(sf::RenderWindow &window, sf::Color newNodeColor, int insertNumberOpacity, int insertData) {
    for (int i = 0; i <= (int) SArray.size(); i++) {
        sf::Vector2f nodePosition = arrayConstants::leftArray;
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        if (i < (int) SArray.size())
            node.drawArrayNode(window, nodePosition, SArray[i]);
        else 
            node.drawArrayNode(window, nodePosition, insertData, 255, newNodeColor);
    }
    for (int i = SArray.size() + 1; i < arrayLength; i++) {
        sf::Vector2f nodePosition = arrayConstants::leftArray;
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        node.drawUnusedNode(window, nodePosition);
    }
}
void StaticArray::drawInsertNodeSwap(sf::RenderWindow &window, int swapIndex, int insertData, int insertDistance) {
    int dataIndex = 0;
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) SArray.size(); i++) {
        if (i == swapIndex) {
            continue;
        }
        if (i == swapIndex + 1) {
            dataIndex++;
            continue;
        }
        node.drawArrayNode(window, nodePosition, SArray[dataIndex]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        dataIndex++;
    }
    sf::Vector2f nodePositionL = arrayConstants::leftArray;
    nodePositionL += sf::Vector2f(arrayConstants::xDistance * swapIndex + insertDistance, 0);
    node.drawArrayNode(window, nodePositionL, SArray[swapIndex]);
    sf::Vector2f nodePositionR = arrayConstants::leftArray;
    nodePositionR += sf::Vector2f(arrayConstants::xDistance * (swapIndex + 1) - insertDistance, 0);
    node.drawArrayNode(window, nodePositionR, insertData);
}

void StaticArray::drawDeleteNodeIndicator(sf::RenderWindow &window, sf::Color fadeColor, int deleteIndex, int numberOpacity) {
    for (int i = 0; i < (int) SArray.size(); i++) {
        sf::Vector2f nodePosition = arrayConstants::leftArray;
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        if (i == deleteIndex)
            node.drawUnusedNode(window, nodePosition, SArray[i], numberOpacity);
        else
            node.drawArrayNode(window, nodePosition, SArray[i]);
    }
    for (int i = (int) SArray.size(); i < arrayLength; i++) {    
        sf::Vector2f nodePosition = arrayConstants::leftArray;    
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        node.drawUnusedNode(window, nodePosition);
    }
}
void StaticArray::drawDeleteNodeSwap(sf::RenderWindow &window, int deleteIndex, int swapIndex, int swapDistance) {
    int dataIndex = 0;
    if (swapIndex == (int) SArray.size() || swapIndex == 0)
        return;
    sf::Vector2f nodePosition = arrayConstants::leftArray;
    for (int i = 0; i < (int) SArray.size(); i++) {
        if (i == deleteIndex) {
            dataIndex++;
            continue;
        }
        if (i == swapIndex) {
            nodePosition.x += arrayConstants::xDistance * 2;
            dataIndex++;
            continue;
        }
        node.drawArrayNode(window, nodePosition, SArray[dataIndex]);
        nodePosition += sf::Vector2f(arrayConstants::xDistance, 0);
        dataIndex++;
    }
    sf::Vector2f nodePositionL = arrayConstants::leftArray;
    nodePositionL += sf::Vector2f(arrayConstants::xDistance * (swapIndex - 1) + swapDistance, 0);
    node.drawUnusedNode(window, nodePositionL);
    sf::Vector2f nodePositionR = arrayConstants::leftArray;
    nodePositionR += sf::Vector2f(arrayConstants::xDistance * swapIndex - swapDistance, 0);
    node.drawArrayNode(window, nodePositionR, SArray[swapIndex]);
    for (int i = (int) SArray.size(); i < arrayLength; i++) {    
        sf::Vector2f nodePosition = arrayConstants::leftArray;    
        nodePosition += sf::Vector2f(arrayConstants::xDistance * i, 0);
        node.drawUnusedNode(window, nodePosition);
    }
}