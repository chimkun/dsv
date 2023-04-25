#ifndef CHOOSEDATASTRUCTURESCREEN_H
#define CHOOSEDATASTRUCTURESCREEN_H

#include <SFML/Graphics.hpp>
#include "button.h"

class chooseDataStructureScreen {
private:
    button linkedListButton, arrayButton, stackButton, queueButton;
    int buttonOpacity, moveDistance;
    int linkedListHoverDistance;
    int arrayHoverDistance;
    int stackHoverDistance;
    int queueHoverDistance;
    bool chooseDataStructureScreenIsChosen;
public:
    chooseDataStructureScreen();
    void onScreen();
    void offScreen();

    bool linkedListButtonIsClick(sf::RenderWindow &window);
    bool arrayButtonIsClick(sf::RenderWindow &window);
    bool stackButtonIsClick(sf::RenderWindow &window);
    bool queueButtonIsClick(sf::RenderWindow &window);

    void buttonIsHover(sf::RenderWindow &window);

    void drawChooseDSScreen(sf::RenderWindow &window);
};

#endif