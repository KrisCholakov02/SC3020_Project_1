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

bool Node::addKey(int newKey, Block *block) {
    if (newKey >= key[size - 1]) {
        key[size] = newKey;
        pointer[size] = block;
        linkedList[size] = NULL;
        size++;
        cout << "Inserted " << newKey << " successfully\n";
    } else {
        int i, t = 0;
        for (i = 0; i < size; i++) {
            if (newKey <= key[i]) {
                break;
            }
            t++;
        }

        for (int j = size; j > t; j--) {
            key[j] = key[j - 1];
            pointer[j] = pointer[j - 1];
            linkedList[j] = linkedList[j - 1];
        }
        key[t] = newKey;
        pointer[t] = block;
        linkedList[t] = NULL;
        size++;
        cout << "Inserted " << newKey << " successfully\n";
    }

    return true;
}

void Node::delKeyInternal(Node *child, int target) {
    int position;
    for (int j = 0; j < size + 1; j++) {
        if (children[j] == child) {
            position = j;
        }
    }
    for (int i = position; i < size + 1; i++) {
        children[i] = children[i + 1];
    }
    for (int j = 0; j < size; j++) {
        if (key[j] == target) {
            position = j;
        }
    }
    for (int i = position; i < size; i++) {
        key[i] = key[i + 1];
    }
    size--;
};