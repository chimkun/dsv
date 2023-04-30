#ifndef CHOOSEDATASTRUCTURESCREEN_H
#define CHOOSEDATASTRUCTURESCREEN_H

#include "button.h"

class chooseDataStructureScreen {
private:
    button linkedListButton, arrayButton, otherButton, backButton;
    int buttonOpacity, moveDistance;
    int linkedListHoverDistance;
    int arrayHoverDistance;
    int otherHoverDistance;
    int backHoverDistance;
    bool chooseDataStructureScreenIsChosen;
public:
    chooseDataStructureScreen();
    void onScreen();
    void offScreen();

    bool linkedListButtonIsClick(sf::RenderWindow &window);
    bool arrayButtonIsClick(sf::RenderWindow &window);
    bool otherButtonIsClick(sf::RenderWindow &window);
    bool backButtonIsClick(sf::RenderWindow &window);

    void buttonIsHover(sf::RenderWindow &window);

    void drawChooseDSScreen(sf::RenderWindow &window);
};

#endif