#ifndef MENUCHOOSELLSCREEN_H
#define MENUCHOOSELLSCREEN_H

#include <SFML/Graphics.hpp>
#include "button.h"

class chooseLinkedListScreen {
private:
    button SLLButton, DLLButton, CLLButton;
    int buttonOpacity, moveDistance;
    int SLLHoverDistance;
    int DLLHoverDistance;
    int CLLHoverDistance;
    bool chooseLLScreenIsChosen;
public:
    chooseLinkedListScreen();
    void onScreen();
    void offScreen();

    bool SLLButtonIsClick(sf::RenderWindow &window);
    bool DLLButtonIsClick(sf::RenderWindow &window);
    bool CLLButtonIsClick(sf::RenderWindow &window);

    void buttonIsHover(sf::RenderWindow &window);

    void drawChooseLLScreen(sf::RenderWindow &window);
};

#endif