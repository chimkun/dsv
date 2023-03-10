#ifndef MENU_H
#define MENU_H

#include "button.h"


class menuScreen {
private:
    sf::Text title;
    Button selectButton;
    Button aboutButton;
public:
    void initTitle(std::string &inputTitle, int titleSize, sf::Font &font);
    void setTitlePosition(sf::Vector2f titlePosition);
};

void menuScreen::initTitle(std::string &inputTitle, int titleSize, sf::Font &font) {
    title.setString(inputTitle);
    title.setCharacterSize(titleSize);
    title.setFont(font);
    title.setFillColor(sf::Color::White);
}

void menuScreen::setTitlePosition(sf::Vector2f titlePosition) {
    title.setPosition(titlePosition);
}

#endif