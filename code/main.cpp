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
    
    // menuScreen mainMenu;
    // initMenuScreen(mainMenu);

    generalScreen theLLscreen;
    const int nodeDistance = 174, firstNodePositionX = 174, initialInsertNodeY = 180,
              firstNodePositionY = 240, nodePositionSpeedAfterInsert = 12;
    const sf::Vector2f firstNodePosition(firstNodePositionX, firstNodePositionY);

    SLL mySLL;
    createList(mySLL);
    const int insertMoveSpeed = 12, fadeSpeed = 10;
    int opacity = 0;
    sf::Vector2f insertNodePosition;
    
    LLdrawType drawType = showcaseLL;

    int insertIndex, insertData, nodePositionXAfterInsert, insertedNodeColor, insertedNodeOpacity;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            // if (event.type == sf::Event::Closed)
            //     window.close();
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
                        std::cout << "insert index < n and data\n";
                        std::cin >> insertIndex >> insertData;
                        mySLL.insertAfterIndex(insertData, insertIndex);
                        insertIndex++;
                        insertNodePosition.x = firstNodePositionX * insertIndex;
                        insertNodePosition.y = firstNodePositionY + initialInsertNodeY;
                        nodePositionXAfterInsert = 0;
                        insertedNodeOpacity = 0;
                        insertedNodeColor = rand() % 4;
                    }
                    break;
            }
        }
        if (opacity + fadeSpeed <= 255)
            opacity += fadeSpeed;
        window.clear();
        switch (drawType) {
            case showcaseLL:
                mySLL.drawList(window, opacity, nodeDistance, firstNodePosition);
                break;
            case insertLL:
                if (nodePositionXAfterInsert >= nodeDistance && insertNodePosition.y == firstNodePositionY)
                    drawType = showcaseLL;
                else {
                    if (nodePositionXAfterInsert < nodeDistance)
                        nodePositionXAfterInsert = std::min(nodeDistance, nodePositionXAfterInsert + insertMoveSpeed);
                    if (insertNodePosition.y > firstNodePositionY)
                        insertNodePosition.y = std::max((float) insertNodePosition.y - insertMoveSpeed, (float) firstNodePositionY);
                    if (insertedNodeOpacity < 255)
                        insertedNodeOpacity += fadeSpeed;
                }
                
                mySLL.drawListAtInsert(window, insertIndex, opacity, nodeDistance, firstNodePosition, 
                                       insertNodePosition, nodePositionXAfterInsert, insertedNodeColor, insertedNodeOpacity);
                break;
        }
        theLLscreen.drawGeneralScreen(window);
        window.display();    
    }

    return 0;
}