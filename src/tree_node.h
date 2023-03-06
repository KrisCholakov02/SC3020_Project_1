#ifndef CZ4031_DB_PROJECT_MASTER_NODE_H
#define CZ4031_DB_PROJECT_MASTER_NODE_H


#include "block.h"
#include "linked_list.h"

class Node
{
    bool isLeafNode;
    int *key;
    int size;
    Node** children;
    Block** pointer;
    LinkedList** linkedList;
    Node* leftSib;
    Node* rightSib;
    friend class BPlusTree;
    int maxSize;
    void delKeyInternal(Node* child, int target);

public:
    Node(int MAX);
    bool canLeafBorrow();
    bool canInternalBorrow();
    bool canLeafMerge();
    bool canInternalMerge();
    bool addKey(int newKey, Block* block);
    void getContent();
};


#endif //CZ4031_DB_PROJECT_MASTER_NODE_H
