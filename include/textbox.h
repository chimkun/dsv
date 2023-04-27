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
    int cursorPosition;
    sf::Clock tickTime;
    sf::Color cursorColor;
    textInfo userInputText;
    std::string inputContent;

    textCursor();
    textCursor(sf::Vector2f &initialLeftCursorPosition, sf::Vector2f &initialRightCursorPosition);

    void setTextCursor(sf::Vector2f &initialLeftCursorPosition, sf::Vector2f &initialRightCursorPosition);
    void setInputContent(std::string &inputContent);
    std::string getInputContent();
    sf::Vector2f getCursorPosition();
    bool cursorOutOfBound();

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
    textBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture,
            sf::Vector2f cursorLeftPosition, sf::Vector2f cursorRightPosition);
    void userInputCharacter(char characterInput);
    void userBackspace();
    void userDelete();
    void userMoveCursor(int arrowKeyCode);

    void textBoxEvent(sf::RenderWindow &window);
    void flipTextBoxState();
    void offTextBoxState();
    void onTextBoxState();
    bool textBoxIsClick();
    bool textBoxButtonIsClick(sf::RenderWindow &window);
    bool inputIsEmpty();

    void processKeyboardEvent(sf::Event &event);
    
    std::string getTextBoxString();
    void setTextBoxString(std::string &inputString);

    std::pair <int, int> getInputDataPair();
    int getInputDataInt();

    void drawTextBox(sf::RenderWindow &window);
};

#endif