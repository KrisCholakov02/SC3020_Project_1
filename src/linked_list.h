#ifndef B_TREE_LINKED_LIST_H
#define B_TREE_LINKED_LIST_H

#include "block.h"

class LL {
    int key;
    Block *pointToBlock;
    LL *nextLL;

    friend class Node;

    friend class BPTree;

public:
    LL() {
        pointToBlock = NULL;
        nextLL = NULL;
    }
};

#endif //B_TREE_LINKED_LIST_H
