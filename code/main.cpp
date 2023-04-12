#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include "menu.h"
#include "general.h"
#include "LLscreen.h"
#include "node.h"

int main()
{
    srand(time(NULL));
    enum LLdrawType {
        showcaseLL, 
        insertLL0, insertLL1, insertLL2, 
        deleteLL0, deleteLL1, deleteLL2
    };
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
    window.setFramerateLimit(60);
    
    generalScreen theLLscreen;

    nodeConstants::initializeConstants();
    arrowConstants::initializeConstants();
    mathConstants::initializeConstants();

    SLL mySLL;
    createList(mySLL);
    int opacity = 0;
    sf::Vector2f insertNodePosition;
    
    LLdrawType drawType = showcaseLL;
    
    //insert data
    int insertIndex, insertData, nodePositionXAfterInsert, insertNodeColor, insertNodeOpacity, gotoIndex;
    sf::Clock flashTimer;

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
                    sf::FloatRect addButtonBounds = theLLscreen.getAddButtonBounds();
                    sf::FloatRect deleteButtonBounds = theLLscreen.getDeleteButtonBounds();
                    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && addButtonBounds.contains(mousePosition)) {
                        drawType = insertLL0;
                        insertNodeProcess(mySLL, insertIndex, insertData, insertNodePosition, gotoIndex,
                                          nodePositionXAfterInsert, insertNodeOpacity, insertNodeColor, flashTimer);
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && deleteButtonBounds.contains(mousePosition)) {
                        drawType = deleteLL1;
                        deleteNodeProcess(mySLL, deleteIndex, nodeOpacity, deleteNodeOpacity, nodePositionDiffX, newArrowOpacity);
                    }
                    break;
            }
        }
        if (opacity + nodeConstants::fadeSpeed <= 255)
            opacity += nodeConstants::fadeSpeed;
        window.clear();
        switch (drawType) {
            case showcaseLL:
                mySLL.drawList(window, opacity, nodeConstants::nodeDistance);
                break;
            case insertLL0:
                if (gotoIndex > insertIndex) {
                    drawType = insertLL1;
                    mySLL.insertAfterIndex(insertData, insertIndex);
                    insertIndex++;
                    break;
                }
                mySLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
                if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
                    gotoIndex++;
                    flashTimer.restart();
                }
                break;
            case insertLL1:
                if (nodePositionXAfterInsert >= nodeConstants::nodeDistance)
                    drawType = insertLL2;
                else {
                    setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 1);
                }
                mySLL.drawListWhenInsert(window, insertIndex, 
                                         opacity, nodePositionXAfterInsert);
                break;
            case insertLL2:
                if (insertNodePosition.y == nodeConstants::firstNodePositionY)
                    drawType = showcaseLL;
                else {
                    setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 2);
                }
                mySLL.drawInsertNode(window, insertIndex, 
                                     opacity, insertNodePosition, insertNodeOpacity);
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
                }
                break;
            case deleteLL2:
                mySLL.drawDeleteNodeMove(window, deleteIndex, nodeOpacity, nodePositionDiffX, newArrowOpacity);
                if (nodePositionDiffX > 0 || newArrowOpacity < 255) {
                    nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
                    newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
                }
                else 
                    drawType = showcaseLL;
                break;
        }
        theLLscreen.drawGeneralScreen(window);
        window.display();    
    }

    return 0;
}