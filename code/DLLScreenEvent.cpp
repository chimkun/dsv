#include "DLLscreenEvent.h"

DLLObject::DLLObject() {
    drawType = showcaseDLL;
    createRandomList();
    this->backToMenu = false;
}

void DLLObject::createList(int numberOfNode, std::vector <int> &a) {
    myDLL.deleteList();
    myDLL.build(a);
    theDLLscreen.theGeneralScreen.initData(numberOfNode);
    processDrawList();
}
void DLLObject::createRandomList() {
    int numberOfNode = rand() % 5 + 1;
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
    theDLLscreen.theCreateScreen.setInputBoxString(sampleInput);
    createList(numberOfNode, a);
}
void DLLObject::createDefinedList(std::vector <int> &userInput) {
    int numberOfNode = (int) userInput.size();
    createList(numberOfNode, userInput);
}
void DLLObject::drawList(sf::RenderWindow &window) {
    opacity = std::min(nodeConstants::fadeSpeed + opacity, 255);
    myDLL.drawList(window, opacity);
}
void DLLObject::processDrawList() {
    opacity = 0;
    drawType = showcaseDLL;
}

void DLLObject::drawInsertIndicator(sf::RenderWindow &window) {
    if (insertIndex == myDLL.getNumberOfNode()) {
        drawType = insertDLL2;
        myDLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, 
                                     nodeConstants::baseColor);
        myDLL.insertAfterIndex(insertIndex, insertData);
        insertIndex++;
        return;
    }
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds())
        sf::sleep(sf::milliseconds(500));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds());
    myDLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
    // DLLCodeBlock.drawInsertCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            DLLCodeBlock.drawInsertCodeBlockSingleLine(window, 2);
        }
        else {
            DLLCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        DLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > insertIndex) {
        drawType = insertDLL1;
        myDLL.insertAfterIndex(insertIndex, insertData);
        insertIndex++;
        markFirst = 1;
    }
}
void DLLObject::drawListWhenInsert(sf::RenderWindow &window) {
    if (markFirst) {
        markFirst = 0;
        sf::sleep(sf::milliseconds(500));
    }
    // std::cout << "opacity: " << opacity << '\n';
    myDLL.drawListWhenInsert(window, insertIndex, 
                             opacity, nodePositionXAfterInsert);
    // DLLCodeBlock.drawInsertCodeBlock(window);
    DLLCodeBlock.drawInsertCodeBlockMultiLine(window, 3, 4);
    if (nodePositionXAfterInsert >= nodeConstants::nodeDistance) {
        drawType = insertDLL2;
        flashTimer.restart();
    }
    else {
        setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 1);
    }
}
void DLLObject::drawInsertNode(sf::RenderWindow &window) {
    // DLLCodeBlock.drawInsertCodeBlock(window);
    DLLCodeBlock.drawInsertCodeBlockMultiLine(window, 5, 6);
    if (insertIndex == myDLL.getNumberOfNode())
        myDLL.drawInsertNode(window, insertIndex, opacity,
                            nodeConstants::baseColor,
                            insertNodePosition, insertNodeOpacity);
    else
        myDLL.drawInsertNode(window, insertIndex, opacity,
                            getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
                            insertNodePosition, insertNodeOpacity);
    if (insertNodePosition.y == nodeConstants::firstNodePositionY)
        drawType = showcaseDLL;
    else {
        setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 2);
    }
}


void DLLObject::drawDeleteIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds())
        sf::sleep(sf::milliseconds(500));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds());
    myDLL.drawDeleteNodeIndicator(window, deleteIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
    // DLLCodeBlock.drawDeleteCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            DLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 2);
        }
        else {
            DLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        DLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > deleteIndex) {
        drawType = deleteDLL1;
        markFirst = 1;
    }
}
void DLLObject::drawDeleteNode(sf::RenderWindow &window) {
    if (markFirst) {
        markFirst = 0;
        sf::sleep(sf::milliseconds(500));
    }
    myDLL.drawDeleteNode(window, deleteIndex, nodeOpacity, deleteNodeOpacity);
    // DLLCodeBlock.drawDeleteCodeBlock(window);
    DLLCodeBlock.drawDeleteCodeBlockMultiLine(window, 3, 4);
    if (deleteNodeOpacity - nodeConstants::fadeSpeed > 0) {
        deleteNodeOpacity = std::max(deleteNodeOpacity - nodeConstants::fadeSpeed, 0);
    }
    else {
        myDLL.deleteAtIndex(deleteIndex);
        nodeOpacity = 255;
        drawType = deleteDLL2;
        flashTimer.restart();
    }
}
void DLLObject::drawDeleteNodeMove(sf::RenderWindow &window) {
    myDLL.drawDeleteNodeMove(window, deleteIndex, nodeOpacity, 
                             nodePositionDiffX, newArrowOpacity,
                             getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer));
    // DLLCodeBlock.drawDeleteCodeBlock(window);
    DLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 5);
    if (nodePositionDiffX > 0 || newArrowOpacity < 255) {
        newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
        if (newArrowOpacity == 255)
            nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
    }
    else 
        drawType = showcaseDLL;
}

void DLLObject::drawSearchIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
        sf::sleep(sf::milliseconds(500));
    }
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = myDLL.getNumberOfNode();
    myDLL.drawSearchIndicator(window, searchIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));   
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
    // DLLCodeBlock.drawSearchCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            if (gotoIndex <= tempSearchIndex)
               DLLCodeBlock.drawSearchCodeBlockSingleLine(window, 4);
        }
        else {
            DLLCodeBlock.drawSearchCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        DLLCodeBlock.drawSearchCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > tempSearchIndex) {
        drawType = searchDLL1;
        flashTimer.restart();
        markFirst = 1;
    }
}
void DLLObject::drawSearchHighlight(sf::RenderWindow &window) {
    myDLL.drawSearchHighlight(window, searchIndex, 
                              getFadeColor(nodeConstants::flashColor, nodeConstants::searchFoundColor, flashTimer), 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::searchFoundColor, flashTimer),
                              infoTextOpacity);
    infoTextOpacity = std::min(255, infoTextOpacity + nodeConstants::fadeSpeed);
    // DLLCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        DLLCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
    }
    else {
        DLLCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
    }
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = searchDLL2;
        flashTimer.restart();
    }
}
void DLLObject::drawSearchRevert(sf::RenderWindow &window) {
    myDLL.drawSearchRevert(window, searchIndex, 
                           getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
                           getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer),
                           infoTextOpacity);
    // DLLCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        DLLCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
    }
    else {
        DLLCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
    }
    infoTextOpacity = std::max(0, infoTextOpacity - nodeConstants::fadeSpeed);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseDLL;
        flashTimer.restart();
    }
}
void DLLObject::drawUpdateIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
        sf::sleep(sf::milliseconds(500));
    }
    myDLL.drawUpdateIndicator(window, updateIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
    // DLLCodeBlock.drawUpdateCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            if (gotoIndex <= updateIndex)
                DLLCodeBlock.drawUpdateCodeBlockSingleLine(window, 5);
        }
        else {
            DLLCodeBlock.drawUpdateCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        DLLCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > updateIndex) {
        drawType = updateDLL1;
        flashTimer.restart();
    }
}
void DLLObject::drawUpdateChangeNum(sf::RenderWindow &window) {
    sf::Color fadeColor;
    if (opacityMultiplier == -1)
        fadeColor = nodeConstants::baseColor;
    else 
        fadeColor = nodeConstants::searchFoundColor;
    myDLL.drawUpdateChangeNum(window, updateIndex, updateData, numberOpacity, fadeColor);
    // DLLCodeBlock.drawUpdateCodeBlock(window);
    DLLCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
    if (opacityMultiplier == -1) {
        numberOpacity = std::max(0, numberOpacity - nodeConstants::fadeSpeed);
        if (numberOpacity == 0) {
            opacityMultiplier = 1;
            myDLL.updateAtIndex(updateIndex, updateData);
        }
    }
    else {
        if (numberOpacity == 0)
            sf::sleep(sf::seconds(0.1));
        numberOpacity = std::min(255, numberOpacity + nodeConstants::fadeSpeed);
    }

    if (opacityMultiplier == 1 && numberOpacity == 255) {
        sf::sleep(sf::seconds(1));
        flashTimer.restart();
        drawType = updateDLL2;
    }
}
void DLLObject::drawUpdateRevert(sf::RenderWindow &window) {
    sf::Color fadeOutlineColor, fadeNumberColor;
    fadeOutlineColor = getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer);
    fadeNumberColor = getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer);
    myDLL.drawUpdateRevert(window, updateIndex, fadeOutlineColor, fadeNumberColor);
    // DLLCodeBlock.drawUpdateCodeBlock(window);
    DLLCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseDLL;
        flashTimer.restart();
    }
}

void DLLObject::processType(sf::RenderWindow &window) {
    if (drawType != chooseMakeDLL)
        theDLLscreen.drawGeneralScreen(window);
    else {
        theDLLscreen.drawCreateScreen(window);
    }
    switch (prevType) {
        case insertDLL0:
            DLLCodeBlock.drawInsertCodeBlock(window);
            break;
        case deleteDLL0:
            DLLCodeBlock.drawDeleteCodeBlock(window);
            break;
        case searchDLL0:
            DLLCodeBlock.drawSearchCodeBlock(window);
            break;
        case updateDLL0:
            DLLCodeBlock.drawUpdateCodeBlock(window);
            break;
    }
    switch (drawType) {
        case makeDLL:
            processDrawList();
            break;
        case showcaseDLL:
            drawList(window);
            break;
        case chooseMakeDLL:
            drawList(window);
            break;
        case insertDLL0:
            drawInsertIndicator(window);
            break;
        case insertDLL1:
            drawListWhenInsert(window);
            break;
        case insertDLL2:
            drawInsertNode(window);
            break;
        case deleteDLL0:
            drawDeleteIndicator(window);
            break;
        case deleteDLL1:
            drawDeleteNode(window);
            break;
        case deleteDLL2:
            drawDeleteNodeMove(window);
            break;
        case searchDLL0:
            drawSearchIndicator(window);
            break;
        case searchDLL1:
            drawSearchHighlight(window);
            break;
        case searchDLL2:
            drawSearchRevert(window);
            break;
        case updateDLL0:
            drawUpdateIndicator(window);
            break;
        case updateDLL1:
            drawUpdateChangeNum(window);
            break;
        case updateDLL2:
            drawUpdateRevert(window);
            break;
    }
}


void DLLObject::processMouseEvent(sf::RenderWindow &window) {
    // std::cerr << "event\n";
    if (drawType == showcaseDLL) {
        if (theDLLscreen.theGeneralScreen.createButtonIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAllButton();
            drawType = chooseMakeDLL;
        }
        else if (theDLLscreen.theGeneralScreen.addButtonIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAllButton();
            theDLLscreen.theGeneralScreen.addButton.flipButtonState();
            // theDLLscreen.theGeneralScreen.addBeginning.flipButtonState();
            // theDLLscreen.theGeneralScreen.addEnding.flipButtonState();
        }
        else if (theDLLscreen.theGeneralScreen.deleteButtonIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAllButton();
            theDLLscreen.theGeneralScreen.deleteButton.flipButtonState();
        }
        else if (theDLLscreen.theGeneralScreen.searchButtonIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAllButton();
            theDLLscreen.theGeneralScreen.searchButton.flipButtonState();
        }
        else if (theDLLscreen.theGeneralScreen.updateButtonIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAllButton();
            theDLLscreen.theGeneralScreen.updateButton.flipButtonState();
        }
        else if (theDLLscreen.theGeneralScreen.backToMenuIsClick(window)) {
            this->backToMenu = true;
            theDLLscreen.theGeneralScreen.turnOffAllButton();
        }
        else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.addButton.textBoxIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAddTextBox();
            theDLLscreen.theGeneralScreen.addButton.onInputBoxState();
        }
        else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.addBeginningText.textBoxButtonIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAddTextBox();
            theDLLscreen.theGeneralScreen.addBeginningText.onTextBoxState();
        }
        else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.addEndingText.textBoxButtonIsClick(window)) {
            theDLLscreen.theGeneralScreen.turnOffAddTextBox();
            theDLLscreen.theGeneralScreen.addEndingText.onTextBoxState();
        }
        else if (theDLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.deleteButton.textBoxIsClick(window)) {
            theDLLscreen.theGeneralScreen.deleteButton.onInputBoxState();
        }
        else if (theDLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.searchButton.textBoxIsClick(window)) {
            theDLLscreen.theGeneralScreen.searchButton.onInputBoxState();
        }
        else if (theDLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.updateButton.textBoxIsClick(window)) {
            theDLLscreen.theGeneralScreen.updateButton.onInputBoxState();
        }
        else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.addButton.confirmButtonIsClick(window)) {
            if (!theDLLscreen.theGeneralScreen.addButton.inputIsEmpty()) {
                drawType = prevType = insertDLL0;
                std::pair <int, int> userInput = theDLLscreen.theGeneralScreen.addButton.getInputDataPair();
                int inputIndex = userInput.first, inputElement = userInput.second;
                insertNodeProcess(inputIndex, inputElement);
                DLLCodeBlock.drawInsertCodeBlock(window);
                DLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.addBeginning.buttonIsClick(window)) {
            if (!theDLLscreen.theGeneralScreen.addBeginningText.inputIsEmpty()) {
                drawType = prevType = insertDLL0;
                int userInput = theDLLscreen.theGeneralScreen.addBeginningText.getInputDataInt();
                int inputIndex = 0, inputElement = userInput;
                insertNodeProcess(inputIndex, inputElement);
                DLLCodeBlock.drawInsertCodeBlock(window);
                DLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.addEnding.buttonIsClick(window)) {
            if (!theDLLscreen.theGeneralScreen.addEndingText.inputIsEmpty()) {
                drawType = prevType = insertDLL0;
                int userInput = theDLLscreen.theGeneralScreen.addEndingText.getInputDataInt();
                int inputIndex = myDLL.getNumberOfNode(), inputElement = userInput;
                insertNodeProcess(inputIndex, inputElement);
                DLLCodeBlock.drawInsertCodeBlock(window);
                DLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theDLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.deleteButton.confirmButtonIsClick(window)) {
            if (!theDLLscreen.theGeneralScreen.deleteButton.inputIsEmpty()) {
                drawType = prevType = deleteDLL0;
                int userInput = theDLLscreen.theGeneralScreen.deleteButton.getInputDataInt();
                deleteIndex = userInput + 1;
                deleteNodeProcess(deleteIndex);
                DLLCodeBlock.drawDeleteCodeBlock(window);
                DLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
            }
        }
        else if (theDLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.delBeginning.buttonIsClick(window)) {
            drawType = prevType = deleteDLL0;
            deleteIndex = 1;
            deleteNodeProcess(deleteIndex);
            DLLCodeBlock.drawDeleteCodeBlock(window);
            DLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
        }
        else if (theDLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.delEnding.buttonIsClick(window)) {
            drawType = prevType = deleteDLL0;
            deleteIndex = myDLL.getNumberOfNode();
            deleteNodeProcess(deleteIndex);
            DLLCodeBlock.drawDeleteCodeBlock(window);
            DLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
        }
        else if (theDLLscreen.theGeneralScreen.searchButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.searchButton.confirmButtonIsClick(window)) {
            if (!theDLLscreen.theGeneralScreen.searchButton.inputIsEmpty()) {
                drawType = prevType = searchDLL0;
                int userInput = theDLLscreen.theGeneralScreen.searchButton.getInputDataInt();
                searchData = userInput;
                searchNodeProcess(searchData);
                DLLCodeBlock.drawSearchCodeBlock(window);
                DLLCodeBlock.drawSearchCodeBlockSingleLine(window, 0);
            }
        }
        else if (theDLLscreen.theGeneralScreen.updateButton.buttonIsChoose() 
              && theDLLscreen.theGeneralScreen.updateButton.confirmButtonIsClick(window)) {
            if (!theDLLscreen.theGeneralScreen.updateButton.inputIsEmpty()) {
                drawType = prevType = updateDLL0;
                std::pair <int, int> userInput = theDLLscreen.theGeneralScreen.updateButton.getInputDataPair();
                updateIndex = userInput.first, updateData = userInput.second;
                updateNodeProcess(updateIndex, updateData);
                DLLCodeBlock.drawUpdateCodeBlock(window);
                DLLCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
            }
        }
    }
    else if (drawType == chooseMakeDLL) {
        if (theDLLscreen.theCreateScreen.userInputButtonIsClick(window)) {
            theDLLscreen.theCreateScreen.flipInputButtonState();
        }
        else if (theDLLscreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = prevType = showcaseDLL;
            createRandomList();
        }
        else if (theDLLscreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = prevType = showcaseDLL;
        }
        else if (theDLLscreen.theCreateScreen.userInputButtonGetState()) {
            if (theDLLscreen.theCreateScreen.textBoxIsClick(window)) {
                theDLLscreen.theCreateScreen.onInputBoxState();
            }
            else if (theDLLscreen.theCreateScreen.confirmButtonIsClick(window)) {
                if (!theDLLscreen.theCreateScreen.inputIsEmpty()) {
                    drawType = makeDLL;
                    std::vector <int> userInput = theDLLscreen.theCreateScreen.getInputData();
                    createDefinedList(userInput);
                }
            }
            else if (theDLLscreen.theCreateScreen.browseButtonIsClick(window)) {
                std::string fileRead;
                if (browseForFile(fileRead)) {
                    std::vector <int> userInput = getInputData(fileRead);
                    if ((int) userInput.size() > 0) {
                        drawType = makeDLL;
                        createDefinedList(userInput);
                    }
                }
            }
            else {
                theDLLscreen.theCreateScreen.offInputBoxState();
            }
        }
    }
}
void DLLObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeDLL) {
        if (theDLLscreen.theCreateScreen.userInputButtonGetState() && theDLLscreen.theCreateScreen.textBoxGetState()) {
            if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                char inputCharacter = (char) event.text.unicode;
                theDLLscreen.theCreateScreen.userInputCharacter(inputCharacter);
            }
        }
    }
    else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.addBeginningText.textBoxIsClick()) {
        theDLLscreen.theGeneralScreen.addBeginningText.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.addEndingText.textBoxIsClick()) {
        theDLLscreen.theGeneralScreen.addEndingText.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void DLLObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeDLL) {
        if (theDLLscreen.theCreateScreen.userInputButtonGetState() && theDLLscreen.theCreateScreen.textBoxGetState()) {
            if (event.key.code == sf::Keyboard::Backspace) {
                theDLLscreen.theCreateScreen.userBackspaceCharacter();
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                theDLLscreen.theCreateScreen.userMoveCursor(event.key.code);
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                theDLLscreen.theCreateScreen.userDeleteCharacter();
            }
        }
    }
    else if (theDLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theDLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theDLLscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theDLLscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void DLLObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (drawType == showcaseDLL) {
        theDLLscreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else if (drawType == chooseMakeDLL) {
        theDLLscreen.theCreateScreen.moveButtonWhenHover(window);
    }
}


void DLLObject::insertNodeProcess(int insertIndex, int insertData) {
    this->insertIndex = insertIndex;
    this->insertData = insertData;
    this->insertNodePosition.x = nodeConstants::firstNodePositionX * (insertIndex + 1);
    this->insertNodePosition.y = nodeConstants::firstNodePositionY + nodeConstants::initialInsertNodeY;
    this->gotoIndex = 1;
    this->nodePositionXAfterInsert = 0;
    this->insertNodeOpacity = 0;
    this->insertNodeColor = rand() % 4;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void DLLObject::deleteNodeProcess(int deleteIndex) {
    this->nodeOpacity = this->deleteNodeOpacity = 255;
    this->nodePositionDiffX = nodeConstants::nodeDistance;
    this->newArrowOpacity = 0;
    this->gotoIndex = 1;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void DLLObject::searchNodeProcess(int searchData) {
    this->searchIndex = myDLL.searchElement(searchData);
    this->gotoIndex = 1;
    this->infoTextOpacity = 0;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void DLLObject::updateNodeProcess(int updateIndex, int updateData) {
    this->gotoIndex = 1;
    this->numberOpacity = 255;
    this->opacityMultiplier = -1;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}

void DLLObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}
bool DLLObject::exitDLLScreen() {
    return this->backToMenu;
}
void DLLObject::setExitToFalse() {
    this->backToMenu = false;
}

void DLLObject::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
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
void DLLObject::drawLLScreen(sf::RenderWindow &window) {
    drawBackground(window);
    processMouseHoverEvent(window);
    processType(window);
}

