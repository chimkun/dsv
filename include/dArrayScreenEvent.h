#ifndef DARRAYSCREENEVENT_H
#define DARRAYSCREENEVENT_H

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "general.h"
#include "dArrayScreen.h"
#include "dArrayCodeBlock.h"
#include "browse.h"
#include "fadecolor.h"

enum dynamicArrayDrawType {
    DArrayback,
    chooseMakeDArray, makeDArray, inputDArray,
    showcaseDArray, 
    insertDArray0, insertDArray1, insertDArray2, insertDArray3,
    deleteDArray0, deleteDArray1, deleteDArray2,
    searchDArray0, searchDArray1, searchDArray2,
    updateDArray0, updateDArray1, updateDArray2
};

class DArrayObject {
private:
    //DArray
        DynamicArray myDArray;
        //create list
        int opacity;
        //color transition
        sf::Clock flashTimer;
        sf::Time remTime;
        //insert data
        int insertIndex, insertData, insertNumberOpacity, 
            insertSwapIndex, insertSwapDistance, newArrayOpacity, yDistance;
        sf::Clock insertSwapTime;
        //delete data
        int deleteIndex, deleteMoveX, deleteMoveY, 
            deleteNumberOpacity, newDelArrayOpacity, deleteCurIndex;
        sf::Clock deleteSwapTime;
        //search data
        int searchIndex, searchData, searchIterateTarget;
        //update data
        int updateIndex, updateData, updateNumberOpacity;
        //mark first time
        bool markFirst;
    //DArray mode
        dynamicArrayDrawType drawType, prevType;
    // Text
        textInfo nodeText;
    // UI
        allScreen theDArrayscreen;
    // BG
        background screenBackground;
    // Code Block
        dArrayScreenCodeBlock DArrayCodeBlock;
    // exit
        bool backToMenu;
public:
    DArrayObject();
    void createList(int numberOfNode, std::vector <int> &a);
    void createDefinedList(std::vector <int> &userInput);
    void createRandomList();
    void drawList(sf::RenderWindow &window);
    void processDrawList();

    void drawInsertCreate(sf::RenderWindow &window);
    void drawInsertIndicator(sf::RenderWindow &window);
    void drawInsertSwapArray(sf::RenderWindow &window);
    void drawInsertNodeSwap(sf::RenderWindow &window);
    void processInsert(sf::RenderWindow &window);

    void drawDeleteCreate(sf::RenderWindow &window);
    void drawDeleteIndicator(sf::RenderWindow &window);
    void drawDeleteArraySwap(sf::RenderWindow &window);
    void processDelete(sf::RenderWindow &window);

    void drawSearchIndicator(sf::RenderWindow &window);
    void drawSearchHighlight(sf::RenderWindow &window);
    void drawSearchRevert(sf::RenderWindow &window);

    void drawUpdateIndicator(sf::RenderWindow &window);
    void drawUpdateChangeNum(sf::RenderWindow &window);
    void drawUpdateRevert(sf::RenderWindow &window);

    void processType(sf::RenderWindow &window);
    void processMouseEvent(sf::RenderWindow &window);
    void processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event);
    void processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event);
    void processMouseHoverEvent(sf::RenderWindow &window);

    void insertNodeProcess(int insertIndex, int insertData);
    void deleteNodeProcess(int deleteIndex);
    void searchNodeProcess(int searchData);
    void updateNodeProcess(int updateIndex, int updateData);
    void deleteDArray();

    bool insertIsValid(int addIndex, int addData);
    bool deleteIsValid(int delIndex);
    bool updateIsValid(int updIndex, int updData);

    dynamicArrayDrawType getType();
    void inputValue(int &value);

    void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                    int &insertNodeOpacity, int insertPhase);

    std::vector<int> getInputData(std::string &inputString);

    bool exitDArrayScreen();
    void setExitToFalse();
    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    
    void drawBackground(sf::RenderWindow &window);
    void drawDArrayScreen(sf::RenderWindow &window);
};

#endif