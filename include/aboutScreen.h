#ifndef ABOUTSCREEN_H
#define ABOUTSCREEN_H

#include "constants.h"
#include "button.h"
#include "text.h"
#include "background.h"

class aboutScreen {
private:
    sf::RectangleShape bgBlend, textFrame;
    button backButton;
    textInfo aboutText;
    std::string aboutString;
    bool isOn;
    int blendOpacity, textOpacity;
    background aboutBg;
public:
    aboutScreen();
    bool backButtonIsClick(sf::RenderWindow &window);
    void drawAboutScreen(sf::RenderWindow &window);
};

#endif