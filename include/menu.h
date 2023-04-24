#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "button.h"

class initialScreen {
private:
    button startButton, aboutButton, exitButton;
public:
    void drawInitialScreen(sf::RenderWindow &window);
};

class menuScreen {
private:
    enum menuButtonType {
        idle,
        initial,
        chooseDataStructure
    };
    menuButtonType MenuType;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    int logoDistance;
    bool isChosen;
public:
    menuScreen();
    bool logoIsClick(sf::RenderWindow &window);
    void drawLogo(sf::RenderWindow &window);

    void processMouseEvent(sf::RenderWindow &window);

    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    void drawMenuScreen(sf::RenderWindow &window);
};

float getDistance(sf::Vector2f pointX, sf::Vector2f pointY);

#endif