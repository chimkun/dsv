#ifndef MENU_H
#define MENU_H

#include <cmath>
#include "chooseDataStructureScreen.h"
#include "menuInitialScreen.h"
#include "menuChooseLLScreen.h"
#include "menuChooseArray.h"
#include "button.h"
#include "background.h"

class menuScreen {
private:
    enum menuButtonType {
        initial,
        chooseDataStructure,
        chooseLL,
        chooseArray
    };
    enum dataStructureType {
        none, SLL, DLL, CLL,
        array, sArray, dArray,
        stack, queue
    };

    menuButtonType MenuType;
    dataStructureType DSType;

    initialScreen MenuInitialScreen;
    chooseDataStructureScreen MenuChooseDSScreen;
    chooseLinkedListScreen MenuChooseLLScreen;
    chooseArrayScreen MenuChooseArrayScreen;

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

    void menuTypeSetInitial();
    int getDSType();
    void backToMenu();

    void processAllEvent(sf::RenderWindow &window, sf::Event &event);
    void drawMenuScreen(sf::RenderWindow &window);
};

float getDistance(sf::Vector2f pointX, sf::Vector2f pointY);

#endif