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
    std::string emptyString = "";
    backButton = button(menuButtonConstants::backButtonPosition, backButtonTexture, emptyString);
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
                    MenuChooseDSScreen.onScreen();
                }
                if (MenuInitialScreen.exitButtonIsClick(window)) {
                    offAllScreen();
                    window.close();
                }
                break;
            case chooseDataStructure:
                if (backButton.buttonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    MenuInitialScreen.onScreen();
                }
                if (MenuChooseDSScreen.linkedListButtonIsClick(window)) {
                    MenuType = chooseLL;
                    offAllScreen();
                    MenuChooseLLScreen.onScreen();
                }
                break;
            case chooseLL:
                if (backButton.buttonIsClick(window)) {
                    MenuType = chooseDataStructure;
                    offAllScreen();
                    MenuChooseDSScreen.onScreen();
                }
                else if (MenuChooseLLScreen.SLLButtonIsClick(window)) {
                    MenuType = initial;
                    offAllScreen();
                    DSType = SLL;
                }
                break;
        }
    }
}
void menuScreen::offAllScreen() {
    MenuInitialScreen.offScreen();
    MenuChooseDSScreen.offScreen();
}

void menuScreen::backButtonHover(sf::RenderWindow &window) {
    if (backButton.buttonIsHover(window) && MenuType != initial) {
        window.draw(backHighlight);
    }
}

void menuScreen::menuTypeSetInitial() {
    MenuType = initial;
}
int menuScreen::getDSType() {
    return DSType;
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
            if (isChosen) {
                backButtonHover(window);
                backButton.drawButton(window);
            }
            break;
        case chooseLL:
            MenuChooseLLScreen.buttonIsHover(window);
            MenuChooseLLScreen.drawChooseLLScreen(window);
            if (isChosen) {
                backButtonHover(window);
                backButton.drawButton(window);
            }
            break;
    }
    drawLogo(window);
}


float getDistance(sf::Vector2f pointX, sf::Vector2f pointY) {
    return sqrt((pointX.x - pointY.x) * (pointX.x - pointY.x) + (pointX.y - pointY.y) * (pointX.y - pointY.y));
}