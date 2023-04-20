#ifndef GENERAL_H
#define GENERAL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "textbox.h"

class generalScreen {
private:
    button createButton, addButton, searchButton, deleteButton, updateButton;
public:
    generalScreen ();
    bool createButtonIsClick(sf::RenderWindow &window);
    bool addButtonIsClick(sf::RenderWindow &window);
    bool searchButtonIsClick(sf::RenderWindow &window);
    bool deleteButtonIsClick(sf::RenderWindow &window);
    bool updateButtonIsClick(sf::RenderWindow &window);
    void drawGeneralScreen(sf::RenderWindow &window);
};

class createScreen {
private:
    button randomInputButton, userInputButton, backToModeButton, confirmInputButton;
    textBox userInputBox;
    bool userInputButtonState;
public:
    createScreen();
    bool userInputButtonIsClick(sf::RenderWindow &window);
    bool randomButtonIsClick(sf::RenderWindow &window);
    bool backButtonIsClick(sf::RenderWindow &window);
    bool textBoxIsClick(sf::RenderWindow &window);
    bool confirmButtonIsClick(sf::RenderWindow &window);

    std::string getInputString();
    void processConfirmButton();

    bool userInputButtonGetState();
    bool textBoxGetState();
    void flipInputButtonState();
    void flipInputBoxState();
    void offInputBoxState();

    void userInputCharacter(char inputCharacter);
    void userBackspaceCharacter();
    void userDeleteCharacter();
    void userMoveCursor(int arrowKeyCode);
    void drawChooseCreateScreen(sf::RenderWindow &window);
};

class allScreen {
private:
    enum allScreenType {
        general, create
    };
    allScreenType currentScreenType;
public:
    generalScreen theGeneralScreen;
    createScreen theCreateScreen;
    allScreen();
    void drawGeneralScreen(sf::RenderWindow &window);
    void drawCreateScreen(sf::RenderWindow &window);
};

class background {
private:
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    int bgCode;
public:
    background();
    void setBackground();
    void drawBackground(sf::RenderWindow &window, int bgOpacity = 50);
};

std::string normalize(std::string &inputString);

int checkStringData(std::string &inputString);

#endif