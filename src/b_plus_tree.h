#ifndef B_TREE_B_PLUS_TREE_H
#define B_TREE_B_PLUS_TREE_H

#include "tree_node.h"

class BPTree {
    TreeNode *root;

    void insertInternal(TreeNode *, TreeNode *, int);

    void removeInternal(TreeNode *, TreeNode *, int);

    TreeNode *findParent(TreeNode *, TreeNode *);

    int numOfNodes;
    int numOfDeletion;
    int MAX;
public:
    BPTree(int max);

    void search(int);

    void searchRange(int, int);

    void insert(int, Block *block);

    void remove(int);

    TreeNode *getRoot();

    int getNumOfNodes();

    int getNumDeletion();

    void printNode(TreeNode *);

    TreeNode *getFirstChild(TreeNode *);

    int getHeight(TreeNode *);
};


#endif //B_TREE_B_PLUS_TREE_H
