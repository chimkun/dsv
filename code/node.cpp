#include "node.h"

Node::Node() {
    data = -1;
    pNext = nullptr;
}
Node::Node(int data) {
    this->data = data;
    pNext = nullptr;
}