#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "chooseDataStructureScreen.h"
#include "menuInitialScreen.h"
#include "menuChooseLLScreen.h"
#include "button.h"
#include "background.h"

class menuScreen {
private:
    enum menuButtonType {
        initial,
        chooseDataStructure,
        chooseLL
    };
    enum dataStructureType {
        none, SLL, DLL, CLL,
        array, dArray,
        stack, queue
    };
    button backButton;

    menuButtonType MenuType;
    dataStructureType DSType;

    initialScreen MenuInitialScreen;
    chooseDataStructureScreen MenuChooseDSScreen;
    chooseLinkedListScreen MenuChooseLLScreen;

    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    int logoDistance, backgroundOpacity;
    bool isChosen;
    background menuBackground;
    sf::Clock offTimer;
    sf::RectangleShape backHighlight;

public:
    menuScreen();
    bool logoIsClick(sf::RenderWindow &window);
    void drawLogo(sf::RenderWindow &window);

    void onLogo();
    void offLogo();
    void offAllScreen();
    void processMouseEvent(sf::RenderWindow &window);

    void backButtonHover(sf::RenderWindow &window);

    void menuTypeSetInitial();
    int getDSType();

    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    void drawMenuScreen(sf::RenderWindow &window);
};

float getDistance(sf::Vector2f pointX, sf::Vector2f pointY);

#endif