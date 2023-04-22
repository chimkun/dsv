#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

class textInfo {
private:
    sf::Font textFont;
public:
    textInfo(int fontType = 0);
    void setFont(int fontType);
    void drawText(sf::RenderWindow &window, sf::Vector2f nodePosition, int textType, int opacity);
    void drawOptionalText(sf::RenderWindow &window, std::string &textStringContent, 
                          sf::Vector2f &textPosition, int opacity);
    void drawOptionalTextSize(sf::RenderWindow &window, std::string &textStringContent, sf::Vector2f &textOrigin,
                              sf::Vector2f &textPosition, int opacity, int textSize);
    sf::FloatRect getTextBound(std::string &textStringContent, sf::Vector2f &textPosition, int textSize);
};

#endif