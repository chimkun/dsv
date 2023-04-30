#include "chooseDataStructureScreen.h"


chooseDataStructureScreen::chooseDataStructureScreen() {
    sf::Texture linkedListButtonTexture, arrayButtonTexture, otherButtonTexture, returnButtonTexture;
    if (!linkedListButtonTexture.loadFromFile("src//include//texture//menuChooseLLButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!arrayButtonTexture.loadFromFile("src//include//texture//menuChooseArrayButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!otherButtonTexture.loadFromFile("src//include//texture//menuChooseOtherButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!returnButtonTexture.loadFromFile("src//include//texture//menuChooseReturnButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    std::string linkedListString = "Linked list", arrayString = "Array", otherString = "Other", returnString = "Back";
    linkedListButton = button(menuButtonConstants::buttonPos4Button[0], linkedListButtonTexture, linkedListString);
    arrayButton = button(menuButtonConstants::buttonPos4Button[1], arrayButtonTexture, arrayString);
    otherButton = button(menuButtonConstants::buttonPos4Button[2], otherButtonTexture, otherString);
    backButton = button(menuButtonConstants::buttonPos4Button[3], returnButtonTexture, returnString);
    buttonOpacity = 0;
    moveDistance = linkedListHoverDistance = arrayHoverDistance = otherHoverDistance = backHoverDistance = 0;
    chooseDataStructureScreenIsChosen = 0;
}
void chooseDataStructureScreen::onScreen() {
    chooseDataStructureScreenIsChosen = 1;
}
void chooseDataStructureScreen::offScreen() {
    chooseDataStructureScreenIsChosen = 0;
    linkedListHoverDistance = arrayHoverDistance = otherHoverDistance = backHoverDistance = 0;
}

bool chooseDataStructureScreen::linkedListButtonIsClick(sf::RenderWindow &window) {
    return linkedListButton.buttonIsClick(window);
}
bool chooseDataStructureScreen::arrayButtonIsClick(sf::RenderWindow &window) {
    return arrayButton.buttonIsClick(window);
}
bool chooseDataStructureScreen::otherButtonIsClick(sf::RenderWindow &window) {
    return otherButton.buttonIsClick(window);
}
bool chooseDataStructureScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backButton.buttonIsClick(window);
}

void chooseDataStructureScreen::buttonIsHover(sf::RenderWindow &window) {
    if (linkedListButton.buttonIsHover(window)) {
        linkedListHoverDistance = std::min(menuButtonConstants::maxHoverDistance, linkedListHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        linkedListHoverDistance = std::max(0, linkedListHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (arrayButton.buttonIsHover(window)) {
        arrayHoverDistance = std::min(menuButtonConstants::maxHoverDistance, arrayHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        arrayHoverDistance = std::max(0, arrayHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }

    if (otherButton.buttonIsHover(window)) {
        otherHoverDistance = std::min(menuButtonConstants::maxHoverDistance, otherHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        otherHoverDistance = std::max(0, otherHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
    
    if (backButton.buttonIsHover(window)) {
        backHoverDistance = std::min(menuButtonConstants::maxHoverDistance, backHoverDistance + menuButtonConstants::hoverMoveSpeed);
    }
    else {
        backHoverDistance = std::max(0, backHoverDistance - menuButtonConstants::hoverFloatBackSpeed);
    }
}

void chooseDataStructureScreen::drawChooseDSScreen(sf::RenderWindow &window) {
    if (chooseDataStructureScreenIsChosen) {
        moveDistance = std::min(moveDistance + menuButtonConstants::moveSpeed, menuButtonConstants::maxMoveDistance);
        buttonOpacity = std::min(buttonOpacity + menuButtonConstants::buttonFadeInSpeed, 255);
    }
    else {
        moveDistance = std::max(moveDistance - menuButtonConstants::moveOutSpeed, 0);
        buttonOpacity = std::max(buttonOpacity - menuButtonConstants::buttonFadeOutSpeed, 0);
    }
    linkedListButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[0].x + moveDistance + linkedListHoverDistance, 
                                         menuButtonConstants::buttonPos4Button[0].y);
    linkedListButton.drawButtonOptional(window, 0.41, 0.2, 48, buttonOpacity);

    arrayButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[1].x + moveDistance + arrayHoverDistance, 
                                         menuButtonConstants::buttonPos4Button[1].y);
    arrayButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
    
    otherButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[2].x + moveDistance + otherHoverDistance, 
                                        menuButtonConstants::buttonPos4Button[2].y);
    otherButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);

    backButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[3].x + moveDistance + backHoverDistance, 
                                        menuButtonConstants::buttonPos4Button[3].y);
    backButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);
}

