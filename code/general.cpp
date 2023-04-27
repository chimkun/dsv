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
    sf::Vector2f addButtonTextBoxPosition(buttonConstants::textBoxDistance, 565),
                 deleteButtonTextBoxPosition(buttonConstants::textBoxDistance, 565 + 85),
                 searchButtonTextBoxPosition(buttonConstants::textBoxDistance, 552 + 85 * 2),
                 updateButtonTextBoxPosition(buttonConstants::textBoxDistance, 552 + 85 * 3);
//     createButton.initButton(sf::Vector2f(-50, 450), createButtonTexture, createString);
    this->createButton.initButton(createButtonPosition, createButtonTexture, createString);
    this->addButton = buttonAndTextBox(addButtonPosition, addButtonTexture, addString, addButtonTextBoxPosition, addButtonTextBoxTexture);
    this->deleteButton = buttonAndTextBox(deleteButtonPosition, deleteButtonTexture, deleteString, deleteButtonTextBoxPosition, deleteButtonTextBoxTexture);
    this->searchButton = buttonAndTextBox(searchButtonPosition, searchButtonTexture, searchString, searchButtonTextBoxPosition, searchButtonTextBoxTexture);
    this->updateButton = buttonAndTextBox(updateButtonPosition, updateButtonTexture, updateString, updateButtonTextBoxPosition, updateButtonTextBoxTexture);

    sf::Texture delButtonSpec;
    if (!delButtonSpec.loadFromFile("src//include//texture//deleteButtonSpec.png")) {
        std::cout << "texture file not found\n";
        exit(-1);
    }

    std::string confirmString = "go!";
    sf::Vector2f addBeginningPos = sf::Vector2f(buttonConstants::textBoxDistance + 325, 565);
    sf::Vector2f addBeginningTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 225, 565);
    addBeginning.initButton(addBeginningPos, addButtonTextBoxTexture, confirmString);
    addBeginningText = textBox(addBeginningTextPos, addButtonTextBoxTexture, 
                               addBeginningTextPos + sf::Vector2f(9, 8), addBeginningTextPos + sf::Vector2f(85, 8));

    sf::Vector2f addEndingPos = sf::Vector2f(buttonConstants::textBoxDistance + 550, 565);
    sf::Vector2f addEndingTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 450, 565);
    addEnding.initButton(addEndingPos, addButtonTextBoxTexture, confirmString);
    addEndingText = textBox(addEndingTextPos, addButtonTextBoxTexture, 
                            addEndingTextPos + sf::Vector2f(9, 8), addEndingTextPos + sf::Vector2f(85, 8));

                            
    sf::Vector2f delBeginningPos = sf::Vector2f(buttonConstants::textBoxDistance + 225, 565 + 85);
    delBeginning.initButton(delBeginningPos, delButtonSpec, confirmString);

    sf::Vector2f delEndingPos = sf::Vector2f(buttonConstants::textBoxDistance + 450, 565 + 85);
    delEnding.initButton(delEndingPos, delButtonSpec, confirmString);
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

void generalScreen::initData(int numberOfNode) {
    int addIndex = rand() % numberOfNode + 1, addData = rand() % 100;
    int deleteIndex = rand() % numberOfNode;
    int searchData = rand() % 100;
    int updateIndex = rand() % numberOfNode + 1, updateData = rand() % 100;
    std::string addString = std::to_string(addIndex) + ',' + std::to_string(addData);
    std::string deleteString = std::to_string(deleteIndex);
    std::string searchString = std::to_string(searchData);
    std::string updateString = std::to_string(updateIndex) + ',' + std::to_string(updateData);

    addButton.setInputString(addString);
    deleteButton.setInputString(deleteString);
    searchButton.setInputString(searchString);
    updateButton.setInputString(updateString);
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
        updateButton.flipButtonState();
}
void generalScreen::turnOffAddTextBox() {
    addButton.offInputBoxState();
    addBeginningText.offTextBoxState();
    addEndingText.offTextBoxState();
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
    if (addButton.buttonIsChoose()) {
        addBeginning.drawButton(window, 0.31, 0.17, 21);
        addBeginningText.drawTextBox(window);

        addEnding.drawButton(window, 0.31, 0.17, 21);
        addEndingText.drawTextBox(window);

        sf::Vector2f origin = sf::Vector2f(0, 0);
        sf::Vector2f addMiddleTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 10, 535);
        std::string insertAtIndex = "insert at middle";
        noteText.drawOptionalTextSize(window, insertAtIndex, origin, addMiddleTextPos, 200, 22);
        
        sf::Vector2f addBeginningTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 220, 535);
        std::string insertAtBeginningString = "insert at beginning";
        noteText.drawOptionalTextSize(window, insertAtBeginningString, origin, addBeginningTextPos, 200, 22);
        
        sf::Vector2f addEndingTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 460, 535);
        std::string insertAtEndingString = "insert at ending";
        noteText.drawOptionalTextSize(window, insertAtEndingString, origin, addEndingTextPos, 200, 22);
    }

    deleteButton.drawButton(window);
    if (deleteButton.buttonIsChoose()) {
        delBeginning.drawButton(window, 0.43, 0.17, 21);

        delEnding.drawButton(window, 0.43, 0.17, 21);

        sf::Vector2f origin = sf::Vector2f(0, 0);
        sf::Vector2f delMiddleTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 10, 535 + 85);
        std::string deleteAtIndex = "delete at middle";
        noteText.drawOptionalTextSize(window, deleteAtIndex, origin, delMiddleTextPos, 200, 22);
        
        sf::Vector2f delBeginningTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 220, 535 + 85);
        std::string delAtBeginningString = "delete at beginning";
        noteText.drawOptionalTextSize(window, delAtBeginningString, origin, delBeginningTextPos, 200, 22);
        
        sf::Vector2f delEndingTextPos = sf::Vector2f(buttonConstants::textBoxDistance + 460, 535 + 85);
        std::string delAtEndingString = "delete at ending";
        noteText.drawOptionalTextSize(window, delAtEndingString, origin, delEndingTextPos, 200, 22);
    }
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

    sf::Texture userInputBoxTexture, confirmInputButtonTexture, browseButtonTexture;
    if (!userInputBoxTexture.loadFromFile("src//include//texture//userInputData.png")) {
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
    sf::Vector2f rightCursorPos = sf::Vector2f(buttonConstants::textBoxDistance + buttonConstants::textCursorDistance + 348, 535 + 25);
    userInputBox = textBox(sf::Vector2f(buttonConstants::textBoxDistance, 552), userInputBoxTexture, leftCursorPos, rightCursorPos);
    // left = textPos + (textCursorDistance, 8)
    // right = textPos + (texture_length, 8)
    browseButton.initButton(sf::Vector2f(buttonConstants::textBoxDistance + 480, 553), browseButtonTexture, browseString);
    confirmInputButton.initButton(sf::Vector2f(buttonConstants::textBoxDistance + 380, 553), confirmInputButtonTexture, confirmString);
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
bool createScreen::browseButtonIsClick(sf::RenderWindow &window) {
    return browseButton.buttonIsClick(window);
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
        browseButton.drawButton(window, 0.16, 0.17, 19);
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