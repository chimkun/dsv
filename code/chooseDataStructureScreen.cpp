#include "chooseDataStructureScreen.h"


chooseDataStructureScreen::chooseDataStructureScreen() {
    sf::Texture linkedListButtonTexture, arrayButtonTexture, stackButtonTexture, queueButtonTexture;
    if (!linkedListButtonTexture.loadFromFile("src//include//texture//menuChooseLLButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!arrayButtonTexture.loadFromFile("src//include//texture//menuChooseArrayButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!stackButtonTexture.loadFromFile("src//include//texture//menuChooseStackButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    if (!queueButtonTexture.loadFromFile("src//include//texture//menuChooseQueueButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    std::string linkedListString = "Linked list", arrayString = "Array", stackString = "Stack", queueString = "Queue";
    linkedListButton = button(menuButtonConstants::buttonPos4Button[0], linkedListButtonTexture, linkedListString);
    arrayButton = button(menuButtonConstants::buttonPos4Button[1], arrayButtonTexture, arrayString);
    stackButton = button(menuButtonConstants::buttonPos4Button[2], stackButtonTexture, stackString);
    queueButton = button(menuButtonConstants::buttonPos4Button[3], queueButtonTexture, queueString);
    buttonOpacity = 0;
    moveDistance = linkedListHoverDistance = arrayHoverDistance = stackHoverDistance = queueHoverDistance = 0;
    chooseDataStructureScreenIsChosen = 0;
}
void chooseDataStructureScreen::onScreen() {
    chooseDataStructureScreenIsChosen = 1;
}
void chooseDataStructureScreen::offScreen() {
    chooseDataStructureScreenIsChosen = 0;
    linkedListHoverDistance = arrayHoverDistance = stackHoverDistance = queueHoverDistance = 0;
}

bool chooseDataStructureScreen::linkedListButtonIsClick(sf::RenderWindow &window) {
    return linkedListButton.buttonIsClick(window);
}
bool chooseDataStructureScreen::arrayButtonIsClick(sf::RenderWindow &window) {
    return arrayButton.buttonIsClick(window);
}
bool chooseDataStructureScreen::stackButtonIsClick(sf::RenderWindow &window) {
    return stackButton.buttonIsClick(window);
}
bool chooseDataStructureScreen::queueButtonIsClick(sf::RenderWindow &window) {
    return queueButton.buttonIsClick(window);
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
    
    stackButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[2].x + moveDistance + stackHoverDistance, 
                                        menuButtonConstants::buttonPos4Button[2].y);
    stackButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);

    queueButton.buttonSprite.setPosition(menuButtonConstants::buttonPos4Button[3].x + moveDistance + queueHoverDistance, 
                                        menuButtonConstants::buttonPos4Button[3].y);
    queueButton.drawButtonOptional(window, 0.41, 0.15, 62, buttonOpacity);

}

