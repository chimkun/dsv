#ifndef BUTTONANDTEXTBOX_H
#define BUTTONANDTEXTBOX_H

#include <SFML/Graphics.hpp>
#include <string>
#include "button.h"
#include "textbox.h"

class buttonAndTextBox {
private:
    button myButton, confirmButton;
    textBox myTextBox;
    std::string textBoxContent;
public:
    buttonAndTextBox();
    buttonAndTextBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string buttonTextContent);
    buttonAndTextBox(sf::Vector2f buttonPosition, sf::Texture &buttonTexture, std::string buttonTextContent,
                     sf::Vector2f textBoxButtonPosition, sf::Texture &textBoxTexture);
    bool buttonIsClick(sf::RenderWindow &window);
    bool textBoxIsClick(sf::RenderWindow &window);

    bool buttonIsChoose();
    bool textBoxIsChoose();
    bool confirmButtonIsClick(sf::RenderWindow &window);
    void flipButtonState();
    void flipInputBoxState();
    void offInputBoxState();
    void onInputBoxState();

    bool inputIsEmpty();
    std::string getInputString();
    void setInputString(std::string &inputString);
    std::pair<int, int> getInputDataPair();
    int getInputDataInt();
    
    void userInputCharacter(char inputCharacter);
    void userBackspaceCharacter();
    void userDeleteCharacter();
    void userMoveCursor(int arrowKeyCode);
    void drawChooseCreateScreen(sf::RenderWindow &window);

    void processKeyboardEvent(sf::Event &event);

    void moveButtonWhenHover(sf::RenderWindow &window);
    void drawButton(sf::RenderWindow &window);
};

#endif