#ifndef ARRAYSCREEN_H
#define ARRAYSCREEN_H

#include <vector>
#include "arrayNode.h"
#include "text.h"

class StaticArray {
private:
    std::vector <int> SArray;
    int arrayLength;
    arrayNode node;
    textInfo arrayText;
public:
    StaticArray();
    void build(std::vector <int> &input);
    void printArray();
    int getArrayLength();
    int getFixedLength();

    void insertAtBeginning(int data);
    void insertAtEnding(int data);
    void insertAtMiddle(int index, int data);

    void deleteAtBeginning();
    void deleteAtEnding();
    void deleteAtMiddle(int index);

    void updateIndex(int index, int newElement);
    int accessIndex(int index);
    int searchValue(int value);

    void drawArray(sf::RenderWindow &window, int opacity);
    void drawArrayIndex(sf::RenderWindow &window, int opacity);

    void drawInsertNodeIndicator(sf::RenderWindow &window, sf::Color newNodeColor, int insertNumberOpacity, int insertData);
    void drawInsertNodeSwap(sf::RenderWindow &window, int swapIndex, 
                            int insertData, int insertDistance);
    
    void drawDeleteNodeIndicator(sf::RenderWindow &window, sf::Color fadeColor, int deleteIndex, int numberOpacity);
    void drawDeleteNodeSwap(sf::RenderWindow &window, int deleteIndex, int swapIndex, int swapDistance);
    
    void drawSearchIndicator(sf::RenderWindow &window, sf::Color fadeColor, int searchIndex);
    void drawSearchRevert(sf::RenderWindow &window, sf::Color fadeColor, sf::Color foundNodeColor, int searchIndex);

    void drawUpdateIndicator(sf::RenderWindow &window, sf::Color fadeColor, int updateIndex, int updateOpacity);
    void drawUpdateChangeNum(sf::RenderWindow &window, int updateIndex, int updateData, 
                             int numberOpacity, sf::Color fadeColor);
    void drawUpdateRevert(sf::RenderWindow &window, sf::Color fadeColor, int updateIndex);
};

#endif