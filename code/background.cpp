#include "background.h"

background::background() {
    bgCode = rand() % 17 + 1;
    std::string bgFile = std::to_string(bgCode) + ".jpg";
    if (!bgTexture.loadFromFile("src//include//texture//bg//" + bgFile)) {
        std::cout << "Background texture not found!\n";
        exit(-1);
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0, 0);
}

void background::setBackground() {
    int u = bgCode;
    while (u == bgCode)
        u = rand() % 17 + 1;
    std::string bgFile = std::to_string(bgCode) + ".jpg";
    if (!bgTexture.loadFromFile("src//include//texture//bg//" + bgFile)) {
        std::cout << "Background texture not found!\n";
        exit(-1);
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0, 0);
}

void background::drawBackground(sf::RenderWindow &window, int bgOpacity) {
    sf::Color bgColor = bgSprite.getColor();
    bgColor.a = bgOpacity;
    bgSprite.setColor(bgColor);

    sf::IntRect bound = bgSprite.getTextureRect();
    float scaleFactor = 1920.0 / bound.width;
    bgSprite.setScale(scaleFactor, scaleFactor);

    window.draw(bgSprite);
}