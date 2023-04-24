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
    MenuType = idle;
}

bool menuScreen::logoIsClick(sf::RenderWindow &window) {
    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
    float mouseToCenterDistance = getDistance(mousePosition, logoConstants::logoCenter);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseToCenterDistance <= logoConstants::logoRadius) {
        isChosen = !isChosen;
        return true;
    }
    return false;
}
void menuScreen::drawLogo(sf::RenderWindow &window) {
    sf::Vector2f logoPosition = logoSprite.getPosition();
    if (isChosen) {
        logoPosition.x = std::max(logoPosition.x - logoConstants::logoMoveSpeed, 
                                  logoConstants::logoCenter.x - logoConstants::minMoveDistance);
    }
    else {
        logoPosition.x = std::min(logoPosition.x + logoConstants::logoMoveSpeed,
                                  logoConstants::logoCenter.x);
    }
    logoSprite.setPosition(logoPosition);
    window.draw(logoSprite);
}

void menuScreen::processMouseEvent(sf::RenderWindow &window) {
    switch (MenuType) {
        case idle:
            if (logoIsClick(window))
                drawLogo(window);
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
    drawLogo(window);
}


float getDistance(sf::Vector2f pointX, sf::Vector2f pointY) {
    return sqrt((pointX.x - pointY.x) * (pointX.x - pointY.x) + (pointX.y - pointY.y) * (pointX.y - pointY.y));
}