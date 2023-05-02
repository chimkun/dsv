#ifndef QUEUESCREENEVENT_H
#define QUEUESCREENEVENT_H

#include <SFML/Window/Keyboard.hpp>
#include "fadecolor.h"
#include "browse.h"
#include "queueScreen.h"
#include "background.h"
#include "queueCodeBlock.h"
#include "queueUI.h"
#include "fadecolor.h"

enum QueueDrawType {
    queueBack,
    queueChoose,
    queueShowcase,
    queuePush,
    queuePop,
    queuePeek,
    queueClear
};

class QueueObject {
private:
    //Queue
        queueClass myQueue;
        // create queue
        int opacity;
        // push queue
        int newNodeOpacity, extraXDistance;
        // pop queue
        int popOpacity;
        bool isPop;
        // peek queue
        sf::Clock colorClock;
    // Text
        textInfo nodeText;
    // UI
        queueAllScreen theQueueScreen;
    // BG
        background screenBackground;
    // Code Block
        queueScreenCodeBlock QueueCodeBlock;
    // others
        bool backToMenu;
        QueueDrawType drawType;
        QueueDrawType prevType;
public:
    QueueObject();
    void createQueue(std::vector <int> &a);
    void createRandomQueue();

    void drawQueue(sf::RenderWindow &window);
    void processDrawList();

    void drawPush(sf::RenderWindow &window);

    void drawPop(sf::RenderWindow &window);

    void drawPeek(sf::RenderWindow &window);

    void drawClear(sf::RenderWindow &window);

    void processType(sf::RenderWindow &window);
    void processMouseEvent(sf::RenderWindow &window);
    void processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event);
    void processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event);
    void processMouseHoverEvent(sf::RenderWindow &window);

    void createQueueProcess();
    void peekQueueProcess();
    void pushQueueProcess(int userInput);
    void popQueueProcess();
    void searchNodeProcess(int searchData);
    void updateNodeProcess(int updateIndex, int updateData);
    void deleteDLL();

    void drawBackground(sf::RenderWindow &window);
    bool exitQueueScreen();
    void setExitToFalse();
    
    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    void drawQueueScreen(sf::RenderWindow &window);
};

void inputValue(int &value);

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase);

std::vector<int> getInputData(std::string &inputString);



#endif