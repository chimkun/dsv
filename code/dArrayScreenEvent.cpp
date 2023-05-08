#include "dArrayScreenEvent.h"

DArrayObject::DArrayObject() {
    drawType = showcaseDArray;
    backToMenu = 0;
    createRandomList();
}

void DArrayObject::createList(int numberOfNode, std::vector <int> &a) {
    myDArray.build(a);
    theDArrayscreen.theGeneralScreen.initData(numberOfNode);
}
void DArrayObject::createRandomList() {
    int numberOfNode = rand() % 6 + 5;  
    std::vector <int> a;
    std::string sampleInput;
    for (int i = 0; i < numberOfNode; i++) {
        int value = rand() % 100;
        a.push_back(value);
        sampleInput += std::to_string(value);
        sampleInput += ',';
    }
    if (!sampleInput.empty())
        sampleInput.pop_back();
    theDArrayscreen.theCreateScreen.setInputBoxString(sampleInput);
    createList(numberOfNode, a);
}
void DArrayObject::createDefinedList(std::vector <int> &userInput) {
    int numberOfNode = (int) userInput.size();
    createList(numberOfNode, userInput);
}
void DArrayObject::drawList(sf::RenderWindow &window) {
    opacity = std::min(nodeConstants::fadeSpeed + opacity, 255);
    myDArray.drawArray(window, opacity);
}
void DArrayObject::processDrawList() {
    opacity = 0;
    drawType = showcaseDArray;
}

void DArrayObject::drawInsertCreate(sf::RenderWindow &window) {
    newArrayOpacity = std::min(255, newArrayOpacity + arrayConstants::fadeSpeed);
    myDArray.drawInsertCreate(window, newArrayOpacity);
    if (newArrayOpacity == 255) {
        drawType = insertDArray1;
    }
}
void DArrayObject::drawInsertIndicator(sf::RenderWindow &window) {
    int nodeColorIndex = insertData % 4;
    sf::Color nodeColor = colorConstants::nodeColor[nodeColorIndex];
    sf::Color fadeColor = getFadeColor(sf::Color::White, nodeColor, flashTimer);
    insertNumberOpacity = std::min(255, insertNumberOpacity + arrayConstants::fadeSpeed - 1);
    yDistance = std::min(arrayConstants::yNewArray, yDistance + arrayConstants::yMoveSpeed);
    // myDArray.drawInsertNodeIndicator(window, fadeColor, insertNumberOpacity, insertData);
    myDArray.drawInsertNodeIndicator(window, fadeColor, yDistance, insertNumberOpacity, insertData);
    // DArrayCodeBlock.drawInsertCodeBlock(window);
    // DArrayCodeBlock.drawInsertCodeBlockMultiLine(window, 1, 2);
    if (insertNumberOpacity == 255 && yDistance == arrayConstants::yNewArray) {
        drawType = insertDArray2;
        newArrayOpacity = 255;
        yDistance = 0;
        markFirst = 1;
    }
}
void DArrayObject::drawInsertSwapArray(sf::RenderWindow &window) {
    if (markFirst) {
        markFirst = 0;
        sf::sleep(sf::seconds(0.2));
    }
    newArrayOpacity = std::max(0, newArrayOpacity - arrayConstants::fadeSpeed + 2);
    yDistance = std::min(arrayConstants::yNewArray, yDistance + arrayConstants::yMoveSpeed - 1);
    myDArray.drawInsertSwapArray(window, yDistance, newArrayOpacity, insertData);
    if (yDistance == arrayConstants::yNewArray && newArrayOpacity == 0) {
        drawType = insertDArray3;
        sf::sleep(sf::seconds(0.2));
        markFirst = 1;
    }
}
void DArrayObject::drawInsertNodeSwap(sf::RenderWindow &window) {
    insertSwapDistance = std::min(arrayConstants::xDistance, insertSwapDistance + arrayConstants::swapXSpeed);
    myDArray.drawInsertNodeSwap(window, insertSwapIndex, insertData, insertSwapDistance);
    // DArrayCodeBlock.drawInsertCodeBlock(window);
    if (insertSwapDistance == arrayConstants::xDistance) {
        if (markFirst) {
            markFirst = 0;
            insertSwapTime.restart();
        }
        sf::Time duration = sf::milliseconds(400);
        if (insertSwapTime.getElapsedTime().asMilliseconds() > duration.asMilliseconds()) {
            markFirst = 1;
            insertSwapDistance = 0;
            insertSwapIndex--;
            if (insertSwapIndex == insertIndex - 1) {
                myDArray.insertAtMiddle(insertIndex, insertData);
                drawType = showcaseDArray;
            }
        }

        if (insertSwapIndex > insertIndex) {
            // DArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 3);
        }
        else {
            // DArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 2);
        }
    }
    else {
        // DArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 4);
    }
}

void DArrayObject::drawDeleteIndicator(sf::RenderWindow &window) {
    int deleteData = myDArray.accessIndex(deleteIndex);
    sf::Color nodeColor = colorConstants::nodeColor[deleteData % 4];
    sf::Color fadeColor = getFadeColor(nodeColor, sf::Color::White, flashTimer);
    deleteNumberOpacity = std::max(0, deleteNumberOpacity - arrayConstants::fadeSpeed);
    myDArray.drawDeleteNodeIndicator(window, fadeColor, deleteIndex, deleteNumberOpacity);
    // DArrayCodeBlock.drawDeleteCodeBlock(window);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()/2.0) {
        // DArrayCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
    }
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = deleteDArray1;
        markFirst = 1;
        flashTimer.restart();
    }
}
void DArrayObject::drawDeleteNodeSwap(sf::RenderWindow &window) {
    if (deleteSwapIndex == myDArray.getArrayLength()) {
        myDArray.deleteAtMiddle(deleteIndex);
        drawType = showcaseDArray;
        return;
    }
    deleteSwapDistance = std::min(arrayConstants::swapXSpeed + deleteSwapDistance, arrayConstants::xDistance);
    myDArray.drawDeleteNodeSwap(window, deleteIndex, deleteSwapIndex, deleteSwapDistance); 
    // DArrayCodeBlock.drawDeleteCodeBlock(window);
    if (deleteSwapDistance == arrayConstants::xDistance) {
        if (markFirst) {
            markFirst = 0;
            deleteSwapTime.restart();
        }
        sf::Time duration = sf::milliseconds(400);
        if (deleteSwapTime.getElapsedTime().asMilliseconds() > duration.asMilliseconds()) {
            markFirst = 1;
            deleteSwapDistance = 0;
            deleteSwapIndex++;
            if (deleteSwapIndex == myDArray.getArrayLength()) {
                myDArray.deleteAtMiddle(deleteIndex);
                drawType = deleteDArray2;
                deleteNumberOpacity = 255;
            }
        }
        if (deleteSwapIndex < myDArray.getArrayLength() - 1) {
            // DArrayCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
        }
        else {
            // DArrayCodeBlock.drawDeleteCodeBlockSingleLine(window, 2);
        }
    }
    else {
        // DArrayCodeBlock.drawDeleteCodeBlockSingleLine(window, 1);
    }
}
void DArrayObject::drawDeleteResize(sf::RenderWindow &window) {
    deleteNumberOpacity = std::max(0, deleteNumberOpacity - arrayConstants::fadeSpeed);
    myDArray.drawDeleteNodeResize(window, deleteNumberOpacity);
    if (deleteNumberOpacity == 0) {
        drawType = showcaseDArray;
    }
}

void DArrayObject::drawSearchIndicator(sf::RenderWindow &window) {
    int searchIndex = myDArray.searchValue(searchData);
    int drawIterateIndex = searchIndex;
    if (searchIndex == -1) 
        drawIterateIndex = myDArray.getArrayLength() - 1;
    // std::cerr << "indicate " << searchIterateTarget << " " << drawIterateIndex << '\n';
    sf::Color fadeColor = getFadeColorOptionalDuration(sf::Color::White, nodeConstants::flashColor, flashTimer, arrayConstants::flashDuration);
    myDArray.drawSearchIndicator(window, fadeColor, searchIterateTarget);
    // DArrayCodeBlock.drawSearchCodeBlock(window);
    // DArrayCodeBlock.drawSearchCodeBlockSingleLine(window, 0);
    // std::cerr << "drawn\n";
    if (flashTimer.getElapsedTime().asSeconds() >= arrayConstants::flashDuration.asSeconds()) {
        searchIterateTarget++;
        flashTimer.restart();
    }
    if (searchIterateTarget > drawIterateIndex) {
        drawType = searchDArray1;
        flashTimer.restart();
    }
}
void DArrayObject::drawSearchHighlight(sf::RenderWindow &window) {
    int searchIndex = myDArray.searchValue(searchData);
    int drawIterateIndex = searchIndex;
    if (searchIndex == -1) 
        drawIterateIndex = 69;
    sf::Color fadeColor = getFadeColorOptionalDuration(nodeConstants::flashColor, nodeConstants::searchFoundColor, flashTimer, arrayConstants::flashDuration);
    myDArray.drawSearchIndicator(window, fadeColor, drawIterateIndex);
    // DArrayCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        // DArrayCodeBlock.drawSearchCodeBlockSingleLine(window, 3);
    }
    else {
        // DArrayCodeBlock.drawSearchCodeBlockMultiLine(window, 1, 2);
    }
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = searchDArray2;
        sf::sleep(sf::seconds(0.5));
        flashTimer.restart();
    }
}
void DArrayObject::drawSearchRevert(sf::RenderWindow &window) {
    int searchIndex = myDArray.searchValue(searchData);
    int drawIterateIndex = searchIndex;
    if (searchIndex == -1) 
        drawIterateIndex = 69;
    sf::Color fadeFlashColor = getFadeColorOptionalDuration(nodeConstants::flashColor, sf::Color::White, flashTimer, arrayConstants::flashDuration);
    sf::Color fadeFoundColor = getFadeColorOptionalDuration(nodeConstants::searchFoundColor, sf::Color::White, flashTimer, arrayConstants::flashDuration);
    myDArray.drawSearchRevert(window, fadeFlashColor, fadeFoundColor, drawIterateIndex);
    // DArrayCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        // DArrayCodeBlock.drawSearchCodeBlockSingleLine(window, 3);
    }
    else {
        // DArrayCodeBlock.drawSearchCodeBlockMultiLine(window, 1, 2);
    }
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseDArray;
        flashTimer.restart();
    }
}
void DArrayObject::drawUpdateIndicator(sf::RenderWindow &window) {
    sf::Color fadeColor = getFadeColor(sf::Color::White, nodeConstants::searchFoundColor, flashTimer);
    updateNumberOpacity = std::max(0, updateNumberOpacity - nodeConstants::fadeSpeed);
    myDArray.drawUpdateIndicator(window, fadeColor, updateIndex, updateNumberOpacity);
    // DArrayCodeBlock.drawUpdateCodeBlock(window);
    // DArrayCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()
     && updateNumberOpacity == 0) {
        drawType = updateDArray1;
        myDArray.updateIndex(updateIndex, updateData);
        flashTimer.restart();
    }
}
void DArrayObject::drawUpdateChangeNum(sf::RenderWindow &window) {
    updateNumberOpacity = std::min(255, updateNumberOpacity + 6);
    myDArray.drawUpdateIndicator(window, nodeConstants::searchFoundColor, updateIndex, updateNumberOpacity);
    // DArrayCodeBlock.drawUpdateCodeBlock(window);
    // DArrayCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()
     && updateNumberOpacity == 255) {
        drawType = updateDArray2;
        flashTimer.restart();
    }
}
void DArrayObject::drawUpdateRevert(sf::RenderWindow &window) {
    sf::Color fadeColor = getFadeColor(nodeConstants::searchFoundColor, sf::Color::White, flashTimer);
    myDArray.drawUpdateRevert(window, fadeColor, updateIndex);
    // DArrayCodeBlock.drawUpdateCodeBlock(window);
    // DArrayCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseDArray;
        flashTimer.restart();
    }
}

void DArrayObject::processType(sf::RenderWindow &window) {
    if (theDArrayscreen.isGeneralScreen()) {
        theDArrayscreen.drawGeneralScreen(window);
    }
    else {
        theDArrayscreen.drawCreateScreen(window);
    }
    switch (drawType) {
        case makeDArray:
            processDrawList();
            break;
        case showcaseDArray:
            drawList(window);
            break;
        case chooseMakeDArray:
            drawList(window);
            break;
        case insertDArray0:
            drawInsertCreate(window);
            break;
        case insertDArray1:
            drawInsertIndicator(window);
            break;
        case insertDArray2:
            drawInsertSwapArray(window);
            break;
        case insertDArray3:
            drawInsertNodeSwap(window);
            break;
        case deleteDArray0:
            drawDeleteIndicator(window);
            break;
        case deleteDArray1:
            drawDeleteNodeSwap(window);
            break;
        case deleteDArray2:
            drawDeleteResize(window);
            break;
        case searchDArray0:
            drawSearchIndicator(window);
            break;
        case searchDArray1:
            drawSearchHighlight(window);
            break;
        case searchDArray2:
            drawSearchRevert(window);
            break;
        case updateDArray0:
            drawUpdateIndicator(window);
            break;
        case updateDArray1:
            drawUpdateChangeNum(window);
            break;
        case updateDArray2:
            drawUpdateRevert(window);
            break;
    }
}


void DArrayObject::processMouseEvent(sf::RenderWindow &window) {
    // std::cerr << "event\n";
    if (theDArrayscreen.isGeneralScreen()) {
        if (theDArrayscreen.theGeneralScreen.createButtonIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAllButton();
            drawType = chooseMakeDArray;
            theDArrayscreen.setCreate();
        }
        else if (theDArrayscreen.theGeneralScreen.addButtonIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAllButton();
            theDArrayscreen.theGeneralScreen.addButton.flipButtonState();
            // theDArrayscreen.theGeneralScreen.addBeginning.flipButtonState();
            // theDArrayscreen.theGeneralScreen.addEnding.flipButtonState();
        }
        else if (theDArrayscreen.theGeneralScreen.deleteButtonIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAllButton();
            theDArrayscreen.theGeneralScreen.deleteButton.flipButtonState();
        }
        else if (theDArrayscreen.theGeneralScreen.searchButtonIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAllButton();
            theDArrayscreen.theGeneralScreen.searchButton.flipButtonState();
        }
        else if (theDArrayscreen.theGeneralScreen.updateButtonIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAllButton();
            theDArrayscreen.theGeneralScreen.updateButton.flipButtonState();
        }
        else if (theDArrayscreen.theGeneralScreen.backToMenuIsClick(window)) {
            this->backToMenu = true;
            theDArrayscreen.theGeneralScreen.turnOffAllButton();
        }
        else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addButton.textBoxIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAddTextBox();
            theDArrayscreen.theGeneralScreen.addButton.onInputBoxState();
        }
        else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addBeginningText.textBoxButtonIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAddTextBox();
            theDArrayscreen.theGeneralScreen.addBeginningText.onTextBoxState();
        }
        else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addEndingText.textBoxButtonIsClick(window)) {
            theDArrayscreen.theGeneralScreen.turnOffAddTextBox();
            theDArrayscreen.theGeneralScreen.addEndingText.onTextBoxState();
        }
        else if (theDArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.deleteButton.textBoxIsClick(window)) {
            theDArrayscreen.theGeneralScreen.deleteButton.onInputBoxState();
        }
        else if (theDArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.searchButton.textBoxIsClick(window)) {
            theDArrayscreen.theGeneralScreen.searchButton.onInputBoxState();
        }
        else if (theDArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.updateButton.textBoxIsClick(window)) {
            theDArrayscreen.theGeneralScreen.updateButton.onInputBoxState();
        }
        else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.addButton.confirmButtonIsClick(window)) {
            if (!theDArrayscreen.theGeneralScreen.addButton.inputIsEmpty()) {
                std::pair <int, int> userInput = theDArrayscreen.theGeneralScreen.addButton.getInputDataPair();
                if (insertIsValid(userInput.first, userInput.second)) {
                    drawType = insertDArray0;
                    int inputIndex = userInput.first, inputElement = userInput.second;
                    insertNodeProcess(inputIndex, inputElement);
                    // // DArrayCodeBlock.drawInsertCodeBlock(window);
                    // // DArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
                }
            }
        }
        else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.addBeginning.buttonIsClick(window)) {
            if (!theDArrayscreen.theGeneralScreen.addBeginningText.inputIsEmpty()) {
                int userInput = theDArrayscreen.theGeneralScreen.addBeginningText.getInputDataInt();
                if (insertIsValid(0, userInput)) {
                    drawType = insertDArray0;
                    int inputIndex = 0, inputElement = userInput;
                    insertNodeProcess(inputIndex, inputElement);
                    // // DArrayCodeBlock.drawInsertBeginCodeBlock(window);
                    // if (myDArray.getNumberOfNode() == 0)
                    //     // DArrayCodeBlock.drawInsertBeginCodeBlockSingleLine(window, 0);
                    // else 
                    //     // DArrayCodeBlock.drawInsertBeginCodeBlockSingleLine(window, 3);
                }
            }
        }
        else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.addEnding.buttonIsClick(window)) {
            if (!theDArrayscreen.theGeneralScreen.addEndingText.inputIsEmpty()) {
                int userInput = theDArrayscreen.theGeneralScreen.addEndingText.getInputDataInt();
                if (insertIsValid(myDArray.getArrayLength(), userInput)) {
                    drawType = insertDArray0;
                    int inputIndex = myDArray.getArrayLength(), inputElement = userInput;
                    insertNodeProcess(inputIndex, inputElement);
                }
                // // DArrayCodeBlock.drawInsertCodeBlock(window);
                // // DArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theDArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.deleteButton.confirmButtonIsClick(window)) {
            if (!theDArrayscreen.theGeneralScreen.deleteButton.inputIsEmpty()) {
                int userInput = theDArrayscreen.theGeneralScreen.deleteButton.getInputDataInt();
                if (deleteIsValid(userInput)) {
                    drawType = deleteDArray0;
                    deleteIndex = userInput;
                    deleteNodeProcess(deleteIndex);
                }
            }
        }
        else if (theDArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.delBeginning.buttonIsClick(window)) {
                if (deleteIsValid(0)) {
                    drawType = deleteDArray0;
                    deleteIndex = 0;
                    deleteNodeProcess(deleteIndex);
                }
        }
        else if (theDArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.delEnding.buttonIsClick(window)) {
            if (deleteIsValid((int) myDArray.getArrayLength() - 1)) {
                drawType = deleteDArray0;
                deleteIndex = myDArray.getArrayLength() - 1;
                deleteNodeProcess(deleteIndex);
            }
        }
        else if (theDArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.searchButton.confirmButtonIsClick(window)) {
            if (!theDArrayscreen.theGeneralScreen.searchButton.inputIsEmpty()) {
                drawType = searchDArray0;
                int userInput = theDArrayscreen.theGeneralScreen.searchButton.getInputDataInt();
                searchData = userInput;
                searchNodeProcess(searchData);
            }
        }
        else if (theDArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() 
              && theDArrayscreen.theGeneralScreen.updateButton.confirmButtonIsClick(window)) {
            if (!theDArrayscreen.theGeneralScreen.updateButton.inputIsEmpty()) {
                std::pair <int, int> userInput = theDArrayscreen.theGeneralScreen.updateButton.getInputDataPair();
                if (updateIsValid(userInput.first, userInput.second)) {
                    drawType = updateDArray0;
                    updateIndex = userInput.first, updateData = userInput.second;
                    updateNodeProcess(updateIndex, updateData);
                }
            }
        }
    }
    else {
        if (theDArrayscreen.theCreateScreen.userInputButtonIsClick(window)) {
            theDArrayscreen.theCreateScreen.flipInputButtonState();
        }
        else if (theDArrayscreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = showcaseDArray;
            createRandomList();
        }
        else if (theDArrayscreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = showcaseDArray;
            theDArrayscreen.setGeneral();
        }
        else if (theDArrayscreen.theCreateScreen.userInputButtonGetState()) {
            if (theDArrayscreen.theCreateScreen.textBoxIsClick(window)) {
                theDArrayscreen.theCreateScreen.onInputBoxState();
            }
            else if (theDArrayscreen.theCreateScreen.confirmButtonIsClick(window)) {
                if (!theDArrayscreen.theCreateScreen.inputIsEmpty()) {
                    drawType = makeDArray;
                    std::vector <int> userInput = theDArrayscreen.theCreateScreen.getInputData();
                    createDefinedList(userInput);
                }
            }
            else if (theDArrayscreen.theCreateScreen.browseButtonIsClick(window)) {
                std::string fileRead;
                if (browseForFile(fileRead)) {
                    std::vector <int> userInput = getInputData(fileRead);
                    if ((int) userInput.size() > 0) {
                        drawType = makeDArray;
                        createDefinedList(userInput);
                    }
                }
            }
            else {
                theDArrayscreen.theCreateScreen.offInputBoxState();
            }
        }
    }
}
void DArrayObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeDArray) {
        if (theDArrayscreen.theCreateScreen.userInputButtonGetState() && theDArrayscreen.theCreateScreen.textBoxGetState()) {
            if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                char inputCharacter = (char) event.text.unicode;
                theDArrayscreen.theCreateScreen.userInputCharacter(inputCharacter);
            }
        }
    }
    else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addBeginningText.textBoxIsClick()) {
        theDArrayscreen.theGeneralScreen.addBeginningText.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addEndingText.textBoxIsClick()) {
        theDArrayscreen.theGeneralScreen.addEndingText.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void DArrayObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeDArray) {
        if (theDArrayscreen.theCreateScreen.userInputButtonGetState() && theDArrayscreen.theCreateScreen.textBoxGetState()) {
            if (event.key.code == sf::Keyboard::Backspace) {
                theDArrayscreen.theCreateScreen.userBackspaceCharacter();
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                theDArrayscreen.theCreateScreen.userMoveCursor(event.key.code);
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                theDArrayscreen.theCreateScreen.userDeleteCharacter();
            }
        }
    }
    else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addBeginningTextIsChoose()) {
        theDArrayscreen.theGeneralScreen.addBeginningText.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.addEndingTextIsChoose()) {
        theDArrayscreen.theGeneralScreen.addEndingText.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theDArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() && theDArrayscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theDArrayscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void DArrayObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (drawType == showcaseDArray) {
        theDArrayscreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else if (drawType == chooseMakeDArray) {
        theDArrayscreen.theCreateScreen.moveButtonWhenHover(window);
    }
}


bool DArrayObject::insertIsValid(int addIndex, int addData) {
    if (0 <= addIndex && addIndex <= myDArray.getArrayLength() && myDArray.getArrayLength() < 16);
        return true;
    return false;
}
bool DArrayObject::deleteIsValid(int delIndex) {
    if (0 <= delIndex && delIndex < myDArray.getArrayLength())
        return true;
    return false;
}
bool DArrayObject::updateIsValid(int updIndex, int updData){
    if (0 <= updIndex && updIndex < myDArray.getArrayLength() && 0 <= updData && updData <= 99)
        return true;
    return false;
}

void DArrayObject::insertNodeProcess(int insertIndex, int insertData) {
    this->insertIndex = insertIndex;
    this->insertData = insertData;
    this->insertNumberOpacity = this->newArrayOpacity = 0;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
    this->insertSwapIndex = myDArray.getArrayLength() - 1;
    this->insertSwapDistance = 0;
    this->yDistance = 0;
}
void DArrayObject::deleteNodeProcess(int deleteIndex) {
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
    this->deleteSwapDistance = 0;
    this->deleteSwapIndex = deleteIndex + 1;
    this->deleteNumberOpacity = 255;
}
void DArrayObject::searchNodeProcess(int searchData) {
    this->searchIndex = myDArray.searchValue(searchData);
    this->searchIterateTarget = 0;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void DArrayObject::updateNodeProcess(int updateIndex, int updateData) {
    this->updateNumberOpacity = 255;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}


void DArrayObject::deleteDArray() {
    // myDArray.deleteList();
    return;
}

void DArrayObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}


bool DArrayObject::exitDArrayScreen() {
    return this->backToMenu;
}
void DArrayObject::setExitToFalse() {
    this->backToMenu = 0;
}
void DArrayObject::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            processMouseEvent(window);
            break;
        case sf::Event::TextEntered:
            processKeyboardInputEvent(window, event);
            break;
        case sf::Event::KeyPressed:
            processKeyboardOtherActionEvent(window, event);
            break;
    }
}
void DArrayObject::drawDArrayScreen(sf::RenderWindow &window) {
    drawBackground(window);
    processMouseHoverEvent(window);
    processType(window);
}

void DArrayObject::inputValue(int &value) {
    std::cin >> value;
}

void DArrayObject::setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase) {
    if (nodePositionXAfterInsert < nodeConstants::nodeDistance)
        nodePositionXAfterInsert = std::min(nodeConstants::nodeDistance, nodePositionXAfterInsert + nodeConstants::insertMoveSpeed);
    if (insertPhase == 2)
        insertNodeOpacity = std::min(insertNodeOpacity + nodeConstants::fadeSpeed, 255);
    if (insertPhase == 2 && insertNodePosition.y > nodeConstants::firstNodePositionY && insertNodeOpacity == 255)
        insertNodePosition.y = std::max((float) insertNodePosition.y - nodeConstants::insertMoveSpeed, (float) nodeConstants::firstNodePositionY);
}

std::vector<int> DArrayObject::getInputData(std::string &inputString) {
    std::string theInputString = inputString;
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