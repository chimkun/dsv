#include "buttonAndTextBox.h"

buttonAndTextBox::buttonAndTextBox() {

}
buttonAndTextBox::buttonAndTextBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string buttonTextContent) {
    this->myButton = button(buttonPosition, buttonTexture, buttonTextContent);
}
buttonAndTextBox::buttonAndTextBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string buttonTextContent,
                                   sf::Vector2f textBoxButtonPosition, sf::Texture &textBoxTexture) {
    this->myButton = button(buttonPosition, buttonTexture, buttonTextContent);
    this->myTextBox = textBox(textBoxButtonPosition, textBoxTexture);
    std::string confirmString = "go!";
    sf::Vector2f diffDistance(textBoxTexture.getSize().x + 20, 1);
    this->confirmButton = button(textBoxButtonPosition + diffDistance, textBoxTexture, confirmString);
}

bool buttonAndTextBox::buttonIsClick(sf::RenderWindow &window) {
    return myButton.buttonIsClick(window);
}
bool buttonAndTextBox::textBoxIsClick(sf::RenderWindow &window) {
    return myTextBox.textBoxButtonIsClick(window);
}

bool buttonAndTextBox::buttonIsChoose() {
    return myButton.isChosen();
}
bool buttonAndTextBox::textBoxIsChoose() {
    return myTextBox.textBoxIsClick();
}
bool buttonAndTextBox::confirmButtonIsClick(sf::RenderWindow &window) {
    return confirmButton.buttonIsClick(window);
}
void buttonAndTextBox::flipButtonState() {
    myButton.flipChoose();
}
void buttonAndTextBox::flipInputBoxState() {
    myTextBox.flipTextBoxState();
}
void buttonAndTextBox::offInputBoxState() {
    myTextBox.offTextBoxState();
}
void buttonAndTextBox::onInputBoxState() {
    if (!myTextBox.textBoxIsClick())
        flipInputBoxState();
}


bool buttonAndTextBox::inputIsEmpty() {
    return myTextBox.inputIsEmpty();
}
std::string buttonAndTextBox::getInputString() {
    return myTextBox.getTextBoxString();
}
std::pair <int, int> buttonAndTextBox::getInputDataPair() {
    std::string inputString = myTextBox.getTextBoxString();
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
int buttonAndTextBox::getInputDataInt() {
    std::string inputString = myTextBox.getTextBoxString();
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

void buttonAndTextBox::userInputCharacter(char inputCharacter) {
    myTextBox.userInputCharacter(inputCharacter);
}
void buttonAndTextBox::userBackspaceCharacter() {
    myTextBox.userBackspace();
}
void buttonAndTextBox::userDeleteCharacter() {
    myTextBox.userDelete();
}
void buttonAndTextBox::userMoveCursor(int arrowKeyCode) {
    myTextBox.userMoveCursor(arrowKeyCode);
}

void buttonAndTextBox::processKeyboardEvent(sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 44 || (event.text.unicode >= 48 && event.text.unicode <= 57)){
            char inputCharacter = (char) event.text.unicode;
            myTextBox.userInputCharacter(inputCharacter);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Backspace) {
            myTextBox.userBackspace();
        }
        else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            myTextBox.userMoveCursor(event.key.code);
        }
        else if (event.key.code == sf::Keyboard::Delete) {
            myTextBox.userDelete();
        }
    }
}


void buttonAndTextBox::moveButtonWhenHover(sf::RenderWindow &window) {
    myButton.moveButtonWhenHover(window);
}
void buttonAndTextBox::drawButton(sf::RenderWindow &window) {
    myButton.drawButton(window);
    if (myButton.isChosen()) {
        myTextBox.drawTextBox(window);
        confirmButton.drawButton(window, 0.33, 0.14, 21);
    }
}