#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "arrow.h"

struct Node {
    int data;
    Node *pNext;
    Node();
    Node(int data);
};

#endif