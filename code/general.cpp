#include "general.h"

generalScreen::generalScreen() {
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

    sf::Texture addButtonTextBoxTexture, deleteButtonTextBoxTexture, 
                searchButtonTextBoxTexture, updateButtonTextBoxTexture;
    if (!addButtonTextBoxTexture.loadFromFile("src//include//texture//addButtonTextBox.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    deleteButtonTextBoxTexture = searchButtonTextBoxTexture = updateButtonTextBoxTexture = addButtonTextBoxTexture;

    std::string createString = "Create";
    std::string addString = "Add";
    std::string deleteString = "Delete";
    std::string searchString = "Search";
    std::string updateString = "Update";

    sf::Vector2f createButtonPosition(-40.0, 450),
                 addButtonPosition(-40.0, 450 + 85),
                 deleteButtonPosition(-40.0, 450 + 85 * 2),
                 searchButtonPosition(-40.0, 450 + 85 * 3),
                 updateButtonPosition(-40.0, 450 + 85 * 4);
    sf::Vector2f addButtonTextBoxPosition(buttonConstants::textBoxDistance, 552),
                 deleteButtonTextBoxPosition(buttonConstants::textBoxDistance, 552 + 85),
                 searchButtonTextBoxPosition(buttonConstants::textBoxDistance, 552 + 85 * 2),
                 updateButtonTextBoxPosition(buttonConstants::textBoxDistance, 552 + 85 * 3);
//     createButton.initButton(sf::Vector2f(-50, 450), createButtonTexture, createString);
    this->createButton.initButton(createButtonPosition, createButtonTexture, createString);
    this->addButton = buttonAndTextBox(addButtonPosition, addButtonTexture, addString, addButtonTextBoxPosition, addButtonTextBoxTexture);
    this->deleteButton = buttonAndTextBox(deleteButtonPosition, deleteButtonTexture, deleteString, deleteButtonTextBoxPosition, deleteButtonTextBoxTexture);
    this->searchButton = buttonAndTextBox(searchButtonPosition, searchButtonTexture, searchString, searchButtonTextBoxPosition, searchButtonTextBoxTexture);
    this->updateButton = buttonAndTextBox(updateButtonPosition, updateButtonTexture, updateString, updateButtonTextBoxPosition, updateButtonTextBoxTexture);
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

void generalScreen::turnOffAllButton() {
    if (createButton.isChosen())
        createButton.flipChoose();
    if (addButton.buttonIsChoose())
        addButton.flipButtonState();
    if (deleteButton.buttonIsChoose())
        deleteButton.flipButtonState();
    if (searchButton.buttonIsChoose())
        searchButton.flipButtonState();
    if (updateButton.buttonIsChoose())
        searchButton.flipButtonState();
}

void generalScreen::moveButtonWhenHover(sf::RenderWindow &window) {
    this->createButton.moveButtonWhenHover(window);
    this->addButton.moveButtonWhenHover(window);
    this->deleteButton.moveButtonWhenHover(window);
    this->searchButton.moveButtonWhenHover(window);
    this->updateButton.moveButtonWhenHover(window);
}
void generalScreen::drawGeneralScreen(sf::RenderWindow &window) {
    createButton.drawButton(window);
    addButton.drawButton(window);
    deleteButton.drawButton(window);
    searchButton.drawButton(window);
    updateButton.drawButton(window);
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
    userInputButton.initButton(sf::Vector2f(-50, 535), userInputTexture, userInputString);
    randomInputButton.initButton(sf::Vector2f(-50, 620), randomInputTexture, randomString);
    backToModeButton.initButton(sf::Vector2f(-50, 705), backToModeTexture, backToModeString);

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
    sf::Vector2f leftCursorPos = sf::Vector2f(buttonConstants::textBoxDistance + buttonConstants::textCursorDistance, 535 + 25);
    sf::Vector2f rightCursorPos = sf::Vector2f(buttonConstants::textBoxDistance + buttonConstants::textCursorDistance + 448, 535 + 25);
    userInputBox = textBox(sf::Vector2f(buttonConstants::textBoxDistance, 552), userInputBoxTexture, leftCursorPos, rightCursorPos);
    // left = textPos + (textCursorDistance, 8)
    // right = textPos + (texture_length, 8)
    confirmInputButton.initButton(sf::Vector2f(buttonConstants::textBoxDistance + 480, 553), confirmInputButtonTexture, confirmString);
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

std::vector<int> createScreen::getInputData() {
    std::string theInputString = getInputString();
    std::string normalizedInput = normalize(theInputString);
    int curNum = 0, maxNum = 0, countNum = 1, mul = 1;
            
    std::vector<int> inputArray;
    for (int i = (int) normalizedInput.size() - 1; i >= 0; i--) {
        if (normalizedInput[i] == ',') {
            if (curNum > 99)
                break;
            if (countNum > 10)
                break;
            inputArray.push_back(curNum);
            countNum++;
            maxNum = std::max(maxNum, curNum);
            curNum = 0;
            mul = 1;
        }
        else {
            curNum += mul * ((int) normalizedInput[i] - '0');
            mul *= 10;
        }
    }
    inputArray.push_back(curNum);
    std::reverse(inputArray.begin(), inputArray.end());
    return inputArray;
}

bool createScreen::userInputButtonGetState() {
    return userInputButton.isChosen();
}
bool createScreen::textBoxGetState() {
    return userInputBox.textBoxIsClick();
}
void createScreen::flipInputButtonState() {
    userInputButton.flipChoose();
}
void createScreen::flipInputBoxState() {
    userInputBox.flipTextBoxState();
}
void createScreen::offInputBoxState() {
    userInputBox.offTextBoxState();
}
void createScreen::onInputBoxState() {
    userInputBox.onTextBoxState();
}
bool createScreen::inputIsEmpty() {
    return userInputBox.inputIsEmpty();
}

void createScreen::moveButtonWhenHover(sf::RenderWindow &window) {
    userInputButton.moveButtonWhenHover(window);
    randomInputButton.moveButtonWhenHover(window);
    backToModeButton.moveButtonWhenHover(window);
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