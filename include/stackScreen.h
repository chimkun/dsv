#ifndef STACKSCREEN_H
#define STACKSCREEN_H

#include <vector>
#include "constants.h"
#include "stackNode.h"

class stackClass {
private:
    std::vector <int> Stack;
    stackNode node;    
public:
    stackClass();

    void createStack(std::vector <int> &input);
    int peekStack();
    void pushStack(int data);
    void popStack();
    void clearStack();
    int getStackSize();

    std::vector <int> getStack();

    void drawStack(sf::RenderWindow &window, int opacity);
    void drawStackPeek(sf::RenderWindow &window, sf::Color peekColor);
    void drawStackPush(sf::RenderWindow &window, int extraYDistance, int opacity);
    void drawStackPop(sf::RenderWindow &window, int popNodeOpacity);
};

#endif