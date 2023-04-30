#include "stackScreenEvent.h"

StackObject::StackObject() {
    drawType = stackShowcase;
    backToMenu = opacity = 0;
    createRandomStack();
}

void StackObject::createStack(std::vector <int> &a) {
    myStack.createStack(a);
}
void StackObject::createRandomStack() {
    std::vector <int> data;
    int n = rand() % 4 + 3;
    for (int i = 0; i < n; i++) {
        int value = rand() % 100;
        data.push_back(value);
    }
    myStack.createStack(data);
}

void StackObject::processType(sf::RenderWindow &window) {
    // if (drawType != chooseMakeDLL)
    //     theStackScreen.drawGeneralScreen(window);
    // else {
    //     theStackScreen.drawCreateScreen(window);
    // }
    switch (drawType) {
        // case makeDLL:
        //     processDrawList();
        //     break;
        case stackShowcase:
            // drawStack(window);
            break;
        // case chooseMakeDLL:
        //     drawList(window);
        //     break;
        // case insertDLL0:
        //     drawInsertIndicator(window);
        //     break;
        // case insertDLL1:
        //     drawListWhenInsert(window);
        //     break;
        // case insertDLL2:
        //     drawInsertNode(window);
        //     break;
        // case deleteDLL0:
        //     drawDeleteIndicator(window);
        //     break;
        // case deleteDLL1:
        //     drawDeleteNode(window);
        //     break;
        // case deleteDLL2:
        //     drawDeleteNodeMove(window);
        //     break;
        // case searchDLL0:
        //     drawSearchIndicator(window);
        //     break;
        // case searchDLL1:
        //     drawSearchHighlight(window);
        //     break;
        // case searchDLL2:
        //     drawSearchRevert(window);
        //     break;
        // case updateDLL0:
        //     drawUpdateIndicator(window);
        //     break;
        // case updateDLL1:
        //     drawUpdateChangeNum(window);
        //     break;
        // case updateDLL2:
        //     drawUpdateRevert(window);
        //     break;
    }
}


void StackObject::processMouseEvent(sf::RenderWindow &window) {
    // std::cerr << "event\n";
    if (drawType == stackShowcase) {
        if (theStackScreen.theGeneralScreen.createButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            drawType = stackChoose;
        }
        else if (theStackScreen.theGeneralScreen.peekButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            theStackScreen.theGeneralScreen.turnOnPeekButton();
            // theStackScreen.theGeneralScreen.addBeginning.flipButtonState();
            // theStackScreen.theGeneralScreen.addEnding.flipButtonState();
        }
        else if (theStackScreen.theGeneralScreen.pushButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            theStackScreen.theGeneralScreen.turnOnPushButton();
        }
        else if (theStackScreen.theGeneralScreen.popButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            theStackScreen.theGeneralScreen.turnOnPopButton();
        }
        else if (theStackScreen.theGeneralScreen.clearButtonIsClick(window)) {
            theStackScreen.theGeneralScreen.turnOffAllButton();
            theStackScreen.theGeneralScreen.turnOnClearButton();
        }
        else if (theStackScreen.theGeneralScreen.backButtonIsClick(window)) {
            this->backToMenu = true;
            theStackScreen.theGeneralScreen.turnOffAllButton();
        }
    }
    else if (drawType == stackChoose) {
        // if (theStackScreen.theCreateScreen.userInputButtonIsClick(window)) {
        //     theStackScreen.theCreateScreen.flipInputButtonState();
        // }
        // else if (theStackScreen.theCreateScreen.randomButtonIsClick(window)) {
        //     drawType = showcaseDLL;
        //     createRandomList();
        // }
        // else if (theStackScreen.theCreateScreen.backButtonIsClick(window)) {
        //     drawType = showcaseDLL;
        // }
        // else if (theStackScreen.theCreateScreen.userInputButtonGetState()) {
        //     if (theStackScreen.theCreateScreen.textBoxIsClick(window)) {
        //         theStackScreen.theCreateScreen.onInputBoxState();
        //     }
        //     else if (theStackScreen.theCreateScreen.confirmButtonIsClick(window)) {
        //         if (!theStackScreen.theCreateScreen.inputIsEmpty()) {
        //             drawType = makeDLL;
        //             std::vector <int> userInput = theStackScreen.theCreateScreen.getInputData();
        //             createDefinedList(userInput);
        //         }
        //     }
        //     else if (theStackScreen.theCreateScreen.browseButtonIsClick(window)) {
        //         std::string fileRead;
        //         if (browseForFile(fileRead)) {
        //             std::vector <int> userInput = getInputData(fileRead);
        //             if ((int) userInput.size() > 0) {
        //                 drawType = makeDLL;
        //                 createDefinedList(userInput);
        //             }
        //         }
        //     }
        //     else {
        //         theStackScreen.theCreateScreen.offInputBoxState();
        //     }
        // }
    }
}
void StackObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == stackChoose) {
        // if (theStackScreen.theCreateScreen.userInputButtonGetState() && theStackScreen.theCreateScreen.textBoxGetState()) {
        //     if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
        //         char inputCharacter = (char) event.text.unicode;
        //         theStackScreen.theCreateScreen.userInputCharacter(inputCharacter);
        //     }
        // }
    }
    else if (theStackScreen.theGeneralScreen.pushButtonIsChoose() && theStackScreen.theGeneralScreen.pushTextBoxIsChoose()) {
        theStackScreen.theGeneralScreen.pushTextBoxKeyboardEvent(event);
    }
}
void StackObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == stackChoose) {
        // if (theStackScreen.theCreateScreen.userInputButtonGetState() && theStackScreen.theCreateScreen.textBoxGetState()) {
        //     if (event.key.code == sf::Keyboard::Backspace) {
        //         theStackScreen.theCreateScreen.userBackspaceCharacter();
        //     }
        //     else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
        //         theStackScreen.theCreateScreen.userMoveCursor(event.key.code);
        //     }
        //     else if (event.key.code == sf::Keyboard::Delete) {
        //         theStackScreen.theCreateScreen.userDeleteCharacter();
        //     }
        // }
    }
    else if (theStackScreen.theGeneralScreen.pushButtonIsChoose() && theStackScreen.theGeneralScreen.pushTextBoxIsChoose()) {
        theStackScreen.theGeneralScreen.pushTextBoxKeyboardEvent(event);
    }
}
void StackObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (drawType == stackShowcase) {
        theStackScreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else if (drawType == stackChoose) {
        // theStackScreen.theCreateScreen.moveButtonWhenHover(window);
    }
}

void StackObject::processDrawList() {
    opacity = 0;
}