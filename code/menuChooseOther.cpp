#include "menuChooseOther.h"

chooseOtherScreen::chooseOtherScreen() {
    sf::Texture stackButtonTexture, queueButtonTexture, backButtonTexture;
    if (!stackButtonTexture.loadFromFile("src//include//texture//menuChooseStackButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!queueButtonTexture.loadFromFile("src//include//texture//menuChooseQueueButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!backButtonTexture.loadFromFile("src//include//texture//menuExitButton3.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    std::string stackString = "Stack", queueString = "Queue", backString = "Back";
    stackButton = button(menuButtonConstants::buttonPos3Button[0], stackButtonTexture, stackString);
    queueButton = button(menuButtonConstants::buttonPos3Button[1], queueButtonTexture, queueString);
    backButton = button(menuButtonConstants::buttonPos3Button[2], backButtonTexture, backString);
    buttonOpacity = 0;
    moveDistance = stackHoverDistance = queueHoverDistance = backHoverDistance = 0;
    chooseOtherScreenIsChosen = 0;
}
void chooseOtherScreen::onScreen() {
    chooseOtherScreenIsChosen = 1;
}
void chooseOtherScreen::offScreen() {
    chooseOtherScreenIsChosen = 0;
    stackHoverDistance = queueHoverDistance = backHoverDistance = 0;
}

bool chooseOtherScreen::stackButtonIsClick(sf::RenderWindow &window) {
    return stackButton.buttonIsClick(window);
}
bool chooseOtherScreen::queueButtonIsClick(sf::RenderWindow &window) {
    return queueButton.buttonIsClick(window);
}
bool chooseOtherScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backButton.buttonIsClick(window);
}

void chooseOtherScreen::buttonIsHover(sf::RenderWindow &window) {
    if (stackButton.buttonIsHover(window)) {
        stackHoverDistance = std::min(menuButtonConstants::maxHoverDistance, stackHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        stackHoverDistance = std::max(0, stackHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (queueButton.buttonIsHover(window)) {
        queueHoverDistance = std::min(menuButtonConstants::maxHoverDistance, queueHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        queueHoverDistance = std::max(0, queueHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
    
    if (backButton.buttonIsHover(window)) {
        backHoverDistance = std::min(menuButtonConstants::maxHoverDistance, backHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        backHoverDistance = std::max(0, backHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
}

void chooseOtherScreen::drawChooseOtherScreen(sf::RenderWindow &window) {
    if (chooseOtherScreenIsChosen) {
        moveDistance = std::min(moveDistance + menuButtonConstants::moveSpeed, menuButtonConstants::maxMoveDistance);
        buttonOpacity = std::min(buttonOpacity + menuButtonConstants::buttonFadeInSpeed, 255);
    }
    else {
        moveDistance = std::max(moveDistance - menuButtonConstants::moveOutSpeed, 0);
        buttonOpacity = std::max(buttonOpacity - menuButtonConstants::buttonFadeOutSpeed, 0);
    }
    stackButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[0].x + moveDistance + stackHoverDistance, 
                                         menuButtonConstants::buttonPos3Button[0].y);
    stackButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);

    queueButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[1].x + moveDistance + queueHoverDistance, 
                                         menuButtonConstants::buttonPos3Button[1].y);
    queueButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);

    backButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[2].x + moveDistance + backHoverDistance, 
                                        menuButtonConstants::buttonPos3Button[2].y);
    backButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
}

