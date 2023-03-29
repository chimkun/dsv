#ifndef MENU_H
#define MENU_H

#include "button.h"

class menuScreen {
private:
    sf::Text title;
    Button selectButton;
    Button aboutButton;
public:
    menuScreen();
    void initTitle(std::string &inputTitle, int titleSize);
    void setTitlePosition(sf::Vector2f &titlePosition);
    void initSelectButton(sf::Vector2f &selectButtonSize, std::string &selectButtonText, 
                          int textCharSize, sf::Vector2f selectButtonPosition);
    void initAboutButton(sf::Vector2f &selectButtonSize, std::string &aboutButtonText, 
                          int textCharSize, sf::Vector2f aboutButtonPosition);
    void drawMenu(sf::RenderWindow &window);
};

void initMenuScreen(menuScreen &mainMenu);

void drawMenuScreen(menuScreen &mainMenu, sf::RenderWindow &window);

#endif