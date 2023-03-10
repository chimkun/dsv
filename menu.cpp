#include "menu.h"
#include <SFML/Graphics.hpp>

void initMenuScreen(menuScreen &mainMenu, std::string &title, sf::Font font) {
    //set title
    mainMenu.initTitle(title, 40, font);
    sf::Vector2f titlePosition(225, 80);
    mainMenu.setTitlePosition(titlePosition);
    //button size
    sf::Vector2f selectButtonSize(300.f, 150.f);
    sf::Vector2f aboutButtonSize = selectButtonSize;
    //button text
    std::string selectText = "SELECT";
    std::string aboutText = "ABOUT";
    int textSize = 40; //same for both type
    //button position
    sf::Vector2f selectButtonPosition(400.f, 400.f);
    sf::Vector2f aboutButtonPosition(1000.f, 400.f);
    //init button
    mainMenu.initSelectButton(selectButtonSize, selectText, font, textSize, selectButtonPosition);
    mainMenu.initAboutButton(aboutButtonSize, aboutText, font, textSize, aboutButtonPosition);
}

void drawMenuScreen(menuScreen &mainMenu, sf::RenderWindow &window) {
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
}
