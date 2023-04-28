#ifndef DLLSCREENEVENT_H
#define DLLSCREENEVENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "DLLCodeBlock.h"
#include "general.h"
#include "DLLscreen.h"
#include "fadecolor.h"
#include "browse.h"

enum DLLdrawType {
    DLLback,
    chooseMakeDLL, makeDLL, inputDLL,
    showcaseDLL, 
    insertDLL0, insertDLL1, insertDLL2, 
    deleteDLL0, deleteDLL1, deleteDLL2,
    searchDLL0, searchDLL1, searchDLL2,
    updateDLL0, updateDLL1, updateDLL2
};

class DLLObject {
private:
    //SLL
        DLL myDLL;
        //create list
        int opacity;
        //color transition
        sf::Clock flashTimer;
        sf::Time remTime;
        //insert data
        int insertIndex, insertData, nodePositionXAfterInsert, insertNodeColor, insertNodeOpacity, gotoIndex;
        sf::Vector2f insertNodePosition;
        //delete data
        int deleteIndex, nodeOpacity, deleteNodeOpacity, nodePositionDiffX, newArrowOpacity;
        //search data
        int searchIndex, searchData, infoTextOpacity;
        //update data
        int updateIndex, updateData, numberOpacity, opacityMultiplier;
        //mark first time
        bool markFirst;
    //LL mode
        DLLdrawType drawType;
    // Text
        textInfo nodeText;
    // UI
        allScreen theDLLscreen;
    // BG
        background screenBackground;
    // Code Block
        DLLscreenCodeBlock DLLCodeBlock;
    // exit
        bool backToMenu;
public:
    DLLObject();
    void createList(int numberOfNode, std::vector <int> &a);
    void createDefinedList(std::vector <int> &userInput);
    void createRandomList();
    void drawList(sf::RenderWindow &window);
    void processDrawList();

    void drawInsertIndicator(sf::RenderWindow &window);
    void processInsert(sf::RenderWindow &window);
    void drawListWhenInsert(sf::RenderWindow &window);
    void drawInsertNode(sf::RenderWindow &window);

    void drawDeleteIndicator(sf::RenderWindow &window);
    void processDelete(sf::RenderWindow &window);
    void drawDeleteNode(sf::RenderWindow &window);
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
    void deleteDLL();

    void drawBackground(sf::RenderWindow &window);
    bool exitDLLScreen();
    void setExitToFalse();
    
    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    void drawLLScreen(sf::RenderWindow &window);

    DLL getType();
};

void inputValue(int &value);

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase);

std::vector<int> getInputData(std::string &inputString);

#endif