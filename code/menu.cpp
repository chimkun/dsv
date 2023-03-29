#include "menu.h"
#include <iostream>

menuScreen::menuScreen() {}

void menuScreen::initTitle(std::string &inputTitle, int titleSize) {
    title.setString(inputTitle);
    title.setCharacterSize(titleSize);
    title.setFillColor(sf::Color::White);
}

void menuScreen::setTitlePosition(sf::Vector2f &titlePosition) {
    title.setPosition(titlePosition);
}

void menuScreen::initSelectButton(sf::Vector2f &selectButtonSize, std::string &selectButtonText,
                                  int textCharSize, sf::Vector2f selectButtonPosition) {
    selectButton = Button(selectButtonSize);
    selectButton.initText(selectButtonText, textCharSize);
    selectButton.setButtonPosition(selectButtonPosition);
}

void menuScreen::initAboutButton(sf::Vector2f &aboutButtonSize, std::string &aboutButtonText,
                                  int textCharSize, sf::Vector2f aboutButtonPosition) {
    aboutButton = Button(aboutButtonSize);
    aboutButton.initText(aboutButtonText, textCharSize);
    aboutButton.setButtonPosition(aboutButtonPosition);
}

void menuScreen::drawMenu(sf::RenderWindow &window) {
    sf::Font font;
    if (!font.loadFromFile("src//font//PlatinumSignOver.ttf")) {
        std::cout << "Font file not found!\n";
        exit(-1);
    }

    title.setFont(font);
    window.draw(title);
    //std::cerr << "HALLP\n";
    selectButton.drawButton(window);
    aboutButton.drawButton(window);
}

void initMenuScreen(menuScreen &mainMenu) {
    //set title
    std::string titleText = "DS VISUALIZER";
    mainMenu.initTitle(titleText, 150);
    sf::Vector2f titlePosition(225, 80);
    mainMenu.setTitlePosition(titlePosition);
    //button size
    sf::Vector2f selectButtonSize(300.f, 150.f);
    sf::Vector2f aboutButtonSize = selectButtonSize;

    //button text
    std::string selectText = "SELECT";
    std::string aboutText = "ABOUT";
    
    int textSize = 50; //same for both type
    //button position
    sf::Vector2f selectButtonPosition(400.f, 400.f);
    sf::Vector2f aboutButtonPosition(1000.f, 400.f);
    
    //init button
    mainMenu.initSelectButton(selectButtonSize, selectText, textSize, selectButtonPosition);
    mainMenu.initAboutButton(aboutButtonSize, aboutText, textSize, aboutButtonPosition);
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
