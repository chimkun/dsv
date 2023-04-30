#include "menuChooseArray.h"

chooseArrayScreen::chooseArrayScreen() {
    sf::Texture staticButtonTexture, dynamicButtonTexture, backButtonTexture;
    if (!staticButtonTexture.loadFromFile("src//include//texture//menuStaticButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!dynamicButtonTexture.loadFromFile("src//include//texture//menuDynamicButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!backButtonTexture.loadFromFile("src//include//texture//menuExitButton3.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    std::string staticString = "Static", dynamicString = "Dynamic", backString = "Back";
    staticButton = button(menuButtonConstants::buttonPos3Button[0], staticButtonTexture, staticString);
    dynamicButton = button(menuButtonConstants::buttonPos3Button[1], dynamicButtonTexture, dynamicString);
    backButton = button(menuButtonConstants::buttonPos3Button[2], backButtonTexture, backString);
    buttonOpacity = 0;
    moveDistance = staticHoverDistance = dynamicHoverDistance = backHoverDistance = 0;
    chooseArrayScreenIsChosen = 0;
}
void chooseArrayScreen::onScreen() {
    chooseArrayScreenIsChosen = 1;
}
void chooseArrayScreen::offScreen() {
    chooseArrayScreenIsChosen = 0;
    staticHoverDistance = dynamicHoverDistance = backHoverDistance = 0;
}

bool chooseArrayScreen::staticButtonIsClick(sf::RenderWindow &window) {
    return staticButton.buttonIsClick(window);
}
bool chooseArrayScreen::dynamicButtonIsClick(sf::RenderWindow &window) {
    return dynamicButton.buttonIsClick(window);
}
bool chooseArrayScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backButton.buttonIsClick(window);
}

void chooseArrayScreen::buttonIsHover(sf::RenderWindow &window) {
    if (staticButton.buttonIsHover(window)) {
        staticHoverDistance = std::min(menuButtonConstants::maxHoverDistance, staticHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        staticHoverDistance = std::max(0, staticHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (dynamicButton.buttonIsHover(window)) {
        dynamicHoverDistance = std::min(menuButtonConstants::maxHoverDistance, dynamicHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        dynamicHoverDistance = std::max(0, dynamicHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
    
    if (backButton.buttonIsHover(window)) {
        backHoverDistance = std::min(menuButtonConstants::maxHoverDistance, backHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        backHoverDistance = std::max(0, backHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
}

void chooseArrayScreen::drawChooseArrayScreen(sf::RenderWindow &window) {
    if (chooseArrayScreenIsChosen) {
        moveDistance = std::min(moveDistance + menuButtonConstants::moveSpeed, menuButtonConstants::maxMoveDistance);
        buttonOpacity = std::min(buttonOpacity + menuButtonConstants::buttonFadeInSpeed, 255);
    }
    else {
        moveDistance = std::max(moveDistance - menuButtonConstants::moveOutSpeed, 0);
        buttonOpacity = std::max(buttonOpacity - menuButtonConstants::buttonFadeOutSpeed, 0);
    }
    staticButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[0].x + moveDistance + staticHoverDistance, 
                                         menuButtonConstants::buttonPos3Button[0].y);
    staticButton.drawButtonOptional(window, 0.41, 0.2, 48, buttonOpacity);

    dynamicButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[1].x + moveDistance + dynamicHoverDistance, 
                                         menuButtonConstants::buttonPos3Button[1].y);
    dynamicButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);

    backButton.buttonSprite.setPosition(menuButtonConstants::buttonPos3Button[2].x + moveDistance + backHoverDistance, 
                                        menuButtonConstants::buttonPos3Button[2].y);
    backButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
}

