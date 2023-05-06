#ifndef ARRAYSCREENEVENT_H
#define ARRAYSCREENEVENT_H

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "general.h"
#include "arrayScreen.h"
// #include "SArrayCodeBlock.h"
#include "browse.h"
#include "fadecolor.h"

enum staticArrayDrawType {
    SArrayback,
    chooseMakeSArray, makeSArray, inputSArray,
    showcaseSArray, 
    insertSArray0, insertSArray1, insertSArray2, 
    deleteSArray0, deleteSArray1, deleteSArray2,
    searchSArray0, searchSArray1, searchSArray2,
    updateSArray0, updateSArray1, updateSArray2
};

class SArrayObject {
private:
    //SArray
        StaticArray mySArray;
        //create list
        int opacity;
        //color transition
        sf::Clock flashTimer;
        sf::Time remTime;
        //insert data
        int insertIndex, insertData, insertNumberOpacity, insertSwapIndex, insertSwapDistance;
        sf::Clock insertSwapTime;
        //delete data
        int deleteIndex, deleteSwapDistance, deleteSwapIndex, deleteNumberOpacity;
        sf::Clock deleteSwapTime;
        //search data
        int searchIndex, searchData, searchIterateTarget;
        //update data
        int updateIndex, updateData, updateNumberOpacity;
        //mark first time
        bool markFirst;
    //SArray mode
        staticArrayDrawType drawType;
    // Text
        textInfo nodeText;
    // UI
        allScreen theSArrayscreen;
    // BG
        background screenBackground;
    // Code Block
        // SArrayscreenCodeBlock SArrayCodeBlock;
    // exit
        bool backToMenu;
public:
    SArrayObject();
    void createList(int numberOfNode, std::vector <int> &a);
    void createDefinedList(std::vector <int> &userInput);
    void createRandomList();
    void drawList(sf::RenderWindow &window);
    void processDrawList();

    void drawInsertIndicator(sf::RenderWindow &window);
    void processInsert(sf::RenderWindow &window);
    void drawInsertNodeSwap(sf::RenderWindow &window);

    void drawDeleteIndicator(sf::RenderWindow &window);
    void processDelete(sf::RenderWindow &window);
    void drawDeleteNodeSwap(sf::RenderWindow &window);
    void drawDeleteNodeMove(sf::RenderWindow &window);

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
    void deleteSArray();

    bool insertIsValid(int addIndex, int addData);
    bool deleteIsValid(int delIndex);
    bool updateIsValid(int updIndex, int updData);

    staticArrayDrawType getType();
    void inputValue(int &value);

    void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                    int &insertNodeOpacity, int insertPhase);

    std::vector<int> getInputData(std::string &inputString);

    bool exitSArrayScreen();
    void setExitToFalse();
    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    
    void drawBackground(sf::RenderWindow &window);
    void drawSArrayScreen(sf::RenderWindow &window);
};
#endif