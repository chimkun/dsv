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
    // menu DS Type
    // none (0), SLL (1), DLL (2), CLL (3),
    // array (4), dArray (5),
    // stack (6), queue (7)

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
    window.setFramerateLimit(60);
    window.clear(sf::Color::Black);

    initializeConstants();

    enum screenType {
        menu,
        SLL
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
                case SLL:
                    mySLLObject.processAllEvent(window, event);
                    break;
            }
        }
        window.clear();
        int dsType = myMenuScreen.getDSType();
        switch (dsType) {
            case 1:
                ScreenType = SLL;
                break;
            default:
                ScreenType = menu;
                break;
        }
        switch (ScreenType) {
            case menu:
                myMenuScreen.drawMenuScreen(window);
                break;
            case SLL:
                mySLLObject.drawLLScreen(window);
                break;
        }
        window.display();
    }
    mySLLObject.deleteSLL();
    return 0;
}