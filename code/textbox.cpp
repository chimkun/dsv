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
    if ('0' <= inputCharacter && inputCharacter <= '9' || inputCharacter == ',') {
        std::string temp = inputContent + inputCharacter;
        sf::FloatRect inputTextBound = userInputText.getTextBound(temp, initialCursorPosition, 21);
        if (inputTextBound.width > rightmostCursorPosition.x - initialCursorPosition.x)
            return;
        if (cursorPosition == 0) {
            inputContent = inputCharacter + inputContent;
        }
        else {
            std::string newString;
            for (int i = 0; i < cursorPosition; i++)
                newString.push_back(inputContent[i]);
            newString.push_back(inputCharacter);
            for (int i = cursorPosition; i < (int) inputContent.size(); i++) {
                newString.push_back(inputContent[i]);
            }
            inputContent = newString;
        }
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
    myTextCursor.cursorPosition = (int) inputString.size();
}

std::pair <int, int> textBox::getInputDataPair() {
    std::string inputString = myTextCursor.getInputContent();
    inputString.push_back(',');
    std::string inputValue;
    int n = 2, countNum = 0, index = 0, element = 0;
    for (int i = 0; i < (int) inputString.size(); i++) {
        if (inputString[i] == ',') {
            countNum++;
            std::reverse(inputValue.begin(), inputValue.end());
            int input = 0, mul10 = 1;
            if ((int) inputValue.size() > 2)
                break;
            for (int i = 0; i < (int) inputValue.size(); i++) {
                input += mul10 * ((int) inputValue[i] - '0');
                mul10 *= 10;
            }
            if (countNum == 1)
                index = input;
            else if (countNum == 2)
                element = input;
            else if (countNum > 2)
                break;       
            while(!inputValue.empty())
                inputValue.pop_back();
        }
        else {
            inputValue.push_back(inputString[i]);
        }
    }
    return std::pair<int, int> (index, element);
}
int textBox::getInputDataInt() {
    std::string inputString = myTextCursor.getInputContent();
    std::string inputValue = inputString;
    std::reverse(inputValue.begin(), inputValue.end());
    int mul = 1, value = 0;
    if ((int) inputValue.size() > 2)
        return value;
    for (int i = 0; i < (int) inputValue.size(); i++) {
        value += mul * ((int) inputValue[i] - '0');
        mul *= 10;
    }
    return value;
}


void textBox::processKeyboardEvent(sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)){
            char inputCharacter = (char) event.text.unicode;
            userInputCharacter(inputCharacter);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Backspace) {
            userBackspace();
        }
        else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            userMoveCursor(event.key.code);
        }
        else if (event.key.code == sf::Keyboard::Delete) {
            userDelete();
        }
    }
}


void textBox::drawTextBox(sf::RenderWindow &window) {
    textBoxButton.drawButton(window);
    myTextCursor.drawTextOnBox(window);
    if (isClicked) {
        myTextCursor.drawTextCursor(window);
    }
}