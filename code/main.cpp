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
#include "menu.h"

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
    codeTextConstants::initializeConstants();
    logoConstants::initializeConstants();
    menuButtonConstants::initializeConstants();

    enum screenType {
        menu,
        LL
    };

    screenType ScreenType = menu;

    menuScreen myMenuScreen;
    SLLObject mySLLObject;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (ScreenType) {
                case menu:
                    myMenuScreen.processAllEvent(window, event);
                    break;
                case LL:
                    mySLLObject.processAllEvent(window, event);
                    break;
            }
        }
        window.clear();
        switch (ScreenType) {
            case menu:
                myMenuScreen.drawMenuScreen(window);
                break;
            case LL:
                mySLLObject.drawLLScreen(window);
                break;
        }
        window.display();
    }
    mySLLObject.deleteSLL();
    return 0;
}