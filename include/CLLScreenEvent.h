#ifndef CLLSCREENEVENT_H
#define CLLSCREENEVENT_H

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "general.h"
#include "CLLscreen.h"
// #include "CLLscreenCodeBlock.h"
#include "browse.h"
#include "fadecolor.h"

enum CLLdrawType {
    CLLback,
    chooseMakeCLL, makeCLL, inputCLL,
    showcaseCLL, 
    insertCLL0, insertCLL1, insertCLL2, 
    deleteCLL0, deleteCLL1, deleteCLL2,
    searchCLL0, searchCLL1, searchCLL2,
    updateCLL0, updateCLL1, updateCLL2
};

class CLLObject {
private:
    //CLL
        CLL myCLL;
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
    //CLL mode
        CLLdrawType drawType;
    // Text
        textInfo nodeText;
    // UI
        allScreen theCLLscreen;
    // BG
        background screenBackground;
    // Code Block
        // CLLscreenCodeBlock CLLCodeBlock;
    // exit
        bool backToMenu;
public:
    CLLObject();
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
    void deleteCLL();

    CLLdrawType getType();
    void inputValue(int &value);

    void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                    int &insertNodeOpacity, int insertPhase);

    std::vector<int> getInputData(std::string &inputString);

    bool exitCLLScreen();
    void setExitToFalse();
    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    
    void drawBackground(sf::RenderWindow &window);
    void drawCLLScreen(sf::RenderWindow &window);
};

#endif