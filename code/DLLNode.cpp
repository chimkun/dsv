#include "DLLNode.h"

DLLNode::DLLNode() {
    data = -1;
    nodeColor = rand() % 4;
    this->nxt = nullptr;
    this->prv = nullptr;
}
DLLNode::DLLNode(int data) {
    this->data = data;
    nodeColor = rand() % 4;
    this->nxt = nullptr;
    this->prv = nullptr;
}