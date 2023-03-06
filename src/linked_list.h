#ifndef CZ4031_DB_PROJECT_MASTER_LL_H
#define CZ4031_DB_PROJECT_MASTER_LL_H


#include "block.h"

class LL
{
    int key;
    Block* pointToBlock;
    LL* nextLL;
    friend class Node;
    friend class BPlusTree;
public:
    LL() {
        pointToBlock = NULL;
        nextLL = NULL;
    };
};


#endif //CZ4031_DB_PROJECT_MASTER_LL_H
