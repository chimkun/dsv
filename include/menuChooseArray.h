#ifndef MENUCHOOSEARRAY_H
#define MENUCHOOSEARRAY_H

#include "button.h"

class chooseArrayScreen {
private:
    button staticButton, dynamicButton, backButton;
    int buttonOpacity, moveDistance;
    int staticHoverDistance;
    int dynamicHoverDistance;
    int backHoverDistance;
    bool chooseArrayScreenIsChosen;
public:
    chooseArrayScreen();
    void onScreen();
    void offScreen();

    bool staticButtonIsClick(sf::RenderWindow &window);
    bool dynamicButtonIsClick(sf::RenderWindow &window);
    bool backButtonIsClick(sf::RenderWindow &window);

    void buttonIsHover(sf::RenderWindow &window);

    void drawChooseArrayScreen(sf::RenderWindow &window);
};

#endif