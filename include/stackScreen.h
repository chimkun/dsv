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

    void drawStackPush(sf::RenderWindow &window, int extraYDistance, int opacity);
};

#endif