#include "aboutScreen.h"

aboutScreen::aboutScreen() {
    bgBlend.setSize(sf::Vector2f(2000, 1200));
    bgBlend.setPosition(sf::Vector2f(-50, -50));
    sf::Color bgColor = sf::Color::Black;
    bgColor.a = 50;
    bgBlend.setFillColor(bgColor);

    textFrame.setSize(sf::Vector2f(1600, 960));
    textFrame.setPosition(sf::Vector2f(320/2, 120/2));
    textFrame.setFillColor(sf::Color(246, 172, 240, 100));

    aboutString = 
    "dsv! is a powerful program developed by chimken that allows users to visualize seven\n"
    "common data structures: singly linked list doubly linked list, circular linked list,\n"
    "static array, dynamic array, stack, and queue.\n"
    "\n"
    "With an easy-to-use interface, users can create, manipulate and visualize these\n"
    "data structures in real-time. The program's dynamic visualization makes it an\n"
    "invaluable tool for students and developers who want to learn how these data structures\n"
    "work and how they can be utilized in their code.\n"
    "\n"
    "dsv! is a must-have program for anyone working with data structures and is sure to make\n"
    "your coding experience easier and more efficient!\n";

    sf::Texture aboutBackButtonTexture;
    if (!aboutBackButtonTexture.loadFromFile("src//include//texture//aboutBackButton.png")) {
        std::cout << "texture file not found! (aboutBackButton.png)\n";
        exit(-1);
    }
    std::string emptyString = "";
    backButton = button(sf::Vector2f(1700, 800), aboutBackButtonTexture, emptyString, 0, 0);
}

bool aboutScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backButton.buttonIsClick(window);
}
void aboutScreen::drawAboutScreen(sf::RenderWindow &window) {
    // blendOpacity = std::min(blendOpacity + aboutScreenConstants::blendFadeSpeed, aboutScreenConstants::blendOpacity);
    // textOpacity = std::min(textOpacity + aboutScreenConstants::textFadeSpeed, 255);
    aboutBg.drawBackground(window);
    window.draw(bgBlend);
    backButton.drawButton(window);
    sf::Vector2f origin = sf::Vector2f(0, 0), position = sf::Vector2f(320/2 + 20, 120/2 + 30);
    aboutText.drawOptionalTextSize(window, aboutString, origin, position, 200, 36);
}