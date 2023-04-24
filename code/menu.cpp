#include "menu.h"

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
    backgroundOpacity = 255;
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
    if (isChosen && offTimer.getElapsedTime().asSeconds() > 7.5)
        offLogo();
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
    if (logoIsClick(window) || // logo is click
        ((MenuInitialScreen.aboutButtonIsClick(window) || MenuInitialScreen.startButtonIsClick(window) || MenuInitialScreen.exitButtonIsClick(window)) && MenuType == initial)) // button on initial screen is click
    {
        onLogo();
    }
    else {
        offLogo();
    }
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
    }
    drawLogo(window);
}


float getDistance(sf::Vector2f pointX, sf::Vector2f pointY) {
    return sqrt((pointX.x - pointY.x) * (pointX.x - pointY.x) + (pointX.y - pointY.y) * (pointX.y - pointY.y));
}