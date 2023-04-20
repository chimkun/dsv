#include "textbox.h"

textCursor::textCursor() {}
textCursor::textCursor(sf::Vector2f initialCursorPosition, sf::Vector2f rightmostCursorPosition) {
    tick = cursorPosition = 0;
    userInputText.setFont(2);
    this->initialCursorPosition = initialCursorPosition;
    this->rightmostCursorPosition = rightmostCursorPosition;
    cursor.setSize(sf::Vector2f(2, 26));
    // cursor.setPosition(400, 535 + 17);
    cursor.setPosition(initialCursorPosition);
    tickTime.restart();
    cursorColor = sf::Color::White;
}
void textCursor::drawTextCursor(sf::RenderWindow &window) {
    if (tickTime.getElapsedTime().asMilliseconds() > textConstants::textCursorTickRate.asMilliseconds()) {
        tickTime.restart();
        tick = !tick;
    }
    sf::Vector2f textOrigin = sf::Vector2f(0, 0);
    std::string stringBeforeCursor;
    for (int i = 0; i < cursorPosition; i++) 
        stringBeforeCursor.push_back(inputContent[i]);
    sf::FloatRect inputTextBound = userInputText.getTextBound(stringBeforeCursor, initialCursorPosition, 21);
    cursor.setPosition(initialCursorPosition + sf::Vector2f(inputTextBound.width + 2, 0));
    int opacity = 0;
    if (tick)
        opacity = 255;
    sf::Color cursorColor = this->cursorColor;
    cursorColor.a = opacity;
    this->cursor.setFillColor(cursorColor);
    window.draw(this->cursor);
}
void textCursor::drawTextOnBox(sf::RenderWindow &window) {
    sf::Vector2f textOrigin = sf::Vector2f(0, 0);
    userInputText.drawOptionalTextSize(window, inputContent, textOrigin, initialCursorPosition, 255, 21);
}
void textCursor::setInputContent(std::string &inputContent) {
    this->inputContent = inputContent;
}
std::string textCursor::getInputContent() {
    return inputContent;
}
void textCursor::userInputCharacter(char inputCharacter) {
    if ((int) inputContent.size() >= 120)
        return;
    if ('0' <= inputCharacter && inputCharacter <= '9') {
        inputContent.push_back(inputCharacter);
        cursorPosition++;
    }
    else if (inputCharacter == ',') {
        inputContent.push_back(inputCharacter);
        cursorPosition++;
    }
}
void textCursor::userBackspace() {
    if (!inputContent.empty() && cursorPosition > 0) {
        int deleteIndex = cursorPosition - 1;
        std::string newString;
        for (int i = 0; i < (int) inputContent.size(); i++) {
            if (i == deleteIndex)
                continue;
            newString.push_back(inputContent[i]);
        }
        inputContent = newString;
        cursorPosition--;
    }
}
void textCursor::userDelete() {
    if (!inputContent.empty() && cursorPosition < (int) inputContent.size()) {
        int deleteIndex = cursorPosition;
        std::string newString;
        for (int i = 0; i < (int) inputContent.size(); i++) {
            if (i == deleteIndex)
                continue;
            newString.push_back(inputContent[i]);
        }
        inputContent = newString;
    }
}
void textCursor::userMoveCursor(int arrowKeyCode) {
    if (arrowKeyCode == sf::Keyboard::Left) {
        cursorPosition = std::max(cursorPosition - 1, 0);
    }
    else if (arrowKeyCode == sf::Keyboard::Right) {
        cursorPosition = std::min(cursorPosition + 1, (int) inputContent.size());
    }
}

textBox::textBox() {}
textBox::textBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture) {
    isClicked = 0;
    std::string emptyString;
    textBoxButton.initButton(buttonPosition, buttonTexture, emptyString);
}
void textBox::userInputCharacter(char inputCharacter) {
    myTextCursor.userInputCharacter(inputCharacter);
}
void textBox::userBackspace() {
    myTextCursor.userBackspace();
}
void textBox::userDelete() {
    myTextCursor.userDelete();
}
void textBox::userMoveCursor(int arrowKeyCode) {
    myTextCursor.userMoveCursor(arrowKeyCode);
}
void textBox::textBoxEvent(sf::RenderWindow &window) {
    if (sf::Event::MouseButtonPressed) {
        if (textBoxButton.buttonIsClick(window)) {
            if (!isClicked) {
                isClicked = true;
            }
        }
        else {
            if (isClicked) {
                isClicked = false;
            }
        }
    }
}
void textBox::drawTextBox(sf::RenderWindow &window) {
    textBoxButton.drawButton(window);
    myTextCursor.drawTextOnBox(window);
    if (isClicked)
        myTextCursor.drawTextCursor(window);
}
void textBox::flipTextBoxState() {
    isClicked = !isClicked;
}
void textBox::offTextBoxState() {
    isClicked = 0;
}
bool textBox::textBoxIsClick() {
    return isClicked;
}
bool textBox::textBoxButtonIsClick(sf::RenderWindow &window) {
    return textBoxButton.buttonIsClick(window);
}
std::string textBox::getTextBoxString() {
    return myTextCursor.getInputContent();
}
