#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "menu.h"
#include "LLscreen.h"

int main()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
    window.clear(sf::Color::Blue);
    window.display();

    menuScreen mainMenu;
    initMenuScreen(mainMenu);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
        }
        window.clear();
        mainMenu.drawMenu(window);
        window.display();    
    }
    return 0;
}