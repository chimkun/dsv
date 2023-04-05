#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "menu.h"
#include "general.h"
#include "LLscreen.h"
#include "node.h"

int main()
{
    srand(time(NULL));
    // enum screenType {
    //     Menu, Select, SinglyLinkedList;
    // };
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
    
    // menuScreen mainMenu;
    // initMenuScreen(mainMenu);

    generalScreen theLLscreen;
    const int nodeDistance = 174;
    SLL mySLL;
    createList(mySLL);
    int opacity = 0, fadeSpeed = 15;
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
                        int insertIndex, insertData;
                        std::cin >> insertIndex >> insertData;
                    }
                    break;
            }
        }
        if (opacity + fadeSpeed <= 255)
            opacity += fadeSpeed;
        window.clear();
        mySLL.drawList(window, opacity, nodeDistance);
        theLLscreen.drawGeneralScreen(window);
        window.display();    
    }

    return 0;
}