#ifndef COMMONOBJECTS_H
#define COMMONOBJECTS_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const std::string& text, const sf::Vector2f& size, const sf::Font& font);
    void setPosition(const sf::Vector2f& position);
    bool isPressed(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape m_button;
    sf::Text m_text;
};

Button::Button(const std::string& text, const sf::Vector2f& size, const sf::Font& font) {
    m_button.setSize(size);
    m_button.setFillColor(sf::Color::White);
    m_button.setOutlineColor(sf::Color::Black);
    m_button.setOutlineThickness(1.f);

    m_text.setString(text);
    m_text.setFont(font);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Black);
}

void Button::setPosition(const sf::Vector2f& position) {
    m_button.setPosition(position);
    m_text.setPosition(position.x + 10, position.y + 10);
}

bool Button::isPressed(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPos = m_button.getPosition();
    sf::Vector2f buttonSize = m_button.getSize();

    return (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
            mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(m_button);
    window.draw(m_text);
}


#endif