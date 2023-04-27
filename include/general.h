#ifndef GENERAL_H
#define GENERAL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "buttonAndTextBox.h"
#include "background.h"

struct generalScreen {
    buttonAndTextBox addButton, searchButton, deleteButton, updateButton;
    button addBeginning, addEnding, delBeginning, delEnding;
    textBox addBeginningText, addEndingText;
    button createButton;
    textInfo noteText;
    generalScreen();    
    bool createButtonIsClick(sf::RenderWindow &window);
    bool addButtonIsClick(sf::RenderWindow &window);
    bool searchButtonIsClick(sf::RenderWindow &window);
    bool deleteButtonIsClick(sf::RenderWindow &window);
    bool updateButtonIsClick(sf::RenderWindow &window);

    void initData(int numberOfNode);

    void turnOffAllButton();
    void turnOffAddTextBox();
    
    void moveButtonWhenHover(sf::RenderWindow &window);

    void drawGeneralScreen(sf::RenderWindow &window);
};

class createScreen {
private:
    button randomInputButton, userInputButton, backToModeButton, confirmInputButton;
    button browseButton;
    textBox userInputBox;
public:
    createScreen();
    bool userInputButtonIsClick(sf::RenderWindow &window);
    bool randomButtonIsClick(sf::RenderWindow &window);
    bool backButtonIsClick(sf::RenderWindow &window);
    bool textBoxIsClick(sf::RenderWindow &window);
    bool confirmButtonIsClick(sf::RenderWindow &window);
    bool browseButtonIsClick(sf::RenderWindow &window);

    std::string getInputString();
    std::vector<int> getInputData();

    bool userInputButtonGetState();
    bool textBoxGetState();
    void flipInputButtonState();
    void flipInputBoxState();
    void offInputBoxState();
    void onInputBoxState();
    bool inputIsEmpty();

    void moveButtonWhenHover(sf::RenderWindow &window);

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

// class background {
// private:
//     sf::Texture bgTexture;
//     sf::Sprite bgSprite;
//     int bgCode;
// public:
//     background();
//     void setBackground();
//     void drawBackground(sf::RenderWindow &window, int bgOpacity = 50);
// };

std::string normalize(std::string &inputString);

#endif