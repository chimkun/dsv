#include "textbox.h"

textCursor::textCursor() {
    cursor.setSize(sf::Vector2f(2, 26));
    initialCursorPosition = sf::Vector2f((float) 383, (float) (535 + 26));
    rightmostCursorPosition = sf::Vector2f((float) (383 + 260), (float) (535 + 26));
    tick = cursorPosition = 0;
    cursor.setPosition(this->initialCursorPosition);
    cursorColor = sf::Color::White;
    userInputText.setFont(2);
    tickTime.restart();
}
textCursor::textCursor(sf::Vector2f &initialLeftCursorPosition, sf::Vector2f &initialRightCursorPosition) {
    cursor.setSize(sf::Vector2f(2, 26));
    initialCursorPosition = initialLeftCursorPosition;
    rightmostCursorPosition = initialRightCursorPosition;
    tick = cursorPosition = 0;
    cursor.setPosition(this->initialCursorPosition);
    cursorColor = sf::Color::White;
    userInputText.setFont(2);
    tickTime.restart();
    // cursor.setPosition(400, 535 + 17);
}
void textCursor::setTextCursor(sf::Vector2f &initialLeftCursorPosition, sf::Vector2f &initialRightCursorPosition) {
    initialCursorPosition = initialLeftCursorPosition;
    rightmostCursorPosition = initialRightCursorPosition;
    cursor.setPosition(initialLeftCursorPosition);
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
    if (cursorOutOfBound())
        cursor.setPosition(rightmostCursorPosition);
    else 
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
sf::Vector2f textCursor::getCursorPosition() {
    std::string stringBeforeCursor;
    for (int i = 0; i < cursorPosition; i++) 
        stringBeforeCursor.push_back(inputContent[i]);
    sf::FloatRect inputTextBound = userInputText.getTextBound(stringBeforeCursor, initialCursorPosition, 21);
    return sf::Vector2f(initialCursorPosition + sf::Vector2f(inputTextBound.width + 2, 0));
}
bool textCursor::cursorOutOfBound() {
    sf::Vector2f currentCursorPosition = getCursorPosition();
    if (currentCursorPosition.x > rightmostCursorPosition.x)
        return true;
    return false;
}

void textCursor::userInputCharacter(char inputCharacter) {
    if ((int) inputContent.size() >= 120)
        return;
    if ('0' <= inputCharacter && inputCharacter <= '9') {
        inputContent.push_back(inputCharacter);
        cursorPosition++;
        if (cursorOutOfBound()) {
            cursorPosition--;
            inputContent.pop_back();
        }
    }
    else if (inputCharacter == ',') {
        inputContent.push_back(inputCharacter);
        cursorPosition++;
        if (cursorOutOfBound()) {
            cursorPosition--;
            inputContent.pop_back();
        }
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
    sf::Vector2f cursorLeftPosition = buttonPosition + sf::Vector2f(buttonConstants::textCursorDistance, 8);
    sf::Vector2f cursorRightPosition = buttonPosition + sf::Vector2f(buttonTexture.getSize().x - 22, 8);
    myTextCursor.setTextCursor(cursorLeftPosition, cursorRightPosition);
    // std::cerr << "pos: " << buttonPosition.x << " " << buttonPosition.y << '\n';
    // std::cerr << "cursor: " << cursorLeftPosition.x << " " << cursorLeftPosition.y << '\n';
}
textBox::textBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture,
                 sf::Vector2f cursorLeftPosition, sf::Vector2f cursorRightPosition) {
    isClicked = 0;
    std::string emptyString;
    textBoxButton.initButton(buttonPosition, buttonTexture, emptyString);
    myTextCursor.setTextCursor(cursorLeftPosition, cursorRightPosition);
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
void textBox::flipTextBoxState() {
    isClicked = !isClicked;
}
void textBox::offTextBoxState() {
    isClicked = 0;
}
void textBox::onTextBoxState() {
    isClicked = 1;
}
bool textBox::textBoxIsClick() {
    return isClicked;
}
bool textBox::textBoxButtonIsClick(sf::RenderWindow &window) {
    return textBoxButton.buttonIsClick(window);
}
bool textBox::inputIsEmpty() {
    return myTextCursor.getInputContent().empty();
}
std::string textBox::getTextBoxString() {
    return myTextCursor.getInputContent();
}
void textBox::setTextBoxString(std::string &inputString) {
    myTextCursor.inputContent = inputString;
}

void textBox::drawTextBox(sf::RenderWindow &window) {
    textBoxButton.drawButton(window);
    myTextCursor.drawTextOnBox(window);
    if (isClicked) {
        myTextCursor.drawTextCursor(window);
    }
}