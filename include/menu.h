#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "button.h"
#include "background.h"

class chooseDataStructureScreen {

};

class initialScreen {
private:
    button startButton, aboutButton, exitButton;
    int buttonOpacity, moveDistance;
    int startHoverDistance;
    int aboutHoverDistance;
    int exitHoverDistance;
    bool initialScreenIsChosen;
public:
    initialScreen();
    void onScreen();
    void offScreen();

    bool startButtonIsClick(sf::RenderWindow &window);
    bool aboutButtonIsClick(sf::RenderWindow &window);
    bool exitButtonIsClick(sf::RenderWindow &window);

    void buttonIsHover(sf::RenderWindow &window);

    void drawInitialScreen(sf::RenderWindow &window);
};

class menuScreen {
private:
    enum menuButtonType {
        initial,
        chooseDataStructure
    };
    menuButtonType MenuType;
    initialScreen MenuInitialScreen;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    int logoDistance, backgroundOpacity;
    bool isChosen;
    background menuBackground;
    sf::Clock offTimer;
public:
    menuScreen();
    bool logoIsClick(sf::RenderWindow &window);
    void drawLogo(sf::RenderWindow &window);

    void onLogo();
    void offLogo();
    void processMouseEvent(sf::RenderWindow &window);

    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    void drawMenuScreen(sf::RenderWindow &window);
};

float getDistance(sf::Vector2f pointX, sf::Vector2f pointY);

#endif