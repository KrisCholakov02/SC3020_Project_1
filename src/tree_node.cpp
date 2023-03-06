#include "tree_node.h"

TreeNode::TreeNode(int max) {
    //dynamic memory allocation
    MAX = max;
    key = new int[MAX];
    children = new TreeNode *[MAX + 1];
    ptr = new Block *[MAX + 1];
    LLholder = new LL *[MAX + 1];
}

void TreeNode::getContent() {
    for (int i = 0; i < size; i++) {
        cout << key[i] << '|';
    }
}

bool TreeNode::canLeafBorrow() {
    return size >= (MAX + 1) / 2 + 1;
}

bool TreeNode::canInternalBorrow() {
    return size >= (MAX + 1) / 2;
}

bool TreeNode::addKey(int x, Block *block) {

    if (x >= key[size - 1]) {
        key[size] = x;
        ptr[size] = block;
        LLholder[size] = NULL;
        size++;
        cout << "Inserted " << x << " successfully\n";
    } else {
        int i, m = 0;
        for (i = 0; i < size; i++) {
            if (x <= key[i]) {
                break;
            }
            m++;
        }

        for (int j = size; j > m; j--) {
            key[j] = key[j - 1];
            ptr[j] = ptr[j - 1];
            LLholder[j] = LLholder[j - 1];
        }
        key[m] = x;
        ptr[m] = block;
        LLholder[m] = NULL;
        size++;
        cout << "Inserted " << x << " successfully\n";
    }

    return true;
}

void TreeNode::delKeyInternal(TreeNode *child, int x) {
    int pos;
    //Deleting the pointer child
    for (int j = 0; j < size + 1; j++) {
        if (children[j] == child) {
            pos = j;
        }
    }
    for (int i = pos; i < size + 1; i++) {
        children[i] = children[i + 1];
    }
    for (int j = 0; j < size; j++) {
        if (key[j] == x) {
            pos = j;
        }
    }
    for (int i = pos; i < size; i++) {
        key[i] = key[i + 1];
    }
    size--;
};
