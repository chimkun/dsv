#include "stackUI.h"

stackGeneralScreen::stackGeneralScreen() {
    sf::Texture createButtonTexture, peekButtonTexture, pushButtonTexture, popButtonTexture, clearButtonTexture, backToMenuTexture;
    if (!createButtonTexture.loadFromFile("src//include//texture//createButton.png")) {
        std::cout << "Texture file not found! (createButton.png)\n";
        exit(-1);
    }
    if (!peekButtonTexture.loadFromFile("src//include//texture//peekStackButton.png")) {
        std::cout << "Texture file not found! (addButton.png)\n";
        exit(-1);
    }
    if (!pushButtonTexture.loadFromFile("src//include//texture//pushStackButton.png")) {
        std::cout << "Texture file not found! (deleteButton.png)\n";
        exit(-1);
    }
    if (!popButtonTexture.loadFromFile("src//include//texture//popStackButton.png")) {
        std::cout << "Texture file not found! (searchButton.png)\n";
        exit(-1);
    }
    if (!clearButtonTexture.loadFromFile("src//include//texture//clearStackButton.png")) {
        std::cout << "Texture file not found! (updateButton.png)\n";
        exit(-1);
    }
    if (!backToMenuTexture.loadFromFile("src//include//texture//backToMenuButton.png")) {
        std::cout << "Texture file not found! (backToMenu.png)\n";
        exit(-1);
    }

    std::string createString = "Create";
    std::string peekString = "Peek";
    std::string pushString = "Push";
    std::string popString = "Pop";
    std::string clearString = "Clear";
    std::string menuString = "Return";

    sf::Vector2f createButtonPosition(-40.0, 450),
                 peekButtonPosition(-40.0, 450 + 85),
                 pushButtonPosition(-40.0, 450 + 85 * 2),
                 popButtonPosition(-40.0, 450 + 85 * 3),
                 clearButtonPosition(-40.0, 450 + 85 * 4),
                 menuButtonPosition(-40.0, 450 + 85 * 5);

    this->createButton.initButton(createButtonPosition, createButtonTexture, createString);
    this->peekButton.initButton(peekButtonPosition, peekButtonTexture, peekString);
    this->pushButton.initButton(pushButtonPosition, pushButtonTexture, pushString);
    this->popButton.initButton(popButtonPosition, popButtonTexture, popString);
    this->clearButton.initButton(clearButtonPosition, clearButtonTexture, clearString);
    this->backButton.initButton(menuButtonPosition, backToMenuTexture, menuString);
    sf::Texture pushTextBoxTexture;
    if (!pushTextBoxTexture.loadFromFile("src//include//texture//addButtonTextBox.png")) {
        std::cout << "texture file not found\n";
        exit(-1);
    }

    std::string confirmString = "go!";
    sf::Vector2f pushTextBoxPos = sf::Vector2f(buttonConstants::textBoxDistance, 450 + 85 * 2 + 10);
    sf::Vector2f pushConfirmButtonPos = pushTextBoxPos + sf::Vector2f(100, 0);
    pushTextBox = textBox(pushTextBoxPos, pushTextBoxTexture, 
                          pushTextBoxPos + sf::Vector2f(9, 8), pushTextBoxPos + sf::Vector2f(85, 8));
    this->pushConfirmButton.initButton(pushConfirmButtonPos, pushTextBoxTexture, confirmString);
}

bool stackGeneralScreen::createButtonIsClick(sf::RenderWindow &window) {
    return createButton.buttonIsClick(window);
}
bool stackGeneralScreen::peekButtonIsClick(sf::RenderWindow &window) {
    return peekButton.buttonIsClick(window);
}
bool stackGeneralScreen::pushButtonIsClick(sf::RenderWindow &window) {
    return pushButton.buttonIsClick(window);
}
bool stackGeneralScreen::confirmPushIsClick(sf::RenderWindow &window) {
    return pushConfirmButton.buttonIsClick(window);
}
bool stackGeneralScreen::popButtonIsClick(sf::RenderWindow &window) {
    return popButton.buttonIsClick(window);
}
bool stackGeneralScreen::clearButtonIsClick(sf::RenderWindow &window) {
    return clearButton.buttonIsClick(window);
}
bool stackGeneralScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backButton.buttonIsClick(window);
}
bool stackGeneralScreen::pushButtonIsChoose() {
    return pushButton.isChosen();
}

void stackGeneralScreen::turnOffAllButton() {
    createButton.offButton();
    peekButton.offButton();
    pushButton.offButton();
    popButton.offButton();
    clearButton.offButton();
    backButton.offButton();
}
void stackGeneralScreen::turnOnCreateButton() {
    createButton.onButton();
}
void stackGeneralScreen::turnOnPeekButton() {
    peekButton.onButton();
}
void stackGeneralScreen::turnOnPushButton() {
    pushButton.onButton();
}
void stackGeneralScreen::turnOnPopButton() {
    popButton.onButton();
}
void stackGeneralScreen::turnOnClearButton() {
    clearButton.onButton();
}
void stackGeneralScreen::turnOnBackButton() {
    backButton.onButton();
}

bool stackGeneralScreen::pushTextBoxIsClick(sf::RenderWindow &window) {
    return pushTextBox.textBoxButtonIsClick(window);
}
bool stackGeneralScreen::pushTextBoxIsChoose() {
    return pushTextBox.textBoxIsClick();
}
bool stackGeneralScreen::pushTextBoxIsEmpty() {
    return pushTextBox.inputIsEmpty();
}
void stackGeneralScreen::onTextBoxState() {
    pushTextBox.onTextBoxState();
}
void stackGeneralScreen::pushTextBoxKeyboardEvent(sf::Event &event) {
    pushTextBox.processKeyboardEvent(event);
}
int stackGeneralScreen::getInputData() {
    return pushTextBox.getInputDataInt();
}
void stackGeneralScreen::initData() {
    int pushData = rand() % 100;
    std::string dataString = std::to_string(pushData);
    pushTextBox.setTextBoxString(dataString);
}

void stackGeneralScreen::moveButtonWhenHover(sf::RenderWindow &window) {
    this->createButton.moveButtonWhenHover(window);
    this->peekButton.moveButtonWhenHover(window);
    this->pushButton.moveButtonWhenHover(window);
    this->popButton.moveButtonWhenHover(window);
    this->clearButton.moveButtonWhenHover(window);
    this->backButton.moveButtonWhenHover(window);
}

void stackGeneralScreen::drawGeneralScreen(sf::RenderWindow &window) {
    createButton.drawButton(window);
    peekButton.drawButton(window);
    pushButton.drawButton(window);
    if (pushButton.isChosen()) {
        pushTextBox.drawTextBox(window);
        pushConfirmButton.drawButton(window, 0.31, 0.17, 21);
    }
    popButton.drawButton(window);
    clearButton.drawButton(window);
    backButton.drawButton(window);
}



stackCreateScreen::stackCreateScreen() {
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

    sf::Texture userInputBoxTexture, confirmInputButtonTexture, browseButtonTexture;
    if (!userInputBoxTexture.loadFromFile("src//include//texture//userInputStack.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    if (!confirmInputButtonTexture.loadFromFile("src//include//texture//confirmInputButton.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    if (!browseButtonTexture.loadFromFile("src//include//texture//confirmInputButton.png")) {
        std::cout << "Texture file not found!\n";
        exit(-1);
    }
    std::string confirmString = "go!", browseString = "browse";
    sf::Vector2f leftCursorPos = sf::Vector2f(buttonConstants::textBoxDistance + buttonConstants::textCursorDistance, 535 + 25);
    sf::Vector2f rightCursorPos = sf::Vector2f(buttonConstants::textBoxDistance + buttonConstants::textCursorDistance + 254, 535 + 25);
    userInputBox = textBox(sf::Vector2f(buttonConstants::textBoxDistance, 552), userInputBoxTexture, leftCursorPos, rightCursorPos);
    // left = textPos + (textCursorDistance, 8)
    // right = textPos + (texture_length, 8)
    browseButton.initButton(sf::Vector2f(buttonConstants::textBoxDistance + 380, 553), browseButtonTexture, browseString);
    confirmInputButton.initButton(sf::Vector2f(buttonConstants::textBoxDistance + 280, 553), confirmInputButtonTexture, confirmString);
}
bool stackCreateScreen::userInputButtonIsClick(sf::RenderWindow &window) {
    return userInputButton.buttonIsClick(window);
}
bool stackCreateScreen::randomButtonIsClick(sf::RenderWindow &window) {
    return randomInputButton.buttonIsClick(window);
}
bool stackCreateScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backToModeButton.buttonIsClick(window);
}
bool stackCreateScreen::textBoxIsClick(sf::RenderWindow &window) {
    return userInputBox.textBoxButtonIsClick(window);
}
bool stackCreateScreen::confirmButtonIsClick(sf::RenderWindow &window) {
    return confirmInputButton.buttonIsClick(window);
}
bool stackCreateScreen::browseButtonIsClick(sf::RenderWindow &window) {
    return browseButton.buttonIsClick(window);
}

std::string stackCreateScreen::getInputString() {
    return userInputBox.getTextBoxString();
}

std::vector<int> stackCreateScreen::getInputData() {
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

bool stackCreateScreen::userInputButtonGetState() {
    return userInputButton.isChosen();
}
bool stackCreateScreen::textBoxGetState() {
    return userInputBox.textBoxIsClick();
}
void stackCreateScreen::flipInputButtonState() {
    userInputButton.flipChoose();
}
void stackCreateScreen::flipInputBoxState() {
    userInputBox.flipTextBoxState();
}
void stackCreateScreen::offInputBoxState() {
    userInputBox.offTextBoxState();
}
void stackCreateScreen::onInputBoxState() {
    userInputBox.onTextBoxState();
}
bool stackCreateScreen::inputIsEmpty() {
    return userInputBox.inputIsEmpty();
}

void stackCreateScreen::moveButtonWhenHover(sf::RenderWindow &window) {
    userInputButton.moveButtonWhenHover(window);
    randomInputButton.moveButtonWhenHover(window);
    backToModeButton.moveButtonWhenHover(window);
}

void stackCreateScreen::userInputCharacter(char inputCharacter) {
    userInputBox.userInputCharacter(inputCharacter);
}
void stackCreateScreen::userBackspaceCharacter() {
    userInputBox.userBackspace();
}
void stackCreateScreen::userDeleteCharacter() {
    userInputBox.userDelete();
}
void stackCreateScreen::userMoveCursor(int arrowKeyCode) {
    userInputBox.userMoveCursor(arrowKeyCode);
}

void stackCreateScreen::setInputBoxString(std::string &inputString) {
    userInputBox.setTextBoxString(inputString);
}

void stackCreateScreen::drawChooseCreateScreen(sf::RenderWindow &window) {
    userInputButton.drawButton(window);
    randomInputButton.drawButton(window);
    backToModeButton.drawButton(window);
    if (userInputButtonGetState() == true) {
        userInputBox.drawTextBox(window);
        browseButton.drawButton(window, 0.16, 0.17, 19);
        confirmInputButton.drawButton(window, 0.33, 0.14, 21);
    }
}



stackAllScreen::stackAllScreen() {
    currentScreenType = general;
}
bool stackAllScreen::isGeneralScreen() {
    if (currentScreenType == general)
        return true;
    return false;
}
void stackAllScreen::setToGeneral() {
    currentScreenType = general;
}
void stackAllScreen::setToCreate() {
    currentScreenType = create;
}

void stackAllScreen::drawGeneralScreen(sf::RenderWindow &window) {
    theGeneralScreen.drawGeneralScreen(window);
}
void stackAllScreen::drawCreateScreen(sf::RenderWindow &window) {
    theCreateScreen.drawChooseCreateScreen(window);
}


