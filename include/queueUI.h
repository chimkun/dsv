#ifndef QUEUEUI_H
#define QUEUEUI_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "button.h"
#include "textbox.h"
#include "general.h"

class queueGeneralScreen {
private:
    button createButton, peekButton, pushButton, popButton, clearButton, backButton;
    textBox pushTextBox;
    button pushConfirmButton;
public:
    queueGeneralScreen();
    bool createButtonIsClick(sf::RenderWindow &window);
    bool peekButtonIsClick(sf::RenderWindow &window);
    bool pushButtonIsClick(sf::RenderWindow &window);
    bool confirmPushIsClick(sf::RenderWindow &window);
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

    bool pushTextBoxIsClick(sf::RenderWindow &window);
    bool pushTextBoxIsChoose();
    bool pushTextBoxIsEmpty();
    void onTextBoxState();
    void pushTextBoxKeyboardEvent(sf::Event &event);
    int getInputData();
    void initData();

    void moveButtonWhenHover(sf::RenderWindow &window);

    void drawGeneralScreen(sf::RenderWindow &window);
};

class queueCreateScreen {
private:
    button randomInputButton, userInputButton, backToModeButton, confirmInputButton;
    button browseButton;
    textBox userInputBox;
public:
    queueCreateScreen();
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

struct queueAllScreen {
    enum allScreenType {
        general, create
    };
    allScreenType currentScreenType;
    queueGeneralScreen theGeneralScreen;
    queueCreateScreen theCreateScreen;

    queueAllScreen();
    bool isGeneralScreen();
    void setToGeneral();
    void setToCreate();

    void drawGeneralScreen(sf::RenderWindow &window);
    void drawCreateScreen(sf::RenderWindow &window);
};

#endif