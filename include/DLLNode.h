#ifndef DLLNODE_H
#define DLLNODE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "arrow.h"
#include "text.h"

struct DLLNode {
    int data, nodeColor;
    DLLNode *nxt, *prv;

    DLLNode ();
    DLLNode (int data);
};

#endif