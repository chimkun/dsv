#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include "LLscreenEvent.h"
#include "constants.h"
#include "general.h"
#include "LLscreen.h"
#include "button.h"
#include "node.h"

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
    window.setFramerateLimit(120);
    window.clear(sf::Color::Black);

    nodeConstants::initializeConstants();
    arrowConstants::initializeConstants();
    mathConstants::initializeConstants();
    textConstants::initializeConstants();

/*

    generalScreen theLLscreen;

    SLL mySLL;
    createList(mySLL);
    int opacity = 0;
    
    LLdrawType drawType = showcaseLL;
    
    //insert data
    int insertIndex, insertData, nodePositionXAfterInsert, insertNodeColor, insertNodeOpacity, gotoIndex;
    sf::Clock flashTimer;
    sf::Vector2f insertNodePosition;

    //delete data
    int deleteIndex, nodeOpacity, deleteNodeOpacity, nodePositionDiffX, newArrowOpacity;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (drawType == showcaseLL) {
                        if (theLLscreen.createButtonIsClick(window)) {
                            opacity = 0;
                            mySLL.deleteList();
                            createList(mySLL);
                        }
                        if (theLLscreen.addButtonIsClick(window)) {
                            drawType = insertLL0;
                            insertNodeProcess(mySLL, insertIndex, insertData, insertNodePosition, gotoIndex,
                                            nodePositionXAfterInsert, insertNodeOpacity, insertNodeColor, flashTimer);
                        }
                        if (theLLscreen.deleteButtonIsClick(window)) {
                            drawType = deleteLL0;
                            deleteNodeProcess(mySLL, deleteIndex, nodeOpacity, deleteNodeOpacity, gotoIndex,
                                            nodePositionDiffX, newArrowOpacity, flashTimer);
                        }
                    }
                    break;
            }
        }
        if (opacity + nodeConstants::fadeSpeed <= 255)
            opacity += nodeConstants::fadeSpeed;
        window.clear();
        switch (drawType) {
            case showcaseLL:
                mySLL.drawList(window, opacity);
                break;
            case insertLL0:
                mySLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
                if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
                    gotoIndex++;
                    flashTimer.restart();
                }
                if (gotoIndex > insertIndex) {
                    drawType = insertLL1;
                    mySLL.insertAfterIndex(insertData, insertIndex);
                    insertIndex++;
                    break;
                }
                break;
            case insertLL1:
                mySLL.drawListWhenInsert(window, insertIndex, 
                                         opacity, nodePositionXAfterInsert);
                if (nodePositionXAfterInsert >= nodeConstants::nodeDistance) {
                    drawType = insertLL2;
                    flashTimer.restart();
                }
                else {
                    setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 1);
                }
                break;
            case insertLL2:
                mySLL.drawInsertNode(window, insertIndex, opacity,
                                     getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
                                     insertNodePosition, insertNodeOpacity);
                if (insertNodePosition.y == nodeConstants::firstNodePositionY)
                    drawType = showcaseLL;
                else {
                    setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 2);
                }
                break;
            case deleteLL0:
                mySLL.drawDeleteNodeIndicator(window, deleteIndex, gotoIndex, 
                                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
                if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
                    gotoIndex++;
                    flashTimer.restart();
                }
                if (gotoIndex > deleteIndex) {
                    drawType = deleteLL1;
                    insertIndex++;
                    break;
                }
                break;
            case deleteLL1:
                mySLL.drawDeleteNode(window, deleteIndex, nodeOpacity, deleteNodeOpacity);
                if (deleteNodeOpacity - nodeConstants::fadeSpeed > 0) {
                    deleteNodeOpacity = std::max(deleteNodeOpacity - nodeConstants::fadeSpeed, 0);
                }
                else {
                    mySLL.deleteAtIndex(deleteIndex);
                    nodeOpacity = 255;
                    drawType = deleteLL2;
                    flashTimer.restart();
                }
                break;
            case deleteLL2:
                mySLL.drawDeleteNodeMove(window, deleteIndex, nodeOpacity, 
                                         nodePositionDiffX, newArrowOpacity,
                                         getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer));
                if (nodePositionDiffX > 0 || newArrowOpacity < 255) {
                    newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
                    if (newArrowOpacity == 255)
                        nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
                }
                else 
                    drawType = showcaseLL;
                break;
        }
        theLLscreen.drawGeneralScreen(window);
        window.display();    
    }

*/
    SLLObject mySLLObject;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    mySLLObject.processMouseEvent(window);
                    break;
                case sf::Event::TextEntered:
                    mySLLObject.processKeyboardInputEvent(window, event);
                    break;
                case sf::Event::KeyPressed:
                    mySLLObject.processKeyboardOtherActionEvent(window, event);
                    break;
            }
        }
        window.clear();
        mySLLObject.drawBackground(window);
        mySLLObject.processType(window);
        window.display();
    }
    mySLLObject.deleteSLL();
    return 0;
}