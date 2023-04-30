#include "menuChooseLLScreen.h"

chooseLinkedListScreen::chooseLinkedListScreen() {
    sf::Texture SLLButtonTexture, DLLButtonTexture, CLLButtonTexture, backButtonTexture;
    if (!SLLButtonTexture.loadFromFile("src//include//texture//menuSLLButton.png")) {
        std::cout << "texture file not found\n";
        exit(-1);
    }
    if (!DLLButtonTexture.loadFromFile("src//include//texture//menuDLLButton.png")) {
        std::cout << "texture file not found\n";
        exit(-1);
    }
    if (!CLLButtonTexture.loadFromFile("src//include//texture//menuCLLButton.png")) {
        std::cout << "texture file not found\n";
        exit(-1);
    }
    if (!backButtonTexture.loadFromFile("src//include//texture//menuChooseReturnButton.png")) {
        std::cout << "texture file not found\n";
        exit(-1);
    }
    std::string SLLString = "Singly", DLLString = "Doubly", CLLString = "Circular", backString = "Back";
    SLLButton = button(menuButtonConstants::buttonPos4Button[0], SLLButtonTexture, SLLString);
    DLLButton = button(menuButtonConstants::buttonPos4Button[1], DLLButtonTexture, DLLString);
    CLLButton = button(menuButtonConstants::buttonPos4Button[2], CLLButtonTexture, CLLString);
    backButton = button(menuButtonConstants::buttonPos4Button[3], backButtonTexture, backString);
    buttonOpacity = moveDistance = 0;
    SLLHoverDistance = DLLHoverDistance = CLLHoverDistance = 0;
    chooseLLScreenIsChosen = 0;
}

void chooseLinkedListScreen::onScreen() {
    chooseLLScreenIsChosen = 1;
}
void chooseLinkedListScreen::offScreen() {
    chooseLLScreenIsChosen = 0;
}

bool chooseLinkedListScreen::SLLButtonIsClick(sf::RenderWindow &window) {
    return SLLButton.buttonIsClick(window);
}
bool chooseLinkedListScreen::DLLButtonIsClick(sf::RenderWindow &window) {
    return DLLButton.buttonIsClick(window);
}
bool chooseLinkedListScreen::CLLButtonIsClick(sf::RenderWindow &window) {
    return CLLButton.buttonIsClick(window);
}
bool chooseLinkedListScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backButton.buttonIsClick(window);
}

void chooseLinkedListScreen::buttonIsHover(sf::RenderWindow &window) {
    if (SLLButton.buttonIsHover(window)) {
        SLLHoverDistance = std::min(menuButtonConstants::maxHoverDistance, SLLHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        SLLHoverDistance = std::max(0, SLLHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (DLLButton.buttonIsHover(window)) {
        DLLHoverDistance = std::min(menuButtonConstants::maxHoverDistance, DLLHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        DLLHoverDistance = std::max(0, DLLHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (CLLButton.buttonIsHover(window)) {
        CLLHoverDistance = std::min(menuButtonConstants::maxHoverDistance, CLLHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        CLLHoverDistance = std::max(0, CLLHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (backButton.buttonIsHover(window)) {
        backHoverDistance = std::min(menuButtonConstants::maxHoverDistance, backHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        backHoverDistance = std::max(0, backHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
}

void chooseLinkedListScreen::drawChooseLLScreen(sf::RenderWindow &window) {
    if (chooseLLScreenIsChosen) {
        moveDistance = std::min(moveDistance + menuButtonConstants::moveSpeed, menuButtonConstants::maxMoveDistance);
        buttonOpacity = std::min(buttonOpacity + menuButtonConstants::buttonFadeInSpeed, 255);
    }
    else {
        moveDistance = std::max(moveDistance - menuButtonConstants::moveOutSpeed, 0);
        buttonOpacity = std::max(buttonOpacity - menuButtonConstants::buttonFadeOutSpeed, 0);
    }
    SLLButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[0].x + moveDistance + SLLHoverDistance, 
                                         menuButtonConstants::buttonPos4Button[0].y);
    SLLButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);

    DLLButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[1].x + moveDistance + DLLHoverDistance, 
                                         menuButtonConstants::buttonPos4Button[1].y);
    DLLButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
    
    CLLButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[2].x + moveDistance + CLLHoverDistance, 
                                        menuButtonConstants::buttonPos4Button[2].y);
    CLLButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
    
    backButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[3].x + moveDistance + backHoverDistance, 
                                        menuButtonConstants::buttonPos4Button[3].y);
    backButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
}