#include "queueUI.h"

queueGeneralScreen::queueGeneralScreen() {
    sf::Texture createButtonTexture, peekButtonTexture, pushButtonTexture, popButtonTexture, clearButtonTexture, backToMenuTexture;
    if (!createButtonTexture.loadFromFile("src//include//texture//createButton.png")) {
        std::cout << "Texture file not found! (createButton.png)\n";
        exit(-1);
    }
    if (!peekButtonTexture.loadFromFile("src//include//texture//peekQueueButton.png")) {
        std::cout << "Texture file not found! (addButton.png)\n";
        exit(-1);
    }
    if (!pushButtonTexture.loadFromFile("src//include//texture//pushQueueButton.png")) {
        std::cout << "Texture file not found! (deleteButton.png)\n";
        exit(-1);
    }
    if (!popButtonTexture.loadFromFile("src//include//texture//popQueueButton.png")) {
        std::cout << "Texture file not found! (searchButton.png)\n";
        exit(-1);
    }
    if (!clearButtonTexture.loadFromFile("src//include//texture//clearQueueButton.png")) {
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

bool queueGeneralScreen::createButtonIsClick(sf::RenderWindow &window) {
    return createButton.buttonIsClick(window);
}
bool queueGeneralScreen::peekButtonIsClick(sf::RenderWindow &window) {
    return peekButton.buttonIsClick(window);
}
bool queueGeneralScreen::pushButtonIsClick(sf::RenderWindow &window) {
    return pushButton.buttonIsClick(window);
}
bool queueGeneralScreen::confirmPushIsClick(sf::RenderWindow &window) {
    return pushConfirmButton.buttonIsClick(window);
}
bool queueGeneralScreen::popButtonIsClick(sf::RenderWindow &window) {
    return popButton.buttonIsClick(window);
}
bool queueGeneralScreen::clearButtonIsClick(sf::RenderWindow &window) {
    return clearButton.buttonIsClick(window);
}
bool queueGeneralScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backButton.buttonIsClick(window);
}
bool queueGeneralScreen::pushButtonIsChoose() {
    return pushButton.isChosen();
}

void queueGeneralScreen::turnOffAllButton() {
    createButton.offButton();
    peekButton.offButton();
    pushButton.offButton();
    popButton.offButton();
    clearButton.offButton();
    backButton.offButton();
}
void queueGeneralScreen::turnOnCreateButton() {
    createButton.onButton();
}
void queueGeneralScreen::turnOnPeekButton() {
    peekButton.onButton();
}
void queueGeneralScreen::turnOnPushButton() {
    pushButton.onButton();
}
void queueGeneralScreen::turnOnPopButton() {
    popButton.onButton();
}
void queueGeneralScreen::turnOnClearButton() {
    clearButton.onButton();
}
void queueGeneralScreen::turnOnBackButton() {
    backButton.onButton();
}

bool queueGeneralScreen::pushTextBoxIsClick(sf::RenderWindow &window) {
    return pushTextBox.textBoxButtonIsClick(window);
}
bool queueGeneralScreen::pushTextBoxIsChoose() {
    return pushTextBox.textBoxIsClick();
}
bool queueGeneralScreen::pushTextBoxIsEmpty() {
    return pushTextBox.inputIsEmpty();
}
void queueGeneralScreen::onTextBoxState() {
    pushTextBox.onTextBoxState();
}
void queueGeneralScreen::pushTextBoxKeyboardEvent(sf::Event &event) {
    pushTextBox.processKeyboardEvent(event);
}
int queueGeneralScreen::getInputData() {
    return pushTextBox.getInputDataInt();
}
void queueGeneralScreen::initData() {
    int pushData = rand() % 100;
    std::string dataString = std::to_string(pushData);
    pushTextBox.setTextBoxString(dataString);
}

void queueGeneralScreen::moveButtonWhenHover(sf::RenderWindow &window) {
    this->createButton.moveButtonWhenHover(window);
    this->peekButton.moveButtonWhenHover(window);
    this->pushButton.moveButtonWhenHover(window);
    this->popButton.moveButtonWhenHover(window);
    this->clearButton.moveButtonWhenHover(window);
    this->backButton.moveButtonWhenHover(window);
}

void queueGeneralScreen::drawGeneralScreen(sf::RenderWindow &window) {
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


queueCreateScreen::queueCreateScreen() {
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
    if (!userInputBoxTexture.loadFromFile("src//include//texture//userInputQueue.png")) {
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
bool queueCreateScreen::userInputButtonIsClick(sf::RenderWindow &window) {
    return userInputButton.buttonIsClick(window);
}
bool queueCreateScreen::randomButtonIsClick(sf::RenderWindow &window) {
    return randomInputButton.buttonIsClick(window);
}
bool queueCreateScreen::backButtonIsClick(sf::RenderWindow &window) {
    return backToModeButton.buttonIsClick(window);
}
bool queueCreateScreen::textBoxIsClick(sf::RenderWindow &window) {
    return userInputBox.textBoxButtonIsClick(window);
}
bool queueCreateScreen::confirmButtonIsClick(sf::RenderWindow &window) {
    return confirmInputButton.buttonIsClick(window);
}
bool queueCreateScreen::browseButtonIsClick(sf::RenderWindow &window) {
    return browseButton.buttonIsClick(window);
}

std::string queueCreateScreen::getInputString() {
    return userInputBox.getTextBoxString();
}

std::vector<int> queueCreateScreen::getInputData() {
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

bool queueCreateScreen::userInputButtonGetState() {
    return userInputButton.isChosen();
}
bool queueCreateScreen::textBoxGetState() {
    return userInputBox.textBoxIsClick();
}
void queueCreateScreen::flipInputButtonState() {
    userInputButton.flipChoose();
}
void queueCreateScreen::flipInputBoxState() {
    userInputBox.flipTextBoxState();
}
void queueCreateScreen::offInputBoxState() {
    userInputBox.offTextBoxState();
}
void queueCreateScreen::onInputBoxState() {
    userInputBox.onTextBoxState();
}
bool queueCreateScreen::inputIsEmpty() {
    return userInputBox.inputIsEmpty();
}

void queueCreateScreen::moveButtonWhenHover(sf::RenderWindow &window) {
    userInputButton.moveButtonWhenHover(window);
    randomInputButton.moveButtonWhenHover(window);
    backToModeButton.moveButtonWhenHover(window);
}

void queueCreateScreen::userInputCharacter(char inputCharacter) {
    userInputBox.userInputCharacter(inputCharacter);
}
void queueCreateScreen::userBackspaceCharacter() {
    userInputBox.userBackspace();
}
void queueCreateScreen::userDeleteCharacter() {
    userInputBox.userDelete();
}
void queueCreateScreen::userMoveCursor(int arrowKeyCode) {
    userInputBox.userMoveCursor(arrowKeyCode);
}

void queueCreateScreen::setInputBoxString(std::string &inputString) {
    userInputBox.setTextBoxString(inputString);
}

void queueCreateScreen::drawChooseCreateScreen(sf::RenderWindow &window) {
    userInputButton.drawButton(window);
    randomInputButton.drawButton(window);
    backToModeButton.drawButton(window);
    if (userInputButtonGetState() == true) {
        userInputBox.drawTextBox(window);
        browseButton.drawButton(window, 0.16, 0.17, 19);
        confirmInputButton.drawButton(window, 0.33, 0.14, 21);
    }
}



queueAllScreen::queueAllScreen() {
    currentScreenType = general;
}
bool queueAllScreen::isGeneralScreen() {
    if (currentScreenType == general)
        return true;
    return false;
}
void queueAllScreen::setToGeneral() {
    currentScreenType = general;
}
void queueAllScreen::setToCreate() {
    currentScreenType = create;
}

void queueAllScreen::drawGeneralScreen(sf::RenderWindow &window) {
    theGeneralScreen.drawGeneralScreen(window);
}
void queueAllScreen::drawCreateScreen(sf::RenderWindow &window) {
    theCreateScreen.drawChooseCreateScreen(window);
}


