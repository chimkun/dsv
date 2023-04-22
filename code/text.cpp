#include "text.h"

textInfo::textInfo(int fontMode) {
    if (fontMode == 0) {
        if (!textFont.loadFromFile("src//font//Aller_Bd.ttf")) {
            std::cout << "font not found\n";
            exit(-1);
        }
    }
    if (fontMode == 1) {
        if (!textFont.loadFromFile("src//font//Exo2-Italic.ttf")) {
            std::cout << "font not found\n";
            exit(-1);
        }
    }
    if (fontMode == 2) {
        if (!textFont.loadFromFile("src//font//arial.ttf")) {
            std::cout << "font not found\n";
            exit(-1);
        }
    }
    if (fontMode == 3) {
        if (!textFont.loadFromFile("src//font//CONSOLA.ttf")) {
            std::cout << "font not found\n";
            exit(-1);
        }
    }
    return;
}
void textInfo::setFont(int fontMode) {
    if (fontMode == 1) {
        if (!textFont.loadFromFile("src//font//Exo2-Italic.ttf")) {
            std::cout << "font not found\n";
            exit(-1);
        }
    }
    if (fontMode == 2) {
        if (!textFont.loadFromFile("src//font//arial.ttf")) {
            std::cout << "font not found\n";
            exit(-1);
        }
    }
    if (fontMode == 3) {
        if (!textFont.loadFromFile("src//font//consolas.ttf")) {
            std::cout << "font not found\n";
            exit(-1);
        }
    }
    return;
}

void textInfo::drawText(sf::RenderWindow &window, sf::Vector2f nodePosition, int textType, int opacity) { 
    sf::Text textContent;
    textContent.setFont(textFont);
    // 1 - head
    // 2 - cur
    // 3 - tail
    // 4 - head/tail
    // 5 - head/cur
    // 6 - tail/cur
    // 7 - temp
    // 8 - next
    // 9 - del
    // 10 - head/temp
    // 11 - tail/temp
    switch (textType) {
        case 1:
            textContent.setString("head");
            break;
        case 2:
            textContent.setString("cur");
            break;
        case 3:
            textContent.setString("tail");
            break;
        case 4:
            textContent.setString("head/tail");
            break;
        case 5:
            textContent.setString("head/cur");
            break;
        case 6:
            textContent.setString("tail/cur");
            break;
        case 7:
            textContent.setString("temp");
            break;
        case 8:
            textContent.setString("next");
            break;
        case 9:
            textContent.setString("del");
            break;
        case 10:
            textContent.setString("head/temp");
            break;
        case 11:
            textContent.setString("tail/next");
            break;
    }
    int extraHeight = 0;
    std::string textString = textContent.getString();
    // std::cerr << "string content: " << textString << '\n';
    for (int i = 0; i < (int) textString.size(); i++) {
        if (textString[i] == 'g' || textString[i] == 'j' || textString[i] == 'p' || textString[i] == 'q' || textString[i] == 'y')
            extraHeight = 10;
    }
    textContent.setCharacterSize(44);
    sf::Color textColor = sf::Color::White;
    textColor.a = opacity;
    textContent.setFillColor(textColor);
    sf::FloatRect textRect = textContent.getLocalBounds();
    textContent.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height);
    sf::Vector2f textPosition = nodePosition;
    textPosition.y += nodeConstants::nodeRadius + 40 + extraHeight;
    textContent.setPosition(textPosition);

    window.draw(textContent);
}

void textInfo::drawOptionalText(sf::RenderWindow &window, std::string &textStringContent, 
                                sf::Vector2f &textPosition, int opacity) {
    sf::Text textContent;
    textContent.setFont(textFont);
    textContent.setString(textStringContent);
    textContent.setCharacterSize(44);
    sf::Color textColor = sf::Color::White;
    textColor.a = opacity;
    textContent.setFillColor(textColor);
    sf::FloatRect textRect = textContent.getLocalBounds();
    textContent.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height);
    textContent.setPosition(textPosition);

    window.draw(textContent);
}

void textInfo::drawOptionalTextSize(sf::RenderWindow &window, std::string &textStringContent, sf::Vector2f &textOrigin,
                                    sf::Vector2f &textPosition, int opacity, int textSize) {
    sf::Text textContent;
    textContent.setFont(textFont);
    textContent.setString(textStringContent);
    textContent.setCharacterSize(textSize);
    sf::Color textColor = sf::Color::White;
    textColor.a = opacity;
    textContent.setFillColor(textColor);
    sf::FloatRect textRect = textContent.getLocalBounds();
    textContent.setOrigin(textOrigin);
    textContent.setPosition(textPosition);
    window.draw(textContent);
}

sf::FloatRect textInfo::getTextBound(std::string &textStringContent, sf::Vector2f &textPosition, int textSize) {
    sf::Text textContent;
    textContent.setFont(textFont);
    textContent.setString(textStringContent);
    textContent.setCharacterSize(textSize);
    textContent.setPosition(textPosition);
    textContent.setOrigin(sf::Vector2f(0, 0));
    return textContent.getGlobalBounds();
}
