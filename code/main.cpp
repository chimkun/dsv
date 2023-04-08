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
        showcaseLL, insertLL
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

    int insertIndex, insertData, nodePositionXAfterInsert, insertedNodeColor, insertedNodeOpacity;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    sf::FloatRect addButtonBounds = theLLscreen.getAddButtonBounds();
                    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && addButtonBounds.contains(mousePosition)) {
                        drawType = insertLL;
                        insertNodeProcess(mySLL, insertIndex, insertData, insertNodePosition, 
                                          nodePositionXAfterInsert, insertedNodeOpacity, insertedNodeColor);
                    }
                    break;
            }
        }
        if (opacity + nodeConstants::fadeSpeed <= 255)
            opacity += nodeConstants::fadeSpeed;
        window.clear();
        switch (drawType) {
            case showcaseLL:
                mySLL.drawList(window, opacity, nodeConstants::nodeDistance, nodeConstants::firstNodePosition);
                break;
            case insertLL:
                if (nodePositionXAfterInsert >= nodeConstants::nodeDistance && insertNodePosition.y == nodeConstants::firstNodePositionY)
                    drawType = showcaseLL;
                else {
                    setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertedNodeOpacity);
                }
                mySLL.drawListAtInsert(window, insertIndex, opacity, nodeConstants::firstNodePosition, insertNodePosition, 
                                       nodePositionXAfterInsert, insertedNodeOpacity);
                break;
        }
        theLLscreen.drawGeneralScreen(window);
        window.display();    
    }

    return 0;
}