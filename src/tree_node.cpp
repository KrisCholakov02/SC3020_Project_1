#include "tree_node.h"
#include "block.h"
#include "linked_list.h"

Node::Node(int max) {
    maxSize = max;
    key = new int[maxSize];
    children = new Node *[maxSize + 1];
    pointer = new Block *[maxSize + 1];
    linkedList = new LinkedList *[maxSize + 1];
}

void Node::getContent() {
    for (int i = 0; i < size; i++) {
        cout << key[i] << '|';
    }
}


bool Node::canLeafBorrow() {
    return size >= (maxSize + 1) / 2 + 1;
}

bool Node::canInternalBorrow() {
    return size >= (maxSize + 1) / 2;
}


bool Node::addKey(int x, Block *block) {
    if (x >= key[size - 1]) {
        key[size] = x;
        pointer[size] = block;
        linkedList[size] = NULL;
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
            pointer[j] = pointer[j - 1];
            linkedList[j] = linkedList[j - 1];
        }
        key[m] = x;
        pointer[m] = block;
        linkedList[m] = NULL;
        size++;
        cout << "Inserted " << x << " successfully\n";
    }

    return true;
}

void Node::delKeyInternal(Node *child, int x) {
    int pos;
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