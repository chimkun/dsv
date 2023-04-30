#ifndef STACKSCREENEVENT_H
#define STACKSCREENEVENT_H

#include <SFML/Window/Keyboard.hpp>
#include "fadecolor.h"
#include "browse.h"
#include "stackScreen.h"
#include "background.h"
#include "stackUI.h"

enum StackDrawType {
    stackBack,
    stackChoose,
    stackShowcase,
    stackPush,
    stackPop,
    stackPeek,
    stackClear
};

class StackObject {
private:
    //Stack
        stackClass myStack;
        // create stack
        int opacity;
    // Text
        textInfo nodeText;
    // UI
        stackAllScreen theStackScreen;
    // BG
        background screenBackground;
    // Code Block
        
    // others
        bool backToMenu;
        StackDrawType drawType;
public:
    StackObject();
    void createStack(std::vector <int> &a);
    void createRandomStack();

    void drawStack(sf::RenderWindow &window);
    void processDrawList();

    void drawPush(sf::RenderWindow &window);

    void drawPopStack(sf::RenderWindow &window);

    void drawPeek(sf::RenderWindow &window);

    void drawClear(sf::RenderWindow &window);

    void processType(sf::RenderWindow &window);
    void processMouseEvent(sf::RenderWindow &window);
    void processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event);
    void processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event);
    void processMouseHoverEvent(sf::RenderWindow &window);

    void createStackProcess();
    void insertNodeProcess(int insertIndex, int insertData);
    void deleteNodeProcess(int deleteIndex);
    void searchNodeProcess(int searchData);
    void updateNodeProcess(int updateIndex, int updateData);
    void deleteDLL();

    void drawBackground(sf::RenderWindow &window);
    bool exitStackScreen();
    void setExitToFalse();
    
    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    void drawLLScreen(sf::RenderWindow &window);
};

void inputValue(int &value);

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase);

std::vector<int> getInputData(std::string &inputString);


#endif