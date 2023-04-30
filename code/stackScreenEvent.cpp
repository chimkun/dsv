#include "stackScreenEvent.h"

StackObject::StackObject() {
    drawType = stackShowcase;
    backToMenu = opacity = 0;
    createRandomStack();
    std::vector <int> curStack = myStack.getStack();
    std::string initialData;
    for (int i = 0; i < (int) curStack.size(); i++) {
        int u = curStack[i];
        std::string curNum = std::to_string(u);
        initialData += curNum;
        initialData.push_back(',');
    }
    initialData.pop_back();
    theStackScreen.theCreateScreen.setInputBoxString(initialData);
    theStackScreen.theGeneralScreen.initData();
}

void StackObject::createStack(std::vector <int> &a) {
    myStack.createStack(a);
    opacity = 0;
}
void StackObject::createRandomStack() {
    std::vector <int> data;
    int n = rand() % 4 + 3;
    for (int i = 0; i < n; i++) {
        int value = rand() % 100;
        data.push_back(value);
    }
    myStack.createStack(data);
    opacity = 0;
}

void StackObject::drawStack(sf::RenderWindow &window) {
    // std::cerr << "opacity: " << opacity << '\n';
    myStack.drawStack(window, opacity);
    opacity = std::min(255, opacity + stackConstants::fadeInSpeed);
}
void StackObject::drawPeek(sf::RenderWindow &window) {
    sf::Color fadeColor = getFadeColor(nodeConstants::baseColor, nodeConstants::searchFoundColor, colorClock);
    myStack.drawStackPeek(window, fadeColor);
}
void StackObject::drawPush(sf::RenderWindow &window) {
    myStack.drawStackPush(window, extraYDistance, newNodeOpacity);
    if (extraYDistance == 0 && newNodeOpacity == 255)
        drawType = stackShowcase;
    else {
        extraYDistance = std::max(0, extraYDistance - stackConstants::yMoveSpeed);
        newNodeOpacity = std::min(255, newNodeOpacity + stackConstants::fadeInSpeed);
    }
}
void StackObject::drawPop(sf::RenderWindow &window) {
    myStack.drawStackPop(window, popOpacity);
    if (popOpacity == 0) {
        if (drawType == stackPop) {
            drawType = stackShowcase;
            isPop = 0;
            if (myStack.getStackSize() > 0)
                myStack.popStack();
        }
        else if (drawType == stackClear) {
            if (myStack.getStackSize() == 1) {
                drawType = stackShowcase;
                isPop = 0;
            }
            if (myStack.getStackSize() > 0)
                myStack.popStack();
            popStackProcess();
        }
    }
    else {
        popOpacity = std::max(0, popOpacity - stackConstants::fadeOutSpeed);
    }
}
void StackObject::processType(sf::RenderWindow &window) {
    if (theStackScreen.isGeneralScreen())
        theStackScreen.drawGeneralScreen(window);
    else {
        theStackScreen.drawCreateScreen(window);
    }
    switch (drawType) {
        case stackShowcase:
            drawStack(window);
            break;
        case stackPeek:
            drawPeek(window);
            break;
        case stackPush:
            drawPush(window);
            break;
        case stackPop:
            drawPop(window);
            break;
        case stackClear:
            drawPop(window);
            break;
    }
}


void StackObject::processMouseEvent(sf::RenderWindow &window) {
    // std::cerr << "event\n";
    if (isPop) 
        return;
    if (theStackScreen.isGeneralScreen()) {
        if (theStackScreen.theGeneralScreen.createButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            theStackScreen.setToCreate();
        }
        else if (theStackScreen.theGeneralScreen.peekButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            drawType = stackPeek;
            // theStackScreen.theGeneralScreen.turnOnPeekButton();
            // theStackScreen.theGeneralScreen.addBeginning.flipButtonState();
            // theStackScreen.theGeneralScreen.addEnding.flipButtonState();
        }
        else if (theStackScreen.theGeneralScreen.pushButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            theStackScreen.theGeneralScreen.turnOnPushButton();
        }
        else if (theStackScreen.theGeneralScreen.popButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            drawType = stackPop;
            isPop = 1;
            popStackProcess();
        }
        else if (theStackScreen.theGeneralScreen.clearButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            drawType = stackClear;
            isPop = 1;
            popStackProcess();
        }
        else if (theStackScreen.theGeneralScreen.backButtonIsClick(window)) {
            this->backToMenu = true;
            theStackScreen.theGeneralScreen.turnOffAllButton();
        }
        else if (theStackScreen.theGeneralScreen.pushButtonIsChoose() && theStackScreen.theGeneralScreen.pushTextBoxIsClick(window)) {
            theStackScreen.theGeneralScreen.onTextBoxState();
        }
        else if (theStackScreen.theGeneralScreen.pushButtonIsChoose() 
              && theStackScreen.theGeneralScreen.confirmPushIsClick(window)) {
            if (!theStackScreen.theGeneralScreen.pushTextBoxIsEmpty()) {
                drawType = stackPush;
                int userInput = theStackScreen.theGeneralScreen.getInputData();
                pushStackProcess(userInput);
            }
        }
    }
    else {
        if (theStackScreen.theCreateScreen.userInputButtonIsClick(window)) {
            theStackScreen.theCreateScreen.flipInputButtonState();
        }
        else if (theStackScreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = stackShowcase;
            createRandomStack();
        }
        else if (theStackScreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = stackShowcase;
            theStackScreen.setToGeneral();
        }
        else if (theStackScreen.theCreateScreen.userInputButtonGetState()) {
            if (theStackScreen.theCreateScreen.textBoxIsClick(window)) {
                theStackScreen.theCreateScreen.onInputBoxState();
            }
            else if (theStackScreen.theCreateScreen.confirmButtonIsClick(window)) {
                if (!theStackScreen.theCreateScreen.inputIsEmpty()) {
                    drawType = stackShowcase;
                    std::vector <int> userInput = theStackScreen.theCreateScreen.getInputData();
                    createStack(userInput);
                    processDrawList();
                }
            }
            else if (theStackScreen.theCreateScreen.browseButtonIsClick(window)) {
                std::string fileRead;
                if (browseForFile(fileRead)) {
                    std::vector <int> userInput = getInputData(fileRead);
                    if ((int) userInput.size() > 0) {
                        drawType = stackShowcase;
                        createStack(userInput);
                        processDrawList();
                    }
                }
            }
            else {
                theStackScreen.theCreateScreen.offInputBoxState();
            }
        }
    }
}
void StackObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (!theStackScreen.isGeneralScreen()) {
        if (theStackScreen.theCreateScreen.userInputButtonGetState() && theStackScreen.theCreateScreen.textBoxGetState()) {
            if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                char inputCharacter = (char) event.text.unicode;
                theStackScreen.theCreateScreen.userInputCharacter(inputCharacter);
            }
        }
    }
    else if (theStackScreen.theGeneralScreen.pushButtonIsChoose() && theStackScreen.theGeneralScreen.pushTextBoxIsChoose()) {
        theStackScreen.theGeneralScreen.pushTextBoxKeyboardEvent(event);
    }
}
void StackObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (!theStackScreen.isGeneralScreen()) {
        if (theStackScreen.theCreateScreen.userInputButtonGetState() && theStackScreen.theCreateScreen.textBoxGetState()) {
            if (event.key.code == sf::Keyboard::Backspace) {
                theStackScreen.theCreateScreen.userBackspaceCharacter();
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                theStackScreen.theCreateScreen.userMoveCursor(event.key.code);
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                theStackScreen.theCreateScreen.userDeleteCharacter();
            }
        }
    }
    else if (theStackScreen.theGeneralScreen.pushButtonIsChoose() && theStackScreen.theGeneralScreen.pushTextBoxIsChoose()) {
        theStackScreen.theGeneralScreen.pushTextBoxKeyboardEvent(event);
    }
}
void StackObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (theStackScreen.isGeneralScreen()) {
        theStackScreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else {
        theStackScreen.theCreateScreen.moveButtonWhenHover(window);
    }
}
void StackObject::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
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

void StackObject::processDrawList() {
    opacity = 0;
}

void StackObject::peekStackProcess() {
    if (this->myStack.getStackSize() == 0) {
        return;
    }
    this->colorClock.restart();
}
void StackObject::pushStackProcess(int userInput) {
    if (this->myStack.getStackSize() >= 7) {
        return;
    }
    this->myStack.pushStack(userInput);
    this->newNodeOpacity = 0;
    this->extraYDistance = stackConstants::yDistance;
}
void StackObject::popStackProcess() {
    if (this->myStack.getStackSize() == 0) {
        return;
    }
    this->popOpacity = 255;
}

bool StackObject::exitStackScreen() {
    return this->backToMenu;
}
void StackObject::setExitToFalse() {
    this->backToMenu = 0;
}

void StackObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}
void StackObject::drawStackScreen(sf::RenderWindow &window) {
    drawBackground(window);
    processMouseHoverEvent(window);
    processType(window);
}