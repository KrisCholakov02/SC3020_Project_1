#include "b_plus_tree.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <set>

using namespace std;

BPlusTree::BPlusTree(int max) {
    root = NULL;
    numNodes = 0;
    numDeletes = 0;
    maxSize = max;
}

void BPlusTree::search(int target) {
    if (root == NULL) {
        cout << "The tree is empty\n";
    } else {
        Node *current = root;
        int nodeAccessed = 1;

        cout << "Index Blocks Accessed: " << endl;
        while (current->isLeafNode == false) {
            if (nodeAccessed < 6) {
                cout << "Index block: " << nodeAccessed << endl;
                for (int i = 0; i < current->size; i++) {
                    cout << current->key[i] << '|';
                }
                cout << "\n";
            }
            for (int i = 0; i < current->size; i++) {
                if (target < current->key[i]) {
                    current = current->children[i];
                    nodeAccessed++;
                    break;
                }
                if (i == current->size - 1) {
                    current = current->children[i + 1];
                    nodeAccessed++;
                    break;
                }
            }
        }
        if (nodeAccessed < 6) {
            cout << "Index block: " << nodeAccessed << endl;
            for (int i = 0; i < current->size; i++) {
                cout << current->key[i] << '|';
            }
            cout << "\n";
        }

        cout << "Number of Index Blocks Accessed:" << endl;
        cout << "Index block accessed: " << nodeAccessed << endl;
        for (int i = 0; i < current->size; i++) {
            if (current->key[i] == target) {
                set<Block *> set = {current->pointer[i]};
                if (current->linkedList[i] != NULL) {
                    LinkedList *linkedList = current->linkedList[i];
                    set.insert(linkedList->pointToBlock);

                    while (linkedList->nextLL != NULL) {
                        linkedList = linkedList->nextLL;
                        set.insert(linkedList->pointToBlock);
                    }

                }

                std::set<Block *>::iterator itr;
                Block *blkContainingKeys;
                std::vector<Record> arrRecords;
                float avgRating;
                string tconst;
                int numVotes;
                float sum = 0;
                float cnt = 0;

                for (itr = set.begin();
                     itr != set.end(); itr++) {
                    blkContainingKeys = *(itr);
                    arrRecords = blkContainingKeys->retrieveRecords(target);

                    for (int j = 0; j < arrRecords.size(); j++) {
                        avgRating = arrRecords[j].retrieveAverageRating();
                        sum += avgRating;
                        cnt++;
                    }
                }

                float avg = sum / cnt;
                int dataCnt = 1;

                cout << "Number of Data Blocks Accessed" << endl;
                cout << "Data Blocks Accessed: " << set.size() << endl;
                cout << "Data Blocks Accessed:" << endl;
                for (itr = set.begin();
                     itr != set.end(); itr++) {
                    if (dataCnt < 6) {
                        blkContainingKeys = *(itr);
                        arrRecords = blkContainingKeys->retrieveRecords(target);

                        cout << "Data Block: " << dataCnt << endl;

                        for (int j = 0; j < arrRecords.size(); j++) {
                            avgRating = arrRecords[j].retrieveAverageRating();
                            tconst = arrRecords[j].retrieveTCONST();
                            numVotes = arrRecords[j].retrieveNumVotes();

                            cout << avgRating << endl;
                            cout << tconst << endl;
                            cout << numVotes << endl;
                        }
                    } else {
                        break;
                    }
                    dataCnt++;
                }
                cout << "Average of averageRating" << endl;
                cout << "Avg. avgRating = " << avg << endl;

                return;
            }
        }
        cout << "Target not found\n";
    }
}

void BPlusTree::searchRange(int startInt, int endInt) {
    if (root == NULL) {
        cout << "The tree is empty\n";
    } else {
        Node *current = root;
        int nodeAccessed = 1;

        cout << "Index Blocks Accessed" << endl;
        while (current->isLeafNode == false) {
            if (nodeAccessed < 6) {
                cout << "Index block: " << nodeAccessed << endl;
                for (int i = 0; i < current->size; i++) {
                    cout << current->key[i] << '|';
                }
                cout << "\n";
            }
            for (int i = 0; i < current->size; i++) {
                if (startInt < current->key[i]) {
                    current = current->children[i];
                    nodeAccessed++;
                    break;
                }
                if (i == current->size - 1) {
                    current = current->children[i + 1];
                    nodeAccessed++;
                    break;
                }
            }
        }
        if (nodeAccessed < 6) {
            cout << "Index block: " << nodeAccessed << endl;
            for (int i = 0; i < current->size; i++) {
                cout << current->key[i] << '|';
            }
            cout << "\n";
        }

        std::set<Block *> set;
        std::set<Block *> overallSet = {};
        std::set<Block *>::iterator itr;
        Block *blkContainingKeys;
        std::vector<Record> arrRecords;
        float avgRating;
        string tconst;
        int numVotes;
        float sum = 0;
        float cnt = 0;
        int dataCnt = 1;

        while (current->key[0] <= endInt) {
            for (int i = 0; i < current->size; i++) {
                if (current->key[i] >= startInt && current->key[i] <= endInt) {
                    set = {current->pointer[i]};
                    overallSet.insert(current->pointer[i]);

                    if (current->linkedList[i] != NULL) {
                        LinkedList *linkedList = current->linkedList[i];
                        set.insert(linkedList->pointToBlock);
                        overallSet.insert(linkedList->pointToBlock);

                        while (linkedList->nextLL != NULL) {
                            linkedList = linkedList->nextLL;
                            set.insert(linkedList->pointToBlock);
                            overallSet.insert(linkedList->pointToBlock);
                        }

                    }

                    for (itr = set.begin();
                         itr != set.end(); itr++) {
                        blkContainingKeys = *(itr);
                        arrRecords = blkContainingKeys->retrieveRecords(current->key[i]);

                        cout << "Data Blocks Accessed" << endl;
                        for (int j = 0; j < arrRecords.size(); j++) {
                            if (dataCnt < 6) {
                                cout << "Data Block: " << dataCnt << endl;

                                avgRating = arrRecords[j].retrieveAverageRating();
                                tconst = arrRecords[j].retrieveTCONST();
                                numVotes = arrRecords[j].retrieveNumVotes();

                                cout << avgRating << endl;
                                cout << tconst << endl;
                                cout << numVotes << endl;
                            }

                            dataCnt++;
                            avgRating = arrRecords[j].retrieveAverageRating();
                            sum += avgRating;
                            cnt++;
                        }
                    }

                }
            }
            current = current->rightSib;
            nodeAccessed++;
            if (nodeAccessed < 6) {
                cout << "Index block: " << nodeAccessed << endl;
                for (int i = 0; i < current->size; i++) {
                    cout << current->key[i] << '|';
                }
                cout << "\n";
            }
        }
        float averageCalculation = sum / cnt;

        cout << "Index Blocks Accessed: " << nodeAccessed << endl;
        cout << "Data Blocks Accessed: " << overallSet.size() << endl;
        cout << "Average of averageRating: " << averageCalculation << endl;
    }
}

int BPlusTree::getNumNodes() {
    return numNodes;
}

int BPlusTree::getNumDeletes() {
    return numDeletes;
}

void BPlusTree::printNode(Node *cursor) {
    cursor->getContent();
    return;
}

Node *BPlusTree::getFirstChild(Node *cursor) {
    return cursor->children[0];
}

int BPlusTree::getHeight(Node *cursor) {
    int height = 0;
    while (!cursor->isLeafNode) {
        cursor = cursor->children[0];
        height++;
    }
    return height;
}

void BPlusTree::insert(int x, Block *block) {
    if (root == NULL) {
        root = new Node(maxSize);
        root->key[0] = x;
        root->isLeafNode = true;
        root->size = 1;
        root->pointer[0] = block;
        root->leftSib = NULL;
        root->rightSib = NULL;
        numNodes++;
        cout << "The block is inserted, key=" << x << "\n";
    } else {
        Node *current = root;
        Node *parent;

        while (current->isLeafNode == false) {
            parent = current;
            for (int i = 0; i < current->size; i++) {
                if (x < current->key[i]) {
                    current = current->children[i];
                    break;
                }
                if (i == current->size - 1) {
                    current = current->children[i + 1];
                    break;
                }
            }
        }

        for (int y = 0; y < current->size; y++) {
            if (current->key[y] == x) {
                cout << "Key already exists\n";
                LinkedList *newLL = new LinkedList;
                newLL->key = x;
                newLL->pointToBlock = block;

                if (current->linkedList[y] == NULL) {
                    current->linkedList[y] = newLL;
                } else {
                    LinkedList *linkedList;
                    linkedList = current->linkedList[y];
                    while (true) {
                        if (linkedList->nextLL == NULL) {
                            linkedList->nextLL = newLL;
                            break;
                        }
                        linkedList = linkedList->nextLL;
                    }
                }
                return;
            }
        }

        if (current->size < maxSize) {
            current->addKey(x, block);
        } else {
            cout << "Inserted key=" << x << " successfully\n";
            int tKeys[maxSize + 1];
            Block *tPtrs[maxSize + 1];
            LinkedList *virHolder[maxSize + 1];

            for (int i = 0; i < maxSize; i++) {
                tKeys[i] = current->key[i];
                tPtrs[i] = current->pointer[i];
                virHolder[i] = current->linkedList[i];
            }

            int i, m = 0;
            for (i = 0; i < maxSize; i++) {
                if (x <= tKeys[m]) {
                    for (int j = maxSize + 1; j > m; j--) {
                        tKeys[j] = tKeys[j - 1];
                        tPtrs[j] = tPtrs[j - 1];
                        virHolder[j] = virHolder[j - 1];
                    }
                    break;
                }
                m++;
            }
            tKeys[m] = x;
            tPtrs[m] = block;
            virHolder[m] = NULL;

            Node *newLeaf = new Node(maxSize);
            newLeaf->isLeafNode = true;
            numNodes++;

            current->size = (maxSize + 1) / 2;
            newLeaf->size = maxSize + 1 - current->size;

            if (current->rightSib != NULL) {
                newLeaf->rightSib = current->rightSib;
                newLeaf->leftSib = current;
                current->rightSib->leftSib = newLeaf;
                current->rightSib = newLeaf;
            } else {
                newLeaf->rightSib = current->rightSib;
                newLeaf->leftSib = current;
                current->rightSib = newLeaf;
            }

            int j = current->size;
            for (i = 0; i < newLeaf->size; i++) {
                newLeaf->key[i] = tKeys[j];
                newLeaf->pointer[i] = tPtrs[j];
                newLeaf->linkedList[i] = virHolder[i];
                j++;
            }
            for (i = 0; i < current->size; i++) {
                current->key[i] = tKeys[i];
                current->pointer[i] = tPtrs[i];
                current->linkedList[i] = virHolder[i];
            }

            if (current == root) {
                Node *newRoot = new Node(maxSize);
                newRoot->isLeafNode = false;
                newRoot->leftSib = NULL;
                newRoot->rightSib = NULL;
                newRoot->size = 1;
                newRoot->children[1] = newLeaf;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->children[0] = current;
                root = newRoot;
                numNodes++;
            } else {
                insertInternal(parent, newLeaf, newLeaf->key[0]);
            }
        }
    }

}

void BPlusTree::insertInternal(Node *current, Node *child, int x) {
    if (current->size < maxSize) {
        int i, m = 0;
        for (i = 0; i < current->size; i++) {
            if (x <= current->key[i]) {
                break;
            }
            m++;
        }

        for (int j = current->size + 1; j > m + 1; j--) {
            current->children[j] = current->children[j - 1];
        }

        for (int j = current->size; j > m; j--) {
            current->key[j] = current->key[j - 1];
        }
        current->size++;
        current->children[i + 1] = child;
        current->key[i] = x;
        cout << "Key is inserted into an internal node\n";
    } else {
        cout << "Key is inserted into an internal node\n";
        int tKeys[maxSize + 1];
        Node *tChildren[maxSize + 2];
        for (int i = 0; i < maxSize + 1; i++) {
            tChildren[i] = current->children[i];
        }
        for (int i = 0; i < maxSize; i++) {
            tKeys[i] = current->key[i];
        }
        int i, m = 0;
        for (i = 0; i < maxSize; i++) {
            if (x <= tKeys[i]) {
                break;
            }
            m++;
        }

        for (int j = maxSize + 2; j > m + 1; j--) {
            tChildren[j] = tChildren[j - 1];
        }

        for (int j = maxSize + 1; j > m; j--) {
            tKeys[j] = tKeys[j - 1];
        }
        tChildren[m + 1] = child;
        tKeys[m] = x;


        Node *internalNode = new Node(maxSize);
        numNodes++;
        internalNode->size = maxSize - (maxSize + 1) / 2;
        current->size = (maxSize + 1) / 2;
        internalNode->isLeafNode = false;
        internalNode->leftSib = NULL;
        internalNode->rightSib = NULL;


        int j = current->size + 1;
        for (i = 0; i < internalNode->size + 1; i++) {
            internalNode->children[i] = tChildren[j];
            j++;
        }
        j = current->size + 1;
        for (i = 0; i < internalNode->size; i++) {
            internalNode->key[i] = tKeys[j];
            j++;
        }
        if (current == root) {

            Node *newRoot = new Node(maxSize);
            newRoot->isLeafNode = false;
            newRoot->leftSib = NULL;
            newRoot->rightSib = NULL;
            newRoot->children[0] = current;
            newRoot->children[1] = internalNode;
            newRoot->key[0] = current->key[current->size];
            newRoot->size = 1;
            root = newRoot;
            numNodes++;
            cout << "New root created\n";
        } else {
            Node *parent = findParent(root, current);
            insertInternal(parent, internalNode, current->key[current->size]);
        }
    }
}

Node *BPlusTree::findParent(Node *current, Node *child) {
    Node *parent;
    if (current->isLeafNode || (current->children[0])->isLeafNode) {
        return NULL;
    }
    for (int i = 0; i < current->size + 1; i++) {
        if (current->children[i] == child) {
            parent = current;
            return parent;
        } else {
            parent = findParent(current->children[i], child);
            if (parent != NULL) {
                return parent;
            }
        }
    }
    return parent;
}

void BPlusTree::remove(int target) {
    if (root == NULL) {
        cout << "The tree is empty\n";
    } else {
        Node *current = root;
        Node *parent;
        int rIndex, lIndex;

        while (current->isLeafNode == false) {
            for (int i = 0; i < current->size; i++) {
                parent = current;
                lIndex = i - 1;
                rIndex = i + 1;
                if (target < current->key[i]) {
                    current = current->children[i];
                    break;
                }
                if (i == current->size - 1) {
                    current = current->children[i + 1];
                    rIndex = i + 2;
                    lIndex = i;
                    break;
                }
            }
        }
        bool found = false;
        int pos;
        for (pos = 0; pos < current->size; pos++) {
            if (current->key[pos] == target) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Target not found\n";
            return;
        }
        for (int i = pos; i < current->size; i++) {
            current->key[i] = current->key[i + 1];
            current->pointer[i] = current->pointer[i + 1];
            current->linkedList[i] = current->linkedList[i + 1];
        }
        current->size--;
        if (current == root) {
            cout << "Removed key=" << target << "\n";

            for (int i = 0; i < maxSize + 1; i++) {
                current->children[i] = NULL;
            }

            current->leftSib = NULL;
            current->rightSib = NULL;
            if (current->size == 0) {
                cout << "Tree is destroyed\n";
                delete[] current->key;
                delete[] current->children;
                delete[] current->pointer;
                delete[] current->linkedList;
                delete current;
                root = NULL;
                numNodes--;
                numDeletes++;
            }
            return;
        }

        cout << "Removed key=" << target << "\n";
        if (current->size >= (maxSize + 1) / 2) {
            return;
        }
        if (lIndex >= 0 &&
            parent->children[lIndex]->canLeafBorrow()) {
            Node *sibling = parent->children[lIndex];

            for (int i = current->size; i > 0; i--) {
                current->key[i] = current->key[i - 1];
                current->pointer[i] = current->pointer[i - 1];
                current->linkedList[i] = current->linkedList[i - 1];
            }
            current->size++;

            int leftMax = sibling->key[sibling->size - 1];
            current->key[0] = leftMax;
            current->linkedList[0] = sibling->linkedList[sibling->size - 1];
            current->pointer[0] = sibling->pointer[sibling->size - 1];

            sibling->size--;

            parent->key[lIndex] = current->key[0];
            cout << "Transferred key=" << current->key[0] << "\n";
            return;

        }
        if (rIndex <= parent->size &&
            parent->children[rIndex]->canLeafBorrow()) {
            Node *sibling = parent->children[rIndex];

            current->size++;

            int rightMin = sibling->key[0];
            current->key[current->size - 1] = rightMin;
            current->linkedList[current->size - 1] = sibling->linkedList[0];
            current->pointer[current->size - 1] = sibling->pointer[0];

            sibling->size--;

            for (int i = 0; i < sibling->size; i++) {
                sibling->key[i] = sibling->key[i + 1];
                sibling->linkedList[i] = sibling->linkedList[i + 1];
                sibling->pointer[i] = sibling->pointer[i + 1];
            }

            parent->key[rIndex - 1] = sibling->key[0];
            cout << "Transferred key=" << current->key[current->size - 1] << "\n";
            return;
        }
        if (lIndex >= 0) {
            Node *sibling = parent->children[lIndex];

            int j = sibling->size;
            for (int i = 0; i < current->size; i++) {
                sibling->key[j] = current->key[i];
                sibling->linkedList[j] = current->linkedList[i];
                sibling->pointer[j] = current->pointer[i];
                j++;
            }

            if (current->rightSib != NULL) {
                sibling->rightSib = current->rightSib;
                current->rightSib->leftSib = sibling;
                current->leftSib = NULL;
                current->rightSib = NULL;
            } else {
                sibling->rightSib = current->rightSib;
                current->leftSib = NULL;
                current->rightSib = NULL;
            }

            int increaseSize = current->size;
            sibling->size += increaseSize;

            numNodes--;
            numDeletes++;
            removeInternal(current, parent, parent->key[lIndex]);
        } else if (rIndex <= parent->size) {
            Node *sibling = parent->children[rIndex];

            for (int i = current->size, j = 0; j < sibling->size; i++, j++) {
                current->key[i] = sibling->key[j];
                current->linkedList[i] = sibling->linkedList[j];
                current->pointer[i] = sibling->pointer[j];
            }

            current->size += sibling->size;

            if (sibling->rightSib != NULL) {
                current->rightSib = sibling->rightSib;
                sibling->rightSib->leftSib = current;
                sibling->leftSib = NULL;
                sibling->rightSib = NULL;
            } else {
                current->rightSib = sibling->rightSib;
                sibling->leftSib = NULL;
                sibling->rightSib = NULL;
            }

            numNodes--;
            numDeletes++;
            removeInternal(sibling, parent, parent->key[rIndex - 1]);

        }
    }
}

void BPlusTree::removeInternal(Node *child, Node *current, int target) {

    if (current == root) {
        if (current->size == 1) {

            if (current->children[1] == child) {
                delete[] child->key;
                delete[] child->children;
                delete[] child->pointer;
                delete[] child->linkedList;
                delete child;
                numNodes--;
                numDeletes++;
                root = current->children[0];
                root->leftSib = NULL;
                root->rightSib = NULL;
                delete[] current->key;
                delete[] current->children;
                delete[] current->pointer;
                delete[] current->linkedList;
                delete current;
                numNodes--;
                numDeletes++;
                cout << "Root node changed\n";
                return;
            } else if (current->children[0] == child) {
                delete[] child->key;
                delete[] child->children;
                delete[] child->pointer;
                delete[] child->linkedList;
                delete child;
                numNodes--;
                numDeletes++;
                root = current->children[1];
                root->leftSib = NULL;
                root->rightSib = NULL;
                delete[] current->key;
                delete[] current->children;
                delete[] current->pointer;
                delete[] current->linkedList;
                delete current;
                numNodes--;
                numDeletes++;
                cout << "Root node changed\n";
                return;
            }
        }
    }
    int position;

    current->delKeyInternal(child, target);

    if (current->size >= (maxSize + 1) / 2 - 1) {
        cout << "Deleted key=" << target << "\n";
        return;
    }

    if (current == root) {
        return;
    }
    Node *parent = findParent(root, current);
    int rIndex, lIndex;

    for (position = 0; position < parent->size + 1; position++) {
        if (parent->children[position] == current) {
            lIndex = position - 1;
            rIndex = position + 1;
            break;
        }
    }
    if (lIndex >= 0 && parent->children[lIndex]->canInternalBorrow()) {
        Node *sibling = parent->children[lIndex];

        for (int i = current->size + 1; i > 0; i--) {
            current->children[i] = current->children[i - 1];
        }
        for (int i = current->size; i > 0; i--) {
            current->key[i] = current->key[i - 1];
        }

        current->children[0] = sibling->children[sibling->size];

        current->key[0] = parent->key[lIndex];
        parent->key[lIndex] = sibling->key[sibling->size - 1];

        sibling->size--;
        current->size++;
        return;

    }
    if (rIndex <= parent->size &&
        parent->children[rIndex]->canInternalBorrow()) {
        Node *sibling = parent->children[rIndex];

        current->children[current->size + 1] = sibling->children[0];
        for (int i = 0; i < sibling->size; ++i) {
            sibling->children[i] = sibling->children[i + 1];
        }

        current->key[current->size] = parent->key[position];
        parent->key[position] = sibling->key[0];
        for (int i = 0; i < sibling->size - 1; i++) {
            sibling->key[i] = sibling->key[i + 1];
        }
        sibling->size--;
        current->size++;
        return;
    }
    if (lIndex >= 0) {

        Node *sibling = parent->children[lIndex];
        sibling->key[sibling->size] = parent->key[lIndex];
        int i = sibling->size + 1;
        for (int j = 0; j < current->size + 1; j++) {
            sibling->children[i] = current->children[j];
            current->children[j] = NULL;
        }
        for (int j = 0; j < current->size; j++) {
            sibling->key[i] = current->key[j];
        }
        sibling->size += current->size + 1;
        current->size = 0;

        numNodes--;
        numDeletes++;
        removeInternal(current, parent, parent->key[lIndex]);
    } else if (rIndex <= parent->size) {

        Node *sibling = parent->children[rIndex];
        current->key[current->size] = parent->key[rIndex - 1];
        int i = current->size + 1;
        for (int j = 0; j < sibling->size + 1; j++) {
            current->children[i] = sibling->children[j];
            sibling->children[j] = NULL;
        }
        for (int j = 0; j < sibling->size; j++) {
            current->key[i] = sibling->key[j];
        }
        current->size += sibling->size + 1;
        sibling->size = 0;
        numNodes--;
        numDeletes++;
        removeInternal(sibling, parent, parent->key[rIndex - 1]);
    }
}

Node *BPlusTree::getRoot() {
    return root;
}
