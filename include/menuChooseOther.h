#ifndef MENUCHOOSEOTHER_H
#define MENUCHOOSEOTHER_H

#include "button.h"

class chooseOtherScreen {
private:
    button stackButton, queueButton, backButton;
    int buttonOpacity, moveDistance;
    int stackHoverDistance;
    int queueHoverDistance;
    int backHoverDistance;
    bool chooseOtherScreenIsChosen;
public:
    chooseOtherScreen();
    void onScreen();
    void offScreen();

    bool stackButtonIsClick(sf::RenderWindow &window);
    bool queueButtonIsClick(sf::RenderWindow &window);
    bool backButtonIsClick(sf::RenderWindow &window);

    void buttonIsHover(sf::RenderWindow &window);

    void drawChooseOtherScreen(sf::RenderWindow &window);
};

#endif