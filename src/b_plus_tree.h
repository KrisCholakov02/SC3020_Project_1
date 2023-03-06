#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include "tree_node.h"
#include "block.h"

class BPlusTree
{
    Node *root;
    int numNodes;
    int numDeletes;
    int maxSize;

    Node* findParent(Node*,Node*);
    void insertInternal(Node*,Node*,int);
    void removeInternal(Node*,Node*,int);
public:
    BPlusTree(int MAX);
    void search(int);
    void searchRange(int, int);
    void insert(int, Block* block);
    void remove(int);
    Node* getRoot();
    int getNumNodes();
    int getNumDeletes();
    Node* getFirstChild(Node*);
    int getHeight(Node*);
    void printNode(Node*);
};

#endif
