#include "CLLscreenEvent.h"

CLLObject::CLLObject() {
    drawType = showcaseCLL;
    backToMenu = 0;
    createRandomList();
}

void CLLObject::createList(int numberOfNode, std::vector <int> &a) {
    myCLL.deleteList();
    myCLL.build(a);
    theCLLscreen.theGeneralScreen.initData(numberOfNode);
}
void CLLObject::createRandomList() {
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
    theCLLscreen.theCreateScreen.setInputBoxString(sampleInput);
    createList(numberOfNode, a);
}
void CLLObject::createDefinedList(std::vector <int> &userInput) {
    int numberOfNode = (int) userInput.size();
    createList(numberOfNode, userInput);
}
void CLLObject::drawList(sf::RenderWindow &window) {
    opacity = std::min(nodeConstants::fadeSpeed + opacity, 255);
    myCLL.drawList(window, opacity);
}
void CLLObject::processDrawList() {
    opacity = 0;
    drawType = showcaseCLL;
}

void CLLObject::drawInsertIndicator(sf::RenderWindow &window) {
    if (insertIndex == myCLL.getNumberOfNode()) {
        myCLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, 
                                      nodeConstants::baseColor);
        drawType = insertCLL2;
        myCLL.insertAtMiddle(insertData, insertIndex);
        insertIndex++;
        return;
    }
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds())
        sf::sleep(sf::milliseconds(500));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds());
    myCLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
    // CLLCodeBlock.drawInsertCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 2);
        }
        else {
            // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > insertIndex) {
        drawType = insertCLL1;
        myCLL.insertAtMiddle(insertIndex, insertData);
        insertIndex++;
        markFirst = 1;
    }
}
void CLLObject::drawListWhenInsert(sf::RenderWindow &window) {
    if (markFirst) {
        markFirst = 0;
        sf::sleep(sf::milliseconds(500));
    }
    myCLL.drawListWhenInsert(window, insertIndex, 
                             opacity, nodePositionXAfterInsert);
    // CLLCodeBlock.drawInsertCodeBlock(window);
    // CLLCodeBlock.drawInsertCodeBlockMultiLine(window, 3, 4);
    if (nodePositionXAfterInsert >= nodeConstants::nodeDistance) {
        drawType = insertCLL2;
        flashTimer.restart();
    }
    else {
        setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 1);
    }
}
void CLLObject::drawInsertNode(sf::RenderWindow &window) {
    // CLLCodeBlock.drawInsertCodeBlock(window);
    // CLLCodeBlock.drawInsertCodeBlockMultiLine(window, 5, 6);
    if (insertIndex == myCLL.getNumberOfNode())
        myCLL.drawInsertNode(window, insertIndex, opacity,
                            nodeConstants::baseColor,
                            insertNodePosition, insertNodeOpacity);
    else
        myCLL.drawInsertNode(window, insertIndex, opacity,
                            getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
                            insertNodePosition, insertNodeOpacity);
    if (insertNodePosition.y == nodeConstants::firstNodePositionY)
        drawType = showcaseCLL;
    else {
        setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 2);
    }
}


void CLLObject::drawDeleteIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds())
        sf::sleep(sf::milliseconds(500));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds());
    myCLL.drawDeleteNodeIndicator(window, deleteIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
    // CLLCodeBlock.drawDeleteCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            // CLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 2);
        }
        else {
            // CLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        // CLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > deleteIndex) {
        drawType = deleteCLL1;
        markFirst = 1;
    }
}
void CLLObject::drawDeleteNode(sf::RenderWindow &window) {
    if (markFirst) {
        markFirst = 0;
        sf::sleep(sf::milliseconds(500));
    }
    myCLL.drawDeleteNode(window, deleteIndex, nodeOpacity, deleteNodeOpacity);
    // CLLCodeBlock.drawDeleteCodeBlock(window);
    // CLLCodeBlock.drawDeleteCodeBlockMultiLine(window, 3, 4);
    if (deleteNodeOpacity - nodeConstants::fadeSpeed > 0) {
        deleteNodeOpacity = std::max(deleteNodeOpacity - nodeConstants::fadeSpeed, 0);
    }
    else {
        myCLL.deleteAtMiddle(deleteIndex);
        nodeOpacity = 255;
        drawType = deleteCLL2;
        flashTimer.restart();
    }
}
void CLLObject::drawDeleteNodeMove(sf::RenderWindow &window) {
    myCLL.drawDeleteNodeMove(window, deleteIndex, nodeOpacity, 
                             nodePositionDiffX, newArrowOpacity,
                             getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer));
    // CLLCodeBlock.drawDeleteCodeBlock(window);
    // CLLCodeBlock.drawDeleteCodeBlockSingleLine(window, 5);
    if (nodePositionDiffX > 0 || newArrowOpacity < 255) {
        newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
        if (newArrowOpacity == 255)
            nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
    }
    else 
        drawType = showcaseCLL;
}

void CLLObject::drawSearchIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
        sf::sleep(sf::milliseconds(500));
    }
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = myCLL.getNumberOfNode();
    myCLL.drawSearchIndicator(window, searchIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));   
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
    // CLLCodeBlock.drawSearchCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            // if (gotoIndex <= tempSearchIndex)
                // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 4);
        }
        else {
            // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > tempSearchIndex) {
        drawType = searchCLL1;
        flashTimer.restart();
        markFirst = 1;
    }
}
void CLLObject::drawSearchHighlight(sf::RenderWindow &window) {
    myCLL.drawSearchHighlight(window, searchIndex, 
                              getFadeColor(nodeConstants::flashColor, nodeConstants::searchFoundColor, flashTimer), 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::searchFoundColor, flashTimer),
                              infoTextOpacity);
    infoTextOpacity = std::min(255, infoTextOpacity + nodeConstants::fadeSpeed);
    // CLLCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        // CLLCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
    }
    else {
        // CLLCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
    }
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = searchCLL2;
        sf::sleep(sf::seconds(3.0f));
        flashTimer.restart();
    }
}
void CLLObject::drawSearchRevert(sf::RenderWindow &window) {
    myCLL.drawSearchRevert(window, searchIndex, 
                           getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
                           getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer),
                           infoTextOpacity);
    // CLLCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        // CLLCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
    }
    else {
        // CLLCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
    }
    infoTextOpacity = std::max(0, infoTextOpacity - nodeConstants::fadeSpeed);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseCLL;
        flashTimer.restart();
    }
}
void CLLObject::drawUpdateIndicator(sf::RenderWindow &window) {
    // std::cerr << "update index, data: " << updateIndex << " " << updateData << '\n';
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
        sf::sleep(sf::milliseconds(500));
    }
    myCLL.drawUpdateIndicator(window, updateIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
    // CLLCodeBlock.drawUpdateCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            // if (gotoIndex <= updateIndex)
                // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 5);
        }
        else {
            // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        // CLLCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > updateIndex) {
        drawType = updateCLL1;
        flashTimer.restart();
    }
}
void CLLObject::drawUpdateChangeNum(sf::RenderWindow &window) {
    sf::Color fadeColor;
    if (opacityMultiplier == -1)
        fadeColor = nodeConstants::baseColor;
    else 
        fadeColor = nodeConstants::searchFoundColor;
    myCLL.drawUpdateChangeNum(window, updateIndex, updateData, numberOpacity, fadeColor);
    // CLLCodeBlock.drawUpdateCodeBlock(window);
    // CLLCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
    if (opacityMultiplier == -1) {
        numberOpacity = std::max(0, numberOpacity - nodeConstants::fadeSpeed);
        if (numberOpacity == 0) {
            opacityMultiplier = 1;
            myCLL.updateIndex(updateIndex, updateData);
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
        drawType = updateCLL2;
    }
}
void CLLObject::drawUpdateRevert(sf::RenderWindow &window) {
    sf::Color fadeOutlineColor, fadeNumberColor;
    fadeOutlineColor = getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer);
    fadeNumberColor = getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer);
    myCLL.drawUpdateRevert(window, updateIndex, fadeOutlineColor, fadeNumberColor);
    // CLLCodeBlock.drawUpdateCodeBlock(window);
    // CLLCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseCLL;
        flashTimer.restart();
    }
}

void CLLObject::processType(sf::RenderWindow &window) {
    if (drawType != chooseMakeCLL) {
        theCLLscreen.drawGeneralScreen(window);
    }
    else {
        theCLLscreen.drawCreateScreen(window);
    }
    switch (drawType) {
        case makeCLL:
            processDrawList();
            break;
        case showcaseCLL:
            std::cerr << "draw list\n";
            drawList(window);
            break;
        case chooseMakeCLL:
            drawList(window);
            break;
        case insertCLL0:
            drawInsertIndicator(window);
            break;
        case insertCLL1:
            drawListWhenInsert(window);
            break;
        case insertCLL2:
            drawInsertNode(window);
            break;
        case deleteCLL0:
            drawDeleteIndicator(window);
            break;
        case deleteCLL1:
            drawDeleteNode(window);
            break;
        case deleteCLL2:
            drawDeleteNodeMove(window);
            break;
        case searchCLL0:
            drawSearchIndicator(window);
            break;
        case searchCLL1:
            drawSearchHighlight(window);
            break;
        case searchCLL2:
            drawSearchRevert(window);
            break;
        case updateCLL0:
            drawUpdateIndicator(window);
            break;
        case updateCLL1:
            drawUpdateChangeNum(window);
            break;
        case updateCLL2:
            drawUpdateRevert(window);
            break;
    }
}


void CLLObject::processMouseEvent(sf::RenderWindow &window) {
    // std::cerr << "event\n";
    if (drawType == showcaseCLL) {
        if (theCLLscreen.theGeneralScreen.createButtonIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAllButton();
            drawType = chooseMakeCLL;
        }
        else if (theCLLscreen.theGeneralScreen.addButtonIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAllButton();
            theCLLscreen.theGeneralScreen.addButton.flipButtonState();
            // theCLLscreen.theGeneralScreen.addBeginning.flipButtonState();
            // theCLLscreen.theGeneralScreen.addEnding.flipButtonState();
        }
        else if (theCLLscreen.theGeneralScreen.deleteButtonIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAllButton();
            theCLLscreen.theGeneralScreen.deleteButton.flipButtonState();
        }
        else if (theCLLscreen.theGeneralScreen.searchButtonIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAllButton();
            theCLLscreen.theGeneralScreen.searchButton.flipButtonState();
        }
        else if (theCLLscreen.theGeneralScreen.updateButtonIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAllButton();
            theCLLscreen.theGeneralScreen.updateButton.flipButtonState();
        }
        else if (theCLLscreen.theGeneralScreen.backToMenuIsClick(window)) {
            this->backToMenu = true;
            theCLLscreen.theGeneralScreen.turnOffAllButton();
        }
        else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.addButton.textBoxIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAddTextBox();
            theCLLscreen.theGeneralScreen.addButton.onInputBoxState();
        }
        else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.addBeginningText.textBoxButtonIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAddTextBox();
            theCLLscreen.theGeneralScreen.addBeginningText.onTextBoxState();
        }
        else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.addEndingText.textBoxButtonIsClick(window)) {
            theCLLscreen.theGeneralScreen.turnOffAddTextBox();
            theCLLscreen.theGeneralScreen.addEndingText.onTextBoxState();
        }
        else if (theCLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.deleteButton.textBoxIsClick(window)) {
            theCLLscreen.theGeneralScreen.deleteButton.onInputBoxState();
        }
        else if (theCLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.searchButton.textBoxIsClick(window)) {
            theCLLscreen.theGeneralScreen.searchButton.onInputBoxState();
        }
        else if (theCLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.updateButton.textBoxIsClick(window)) {
            theCLLscreen.theGeneralScreen.updateButton.onInputBoxState();
        }
        else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.addButton.confirmButtonIsClick(window)) {
            if (!theCLLscreen.theGeneralScreen.addButton.inputIsEmpty()) {
                drawType = insertCLL0;
                std::pair <int, int> userInput = theCLLscreen.theGeneralScreen.addButton.getInputDataPair();
                int inputIndex = userInput.first, inputElement = userInput.second;
                insertNodeProcess(inputIndex, inputElement);
                if (!inputIndex == myCLL.getNumberOfNode()) {
                    // CLLCodeBlock.drawInsertCodeBlock(window);
                    // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
                }
            }
        }
        else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.addBeginning.buttonIsClick(window)) {
            if (!theCLLscreen.theGeneralScreen.addBeginningText.inputIsEmpty()) {
                drawType = insertCLL0;
                int userInput = theCLLscreen.theGeneralScreen.addBeginningText.getInputDataInt();
                int inputIndex = 0, inputElement = userInput;
                insertNodeProcess(inputIndex, inputElement);
                // CLLCodeBlock.drawInsertCodeBlock(window);
                // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.addEnding.buttonIsClick(window)) {
            if (!theCLLscreen.theGeneralScreen.addEndingText.inputIsEmpty()) {
                drawType = insertCLL0;
                int userInput = theCLLscreen.theGeneralScreen.addBeginningText.getInputDataInt();
                int inputIndex = myCLL.getNumberOfNode(), inputElement = userInput;
                insertNodeProcess(inputIndex, inputElement);
                // CLLCodeBlock.drawInsertCodeBlock(window);
                // CLLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theCLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.deleteButton.confirmButtonIsClick(window)) {
            if (!theCLLscreen.theGeneralScreen.deleteButton.inputIsEmpty()) {
                drawType = deleteCLL0;
                int userInput = theCLLscreen.theGeneralScreen.deleteButton.getInputDataInt();
                deleteIndex = userInput + 1;
                deleteNodeProcess(deleteIndex);
            }
        }
        else if (theCLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.delBeginning.buttonIsClick(window)) {
            drawType = deleteCLL0;
            deleteIndex = 1;
            deleteNodeProcess(deleteIndex);
        }
        else if (theCLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.delEnding.buttonIsClick(window)) {
            drawType = deleteCLL0;
            deleteIndex = myCLL.getNumberOfNode();
            deleteNodeProcess(deleteIndex);
        }
        else if (theCLLscreen.theGeneralScreen.searchButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.searchButton.confirmButtonIsClick(window)) {
            if (!theCLLscreen.theGeneralScreen.searchButton.inputIsEmpty()) {
                drawType = searchCLL0;
                int userInput = theCLLscreen.theGeneralScreen.searchButton.getInputDataInt();
                searchData = userInput;
                searchNodeProcess(searchData);
            }
        }
        else if (theCLLscreen.theGeneralScreen.updateButton.buttonIsChoose() 
              && theCLLscreen.theGeneralScreen.updateButton.confirmButtonIsClick(window)) {
            if (!theCLLscreen.theGeneralScreen.updateButton.inputIsEmpty()) {
                drawType = updateCLL0;
                std::pair <int, int> userInput = theCLLscreen.theGeneralScreen.updateButton.getInputDataPair();
                updateIndex = userInput.first, updateData = userInput.second;
                updateIndex++;
                updateNodeProcess(updateIndex, updateData);
            }
        }
    }
    else if (drawType == chooseMakeCLL) {
        if (theCLLscreen.theCreateScreen.userInputButtonIsClick(window)) {
            theCLLscreen.theCreateScreen.flipInputButtonState();
        }
        else if (theCLLscreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = showcaseCLL;
            createRandomList();
        }
        else if (theCLLscreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = showcaseCLL;
        }
        else if (theCLLscreen.theCreateScreen.userInputButtonGetState()) {
            if (theCLLscreen.theCreateScreen.textBoxIsClick(window)) {
                theCLLscreen.theCreateScreen.onInputBoxState();
            }
            else if (theCLLscreen.theCreateScreen.confirmButtonIsClick(window)) {
                if (!theCLLscreen.theCreateScreen.inputIsEmpty()) {
                    drawType = makeCLL;
                    std::vector <int> userInput = theCLLscreen.theCreateScreen.getInputData();
                    createDefinedList(userInput);
                }
            }
            else if (theCLLscreen.theCreateScreen.browseButtonIsClick(window)) {
                std::string fileRead;
                if (browseForFile(fileRead)) {
                    std::vector <int> userInput = getInputData(fileRead);
                    if ((int) userInput.size() > 0) {
                        drawType = makeCLL;
                        createDefinedList(userInput);
                    }
                }
            }
            else {
                theCLLscreen.theCreateScreen.offInputBoxState();
            }
        }
    }
}
void CLLObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeCLL) {
        if (theCLLscreen.theCreateScreen.userInputButtonGetState() && theCLLscreen.theCreateScreen.textBoxGetState()) {
            if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                char inputCharacter = (char) event.text.unicode;
                theCLLscreen.theCreateScreen.userInputCharacter(inputCharacter);
            }
        }
    }
    else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.addBeginningText.textBoxIsClick()) {
        theCLLscreen.theGeneralScreen.addBeginningText.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.addEndingText.textBoxIsClick()) {
        theCLLscreen.theGeneralScreen.addEndingText.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void CLLObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeCLL) {
        if (theCLLscreen.theCreateScreen.userInputButtonGetState() && theCLLscreen.theCreateScreen.textBoxGetState()) {
            if (event.key.code == sf::Keyboard::Backspace) {
                theCLLscreen.theCreateScreen.userBackspaceCharacter();
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                theCLLscreen.theCreateScreen.userMoveCursor(event.key.code);
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                theCLLscreen.theCreateScreen.userDeleteCharacter();
            }
        }
    }
    else if (theCLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theCLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theCLLscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theCLLscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void CLLObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (drawType == showcaseCLL) {
        theCLLscreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else if (drawType == chooseMakeCLL) {
        theCLLscreen.theCreateScreen.moveButtonWhenHover(window);
    }
}


void CLLObject::insertNodeProcess(int insertIndex, int insertData) {
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
void CLLObject::deleteNodeProcess(int deleteIndex) {
    this->nodeOpacity = this->deleteNodeOpacity = 255;
    this->nodePositionDiffX = nodeConstants::nodeDistance;
    this->newArrowOpacity = 0;
    this->gotoIndex = 1;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void CLLObject::searchNodeProcess(int searchData) {
    this->searchIndex = myCLL.searchValue(searchData);
    this->gotoIndex = 1;
    this->infoTextOpacity = 0;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void CLLObject::updateNodeProcess(int updateIndex, int updateData) {
    this->gotoIndex = 1;
    this->numberOpacity = 255;
    this->opacityMultiplier = -1;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}


void CLLObject::deleteCLL() {
    myCLL.deleteList();
    return;
}

void CLLObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}


bool CLLObject::exitCLLScreen() {
    return this->backToMenu;
}
void CLLObject::setExitToFalse() {
    this->backToMenu = 0;
}
void CLLObject::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
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
void CLLObject::drawCLLScreen(sf::RenderWindow &window) {
    drawBackground(window);
    processMouseHoverEvent(window);
    processType(window);
    std::cerr << "done\n";
}

void CLLObject::inputValue(int &value) {
    std::cin >> value;
}

void CLLObject::setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase) {
    if (nodePositionXAfterInsert < nodeConstants::nodeDistance)
        nodePositionXAfterInsert = std::min(nodeConstants::nodeDistance, nodePositionXAfterInsert + nodeConstants::insertMoveSpeed);
    if (insertPhase == 2)
        insertNodeOpacity = std::min(insertNodeOpacity + nodeConstants::fadeSpeed, 255);
    if (insertPhase == 2 && insertNodePosition.y > nodeConstants::firstNodePositionY && insertNodeOpacity == 255)
        insertNodePosition.y = std::max((float) insertNodePosition.y - nodeConstants::insertMoveSpeed, (float) nodeConstants::firstNodePositionY);
}

std::vector<int> CLLObject::getInputData(std::string &inputString) {
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