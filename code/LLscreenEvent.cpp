#include "LLscreenEvent.h"

SLLObject::SLLObject() {
    drawType = showcaseLL;
}

void SLLObject::createList(int numberOfNode, int *a) {
    mySLL.deleteList();
    mySLL.build(numberOfNode, a);
}
void SLLObject::processCreateList(int inputType) {
    //1 - user input
    //3 - random input
    if (inputType == 1) {
        int numberOfNode;
        while (true) {
            std::cout << "input number of node: ";
            inputValue(numberOfNode);
            if (numberOfNode < 0 || numberOfNode > 99) {
                std::cout << "number of elements must be an integer in range [0..10]";
            }
            else 
                break;
        }
        int *a = new int (numberOfNode);
        std::cout << "input N elements: ";
        for (int i = 0; i < numberOfNode; i++) {
            std::cin >> a[i];
            if (a[i] < 0 || a[i] > 99) {
                std::cout << "input value must be an integer in range [0..10]";
                i--;
            }
        }
        createList(numberOfNode, a);
    }
    else if (inputType == 2) {
        int numberOfNode = 0;
        int *a = new int(0);
        createList(numberOfNode, a);
    }
    else if (inputType == 3) {
        int numberOfNode = rand() % 10;
        int *a = new int(numberOfNode);
        for (int i = 0; i < numberOfNode; i++) {
            a[i] = rand() % 100;
        }
        createList(numberOfNode, a);
    }
    drawType = showcaseLL;
}

void SLLObject::drawList(sf::RenderWindow &window) {
    opacity = std::min(nodeConstants::fadeSpeed + opacity, 255);
    mySLL.drawList(window, opacity, nodeText);
    // std::cerr << "drew list\n";
}
void SLLObject::processDrawList() {
    opacity = 0;
}

void SLLObject::drawInsertIndicator(sf::RenderWindow &window) {
    mySLL.drawInsertNodeIndicator(window, insertIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        gotoIndex++;
        flashTimer.restart();
    }
    if (gotoIndex > insertIndex) {
        drawType = insertLL1;
        mySLL.insertAfterIndex(insertData, insertIndex);
        insertIndex++;
    }
}
void SLLObject::drawListWhenInsert(sf::RenderWindow &window) {
    mySLL.drawListWhenInsert(window, insertIndex, 
                             opacity, nodePositionXAfterInsert, nodeText);
    if (nodePositionXAfterInsert >= nodeConstants::nodeDistance) {
        drawType = insertLL2;
        flashTimer.restart();
    }
    else {
        setInsertNode(nodePositionXAfterInsert, insertNodePosition, insertNodeOpacity, 1);
    }
}
void SLLObject::drawInsertNode(sf::RenderWindow &window) {
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
    mySLL.drawDeleteNodeIndicator(window, deleteIndex, gotoIndex, 
                                  getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        gotoIndex++;
        flashTimer.restart();
    }
    if (gotoIndex > deleteIndex) {
        drawType = deleteLL1;
    }
}
void SLLObject::drawDeleteNode(sf::RenderWindow &window) {
    mySLL.drawDeleteNode(window, deleteIndex, nodeOpacity, deleteNodeOpacity, nodeText);
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
    if (nodePositionDiffX > 0 || newArrowOpacity < 255) {
        newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
        if (newArrowOpacity == 255)
            nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
    }
    else 
        drawType = showcaseLL;
}

void SLLObject::drawSearchIndicator(sf::RenderWindow &window) {
    std::cout.flush();
    int tempSearchIndex = searchIndex;
    if (searchIndex == -1)
        tempSearchIndex = mySLL.getNumberOfNode();
    mySLL.drawSearchIndicator(window, searchIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        gotoIndex++;
        flashTimer.restart();
    }
    if (gotoIndex > tempSearchIndex) {
        drawType = searchLL1;
        flashTimer.restart();
    }
}
void SLLObject::drawSearchHighlight(sf::RenderWindow &window) {
    mySLL.drawSearchHighlight(window, searchIndex, 
                              getFadeColor(nodeConstants::flashColor, nodeConstants::searchFoundColor, flashTimer), 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::searchFoundColor, flashTimer),
                              infoTextOpacity, nodeText);
    infoTextOpacity = std::min(255, infoTextOpacity + nodeConstants::fadeSpeed);
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
    infoTextOpacity = std::max(0, infoTextOpacity - nodeConstants::fadeSpeed);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = showcaseLL;
        flashTimer.restart();
    }
}
void SLLObject::drawUpdateIndicator(sf::RenderWindow &window) {
    mySLL.drawUpdateIndicator(window, updateIndex, gotoIndex, 
                              getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer), nodeText);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        gotoIndex++;
        flashTimer.restart();
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
            processCreateList(1);
            processDrawList();
            break;
        case showcaseLL:
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
        if (theLLscreen.theGeneralScreen.addButtonIsClick(window)) {
            drawType = insertLL0;
            insertNodeProcess(mySLL, insertIndex, insertData, insertNodePosition, gotoIndex,
                              nodePositionXAfterInsert, insertNodeOpacity, insertNodeColor, flashTimer);
        }
        if (theLLscreen.theGeneralScreen.deleteButtonIsClick(window)) {
            drawType = deleteLL0;
            deleteNodeProcess(mySLL, deleteIndex, nodeOpacity, deleteNodeOpacity, gotoIndex,
                              nodePositionDiffX, newArrowOpacity, flashTimer);
        }
        if (theLLscreen.theGeneralScreen.searchButtonIsClick(window)) {
            drawType = searchLL0;
            searchNodeProcess(mySLL, searchIndex, gotoIndex, infoTextOpacity, flashTimer);
        }
        if (theLLscreen.theGeneralScreen.updateButtonIsClick(window)) {
            drawType = updateLL0;
            updateNodeProcess(mySLL, updateIndex, updateData, gotoIndex, numberOpacity, opacityMultiplier, flashTimer);
        }
    }
    else if (drawType == chooseMakeLL) {
        if (theLLscreen.theCreateScreen.userInputButtonIsClick(window)) {
            theLLscreen.theCreateScreen.flipInputButtonState();
        }
        else if (theLLscreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = showcaseLL;
            processCreateList();
            processDrawList();
        }
        else if (theLLscreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = showcaseLL;
        }
        else if (theLLscreen.theCreateScreen.userInputButtonGetState()) {
            if (theLLscreen.theCreateScreen.textBoxIsClick(window) && !theLLscreen.theCreateScreen.textBoxGetState()) {
                theLLscreen.theCreateScreen.flipInputBoxState();
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
}

void SLLObject::deleteSLL() {
    mySLL.deleteList();
    return;
}

void SLLObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}

void inputValue(int &value) {
    std::cin >> value;
}

void insertNodeProcess(SLL &mySLL, int &insertIndex, int &insertData, sf::Vector2f &insertNodePosition, int &gotoIndex,
                       int &nodePositionXAfterInsert, int &insertNodeOpacity, int &insertNodeColor, sf::Clock &flashTimer) {
    std::cout << "insert index <= n and data to add\n";
    std::cin >> insertIndex >> insertData;
    insertNodePosition.x = nodeConstants::firstNodePositionX * (insertIndex + 1);
    insertNodePosition.y = nodeConstants::firstNodePositionY + nodeConstants::initialInsertNodeY;
    gotoIndex = 1;
    nodePositionXAfterInsert = 0;
    insertNodeOpacity = 0;
    insertNodeColor = rand() % 4;
    flashTimer.restart();
    std::cerr << "insert index, data: " << insertIndex << " " << insertData << '\n';
}

void deleteNodeProcess(SLL &mySLL, int &deleteIndex, int &nodeOpacity, int &deleteNodeOpacity, int &gotoIndex,
                       int &nodePositionDiffX, int &newArrowOpacity, sf::Clock &flashTimer) {
    std::cout << "insert index [1..n] to delete: ";
    std::cin >> deleteIndex;
    nodeOpacity = deleteNodeOpacity = 255;
    nodePositionDiffX = nodeConstants::nodeDistance;
    newArrowOpacity = 0;
    gotoIndex = 1;
    flashTimer.restart();
}

void searchNodeProcess(SLL &mySLL, int &searchIndex, int &gotoIndex, int &infoTextOpacity, sf::Clock &flashTimer) {
    std::cout << "insert value to search: ";
    int searchValue;
    std::cin >> searchValue;
    searchIndex = mySLL.searchElement(searchValue);
    gotoIndex = 1;
    infoTextOpacity = 0;
    flashTimer.restart();
}

void updateNodeProcess(SLL &mySLL, int &updateIndex, int &updateData, int &gotoIndex, 
                       int &numberOpacity, int &opacityMultiplier, sf::Clock &flashTimer) {
    std::cout << "insert index, value to update: ";
    std::cin >> updateIndex >> updateData;
    gotoIndex = 1;
    numberOpacity = 255;
    opacityMultiplier = -1;
    flashTimer.restart();
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
