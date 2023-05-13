#include "menuInitialScreen.h"

initialScreen::initialScreen() {
    sf::Texture startButtonTexture, aboutButtonTexture, exitButtonTexture;
    if (!startButtonTexture.loadFromFile("src//include//texture//menuStartButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!aboutButtonTexture.loadFromFile("src//include//texture//menuAboutButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!exitButtonTexture.loadFromFile("src//include//texture//menuExitButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    std::string startButtonString = "Start", aboutButtonString = "About", exitButtonString = "Exit";
    startButton = button(menuButtonConstants::buttonPos3Button[0], startButtonTexture, startButtonString);
    aboutButton = button(menuButtonConstants::buttonPos3Button[1], aboutButtonTexture, aboutButtonString);
    exitButton = button(menuButtonConstants::buttonPos3Button[2], exitButtonTexture, exitButtonString);
    buttonOpacity = 0;
    moveDistance = startHoverDistance = aboutHoverDistance = exitHoverDistance = 0;
    initialScreenIsChosen = 0;
}
void initialScreen::onScreen() {
    initialScreenIsChosen = 1;

}
void initialScreen::offScreen() {
    initialScreenIsChosen = 0;
    startHoverDistance = aboutHoverDistance = exitHoverDistance = 0;
}

bool initialScreen::screenIsChosen() {
    return initialScreenIsChosen;
}

bool initialScreen::startButtonIsClick(sf::RenderWindow &window) {
    return startButton.buttonIsClick(window);
}
bool initialScreen::aboutButtonIsClick(sf::RenderWindow &window) {
    return aboutButton.buttonIsClick(window);
}
bool initialScreen::exitButtonIsClick(sf::RenderWindow &window) {
    return exitButton.buttonIsClick(window);
}

void initialScreen::buttonIsHover(sf::RenderWindow &window) {
    if (startButton.buttonIsHover(window)) {
        startHoverDistance = std::min(menuButtonConstants::maxHoverDistance, startHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        startHoverDistance = std::max(0, startHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (aboutButton.buttonIsHover(window)) {
        aboutHoverDistance = std::min(menuButtonConstants::maxHoverDistance, aboutHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        aboutHoverDistance = std::max(0, aboutHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (exitButton.buttonIsHover(window)) {
        exitHoverDistance = std::min(menuButtonConstants::maxHoverDistance, exitHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        exitHoverDistance = std::max(0, exitHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
}

/// @brief 
/// @param window 
void initialScreen::drawInitialScreen(sf::RenderWindow &window) {
    if (initialScreenIsChosen) {
        moveDistance = std::min(moveDistance + menuButtonConstants::moveSpeed, menuButtonConstants::maxMoveDistance);
        buttonOpacity = std::min(buttonOpacity + menuButtonConstants::buttonFadeInSpeed, 255);
    }
    else {
        moveDistance = std::max(moveDistance - menuButtonConstants::moveOutSpeed, 0);
        buttonOpacity = std::max(buttonOpacity - menuButtonConstants::buttonFadeOutSpeed, 0);
    }
    startButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[0].x + moveDistance + startHoverDistance, 
                                         menuButtonConstants::buttonPos3Button[0].y);
    startButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
    aboutButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[1].x + moveDistance + aboutHoverDistance, 
                                         menuButtonConstants::buttonPos3Button[1].y);
    aboutButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
    
    exitButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[2].x + moveDistance + exitHoverDistance, 
                                        menuButtonConstants::buttonPos3Button[2].y);
    exitButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
}