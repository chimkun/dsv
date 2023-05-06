#include "arrayScreenEvent.h"

SArrayObject::SArrayObject() {
    drawType = showcaseSArray;
    backToMenu = 0;
    createRandomList();
}

void SArrayObject::createList(int numberOfNode, std::vector <int> &a) {
    // std::cerr << "del list\n";
    // std::cerr << "build: "; for(auto u:a) std::cerr << u << " "; std::cerr << '\n';
    mySArray.build(a);
    // std::cerr << "done: "; mySArray.printList();
    theSArrayscreen.theGeneralScreen.initData(numberOfNode);
}
void SArrayObject::createRandomList() {
    int numberOfNode = rand() % 4 + 4;  
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
    theSArrayscreen.theCreateScreen.setInputBoxString(sampleInput);
    createList(numberOfNode, a);
}
void SArrayObject::createDefinedList(std::vector <int> &userInput) {
    int numberOfNode = (int) userInput.size();
    createList(numberOfNode, userInput);
}
void SArrayObject::drawList(sf::RenderWindow &window) {
    opacity = std::min(nodeConstants::fadeSpeed + opacity, 255);
    mySArray.drawArray(window, opacity);
    mySArray.printArray();
}
void SArrayObject::processDrawList() {
    opacity = 0;
    drawType = showcaseSArray;
}

void SArrayObject::drawInsertIndicator(sf::RenderWindow &window) {
    int nodeColorIndex = insertData % 4;
    sf::Color nodeColor = colorConstants::nodeColor[nodeColorIndex];
    sf::Color fadeColor = getFadeColor(sf::Color::White, nodeColor, flashTimer);
    insertNumberOpacity = std::min(255, insertNumberOpacity + arrayConstants::fadeSpeed);
    mySArray.drawInsertNodeIndicator(window, fadeColor, insertNumberOpacity, insertData);
    if (insertNumberOpacity == 255) {
        drawType = insertSArray1;
    }
}
void SArrayObject::drawInsertNodeSwap(sf::RenderWindow &window) {
    insertSwapDistance = std::min(arrayConstants::xDistance, insertSwapDistance + arrayConstants::swapXSpeed);
    mySArray.drawInsertNodeSwap(window, insertSwapIndex, insertData, insertSwapDistance);
    if (insertSwapDistance == arrayConstants::xDistance) {
        if (markFirst) {
            markFirst = 0;
            insertSwapTime.restart();
        }
        sf::Time duration = sf::milliseconds(100);
        if (insertSwapTime.getElapsedTime().asMilliseconds() > duration.asMilliseconds()) {
            markFirst = 1;
            insertSwapDistance = 0;
            insertSwapIndex--;
            if (insertSwapIndex == 0) {
                mySArray.insertAtMiddle(insertIndex, insertData);
                drawType = showcaseSArray;
            }
        }
    }
}

void SArrayObject::drawDeleteIndicator(sf::RenderWindow &window) {
    int deleteData = mySArray.accessIndex(deleteIndex);
    sf::Color nodeColor = colorConstants::nodeColor[deleteData % 4];
    sf::Color fadeColor = getFadeColor(nodeColor, sf::Color::White, flashTimer);
    deleteNumberOpacity = std::max(0, deleteNumberOpacity - arrayConstants::fadeSpeed);
    mySArray.drawDeleteNodeIndicator(window, fadeColor, deleteIndex, deleteNumberOpacity);
    if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
        drawType = deleteSArray1;
        markFirst = 1;
        flashTimer.restart();
    }
}
void SArrayObject::drawDeleteNodeSwap(sf::RenderWindow &window) {
    if (deleteSwapIndex == mySArray.getArrayLength()) {
        mySArray.deleteAtMiddle(deleteIndex);
        drawType = showcaseSArray;
        return;
    }
    deleteSwapDistance = std::min(arrayConstants::swapXSpeed + deleteSwapDistance, arrayConstants::xDistance);
    mySArray.drawDeleteNodeSwap(window, deleteIndex, deleteSwapIndex, deleteSwapDistance); 
    if (deleteSwapDistance == arrayConstants::xDistance) {
        if (markFirst) {
            markFirst = 0;
            deleteSwapTime.restart();
        }
        sf::Time duration = sf::milliseconds(100);
        if (deleteSwapTime.getElapsedTime().asMilliseconds() > duration.asMilliseconds()) {
            markFirst = 1;
            deleteSwapDistance = 0;
            deleteSwapIndex++;
            if (deleteSwapIndex == mySArray.getArrayLength()) {
                mySArray.deleteAtMiddle(deleteIndex);
                drawType = showcaseSArray;
            }
        }
    }
}
void SArrayObject::drawDeleteNodeMove(sf::RenderWindow &window) {
    // // std::cerr << "node move\n";
    // mySArray.drawDeleteNodeMove(window, deleteIndex, nodeOpacity, 
    //                          nodePositionDiffX, newArrowOpacity,
    //                          getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer));
    // if (deleteIndex == 1) {
    //     SArrayCodeBlock.drawDeleteBeginCodeBlock(window);
    //     SArrayCodeBlock.drawDeleteBeginCodeBlockMultiLine(window, 3, 4);
    // }
    // else {
    //     SArrayCodeBlock.drawDeleteCodeBlock(window);
    //     SArrayCodeBlock.drawDeleteCodeBlockSingleLine(window, 5);
    // }
    // if (nodePositionDiffX > 0 || newArrowOpacity < 255) {
    //     if (deleteIndex != 1) {
    //         newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
    //         if (newArrowOpacity == 255)
    //             nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
    //     }
    //     else {
    //         nodePositionDiffX = std::max(nodePositionDiffX - nodeConstants::insertMoveSpeed, 0);
    //         if (nodePositionDiffX == 0) {
    //             newArrowOpacity = std::min(255, newArrowOpacity + nodeConstants::fadeSpeed);
    //         }
    //     }
    // }
    // else 
    //     drawType = showcaseSArray;
}

// void SArrayObject::drawSearchIndicator(sf::RenderWindow &window) {
//     if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
//         sf::sleep(sf::milliseconds(500));
//     }
//     int tempSearchIndex = searchIndex;
//     if (searchIndex == -1)
//         tempSearchIndex = mySArray.getNumberOfNode();
//     mySArray.drawSearchIndicator(window, searchIndex, gotoIndex, 
//                               getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));   
//     remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
//     SArrayCodeBlock.drawSearchCodeBlock(window);
//     if (!markFirst) {
//         if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
//             gotoIndex++;
//             flashTimer.restart();
//             if (gotoIndex <= tempSearchIndex)
//                 SArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 4);
//         }
//         else {
//             SArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
//         }
//     }
//     else {
//         markFirst = 0;
//         flashTimer.restart();
//         SArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
//     }
//     if (gotoIndex > tempSearchIndex) {
//         drawType = searchSArray1;
//         flashTimer.restart();
//         markFirst = 1;
//     }
// }
// void SArrayObject::drawSearchHighlight(sf::RenderWindow &window) {
//     mySArray.drawSearchHighlight(window, searchIndex, 
//                               getFadeColor(nodeConstants::flashColor, nodeConstants::searchFoundColor, flashTimer), 
//                               getFadeColor(nodeConstants::baseColor, nodeConstants::searchFoundColor, flashTimer),
//                               infoTextOpacity);
//     infoTextOpacity = std::min(255, infoTextOpacity + nodeConstants::fadeSpeed);
//     SArrayCodeBlock.drawSearchCodeBlock(window);
//     if (searchIndex == -1) {
//         SArrayCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
//     }
//     else {
//         SArrayCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
//     }
//     if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
//         drawType = searchSArray2;
//         sf::sleep(sf::seconds(3.0f));
//         flashTimer.restart();
//     }
// }
// void SArrayObject::drawSearchRevert(sf::RenderWindow &window) {
//     mySArray.drawSearchRevert(window, searchIndex, 
//                            getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer),
//                            getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer),
//                            infoTextOpacity);
//     SArrayCodeBlock.drawSearchCodeBlock(window);
//     if (searchIndex == -1) {
//         SArrayCodeBlock.drawSearchCodeBlockSingleLine(window, 5);
//     }
//     else {
//         SArrayCodeBlock.drawSearchCodeBlockMultiLine(window, 2, 3);
//     }
//     infoTextOpacity = std::max(0, infoTextOpacity - nodeConstants::fadeSpeed);
//     if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
//         drawType = showcaseSArray;
//         flashTimer.restart();
//     }
// }
// void SArrayObject::drawUpdateIndicator(sf::RenderWindow &window) {
//     // std::cerr << "update index, data: " << updateIndex << " " << updateData << '\n';
//     if (flashTimer.getElapsedTime().asMilliseconds() < remTime.asMilliseconds()) {
//         sf::sleep(sf::milliseconds(500));
//     }
//     mySArray.drawUpdateIndicator(window, updateIndex, gotoIndex, 
//                               getFadeColor(nodeConstants::baseColor, nodeConstants::flashColor, flashTimer));
//     remTime = sf::milliseconds(flashTimer.getElapsedTime().asMilliseconds()); 
//     SArrayCodeBlock.drawUpdateCodeBlock(window);
//     if (!markFirst) {
//         if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
//             gotoIndex++;
//             flashTimer.restart();
//             if (gotoIndex <= updateIndex)
//                 SArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 5);
//         }
//         else {
//             SArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 1);
//         }
//     }
//     else {
//         markFirst = 0;
//         flashTimer.restart();
//         SArrayCodeBlock.drawUpdateCodeBlockSingleLine(window, 0);
//     }
//     if (gotoIndex > updateIndex) {
//         drawType = updateSArray1;
//         flashTimer.restart();
//     }
// }
// void SArrayObject::drawUpdateChangeNum(sf::RenderWindow &window) {
//     sf::Color fadeColor;
//     if (opacityMultiplier == -1)
//         fadeColor = nodeConstants::baseColor;
//     else 
//         fadeColor = nodeConstants::searchFoundColor;
//     mySArray.drawUpdateChangeNum(window, updateIndex, updateData, numberOpacity, fadeColor);
//     SArrayCodeBlock.drawUpdateCodeBlock(window);
//     SArrayCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
//     if (opacityMultiplier == -1) {
//         numberOpacity = std::max(0, numberOpacity - nodeConstants::fadeSpeed);
//         if (numberOpacity == 0) {
//             opacityMultiplier = 1;
//             mySArray.updateIndex(updateIndex, updateData);
//         }
//     }
//     else {
//         if (numberOpacity == 0)
//             sf::sleep(sf::seconds(0.1));
//         numberOpacity = std::min(255, numberOpacity + nodeConstants::fadeSpeed);
//     }

//     if (opacityMultiplier == 1 && numberOpacity == 255) {
//         sf::sleep(sf::seconds(1));
//         flashTimer.restart();
//         drawType = updateSArray2;
//     }
// }
// void SArrayObject::drawUpdateRevert(sf::RenderWindow &window) {
//     sf::Color fadeOutlineColor, fadeNumberColor;
//     fadeOutlineColor = getFadeColor(nodeConstants::flashColor, nodeConstants::baseColor, flashTimer);
//     fadeNumberColor = getFadeColor(nodeConstants::searchFoundColor, nodeConstants::baseColor, flashTimer);
//     mySArray.drawUpdateRevert(window, updateIndex, fadeOutlineColor, fadeNumberColor);
//     SArrayCodeBlock.drawUpdateCodeBlock(window);
//     SArrayCodeBlock.drawUpdateCodeBlockMultiLine(window, 2, 4);
//     if (flashTimer.getElapsedTime().asSeconds() >= nodeConstants::flashDuration.asSeconds()) {
//         drawType = showcaseSArray;
//         flashTimer.restart();
//     }
// }

void SArrayObject::processType(sf::RenderWindow &window) {
    if (theSArrayscreen.isGeneralScreen()) {
        theSArrayscreen.drawGeneralScreen(window);
    }
    else {
        theSArrayscreen.drawCreateScreen(window);
    }
    switch (drawType) {
        case makeSArray:
            processDrawList();
            break;
        case showcaseSArray:
            drawList(window);
            break;
        case chooseMakeSArray:
            drawList(window);
            break;
        case insertSArray0:
            drawInsertIndicator(window);
            break;
        case insertSArray1:
            drawInsertNodeSwap(window);
            break;
        // case insertSArray2:
        //     drawInsertNode(window);
        //     break;
        case deleteSArray0:
            drawDeleteIndicator(window);
            break;
        case deleteSArray1:
            drawDeleteNodeSwap(window);
            break;
        // case deleteSArray2:
        //     drawDeleteNodeMove(window);
        //     break;
        // case searchSArray0:
        //     drawSearchIndicator(window);
        //     break;
        // case searchSArray1:
        //     drawSearchHighlight(window);
        //     break;
        // case searchSArray2:
        //     drawSearchRevert(window);
        //     break;
        // case updateSArray0:
        //     drawUpdateIndicator(window);
        //     break;
        // case updateSArray1:
        //     drawUpdateChangeNum(window);
        //     break;
        // case updateSArray2:
        //     drawUpdateRevert(window);
        //     break;
    }
}


void SArrayObject::processMouseEvent(sf::RenderWindow &window) {
    // std::cerr << "event\n";
    if (theSArrayscreen.isGeneralScreen()) {
        if (theSArrayscreen.theGeneralScreen.createButtonIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAllButton();
            drawType = chooseMakeSArray;
            theSArrayscreen.setCreate();
        }
        else if (theSArrayscreen.theGeneralScreen.addButtonIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAllButton();
            theSArrayscreen.theGeneralScreen.addButton.flipButtonState();
            // theSArrayscreen.theGeneralScreen.addBeginning.flipButtonState();
            // theSArrayscreen.theGeneralScreen.addEnding.flipButtonState();
        }
        else if (theSArrayscreen.theGeneralScreen.deleteButtonIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAllButton();
            theSArrayscreen.theGeneralScreen.deleteButton.flipButtonState();
        }
        else if (theSArrayscreen.theGeneralScreen.searchButtonIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAllButton();
            theSArrayscreen.theGeneralScreen.searchButton.flipButtonState();
        }
        else if (theSArrayscreen.theGeneralScreen.updateButtonIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAllButton();
            theSArrayscreen.theGeneralScreen.updateButton.flipButtonState();
        }
        else if (theSArrayscreen.theGeneralScreen.backToMenuIsClick(window)) {
            this->backToMenu = true;
            theSArrayscreen.theGeneralScreen.turnOffAllButton();
        }
        else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addButton.textBoxIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAddTextBox();
            theSArrayscreen.theGeneralScreen.addButton.onInputBoxState();
        }
        else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addBeginningText.textBoxButtonIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAddTextBox();
            theSArrayscreen.theGeneralScreen.addBeginningText.onTextBoxState();
        }
        else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addEndingText.textBoxButtonIsClick(window)) {
            theSArrayscreen.theGeneralScreen.turnOffAddTextBox();
            theSArrayscreen.theGeneralScreen.addEndingText.onTextBoxState();
        }
        else if (theSArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.deleteButton.textBoxIsClick(window)) {
            theSArrayscreen.theGeneralScreen.deleteButton.onInputBoxState();
        }
        else if (theSArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.searchButton.textBoxIsClick(window)) {
            theSArrayscreen.theGeneralScreen.searchButton.onInputBoxState();
        }
        else if (theSArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.updateButton.textBoxIsClick(window)) {
            theSArrayscreen.theGeneralScreen.updateButton.onInputBoxState();
        }
        else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.addButton.confirmButtonIsClick(window)) {
            if (!theSArrayscreen.theGeneralScreen.addButton.inputIsEmpty()) {
                std::pair <int, int> userInput = theSArrayscreen.theGeneralScreen.addButton.getInputDataPair();
                if (insertIsValid(userInput.first, userInput.second)) {
                    drawType = insertSArray0;
                    int inputIndex = userInput.first, inputElement = userInput.second;
                    inputIndex++;
                    insertNodeProcess(inputIndex, inputElement);
                    // SArrayCodeBlock.drawInsertCodeBlock(window);
                    // SArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
                }
            }
        }
        else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.addBeginning.buttonIsClick(window)) {
            if (!theSArrayscreen.theGeneralScreen.addBeginningText.inputIsEmpty()) {
                // int userInput = theSArrayscreen.theGeneralScreen.addBeginningText.getInputDataInt();
                // if (insertIsValid(0, userInput)) {
                //     drawType = insertSArray0;
                //     int inputIndex = 1, inputElement = userInput;
                //     insertNodeProcess(inputIndex, inputElement);
                //     SArrayCodeBlock.drawInsertBeginCodeBlock(window);
                //     if (mySArray.getNumberOfNode() == 0)
                //         SArrayCodeBlock.drawInsertBeginCodeBlockSingleLine(window, 0);
                //     else 
                //         SArrayCodeBlock.drawInsertBeginCodeBlockSingleLine(window, 3);
                // }
            }
        }
        else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.addEnding.buttonIsClick(window)) {
            if (!theSArrayscreen.theGeneralScreen.addEndingText.inputIsEmpty()) {
                // int userInput = theSArrayscreen.theGeneralScreen.addEndingText.getInputDataInt();
                // if (insertIsValid(mySArray.getNumberOfNode(), userInput)) {
                //     drawType = insertSArray0;
                //     int inputIndex = mySArray.getNumberOfNode(), inputElement = userInput;
                //     insertNodeProcess(inputIndex, inputElement);
                //     insertNodePosition.x += nodeConstants::nodeDistance;
                // }
                // std::cerr << "ending index: " << insertIndex << "  " << insertNodePosition.x << "  " << mySArray.getNumberOfNode() << '\n';
                // SArrayCodeBlock.drawInsertCodeBlock(window);
                // SArrayCodeBlock.drawInsertCodeBlockSingleLine(window, 0);
            }
        }
        else if (theSArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.deleteButton.confirmButtonIsClick(window)) {
            if (!theSArrayscreen.theGeneralScreen.deleteButton.inputIsEmpty()) {
                int userInput = theSArrayscreen.theGeneralScreen.deleteButton.getInputDataInt();
                if (deleteIsValid(userInput)) {
                    drawType = deleteSArray0;
                    deleteIndex = userInput;
                    deleteNodeProcess(deleteIndex);
                }
            }
        }
        else if (theSArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.delBeginning.buttonIsClick(window)) {
                // if (deleteIsValid(0)) {
                //     drawType = deleteSArray0;
                //     deleteIndex = 1;
                //     deleteNodeProcess(deleteIndex);
                // }
        }
        else if (theSArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.delEnding.buttonIsClick(window)) {
            // if (deleteIsValid((int) mySArray.getNumberOfNode() - 1)) {
            //     drawType = deleteSArray0;
            //     deleteIndex = mySArray.getNumberOfNode();
            //     deleteNodeProcess(deleteIndex);
            // }
        }
        else if (theSArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.searchButton.confirmButtonIsClick(window)) {
            if (!theSArrayscreen.theGeneralScreen.searchButton.inputIsEmpty()) {
                // drawType = searchSArray0;
                // int userInput = theSArrayscreen.theGeneralScreen.searchButton.getInputDataInt();
                // searchData = userInput;
                // searchNodeProcess(searchData);
            }
        }
        else if (theSArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() 
              && theSArrayscreen.theGeneralScreen.updateButton.confirmButtonIsClick(window)) {
            if (!theSArrayscreen.theGeneralScreen.updateButton.inputIsEmpty()) {
                // std::pair <int, int> userInput = theSArrayscreen.theGeneralScreen.updateButton.getInputDataPair();
                // if (updateIsValid(userInput.first, userInput.second)) {
                //     drawType = updateSArray0;
                //     updateIndex = userInput.first, updateData = userInput.second;
                //     updateIndex++;
                //     updateNodeProcess(updateIndex, updateData);
                // }
            }
        }
    }
    else {
        if (theSArrayscreen.theCreateScreen.userInputButtonIsClick(window)) {
            theSArrayscreen.theCreateScreen.flipInputButtonState();
        }
        else if (theSArrayscreen.theCreateScreen.randomButtonIsClick(window)) {
            drawType = showcaseSArray;
            createRandomList();
        }
        else if (theSArrayscreen.theCreateScreen.backButtonIsClick(window)) {
            drawType = showcaseSArray;
            theSArrayscreen.setGeneral();
        }
        else if (theSArrayscreen.theCreateScreen.userInputButtonGetState()) {
            if (theSArrayscreen.theCreateScreen.textBoxIsClick(window)) {
                theSArrayscreen.theCreateScreen.onInputBoxState();
            }
            else if (theSArrayscreen.theCreateScreen.confirmButtonIsClick(window)) {
                // if (!theSArrayscreen.theCreateScreen.inputIsEmpty()) {
                //     drawType = makeSArray;
                //     std::vector <int> userInput = theSArrayscreen.theCreateScreen.getInputData();
                //     createDefinedList(userInput);
                // }
            }
            else if (theSArrayscreen.theCreateScreen.browseButtonIsClick(window)) {
                // std::string fileRead;
                // if (browseForFile(fileRead)) {
                //     std::vector <int> userInput = getInputData(fileRead);
                //     if ((int) userInput.size() > 0) {
                //         drawType = makeSArray;
                //         createDefinedList(userInput);
                //     }
                // }
            }
            else {
                theSArrayscreen.theCreateScreen.offInputBoxState();
            }
        }
    }
}
void SArrayObject::processKeyboardInputEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeSArray) {
        if (theSArrayscreen.theCreateScreen.userInputButtonGetState() && theSArrayscreen.theCreateScreen.textBoxGetState()) {
            if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                char inputCharacter = (char) event.text.unicode;
                theSArrayscreen.theCreateScreen.userInputCharacter(inputCharacter);
            }
        }
    }
    else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addBeginningText.textBoxIsClick()) {
        theSArrayscreen.theGeneralScreen.addBeginningText.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addEndingText.textBoxIsClick()) {
        theSArrayscreen.theGeneralScreen.addEndingText.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void SArrayObject::processKeyboardOtherActionEvent(sf::RenderWindow &window, sf::Event &event) {
    if (drawType == chooseMakeSArray) {
        if (theSArrayscreen.theCreateScreen.userInputButtonGetState() && theSArrayscreen.theCreateScreen.textBoxGetState()) {
            if (event.key.code == sf::Keyboard::Backspace) {
                theSArrayscreen.theCreateScreen.userBackspaceCharacter();
            }
            else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                theSArrayscreen.theCreateScreen.userMoveCursor(event.key.code);
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                theSArrayscreen.theCreateScreen.userDeleteCharacter();
            }
        }
    }
    else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.addButton.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addBeginningTextIsChoose()) {
        theSArrayscreen.theGeneralScreen.addBeginningText.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.addButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.addEndingTextIsChoose()) {
        theSArrayscreen.theGeneralScreen.addEndingText.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.deleteButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.deleteButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.deleteButton.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.searchButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.searchButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.searchButton.processKeyboardEvent(event);
    }
    else if (theSArrayscreen.theGeneralScreen.updateButton.buttonIsChoose() && theSArrayscreen.theGeneralScreen.updateButton.textBoxIsChoose()) {
        theSArrayscreen.theGeneralScreen.updateButton.processKeyboardEvent(event);
    }
}
void SArrayObject::processMouseHoverEvent(sf::RenderWindow &window) {
    if (drawType == showcaseSArray) {
        theSArrayscreen.theGeneralScreen.moveButtonWhenHover(window);
    }
    else if (drawType == chooseMakeSArray) {
        theSArrayscreen.theCreateScreen.moveButtonWhenHover(window);
    }
}


bool SArrayObject::insertIsValid(int addIndex, int addData) {
    if (0 <= addIndex && addIndex <= mySArray.getArrayLength() && mySArray.getArrayLength() < mySArray.getFixedLength())
        return true;
    return false;
}
bool SArrayObject::deleteIsValid(int delIndex) {
    if (0 <= delIndex && delIndex < mySArray.getArrayLength())
        return true;
    return false;
}
bool SArrayObject::updateIsValid(int updIndex, int updData){
    // if (0 <= updIndex && updIndex < mySArray.getNumberOfNode() && 0 <= updData && updData <= 99)
    //     return true;
    return false;
}

void SArrayObject::insertNodeProcess(int insertIndex, int insertData) {
    this->insertIndex = insertIndex;
    this->insertData = insertData;
    this->insertNumberOpacity = 0;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
    this->insertSwapIndex = mySArray.getArrayLength() - 1;
    this->insertSwapDistance = 0;
}
void SArrayObject::deleteNodeProcess(int deleteIndex) {
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
    this->deleteSwapDistance = 0;
    this->deleteSwapIndex = deleteIndex + 1;
    this->deleteNumberOpacity = 255;
}
void SArrayObject::searchNodeProcess(int searchData) {
    this->searchIndex = mySArray.searchValue(searchData);
    this->infoTextOpacity = 0;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}
void SArrayObject::updateNodeProcess(int updateIndex, int updateData) {
    this->numberOpacity = 255;
    this->opacityMultiplier = -1;
    this->flashTimer.restart();
    this->remTime = sf::milliseconds(0);
    this->markFirst = 1;
}


void SArrayObject::deleteSArray() {
    // mySArray.deleteList();
    return;
}

void SArrayObject::drawBackground(sf::RenderWindow &window) {
    screenBackground.drawBackground(window);
}


bool SArrayObject::exitSArrayScreen() {
    return this->backToMenu;
}
void SArrayObject::setExitToFalse() {
    this->backToMenu = 0;
}
void SArrayObject::processAllEvent(sf::RenderWindow &window, sf::Event &event) {
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
void SArrayObject::drawSArrayScreen(sf::RenderWindow &window) {
    drawBackground(window);
    processMouseHoverEvent(window);
    processType(window);
}

void SArrayObject::inputValue(int &value) {
    std::cin >> value;
}

void SArrayObject::setInsertNode(int &nodePositionXAfterInsert, sf::Vector2f &insertNodePosition,
                   int &insertNodeOpacity, int insertPhase) {
    if (nodePositionXAfterInsert < nodeConstants::nodeDistance)
        nodePositionXAfterInsert = std::min(nodeConstants::nodeDistance, nodePositionXAfterInsert + nodeConstants::insertMoveSpeed);
    if (insertPhase == 2)
        insertNodeOpacity = std::min(insertNodeOpacity + nodeConstants::fadeSpeed, 255);
    if (insertPhase == 2 && insertNodePosition.y > nodeConstants::firstNodePositionY && insertNodeOpacity == 255)
        insertNodePosition.y = std::max((float) insertNodePosition.y - nodeConstants::insertMoveSpeed, (float) nodeConstants::firstNodePositionY);
}

std::vector<int> SArrayObject::getInputData(std::string &inputString) {
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