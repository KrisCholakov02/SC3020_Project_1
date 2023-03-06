#ifndef CZ4031_DB_PROJECT_MASTER_LL_H
#define CZ4031_DB_PROJECT_MASTER_LL_H


#include "block.h"

class LinkedList
{
    int key;
    Block* pointToBlock;
    LinkedList* nextLL;
    friend class Node;
    friend class BPlusTree;
public:
    LinkedList() {
        pointToBlock = NULL;
        nextLL = NULL;
    };
};


#endif //CZ4031_DB_PROJECT_MASTER_LL_H
