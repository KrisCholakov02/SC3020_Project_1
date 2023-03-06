#ifndef CZ4031_DB_PROJECT_MASTER_NODE_H
#define CZ4031_DB_PROJECT_MASTER_NODE_H


#include "block.h"
#include "linked_list.h"

class Node
{
    bool isLeaf;
    int *key, size;
    Node** children;
    Block** ptr;
    LL** LLholder;
    Node* leftSib;
    Node* rightSib;
    friend class BPTree;
    int MAX;
    void delKeyInternal(Node* child, int x);

public:
    Node(int MAX);
    bool canLeafBorrow();
    bool canInternalBorrow();
    bool canLeafMerge();
    bool canInternalMerge();
    bool addKey(int k, Block* block);
    void getContent();
};


#endif //CZ4031_DB_PROJECT_MASTER_NODE_H
