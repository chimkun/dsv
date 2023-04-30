#ifndef STACKUI_H
#define STACKUI_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "button.h"
#include "textbox.h"
#include "general.h"

class stackGeneralScreen {
private:
    button createButton, peekButton, pushButton, popButton, clearButton, backButton;
    textBox pushTextBox;
public:
    stackGeneralScreen();
    bool createButtonIsClick(sf::RenderWindow &window);
    bool peekButtonIsClick(sf::RenderWindow &window);
    bool pushButtonIsClick(sf::RenderWindow &window);
    bool popButtonIsClick(sf::RenderWindow &window);
    bool clearButtonIsClick(sf::RenderWindow &window);
    bool backButtonIsClick(sf::RenderWindow &window);

    bool pushButtonIsChoose();

    void turnOffAllButton();
    void turnOnCreateButton();
    void turnOnPeekButton();
    void turnOnPushButton();
    void turnOnPopButton();
    void turnOnClearButton();
    void turnOnBackButton();

    bool pushTextBoxIsChoose();
    void pushTextBoxKeyboardEvent(sf::Event &event);

    void moveButtonWhenHover(sf::RenderWindow &window);

    void drawGeneralScreen(sf::RenderWindow &window);
};

class stackCreateScreen {

private:
    button randomInputButton, userInputButton, backToModeButton, confirmInputButton;
    button browseButton;
    textBox userInputBox;
public:
    stackCreateScreen();
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

    void setInputBoxString(std::string &inputString);
    
    void drawChooseCreateScreen(sf::RenderWindow &window);
};

struct stackAllScreen {
    enum allScreenType {
        general, create
    };
    allScreenType currentScreenType;
    stackGeneralScreen theGeneralScreen;
    stackCreateScreen theCreateScreen;

    stackAllScreen();
    bool isGeneralScreen();
    void drawGeneralScreen(sf::RenderWindow &window);
    void drawCreateScreen(sf::RenderWindow &window);
};

#endif