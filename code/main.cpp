#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "menu.h"
#include "LLscreen.h"
#include "node.h"

int main()
{
    // enum screenType {
    //     Menu, Select, SinglyLinkedList;
    // };
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
    
    // menuScreen mainMenu;
    // initMenuScreen(mainMenu);


    SLL mySLL;
    createList(mySLL);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            // if (event.type == sf::Event::Closed)
            //     window.close();
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        mySLL.drawList(window);
        window.display();    
    }
    return 0;
}