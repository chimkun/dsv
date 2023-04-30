#include "stackScreen.h"

stackClass::stackClass() {
    int n = rand() % 5 + 3;
    Stack.clear();
    for (int i = 0; i < n; i++) {
        int u = rand() % 100;
        Stack.push_back(u);
    }
}

void stackClass::createStack(std::vector <int> &input) {
    Stack = input;
}
int stackClass::peekStack() {
    if (!Stack.empty())
        return Stack[(int) Stack.size() - 1];
    return -1;
}
void stackClass::popStack() {
    if (!Stack.empty())
        Stack.pop_back();
}
void stackClass::pushStack(int data) {
    Stack.push_back(data);
}
void stackClass::clearStack() {
    Stack.clear();
}

void stackClass::drawStackPush(sf::RenderWindow &window, int extraYDistance, int opacity) {
    for (int i = 0; i < (int) Stack.size() - 1; i++) {
        sf::Vector2f nodePosition = stackConstants::bottomStack;
        nodePosition -= sf::Vector2f(0, stackConstants::yDistance * i);
        node.drawStackNode(window, nodePosition, Stack[i]);
    }
    sf::Vector2f addPosition = stackConstants::bottomStack;
    addPosition -= sf::Vector2f(0, stackConstants::yDistance * ((int) Stack.size() - 1) + extraYDistance);
    node.drawStackNode(window, addPosition, Stack[(int) Stack.size() - 1], opacity);
}