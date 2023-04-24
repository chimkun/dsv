#include "LLscreenEvent.h"

SLLObject::SLLObject() {
    drawType = showcaseLL;
}

void SLLObject::createList(int numberOfNode, int *&a) {
    mySLL.deleteList();
    mySLL.build(numberOfNode, a);
}
void SLLObject::craeteRandomList() {
    int numberOfNode = rand() % 10 + 1;
    int *a = new int(numberOfNode);
    for (int i = 0; i < numberOfNode; i++) {
        a[i] = rand() % 99 + 1;
    }
    createList(numberOfNode, a);
    delete[] a;
}
void SLLObject::createDefinedList(std::vector <int> &userInput) {
    int numberOfNode = (int) userInput.size();
    int *a = new int(numberOfNode);
    for (int i = 0; i < numberOfNode; i++) {
        a[i] = userInput[i];
    }
    createList(numberOfNode, a);
    delete[] a;
}
void SLLObject::drawList(sf::RenderWindow &window) {
    opacity = std::min(nodeConstants::fadeSpeed + opacity, 255);
    mySLL.drawList(window, opacity, nodeText);
}
void SLLObject::processDrawList() {
    opacity = 0;
    drawType = showcaseLL;
}

void SLLObject::drawInsertIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds())
        sf::sleep(sf::milliseconds(500));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds());
    mySLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);
    LLCodeBlock.drawInsertCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            LLCodeBlock.drawInsertCodeBlockSingleLine(window, 2);
        }
        else {
            LLCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        LLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > insertIndex) {
        drawType = insertLL1;
        mySLL.insertAfterIndex(insertData, insertIndex);
        insertIndex++;
        markFirst = 1;
    }
}
void SLLObject::drawListWhenInsert(sf::RenderWindow &window) {
    if (markFirst) {
        markFirst = 0;
        sf::sleep(sf::milliseconds(500));
    }
    mySLL.drawListWhenInsert(window, insertIndex, 
                             opacity, nodePositionXAfterInsert, nodeText);
    LLCodeBlock.drawInsertCodeBlock(window);
    LLCodeBlock.drawInsertCodeBlockMultiLine(window, 3, 4);
    if (nodePositionXAfterInsert >= nodeConstants::nodeDistance) {
        drawType = insertLL2;
        flashTimer.restart();
    }
    else {
        setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 1);
    }
}
void SLLObject::drawInsertNode(sf::RenderWindow &window) {
    LLCodeBlock.drawInsertCodeBlock(window);
    LLCodeBlock.drawInsertCodeBlockMultiLine(window, 5, 6);
    mySLL.drawInsertNode(window, insertIndex, opacity,
                         getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
                         insertNodePosition, insertNodeOpacity, nodeText);
    if (insertNodePosition.y == nodeConstants::firstNodePositionY)
        drawType = showcaseLL;
    else {
        setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 2);
    }
}


void SLLObject::drawDeleteIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds())
        sf::sleep(sf::milliseconds(500));
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds());
    mySLL.drawDeleteNodeIndicator(window, deleteIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);
    LLCodeBlock.drawDeleteCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            LLCodeBlock.drawDeleteCodeBlockSingleLine(window, 2);
        }
        else {
            LLCodeBlock.drawDeleteCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        LLCodeBlock.drawDeleteCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > deleteIndex) {
        drawType = deleteLL1;
        markFirst = 1;
    }
}
void SLLObject::drawDeleteNode(sf::RenderWindow &window) {
    if (markFirst) {
        markFirst = 0;
        sf::sleep(sf::milliseconds(500));
    }
    mySLL.drawDeleteNode(window, deleteIndex, nodeOpacity, deleteNodeOpacity, nodeText);
    LLCodeBlock.drawDeleteCodeBlock(window);
    LLCodeBlock.drawDeleteCodeBlockMultiLine(window, 3, 4);
    if (deleteNodeOpacity - nodeConstants::fadeSpeed > 0) {
        deleteNodeOpacity = std::max(deleteNodeOpacity - nodeConstants::fadeSpeed, 0);
    }
    else {
        mySLL.deleteAtIndex(deleteIndex);
        nodeOpacity = 255;
        drawType = deleteLL2;
        flashTimer.restart();
    }
}
void SLLObject::drawDeleteNodeMove(sf::RenderWindow &window) {
    mySLL.drawDeleteNodeMove(window, deleteIndex, nodeOpacity, 
                             nodePositionDiffX, newArrowOpacity,
                             getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer), nodeText);
    LLCodeBlock.drawDeleteCodeBlock(window);
    LLCodeBlock.drawDeleteCodeBlockSingleLine(window, 5);
    if (nodePositionDiffX > 0 || newArrowOpacity < 255) {
        newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
        if (newArrowOpacity == 255)
            nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
    }
    else 
        drawType = showcaseLL;
}

void SLLObject::drawSearchIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
        sf::sleep(sf::milliseconds(500));
    }
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = mySLL.getNumberOfNode();
    mySLL.drawSearchIndicator(window, searchIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);   
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
    LLCodeBlock.drawSearchCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            if (gotoIndex <= tempSearchIndex)
                LLCodeBlock.drawInsertCodeBlockSingleLine(window, 4);
        }
        else {
            LLCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        LLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > tempSearchIndex) {
        drawType = searchLL1;
        flashTimer.restart();
        markFirst = 1;
    }
}
void SLLObject::drawSearchHighlight(sf::RenderWindow &window) {
    mySLL.drawSearchHighlight(window, searchIndex, 
                              getFadeColor(nodeConstants::flashColor, nodeConstants::searchFoundColor, flashTimer), 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::searchFoundColor, flashTimer),
                              infoTextOpacity, nodeText);
    infoTextOpacity = std::min(255, infoTextOpacity + nodeConstants::fadeSpeed);
    LLCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        LLCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
    }
    else {
        LLCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
    }
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = searchLL2;
        sf::sleep(sf::seconds(3.0f));
        flashTimer.restart();
    }
}
void SLLObject::drawSearchRevert(sf::RenderWindow &window) {
    mySLL.drawSearchRevert(window, searchIndex, 
                           getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
                           getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer),
                           infoTextOpacity, nodeText);
    LLCodeBlock.drawSearchCodeBlock(window);
    if (searchIndex == -1) {
        LLCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
    }
    else {
        LLCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
    }
    infoTextOpacity = std::max(0, infoTextOpacity - nodeConstants::fadeSpeed);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseLL;
        flashTimer.restart();
    }
}
void SLLObject::drawUpdateIndicator(sf::RenderWindow &window) {
    if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
        sf::sleep(sf::milliseconds(500));
    }
    mySLL.drawUpdateIndicator(window, updateIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);
    remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
    LLCodeBlock.drawUpdateCodeBlock(window);
    if (!markFirst) {
        if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
            gotoIndex++;
            flashTimer.restart();
            if (gotoIndex <= updateIndex)
                LLCodeBlock.drawInsertCodeBlockSingleLine(window, 5);
        }
        else {
            LLCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
        }
    }
    else {
        markFirst = 0;
        flashTimer.restart();
        LLCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
    }
    if (gotoIndex > updateIndex) {
        drawType = updateLL1;
        flashTimer.restart();
    }
}
void SLLObject::drawUpdateChangeNum(sf::RenderWindow &window) {
    sf::Color fadeColor;
    if (opacityMultiplier == -1)
        fadeColor = nodeConstants::baseColor;
    else 
        fadeColor = nodeConstants::searchFoundColor;
    mySLL.drawUpdateChangeNum(window, updateIndex, updateData, numberOpacity, fadeColor, nodeText);
    LLCodeBlock.drawUpdateCodeBlock(window);
    LLCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
    if (opacityMultiplier == -1) {
        numberOpacity = std::max(0, numberOpacity - nodeConstants::fadeSpeed);
        if (numberOpacity == 0) {
            opacityMultiplier = 1;
            mySLL.deleteAtIndex(updateIndex);
            mySLL.insertAfterIndex(updateData, updateIndex - 1);
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
        drawType = updateLL2;
    }
}
void SLLObject::drawUpdateRevert(sf::RenderWindow &window) {
    sf::Color fadeOutlineColor, fadeNumberColor;
    fadeOutlineColor = getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer);
    fadeNumberColor = getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer);
    mySLL.drawUpdateRevert(window, updateIndex, fadeOutlineColor, fadeNumberColor, nodeText);
    LLCodeBlock.drawUpdateCodeBlock(window);
    LLCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseLL;
        flashTimer.restart();
    }
}

void SLLObject::processType(sf::RenderWindow &window) {
    if (drawType != chooseMakeLL)
        theLLscreen.drawGeneralScreen(window);
    else {
        theLLscreen.drawCreateScreen(window);
    }
    switch (drawType) {
        case makeLL:
            processDrawList();
            break;
        case showcaseLL:
            drawList(window);
            break;
        case chooseMakeLL:
            drawList(window);
            break;
        case insertLL0:
            drawInsertIndicator(window);
            break;
        case insertLL1:
            drawListWhenInsert(window);
            break;
        case insertLL2:
            drawInsertNode(window);
            break;
        case deleteLL0:
            drawDeleteIndicator(window);
            break;
        case deleteLL1:
            drawDeleteNode(window);
            break;
        case deleteLL2:
            drawDeleteNodeMove(window);
            break;
        case searchLL0:
            drawSearchIndicator(window);
            break;
        case searchLL1:
            drawSearchHighlight(window);
            break;
        case searchLL2:
            drawSearchRevert(window);
            break;
        case updateLL0:
            drawUpdateIndicator(window);
            break;
        case updateLL1:
            drawUpdateChangeNum(window);
            break;
        case updateLL2:
            drawUpdateRevert(window);
            break;
    }
}

void SLLObject::processMouseEvent(sf::RenderWindow &window) {
    if (drawType == showcaseLL) {
        if (theLLscreen.theGeneralScreen.createButtonIsClick(window)) {
            drawType = chooseMakeLL;
        }
        else if (theLLscreen.theGeneralScreen.addButtonIsClick(window)) {
            theLLscreen.theGeneralScreen.turnOffAllButton();
            theLLscreen.theGeneralScreen.addButton.flipButtonState();
        }
        else if (theLLscreen.theGeneralScreen.deleteButtonIsClick(window)) {
            theLLscreen.theGeneralScreen.turnOffAllButton();
            theLLscreen.theGeneralScreen.deleteButton.flipButtonState();
        }
        else if (theLLscreen.theGeneralScreen.searchButtonIsClick(window)) {
            theLLscreen.theGeneralScreen.turnOffAllButton();
            theLLscreen.theGeneralScreen.searchButton.flipButtonState();
        }
        else if (theLLscreen.theGeneralScreen.updateButtonIsClick(window)) {
            theLLscreen.theGeneralScreen.turnOffAllButton();
            theLLscreen.theGeneralScreen.updateButton.flipButtonState();
        }
        else if (theLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theLLscreen.theGeneralScreen.addButton.textBoxIsClick(window)) {
            theLLscreen.theGeneralScreen.addButton.onInputBoxState();
        }
        else if (theLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theLLscreen.theGeneralScreen.deleteButton.textBoxIsClick(window)) {
            theLLscreen.theGeneralScreen.deleteButton.onInputBoxState();
        }
        else if (theLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theLLscreen.theGeneralScreen.searchButton.textBoxIsClick(window)) {
            theLLscreen.theGeneralScreen.searchButton.onInputBoxState();
        }
        else if (theLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theLLscreen.theGeneralScreen.updateButton.textBoxIsClick(window)) {
            theLLscreen.theGeneralScreen.updateButton.onInputBoxState();
        }
        else if (theLLscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theLLscreen.theGeneralScreen.addButton.confirmButtonIsClick(window)) {
            if (!theLLscreen.theGeneralScreen.addButton.inputIsEmpty()) {
                drawType = insertLL0;
                std::pair <int, int> userInput = theLLscreen.theGeneralScreen.addButton.getInputDataPair();
                int inputIndex = userInput.first, inputElement = userInput.second;
                insertNodeProcess(inputIndex, inputElement);
                LLCodeBlock.drawInsertCodeBlock(window);
                LLCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theLLscreen.theGeneralScreen.deleteButton.confirmButtonIsClick(window)) {
            if (!theLLscreen.theGeneralScreen.deleteButton.inputIsEmpty()) {
                drawType = deleteLL0;
                int userInput = theLLscreen.theGeneralScreen.deleteButton.getInputDataInt();
                deleteIndex = userInput;
                deleteNodeProcess(deleteIndex);
            }
        }
        else if (theLLscreen.theGeneralScreen.searchButton.buttonIsChoose() 
              && theLLscreen.theGeneralScreen.searchButton.confirmButtonIsClick(window)) {
            if (!theLLscreen.theGeneralScreen.searchButton.inputIsEmpty()) {
                drawType = searchLL0;
                int userInput = theLLscreen.theGeneralScreen.searchButton.getInputDataInt();
                searchData = userInput;
                searchNodeProcess(searchData);
            }
        }
        else if (theLLscreen.theGeneralScreen.updateButton.buttonIsChoose() 
              && theLLscreen.theGeneralScreen.updateButton.confirmButtonIsClick(window)) {
            if (!theLLscreen.theGeneralScreen.updateButton.inputIsEmpty()) {
                drawType = updateLL0;
                std::pair <int, int> userInput = theLLscreen.theGeneralScreen.updateButton.getInputDataPair();
                updateIndex = userInput.first, updateData = userInput.second;
                updateNodeProcess(updateIndex, updateData);
            }
        }
    }
    else if (drawType == chooseMakeLL) {
        if (theLLscreen.theCreateScreen.userInputButtonIsClick(window)) {
            theLLscreen.theCreateScreen.flipInputButtonState();
        }
        else if (theLLscreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = showcaseLL;
            craeteRandomList();
        }
        else if (theLLscreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = showcaseLL;
        }
        else if (theLLscreen.theCreateScreen.userInputButtonGetState()) {
            if (theLLscreen.theCreateScreen.textBoxIsClick(window)) {
                theLLscreen.theCreateScreen.onInputBoxState();
            }
            else if (theLLscreen.theCreateScreen.confirmButtonIsClick(window)) {
                if (!theLLscreen.theCreateScreen.inputIsEmpty()) {
                    drawType = makeLL;
                    std::vector <int> userInput = theLLscreen.theCreateScreen.getInputData();
                    createDefinedList(userInput);
                }
            }
            else {
                theLLscreen.theCreateScreen.offInputBoxState();
            }
        }
    }
}
void SLLObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeLL) {
        if (theLLscreen.theCreateScreen.userInputButtonGetState() && theLLscreen.theCreateScreen.textBoxGetState()) {
            if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                char inputCharacter = (char) event.text.unicode;
                theLLscreen.theCreateScreen.userInputCharacter(inputCharacter);
            }
        }
    }
    else if (theLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theLLscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theLLscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theLLscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theLLscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void SLLObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeLL) {
        if (theLLscreen.theCreateScreen.userInputButtonGetState() && theLLscreen.theCreateScreen.textBoxGetState()) {
            if (event.key.code == sf::Keyboard::Backspace) {
                theLLscreen.theCreateScreen.userBackspaceCharacter();
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                theLLscreen.theCreateScreen.userMoveCursor(event.key.code);
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                theLLscreen.theCreateScreen.userDeleteCharacter();
            }
        }
    }
    else if (theLLscreen.theGeneralScreen.addButton.buttonIsChoose() && theLLscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theLLscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theLLscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theLLscreen.theGeneralScreen.searchButton.buttonIsChoose() && theLLscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theLLscreen.theGeneralScreen.updateButton.buttonIsChoose() && theLLscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theLLscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void SLLObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (drawType == showcaseLL) {
        theLLscreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else if (drawType == chooseMakeLL) {
        theLLscreen.theCreateScreen.moveButtonWhenHover(window);
    }
}


void SLLObject::insertNodeProcess(int insertIndex, int insertData) {
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
void SLLObject::deleteNodeProcess(int deleteIndex) {
    this->nodeOpacity = this->deleteNodeOpacity = 255;
    this->nodePositionDiffX = nodeConstants::nodeDistance;
    this->newArrowOpacity = 0;
    this->gotoIndex = 1;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void SLLObject::searchNodeProcess(int searchData) {
    this->searchIndex = mySLL.searchElement(searchData);
    this->gotoIndex = 1;
    this->infoTextOpacity = 0;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void SLLObject::updateNodeProcess(int updateIndex, int updateData) {
    this->gotoIndex = 1;
    this->numberOpacity = 255;
    this->opacityMultiplier = -1;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}


void SLLObject::deleteSLL() {
    mySLL.deleteList();
    return;
}

void SLLObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}

void SLLObject::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
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
void SLLObject::drawLLScreen(sf::RenderWindow &window) {
    drawBackground(window);
    processMouseHoverEvent(window);
    processType(window);
}

void inputValue(int &value) {
    std::cin >> value;
}

void setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase) {
    if (nodePositionXAfterInsert < nodeConstants::nodeDistance)
        nodePositionXAfterInsert = std::min(nodeConstants::nodeDistance, nodePositionXAfterInsert + nodeConstants::insertMoveSpeed);
    if (insertPhase == 2)
        insertNodeOpacity = std::min(insertNodeOpacity + nodeConstants::fadeSpeed, 255);
    if (insertPhase == 2 && insertNodePosition.y > nodeConstants::firstNodePositionY && insertNodeOpacity == 255)
        insertNodePosition.y = std::max((float) insertNodePosition.y - nodeConstants::insertMoveSpeed, (float) nodeConstants::firstNodePositionY);
}