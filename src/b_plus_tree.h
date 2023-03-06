#ifndef CZ4031_DB_PROJECT_MASTER_BPTREE_H
#define CZ4031_DB_PROJECT_MASTER_BPTREE_H

#include "tree_node.h"
#include "block.h"

class BPlusTree
{
    Node *root;
    void insertInternal(Node*,Node*,int);
    void removeInternal(Node*,Node*,int);
    Node* findParent(Node*,Node*);
    int numNodes;
    int numDeleteions;
    int MAX;

public:
    BPlusTree(int MAX);
    void search(int);
    void searchRange(int, int);
    void insert(int, Block* block);
    void remove(int);
    Node* getRoot();
    int getNumOfNodes();
    int getNumDeletion();
    void printNode(Node*);
    Node* getFirstChild(Node*);
    int getHeight(Node*);
};


#endif //CZ4031_DB_PROJECT_MASTER_BPTREE_H
