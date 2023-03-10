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
    void initTitle(std::string &inputTitle, int titleSize, sf::Font &font);
    void setTitlePosition(sf::Vector2f &titlePosition);
    void initSelectButton(sf::Vector2f &selectButtonSize, std::string &selectButtonText, sf::Font font,
                          int textCharSize, sf::Vector2f selectButtonPosition);
    // void initSelectButtonSize(sf::Vector2f &selectButtonSize);
    // void initSelectButtonText(std::string &selectButtonText, sf::Font font, int textCharSize);
    // void initSelectButtonPosition(sf::Vector2f selectButtonPosition);
    void initAboutButton(sf::Vector2f &selectButtonSize, std::string &aboutButtonText, sf::Font font,
                          int textCharSize, sf::Vector2f aboutButtonPosition);
    // void initAboutButtonSize(sf::Vector2f &aboutButtonSize);
    // void initAboutButtonText(std::string &aboutButtonText, sf::Font font, int textCharSize);
    // void initAboutButtonPosition(sf::Vector2f &aboutButtonPosition);
    void drawMenu(sf::RenderWindow &window);
};

menuScreen::menuScreen() {}

void menuScreen::initTitle(std::string &inputTitle, int titleSize, sf::Font &font) {
    title.setString(inputTitle);
    title.setCharacterSize(titleSize);
    title.setFont(font);
    title.setFillColor(sf::Color::White);
}

void menuScreen::setTitlePosition(sf::Vector2f &titlePosition) {
    title.setPosition(titlePosition);
}

// void menuScreen::initSelectButtonSize(sf::Vector2f &selectButtonSize) {
//     selectButton = Button(selectButtonSize);
// }
// void menuScreen::initSelectButtonText(std::string &selectButtonText, sf::Font font, int textCharSize) {
//     selectButton.initText(selectButtonText, font, textCharSize);
// }
// void menuScreen::initSelectButtonPosition(sf::Vector2f selectButtonPosition) {
//     selectButton.setButtonPosition(selectButtonPosition);
// }
void menuScreen::initSelectButton(sf::Vector2f &selectButtonSize, std::string &selectButtonText, sf::Font font,
                                  int textCharSize, sf::Vector2f selectButtonPosition) {
    selectButton = Button(selectButtonSize);
    selectButton.initText(selectButtonText, font, textCharSize);
    selectButton.setButtonPosition(selectButtonPosition);
}

// void menuScreen::initAboutButtonSize(sf::Vector2f &aboutButtonSize) {
//     aboutButton = Button(aboutButtonSize);
// }
// void menuScreen::initAboutButtonText(std::string &aboutButtonText, sf::Font font, int textCharSize) {
//     aboutButton.initText(aboutButtonText, font, textCharSize);
// }
// void menuScreen::initAboutButtonPosition(sf::Vector2f &aboutButtonPosition) {
//     aboutButton.setButtonPosition(aboutButtonPosition);
// }
void menuScreen::initAboutButton(sf::Vector2f &aboutButtonSize, std::string &aboutButtonText, sf::Font font,
                                  int textCharSize, sf::Vector2f aboutButtonPosition) {
    aboutButton = Button(aboutButtonSize);
    aboutButton.initText(aboutButtonText, font, textCharSize);
    aboutButton.setButtonPosition(aboutButtonPosition);
}

void menuScreen::drawMenu(sf::RenderWindow &window) {
    window.draw(title);
    selectButton.drawButton(window);
    aboutButton.drawButton(window);
}

void initMenuScreen(menuScreen &mainMenu, std::string &title);

void drawMenuScreen(menuScreen &mainMenu, sf::RenderWindow &window);

#endif