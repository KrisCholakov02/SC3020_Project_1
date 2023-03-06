#ifndef B_TREE_TREE_NODE_H
#define B_TREE_TREE_NODE_H

#include "block.h"
#include "tree_node.h"
#include "linked_list.h"
#include "b_plus_tree.h"

class TreeNode {
    bool isLeaf;
    int *key, size;
    TreeNode **children;
    Block **ptr;
    LL **LLholder;
    TreeNode *leftSib;
    TreeNode *rightSib;
    int MAX;

    void delKeyInternal(TreeNode *child, int x);
    friend class BPTree;
public:
    TreeNode(int MAX);

    bool canLeafBorrow();

    bool canInternalBorrow();

    bool canLeafMerge();

    bool canInternalMerge();

    bool addKey(int k, Block *block);

    void getContent();
};


#endif //B_TREE_TREE_NODE_H
