#include "general.h"

generalScreen::generalScreen () {
    sf::Texture createButtonTexture, addButtonTexture, deleteButtonTexture, searchButtonTexture, updateButtonTexture;
    if (!createButtonTexture.loadFromFile("src//include//texture//createButton.png")) {
        std::cout << "Texture file not found! (createButton.png)\n";
        exit(-1);
    }
    if (!addButtonTexture.loadFromFile("src//include//texture//addButton.png")) {
        std::cout << "Texture file not found! (addButton.png)\n";
        exit(-1);
    }
    if (!deleteButtonTexture.loadFromFile("src//include//texture//deleteButton.png")) {
        std::cout << "Texture file not found! (deleteButton.png)\n";
        exit(-1);
    }
    if (!searchButtonTexture.loadFromFile("src//include//texture//searchButton.png")) {
        std::cout << "Texture file not found! (searchButton.png)\n";
        exit(-1);
    }
    if (!updateButtonTexture.loadFromFile("src//include//texture//updateButton.png")) {
        std::cout << "Texture file not found! (updateButton.png)\n";
        exit(-1);
    }
    sf::Texture userInputDataTexture;
    if (!userInputDataTexture.loadFromFile("src//include//texture//userInputData.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }

    std::string createString = "Create";
    std::string addString = "Add";
    std::string deleteString = "Delete";
    std::string searchString = "Search";
    std::string updateString = "Update";
    createButton.initButton(sf::Vector2f(-40, 450), createButtonTexture, createString);
    addButton.initButton(sf::Vector2f(-40, 535), addButtonTexture, addString);
    deleteButton.initButton(sf::Vector2f(-40, 620), deleteButtonTexture, deleteString);
    searchButton.initButton(sf::Vector2f(-40, 705), searchButtonTexture, searchString);
    updateButton.initButton(sf::Vector2f(-40, 790), updateButtonTexture, updateString);
}

bool generalScreen::createButtonIsClick(sf::RenderWindow &window) {
    return createButton.buttonIsClick(window);
}
bool generalScreen::addButtonIsClick(sf::RenderWindow &window) {
    return addButton.buttonIsClick(window);
}
bool generalScreen::deleteButtonIsClick(sf::RenderWindow &window) {
    return deleteButton.buttonIsClick(window);
}
bool generalScreen::searchButtonIsClick(sf::RenderWindow &window) {
    return searchButton.buttonIsClick(window);
}
bool generalScreen::updateButtonIsClick(sf::RenderWindow &window) {
    return updateButton.buttonIsClick(window);
}


createScreen::createScreen() {
    sf::Texture randomInputTexture, userInputTexture, backToModeTexture;
    if (!randomInputTexture.loadFromFile("src//include//texture//randomButton.png")) {
        std::cout << "Texture file not found! (randomButton.png)\n";
        exit(-1);
    }
    if (!userInputTexture.loadFromFile("src//include//texture//userInputButton.png")) {
        std::cout << "Texture file not found! (userInputButton.png)\n";
        exit(-1);
    }
    if (!backToModeTexture.loadFromFile("src//include//texture//backToModeButton.png")) {
        std::cout << "Texture file not found! (backToModeButton.png)\n";
        exit(-1);
    }
    std::string randomString = "Random";
    std::string userInputString = "User input";
    std::string backToModeString = "Back";
    userInputButton.initButton(sf::Vector2f(-40, 535), userInputTexture, userInputString);
    randomInputButton.initButton(sf::Vector2f(-40, 620), randomInputTexture, randomString);
    backToModeButton.initButton(sf::Vector2f(-40, 705), backToModeTexture, backToModeString);

    sf::Texture userInputBoxTexture, confirmInputButtonTexture;
    if (!userInputBoxTexture.loadFromFile("src//include//texture//userInputData.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    if (!confirmInputButtonTexture.loadFromFile("src//include//texture//confirmInputButton.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    std::string confirmString = "go!";
    userInputBox = textBox(sf::Vector2f(370, 552), userInputBoxTexture);
    confirmInputButton.initButton(sf::Vector2f(370 + 330, 553), confirmInputButtonTexture, confirmString);
}
bool createScreen::userInputButtonIsClick(sf::RenderWindow &window) {
    return userInputButton.buttonIsClick(window);
}
bool createScreen::randomButtonIsClick(sf::RenderWindow &window) {
    return randomInputButton.buttonIsClick(window);
}
bool createScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backToModeButton.buttonIsClick(window);
}
bool createScreen::textBoxIsClick(sf::RenderWindow &window) {
    return userInputBox.textBoxButtonIsClick(window);
}
bool createScreen::confirmButtonIsClick(sf::RenderWindow &window) {
    return confirmInputButton.buttonIsClick(window);
}
std::string createScreen::getInputString() {
    return userInputBox.getTextBoxString();
}

void createScreen::processConfirmButton() {
    std::string theInputString = getInputString();
    std::string normalizedInput = normalize(theInputString);
}

bool createScreen::userInputButtonGetState() {
    return userInputButtonState;
}
bool createScreen::textBoxGetState() {
    return userInputBox.textBoxIsClick();
}
void createScreen::flipInputButtonState() {
    userInputButtonState = !userInputButtonState;
}
void createScreen::flipInputBoxState() {
    userInputBox.flipTextBoxState();
}
void createScreen::offInputBoxState() {
    userInputBox.offTextBoxState();
}
void createScreen::userInputCharacter(char inputCharacter) {
    userInputBox.userInputCharacter(inputCharacter);
}
void createScreen::userBackspaceCharacter() {
    userInputBox.userBackspace();
}
void createScreen::userDeleteCharacter() {
    userInputBox.userDelete();
}
void createScreen::userMoveCursor(int arrowKeyCode) {
    userInputBox.userMoveCursor(arrowKeyCode);
}


void generalScreen::drawGeneralScreen(sf::RenderWindow &window) {
    createButton.drawButton(window);
    addButton.drawButton(window);
    deleteButton.drawButton(window);
    searchButton.drawButton(window);
    updateButton.drawButton(window);
}
void createScreen::drawChooseCreateScreen(sf::RenderWindow &window) {
    userInputButton.drawButton(window);
    randomInputButton.drawButton(window);
    backToModeButton.drawButton(window);
    if (userInputButtonGetState() == true) {
        userInputBox.drawTextBox(window);
        confirmInputButton.drawButton(window, 0.33, 0.14, 21);
    }
}

allScreen::allScreen() {
    currentScreenType = general;
}
void allScreen::drawGeneralScreen(sf::RenderWindow &window) {
    theGeneralScreen.drawGeneralScreen(window);
}
void allScreen::drawCreateScreen(sf::RenderWindow &window) {
    theCreateScreen.drawChooseCreateScreen(window);
}


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

std::string normalize(std::string &inputString) {
    int startIndex = 0;
    for (int i = 0; i < (int) inputString.size(); i++) {
        if (inputString[i] != ',') {
            startIndex = i;
            break;
        }
    }
    std::string temp;
    bool isComma = 0;
    for (int i = startIndex; i < (int) inputString.size(); i++) {
        if (inputString[i] != ',') {
            temp.push_back(inputString[i]);
            isComma = 0;
        }
        else {
            if (!isComma) {
                isComma = 1;
                temp.push_back(',');
            }
        }
    }
    while (!temp.empty() && temp[(int) temp.size() - 1] == ',')
        temp.pop_back();
    return temp;
}

int checkStringData(std::string &inputString) {
    int curNum = 0, maxNum = 0, countNum = 1, mul = 1, errorCode = 0;
    //0 - good
    //1 - num out of range [0..99]
    //2 - total number > 10
    for (int i = (int) inputString.size() - 1; i >= 0; i--) {
        if (inputString[i] == ',') {
            countNum++;
            maxNum = std::max(maxNum, curNum);
            curNum = 0;
            mul = 1;
            if (countNum > 10) {
                errorCode = 2;
                break;
            }
        }
        else {
            curNum += mul * ((int) inputString[i] - '0');
            if (mul >= 100) {
                errorCode = 1;
                break;
            }
            mul *= 10;
        }
    }
    return errorCode;
}