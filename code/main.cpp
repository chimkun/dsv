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
    window.setFramerateLimit(60);
    window.clear(sf::Color::Black);

    nodeConstants::initializeConstants();
    arrowConstants::initializeConstants();
    mathConstants::initializeConstants();
    textConstants::initializeConstants();
    buttonConstants::initializeConstants();
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
        mySLLObject.processMouseHoverEvent(window);
        mySLLObject.drawBackground(window);
        mySLLObject.processType(window);
        window.display();
    }
    mySLLObject.deleteSLL();
    return 0;
}