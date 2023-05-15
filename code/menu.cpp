#include "menu.h"

menuScreen::menuScreen() {
    if (!logoTexture.loadFromFile("src//include//texture//logo.png")) {
        std::cout << "texture file not found! (logo.png)\n";
        exit(-1);
    }
    logoSprite.setTexture(logoTexture);
    sf::IntRect spriteBound = logoSprite.getTextureRect();
    logoSprite.setOrigin((float) spriteBound.width / 2.0, (float) spriteBound.height / 2.0);
    logoSprite.setPosition(logoConstants::logoCenter);
    
    MenuType = initial;
    DSType = none;

    backgroundOpacity = 255;
    isChosen = 0;

    sf::Texture backButtonTexture;
    if (!backButtonTexture.loadFromFile("src//include//texture//menuBackButton.png")) {
        std::cout << "texture file not found!\n";
        exit(-1);
    }
    backHighlight.setPosition(menuButtonConstants::backButtonPosition);
    backHighlight.setSize(sf::Vector2f(311.523, 148.574));
    sf::Color backHighlightColor = sf::Color(130, 130, 130, 100);
    backHighlight.setFillColor(backHighlightColor);
}

bool menuScreen::logoIsClick(sf::RenderWindow &window) {
    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
    float mouseToCenterDistance = getDistance(mousePosition, logoConstants::logoCenter);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseToCenterDistance <= logoConstants::logoRadius) {
        return true;
    }
    return false;
}
void menuScreen::onLogo() {
    isChosen = 1;
    offTimer.restart();
    MenuInitialScreen.onScreen();
}
void menuScreen::offLogo() {
    isChosen = 0;
    MenuInitialScreen.offScreen();
}

void menuScreen::drawLogo(sf::RenderWindow &window) {
    sf::Vector2f logoPosition = logoSprite.getPosition();
    if (isChosen && offTimer.getElapsedTime().asSeconds() > 7.5) {
        offLogo();
        offAllScreen();
    }
    if (isChosen) {
        logoPosition.x = std::max(logoPosition.x - logoConstants::logoMoveSpeed, 
                                  logoConstants::logoCenter.x - logoConstants::minMoveDistance);
        backgroundOpacity = std::max(logoConstants::backgroundMinOpacity, backgroundOpacity - logoConstants::backgroundFadeSpeed);
    }
    else {
        logoPosition.x = std::min(logoPosition.x + logoConstants::logoFloatSpeed,
                                  logoConstants::logoCenter.x);
        backgroundOpacity = std::min(255, backgroundOpacity + logoConstants::backgroundFadeSpeed);
    }
    logoSprite.setPosition(logoPosition);
    window.draw(logoSprite);
}

void menuScreen::processMouseEvent(sf::RenderWindow &window) {
    drawLogo(window);
    if (!isChosen) {
        if (logoIsClick(window)) {
            onLogo();
            switch (MenuType) {
                case initial:
                    offAllScreen();
                    MenuInitialScreen.onScreen();
                    break;
                case chooseDataStructure:
                    offAllScreen();
                    MenuChooseDSScreen.onScreen();
                    break;
                case chooseLL:
                    offAllScreen();
                    MenuChooseLLScreen.onScreen();
                    break;
                case chooseOther:
                    offAllScreen();
                    MenuChooseOtherScreen.onScreen();
                    break;
            }
        }
        else {
            offAllScreen();
        }
    }
    else {
        switch (MenuType) {
            case initial:
                if (MenuInitialScreen.startButtonIsClick(window)) {
                    MenuType = chooseDataStructure;
                    offAllScreen();
                    onLogo();
                    MenuChooseDSScreen.onScreen();
                }
                if (MenuInitialScreen.aboutButtonIsClick(window)) {
                    offAllScreen();
                    onLogo();
                    DSType = about;
                }
                if (MenuInitialScreen.exitButtonIsClick(window)) {
                    offAllScreen();
                    window.close();
                }
                break;
            case chooseDataStructure:
                if (MenuChooseDSScreen.backButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    onLogo();
                    MenuInitialScreen.onScreen();
                }
                if (MenuChooseDSScreen.linkedListButtonIsClick(window)) {
                    MenuType = chooseLL;
                    offAllScreen();
                    onLogo();
                    MenuChooseLLScreen.onScreen();
                }
                if (MenuChooseDSScreen.arrayButtonIsClick(window)) {
                    MenuType = chooseArray;
                    offAllScreen();
                    onLogo();
                    MenuChooseArrayScreen.onScreen();
                }
                if (MenuChooseDSScreen.otherButtonIsClick(window)) {
                    MenuType = chooseOther;
                    offAllScreen();
                    onLogo();
                    MenuChooseOtherScreen.onScreen();
                }
                break;
            case chooseLL:
                if (MenuChooseLLScreen.backButtonIsClick(window)) {
                    MenuType = chooseDataStructure;
                    offAllScreen();
                    onLogo();
                    MenuChooseDSScreen.onScreen();
                }
                else if (MenuChooseLLScreen.SLLButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    offLogo();
                    DSType = SLL;
                }
                else if (MenuChooseLLScreen.DLLButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    offLogo();
                    DSType = DLL;
                }
                else if (MenuChooseLLScreen.CLLButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    offLogo();
                    DSType = CLL;
                }
                break;
            case chooseArray:
                if (MenuChooseArrayScreen.backButtonIsClick(window)) {
                    MenuType = chooseDataStructure;
                    offAllScreen();
                    onLogo();
                    MenuChooseDSScreen.onScreen();
                }
                else if (MenuChooseArrayScreen.staticButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    offLogo();
                    DSType = sArray;
                }
                else if (MenuChooseArrayScreen.dynamicButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    offLogo();
                    DSType = dArray;
                }
                break;
            case chooseOther:
                if (MenuChooseOtherScreen.stackButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    offLogo();
                    DSType = Stack;
                }
                if (MenuChooseOtherScreen.queueButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    offLogo();
                    DSType = Queue;
                }
                if (MenuChooseOtherScreen.backButtonIsClick(window)) {
                    MenuType = chooseDataStructure;
                    offAllScreen();
                    onLogo();
                    MenuChooseDSScreen.onScreen();
                }
                break;
        }
    }
}
void menuScreen::offAllScreen() {
    MenuInitialScreen.offScreen();
    MenuChooseDSScreen.offScreen();
}

void menuScreen::menuTypeSetInitial() {
    MenuType = initial;
}
int menuScreen::getDSType() {
    return DSType;
}
void menuScreen::backToMenu() {
    MenuType = initial;
    DSType = none;
}

void menuScreen::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            processMouseEvent(window);
            break;
    }
}


void menuScreen::drawMenuScreen(sf::RenderWindow &window) {
    menuBackground.drawBackground(window, backgroundOpacity);
    switch (MenuType) {
        case initial:
            MenuInitialScreen.buttonIsHover(window);
            MenuInitialScreen.drawInitialScreen(window);
            break;
        case chooseDataStructure:
            MenuChooseDSScreen.buttonIsHover(window);
            MenuChooseDSScreen.drawChooseDSScreen(window);
            break;
        case chooseLL:
            MenuChooseLLScreen.buttonIsHover(window);
            MenuChooseLLScreen.drawChooseLLScreen(window);
            break;
        case chooseArray:
            MenuChooseArrayScreen.buttonIsHover(window);
            MenuChooseArrayScreen.drawChooseArrayScreen(window);
            break;
        case chooseOther:
            MenuChooseOtherScreen.buttonIsHover(window);
            MenuChooseOtherScreen.drawChooseOtherScreen(window);
            break;
    }
    drawLogo(window);
}


float getDistance(sf::Vector2f pointX, sf::Vector2f pointY) {
    return sqrt((pointX.x - pointY.x) * (pointX.x - pointY.x) + (pointX.y - pointY.y) * (pointX.y - pointY.y));
}