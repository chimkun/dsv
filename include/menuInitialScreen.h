#ifndef MENUINITIALSCREEN_H
#define MENUINITIALSCREEN_H

#include "button.h"

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

    bool screenIsChosen();

    bool startButtonIsClick(sf::RenderWindow &window);
    bool aboutButtonIsClick(sf::RenderWindow &window);
    bool exitButtonIsClick(sf::RenderWindow &window);

    void buttonIsHover(sf::RenderWindow &window);

    void drawInitialScreen(sf::RenderWindow &window);
};

#endif