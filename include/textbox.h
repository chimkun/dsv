#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "button.h"
#include "text.h"

struct textCursor {
    sf::RectangleShape cursor;
    sf::Vector2f initialCursorPosition;
    sf::Vector2f rightmostCursorPosition;
    bool tick;
    sf::Clock tickTime;
    sf::Color cursorColor;
    textInfo userInputText;
    std::string inputContent;
    int cursorPosition;

    textCursor();
    textCursor(sf::Vector2f initialCursorPosition, sf::Vector2f rightMostCursorPosition);
    void setInputContent(std::string &inputContent);
    std::string getInputContent();

    void userInputCharacter(char characterInput);
    void userBackspace();
    void userDelete();
    void userMoveCursor(int arrowKeyCode);

    void drawTextCursor(sf::RenderWindow &window);
    void drawTextOnBox(sf::RenderWindow &window);
};

class textBox {
private:
    textCursor myTextCursor;
    textInfo userInputFont;
    button textBoxButton;
    bool isClicked;
public:
    textBox();
    textBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture);
    void userInputCharacter(char characterInput);
    void userBackspace();
    void userDelete();
    void userMoveCursor(int arrowKeyCode);

    void textBoxEvent(sf::RenderWindow &window);
    void flipTextBoxState();
    void offTextBoxState();
    bool textBoxIsClick();
    bool textBoxButtonIsClick(sf::RenderWindow &window);
    std::string getTextBoxString();

    void drawTextBox(sf::RenderWindow &window);
};

#endif