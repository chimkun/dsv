#include "queueScreenEvent.h"

QueueObject::QueueObject() {
    drawType = queueShowcase;
    prevType = queueShowcase;
    backToMenu = opacity = 0;
    createRandomQueue();
    std::vector <int> curQueue = myQueue.getQueue();
    std::string initialData;
    for (int i = 0; i < (int) curQueue.size(); i++) {
        int u = curQueue[i];
        std::string curNum = std::to_string(u);
        initialData += curNum;
        initialData.push_back(',');
    }
    initialData.pop_back();
    theQueueScreen.theCreateScreen.setInputBoxString(initialData);
    theQueueScreen.theGeneralScreen.initData();
}

void QueueObject::createQueue(std::vector <int> &a) {
    myQueue.createQueue(a);
    opacity = 0;
}
void QueueObject::createRandomQueue() {
    std::vector <int> data;
    int n = rand() % 4 + 3;
    for (int i = 0; i < n; i++) {
        int value = rand() % 100;
        data.push_back(value);
    }
    myQueue.createQueue(data);
    opacity = 0;
}

void QueueObject::drawQueue(sf::RenderWindow &window) {
    // std::cerr << "opacity: " << opacity << '\n';
    myQueue.drawQueue(window, opacity);
    opacity = std::min(255, opacity + queueConstants::fadeSpeed);
}
void QueueObject::drawPeek(sf::RenderWindow &window) {
    sf::Color fadeColor = getFadeColor(nodeConstants::baseColor, nodeConstants::searchFoundColor, colorClock);
    myQueue.drawQueuePeek(window, fadeColor);
    // QueueCodeBlock.drawPeekCodeBlock(window);
    if (myQueue.getQueueSize() == 0) {
        QueueCodeBlock.drawPeekCodeBlockSingleLine(window, 0);
        QueueCodeBlock.drawPeekCodeBlockSingleLine(window, 1);
    }
    else {
        QueueCodeBlock.drawPeekCodeBlockSingleLine(window, 2);
    }
}
void QueueObject::drawPush(sf::RenderWindow &window) {
    myQueue.drawQueuePush(window, extraXDistance, newNodeOpacity);
    if (extraXDistance == 0 && newNodeOpacity == 255)
        drawType = queueShowcase;
    else {
        extraXDistance = std::max(0, extraXDistance - queueConstants::xMoveSpeed);
        newNodeOpacity = std::min(255, newNodeOpacity + queueConstants::fadeSpeed);
    }
    // QueueCodeBlock.drawPushCodeBlock(window);
    QueueCodeBlock.drawPushCodeBlockSingleLine(window, 0);
}
void QueueObject::drawPop(sf::RenderWindow &window) {
    myQueue.drawQueuePop(window, popOpacity);
    if (myQueue.getQueueSize() > 0) {
        if (drawType == queuePop) {
            // QueueCodeBlock.drawPopCodeBlock(window);
            QueueCodeBlock.drawPopCodeBlockSingleLine(window, 0);
            QueueCodeBlock.drawPopCodeBlockSingleLine(window, 1);
        }
        else {
            // QueueCodeBlock.drawClearCodeBlock(window);
            QueueCodeBlock.drawClearCodeBlockSingleLine(window, 0);
            QueueCodeBlock.drawClearCodeBlockSingleLine(window, 1);
        }
    }
    if (popOpacity == 0) {
        if (drawType == queuePop) {
            drawType = queueShowcase;
            isPop = 0;
            if (myQueue.getQueueSize() > 0)
                myQueue.popQueue();
        }
        else if (drawType == queueClear) {
            if (myQueue.getQueueSize() == 1) {
                drawType = queueShowcase;
                isPop = 0;
            }
            if (myQueue.getQueueSize() > 0)
                myQueue.popQueue();
            popQueueProcess();
        }
    }
    else {
        popOpacity = std::max(0, popOpacity - queueConstants::fadeSpeed);
    }
}
void QueueObject::processType(sf::RenderWindow &window) {
    if (theQueueScreen.isGeneralScreen())
        theQueueScreen.drawGeneralScreen(window);
    else {
        theQueueScreen.drawCreateScreen(window);
    }
    switch (prevType) {
        case queuePeek:
            QueueCodeBlock.drawPeekCodeBlock(window);
            break;
        case queuePush:
            QueueCodeBlock.drawPushCodeBlock(window);
            break;
        case queuePop:
            QueueCodeBlock.drawPopCodeBlock(window);
            break;
        case queueClear:
            QueueCodeBlock.drawClearCodeBlock(window);
            break;
    }
    switch (drawType) {
        case queueShowcase:
            drawQueue(window);
            break;
        case queuePeek:
            drawPeek(window);
            break;
        case queuePush:
            drawPush(window);
            break;
        case queuePop:
            drawPop(window);
            break;
        case queueClear:
            drawPop(window);
            break;
    }
}


void QueueObject::processMouseEvent(sf::RenderWindow &window) {
    // std::cerr << "event\n";
    if (isPop) 
        return;
    if (theQueueScreen.isGeneralScreen()) {
        if (theQueueScreen.theGeneralScreen.createButtonIsClick(window)) {
            theQueueScreen.theGeneralScreen.turnOffAllButton();
            theQueueScreen.setToCreate();
        }
        else if (theQueueScreen.theGeneralScreen.peekButtonIsClick(window)) {
            theQueueScreen.theGeneralScreen.turnOffAllButton();
            drawType = prevType = queuePeek;
            // theQueueScreen.theGeneralScreen.turnOnPeekButton();
            // theQueueScreen.theGeneralScreen.addBeginning.flipButtonState();
            // theQueueScreen.theGeneralScreen.addEnding.flipButtonState();
        }
        else if (theQueueScreen.theGeneralScreen.pushButtonIsClick(window)) {
            theQueueScreen.theGeneralScreen.turnOffAllButton();
            theQueueScreen.theGeneralScreen.turnOnPushButton();
        }
        else if (theQueueScreen.theGeneralScreen.popButtonIsClick(window)) {
            theQueueScreen.theGeneralScreen.turnOffAllButton();
            drawType = prevType = queuePop;
            isPop = 1;
            popQueueProcess();
        }
        else if (theQueueScreen.theGeneralScreen.clearButtonIsClick(window)) {
            theQueueScreen.theGeneralScreen.turnOffAllButton();
            drawType = prevType = queueClear;
            isPop = 1;
            popQueueProcess();
        }
        else if (theQueueScreen.theGeneralScreen.backButtonIsClick(window)) {
            this->backToMenu = true;
            theQueueScreen.theGeneralScreen.turnOffAllButton();
        }
        else if (theQueueScreen.theGeneralScreen.pushButtonIsChoose() && theQueueScreen.theGeneralScreen.pushTextBoxIsClick(window)) {
            theQueueScreen.theGeneralScreen.onTextBoxState();
        }
        else if (theQueueScreen.theGeneralScreen.pushButtonIsChoose() 
              && theQueueScreen.theGeneralScreen.confirmPushIsClick(window)) {
            if (!theQueueScreen.theGeneralScreen.pushTextBoxIsEmpty()) {
                drawType = prevType = queuePush;
                int userInput = theQueueScreen.theGeneralScreen.getInputData();
                pushQueueProcess(userInput);
            }
        }
    }
    else {
        if (theQueueScreen.theCreateScreen.userInputButtonIsClick(window)) {
            theQueueScreen.theCreateScreen.flipInputButtonState();
        }
        else if (theQueueScreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = queueShowcase;
            createRandomQueue();
        }
        else if (theQueueScreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = queueShowcase;
            theQueueScreen.setToGeneral();
        }
        else if (theQueueScreen.theCreateScreen.userInputButtonGetState()) {
            if (theQueueScreen.theCreateScreen.textBoxIsClick(window)) {
                theQueueScreen.theCreateScreen.onInputBoxState();
            }
            else if (theQueueScreen.theCreateScreen.confirmButtonIsClick(window)) {
                if (!theQueueScreen.theCreateScreen.inputIsEmpty()) {
                    drawType = prevType = queueShowcase;
                    std::vector <int> userInput = theQueueScreen.theCreateScreen.getInputData();
                    createQueue(userInput);
                    processDrawList();
                }
            }
            else if (theQueueScreen.theCreateScreen.browseButtonIsClick(window)) {
                std::string fileRead;
                if (browseForFile(fileRead)) {
                    std::vector <int> userInput = getInputData(fileRead);
                    if ((int) userInput.size() > 0) {
                        drawType = prevType = queueShowcase;
                        createQueue(userInput);
                        processDrawList();
                    }
                }
            }
            else {
                theQueueScreen.theCreateScreen.offInputBoxState();
            }
        }
    }
}
void QueueObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (!theQueueScreen.isGeneralScreen()) {
        if (theQueueScreen.theCreateScreen.userInputButtonGetState() && theQueueScreen.theCreateScreen.textBoxGetState()) {
            if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                char inputCharacter = (char) event.text.unicode;
                theQueueScreen.theCreateScreen.userInputCharacter(inputCharacter);
            }
        }
    }
    else if (theQueueScreen.theGeneralScreen.pushButtonIsChoose() && theQueueScreen.theGeneralScreen.pushTextBoxIsChoose()) {
        theQueueScreen.theGeneralScreen.pushTextBoxKeyboardEvent(event);
    }
}
void QueueObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (!theQueueScreen.isGeneralScreen()) {
        if (theQueueScreen.theCreateScreen.userInputButtonGetState() && theQueueScreen.theCreateScreen.textBoxGetState()) {
            if (event.key.code == sf::Keyboard::Backspace) {
                theQueueScreen.theCreateScreen.userBackspaceCharacter();
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                theQueueScreen.theCreateScreen.userMoveCursor(event.key.code);
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                theQueueScreen.theCreateScreen.userDeleteCharacter();
            }
        }
    }
    else if (theQueueScreen.theGeneralScreen.pushButtonIsChoose() && theQueueScreen.theGeneralScreen.pushTextBoxIsChoose()) {
        theQueueScreen.theGeneralScreen.pushTextBoxKeyboardEvent(event);
    }
}
void QueueObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (theQueueScreen.isGeneralScreen()) {
        theQueueScreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else {
        theQueueScreen.theCreateScreen.moveButtonWhenHover(window);
    }
}
void QueueObject::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
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

void QueueObject::processDrawList() {
    opacity = 0;
}

void QueueObject::peekQueueProcess() {
    if (this->myQueue.getQueueSize() == 0) {
        return;
    }
    this->colorClock.restart();
}
void QueueObject::pushQueueProcess(int userInput) {
    if (this->myQueue.getQueueSize() >= 12) {
        return;
    }
    this->myQueue.pushQueue(userInput);
    this->newNodeOpacity = 0;
    this->extraXDistance = queueConstants::xDistance;
}
void QueueObject::popQueueProcess() {
    if (this->myQueue.getQueueSize() == 0) {
        return;
    }
    this->popOpacity = 255;
}

bool QueueObject::exitQueueScreen() {
    return this->backToMenu;
}
void QueueObject::setExitToFalse() {
    this->backToMenu = 0;
}

void QueueObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}
void QueueObject::drawQueueScreen(sf::RenderWindow &window) {
    drawBackground(window);
    processMouseHoverEvent(window);
    processType(window);
}