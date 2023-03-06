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
                float count = 0;


                for (itr = set.begin();
                     itr != set.end(); itr++) {
                    blkContainingKeys = *(itr);
                    arrRecords = blkContainingKeys->retrieveRecords(target);

                    for (int j = 0; j < arrRecords.size(); j++) {
                        avgRating = arrRecords[j].retrieveAverageRating();
                        sum += avgRating;
                        count++;
                    }
                }

                float averageCalculation = sum / count;
                int dataCount = 1;

                cout << "Number of Data Blocks Accessed" << endl;
                cout << "Data Blocks Accessed: " << set.size() << endl;
                cout << "Data Blocks Accessed:" << endl;
                for (itr = set.begin();
                     itr != set.end(); itr++) {
                    if (dataCount < 6) {
                        blkContainingKeys = *(itr);
                        arrRecords = blkContainingKeys->retrieveRecords(target);

                        cout << "Data Block: " << dataCount << endl;

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
                    dataCount++;
                }
                cout << "Average of averageRating" << endl;
                cout << "Avg. avgRating = " << averageCalculation << endl;

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
        Node *cursor = root;
        int nodeAccessed = 1;

        cout << "Index Blocks Accessed" << endl;
        while (cursor->isLeafNode == false) {
            if (nodeAccessed < 6) {
                cout << "Index block: " << nodeAccessed << endl;
                for (int i = 0; i < cursor->size; i++) {
                    cout << cursor->key[i] << '|';
                }
                cout << "\n";
            }
            for (int i = 0; i < cursor->size; i++) {
                if (startInt < cursor->key[i]) {
                    cursor = cursor->children[i];
                    nodeAccessed++;
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->children[i + 1];
                    nodeAccessed++;
                    break;
                }
            }
        }
        if (nodeAccessed < 6) {
            cout << "Index block: " << nodeAccessed << endl;
            for (int i = 0; i < cursor->size; i++) {
                cout << cursor->key[i] << '|';
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
        float count = 0;
        int dataCount = 1;

        while (cursor->key[0] <= endInt) {
            for (int i = 0; i < cursor->size; i++) {
                if (cursor->key[i] >= startInt && cursor->key[i] <= endInt) {

                    set = {cursor->pointer[i]};
                    overallSet.insert(cursor->pointer[i]);

                    if (cursor->linkedList[i] != NULL) {
                        LinkedList *linkedList = cursor->linkedList[i];
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
                        arrRecords = blkContainingKeys->retrieveRecords(cursor->key[i]);

                        cout << "Data Blocks Accessed" << endl;
                        for (int j = 0; j < arrRecords.size(); j++) {
                            if (dataCount < 6) {
                                cout << "Data Block: " << dataCount << endl;

                                avgRating = arrRecords[j].retrieveAverageRating();
                                tconst = arrRecords[j].retrieveTCONST();
                                numVotes = arrRecords[j].retrieveNumVotes();

                                cout << avgRating << endl;
                                cout << tconst << endl;
                                cout << numVotes << endl;

                            }
                            dataCount++;
                            avgRating = arrRecords[j].retrieveAverageRating();
                            sum += avgRating;
                            count++;
                        }
                    }

                }
            }
            cursor = cursor->rightSib;
            nodeAccessed++;
            if (nodeAccessed < 6) {
                cout << "Index block: " << nodeAccessed << endl;
                for (int i = 0; i < cursor->size; i++) {
                    cout << cursor->key[i] << '|';
                }
                cout << "\n";
            }
        }


        float averageCalculation = sum / count;

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
        Node *cursor = root;
        Node *parent;

        while (cursor->isLeafNode == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->children[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->children[i + 1];
                    break;
                }
            }
        }

        for (int y = 0; y < cursor->size; y++) {
            if (cursor->key[y] == x) {
                cout << "Key already exists\n";
                LinkedList *newLL = new LinkedList;
                newLL->key = x;
                newLL->pointToBlock = block;

                if (cursor->linkedList[y] == NULL) {
                    cursor->linkedList[y] = newLL;
                } else {
                    LinkedList *existingLL;
                    existingLL = cursor->linkedList[y];
                    while (true) {
                        if (existingLL->nextLL == NULL) {
                            existingLL->nextLL = newLL;
                            break;
                        }
                        existingLL = existingLL->nextLL;
                    }
                }

                return;
            }
        }

        if (cursor->size < maxSize) {
            cursor->addKey(x, block);
        } else {
            cout << "Inserted key=" << x << " successfully\n";
            int virNode[maxSize + 1];
            Block *virPtr[maxSize + 1];
            LinkedList *virHolder[maxSize + 1];

            for (int i = 0; i < maxSize; i++) {
                virNode[i] = cursor->key[i];
                virPtr[i] = cursor->pointer[i];
                virHolder[i] = cursor->linkedList[i];
            }

            int i, m = 0;
            for (i = 0; i < maxSize; i++) {
                if (x <= virNode[m]) {
                    for (int j = maxSize + 1; j > m; j--) {
                        virNode[j] = virNode[j - 1];
                        virPtr[j] = virPtr[j - 1];
                        virHolder[j] = virHolder[j - 1];
                    }
                    break;
                }
                m++;
            }
            virNode[m] = x;
            virPtr[m] = block;
            virHolder[m] = NULL;

            Node *newLeaf = new Node(maxSize);
            newLeaf->isLeafNode = true;
            numNodes++;

            cursor->size = (maxSize + 1) / 2;
            newLeaf->size = maxSize + 1 - cursor->size;

            if (cursor->rightSib != NULL) {
                newLeaf->rightSib = cursor->rightSib;
                newLeaf->leftSib = cursor;
                cursor->rightSib->leftSib = newLeaf;
                cursor->rightSib = newLeaf;
            } else {
                newLeaf->rightSib = cursor->rightSib;
                newLeaf->leftSib = cursor;
                cursor->rightSib = newLeaf;
            }


            int j = cursor->size;
            for (i = 0; i < newLeaf->size; i++) {
                newLeaf->key[i] = virNode[j];
                newLeaf->pointer[i] = virPtr[j];
                newLeaf->linkedList[i] = virHolder[i];
                j++;
            }
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virNode[i];
                cursor->pointer[i] = virPtr[i];
                cursor->linkedList[i] = virHolder[i];
            }

            if (cursor == root) {
                Node *newRoot = new Node(maxSize);
                newRoot->isLeafNode = false;
                newRoot->leftSib = NULL;
                newRoot->rightSib = NULL;
                newRoot->size = 1;
                newRoot->children[1] = newLeaf;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->children[0] = cursor;
                root = newRoot;
                numNodes++;
            } else {
                insertInternal(parent, newLeaf, newLeaf->key[0]);
            }
        }
    }

}

void BPlusTree::insertInternal(Node *cursor, Node *child, int x) {
    if (cursor->size < maxSize) {

        int i, m = 0;
        for (i = 0; i < cursor->size; i++) {
            if (x <= cursor->key[i]) {
                break;
            }
            m++;
        }

        for (int j = cursor->size + 1; j > m + 1; j--) {
            cursor->children[j] = cursor->children[j - 1];
        }

        for (int j = cursor->size; j > m; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        cursor->size++;
        cursor->children[i + 1] = child;
        cursor->key[i] = x;
        cout << "Key is inserted into an internal node\n";
    } else {
        cout << "Key is inserted into an internal node\n";
        int virKey[maxSize + 1];
        Node *virChildren[maxSize + 2];
        for (int i = 0; i < maxSize + 1; i++) {
            virChildren[i] = cursor->children[i];
        }
        for (int i = 0; i < maxSize; i++) {
            virKey[i] = cursor->key[i];
        }
        int i, m = 0;
        for (i = 0; i < maxSize; i++) {
            if (x <= virKey[i]) {
                break;
            }
            m++;
        }

        for (int j = maxSize + 2; j > m + 1; j--) {
            virChildren[j] = virChildren[j - 1];
        }

        for (int j = maxSize + 1; j > m; j--) {
            virKey[j] = virKey[j - 1];
        }
        virChildren[m + 1] = child;
        virKey[m] = x;


        Node *nodeInternal = new Node(maxSize);
        numNodes++;
        nodeInternal->size = maxSize - (maxSize + 1) / 2;
        cursor->size = (maxSize + 1) / 2;
        nodeInternal->isLeafNode = false;
        nodeInternal->leftSib = NULL;
        nodeInternal->rightSib = NULL;


        int j = cursor->size + 1;
        for (i = 0; i < nodeInternal->size + 1; i++) {
            nodeInternal->children[i] = virChildren[j];
            j++;
        }
        j = cursor->size + 1;
        for (i = 0; i < nodeInternal->size; i++) {
            nodeInternal->key[i] = virKey[j];
            j++;
        }
        if (cursor == root) {

            Node *newRoot = new Node(maxSize);
            newRoot->isLeafNode = false;
            newRoot->leftSib = NULL;
            newRoot->rightSib = NULL;
            newRoot->children[0] = cursor;
            newRoot->children[1] = nodeInternal;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->size = 1;
            root = newRoot;
            numNodes++;
            cout << "New root created\n";
        } else {
            Node *parent = findParent(root, cursor);
            insertInternal(parent, nodeInternal, cursor->key[cursor->size]);
        }
    }
}

Node *BPlusTree::findParent(Node *cursor, Node *child) {
    Node *parent;
    if (cursor->isLeafNode || (cursor->children[0])->isLeafNode) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->children[i] == child) {
            parent = cursor;
            return parent;
        } else {
            parent = findParent(cursor->children[i], child);
            if (parent != NULL) {
                return parent;
            }
        }
    }
    return parent;
}

void BPlusTree::remove(int x) {
    if (root == NULL) {
        cout << "The tree is empty\n";
    } else {
        Node *cursor = root;
        Node *parent;
        int rightIndex, leftIndex;

        while (cursor->isLeafNode == false) {
            for (int i = 0; i < cursor->size; i++) {
                parent = cursor;
                leftIndex = i - 1;
                rightIndex = i + 1;
                if (x < cursor->key[i]) {
                    cursor = cursor->children[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->children[i + 1];
                    rightIndex = i + 2;
                    leftIndex = i;
                    break;
                }
            }
        }
        bool found = false;
        int pos;
        for (pos = 0; pos < cursor->size; pos++) {
            if (cursor->key[pos] == x) {
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Target not found\n";
            return;
        }
        for (int i = pos; i < cursor->size; i++) {
            cursor->key[i] = cursor->key[i + 1];
            cursor->pointer[i] = cursor->pointer[i + 1];
            cursor->linkedList[i] = cursor->linkedList[i + 1];
        }
        cursor->size--;
        if (cursor == root) {
            cout << "Removed key=" << x << "\n";

            for (int i = 0; i < maxSize + 1; i++) {
                cursor->children[i] = NULL;
            }

            cursor->leftSib = NULL;
            cursor->rightSib = NULL;
            if (cursor->size == 0) {
                cout << "Tree is destroyed\n";
                delete[] cursor->key;
                delete[] cursor->children;
                delete[] cursor->pointer;
                delete[] cursor->linkedList;
                delete cursor;
                root = NULL;
                numNodes--;
                numDeletes++;
            }
            return;
        }

        cout << "Removed key=" << x << "\n";
        if (cursor->size >= (maxSize + 1) / 2)
        {
            return;
        }
        if (leftIndex >= 0 &&
            parent->children[leftIndex]->canLeafBorrow()) {
            Node *sibling = parent->children[leftIndex];

            for (int i = cursor->size; i > 0; i--) {
                cursor->key[i] = cursor->key[i - 1];
                cursor->pointer[i] = cursor->pointer[i - 1];
                cursor->linkedList[i] = cursor->linkedList[i - 1];
            }


            cursor->size++;


            int leftMax = sibling->key[sibling->size - 1];
            cursor->key[0] = leftMax;
            cursor->linkedList[0] = sibling->linkedList[sibling->size - 1];
            cursor->pointer[0] = sibling->pointer[sibling->size - 1];


            sibling->size--;


            parent->key[leftIndex] = cursor->key[0];
            cout << "Transferred key=" << cursor->key[0] << "\n";
            return;

        }
        if (rightIndex <= parent->size &&
            parent->children[rightIndex]->canLeafBorrow()) {

            Node *sibling = parent->children[rightIndex];


            cursor->size++;


            int rightMin = sibling->key[0];
            cursor->key[cursor->size - 1] = rightMin;
            cursor->linkedList[cursor->size - 1] = sibling->linkedList[0];
            cursor->pointer[cursor->size - 1] = sibling->pointer[0];


            sibling->size--;


            for (int i = 0; i < sibling->size; i++) {
                sibling->key[i] = sibling->key[i + 1];
                sibling->linkedList[i] = sibling->linkedList[i + 1];
                sibling->pointer[i] = sibling->pointer[i + 1];
            }


            parent->key[rightIndex - 1] = sibling->key[0];
            cout << "Transferred key=" << cursor->key[cursor->size - 1] << "\n";
            return;

        }
        if (leftIndex >= 0)
        {
            Node *sibling = parent->children[leftIndex];

            int j = sibling->size;
            for (int i = 0; i < cursor->size; i++) {
                sibling->key[j] = cursor->key[i];
                sibling->linkedList[j] = cursor->linkedList[i];
                sibling->pointer[j] = cursor->pointer[i];
                j++;
            }


            if (cursor->rightSib != NULL) {
                sibling->rightSib = cursor->rightSib;
                cursor->rightSib->leftSib = sibling;
                cursor->leftSib = NULL;
                cursor->rightSib = NULL;
            } else {
                sibling->rightSib = cursor->rightSib;
                cursor->leftSib = NULL;
                cursor->rightSib = NULL;
            }


            int increaseSize = cursor->size;
            sibling->size += increaseSize;


            numNodes--;
            numDeletes++;
            removeInternal(cursor, parent, parent->key[leftIndex]);

        } else if (rightIndex <= parent->size) {
            Node *sibling = parent->children[rightIndex];

            for (int i = cursor->size, j = 0; j < sibling->size; i++, j++) {
                cursor->key[i] = sibling->key[j];
                cursor->linkedList[i] = sibling->linkedList[j];
                cursor->pointer[i] = sibling->pointer[j];
            }


            cursor->size += sibling->size;


            if (sibling->rightSib != NULL) {
                cursor->rightSib = sibling->rightSib;
                sibling->rightSib->leftSib = cursor;
                sibling->leftSib = NULL;
                sibling->rightSib = NULL;
            } else {
                cursor->rightSib = sibling->rightSib;
                sibling->leftSib = NULL;
                sibling->rightSib = NULL;
            }


            numNodes--;
            numDeletes++;
            removeInternal(sibling, parent, parent->key[rightIndex - 1]);

        }
    }
}

void BPlusTree::removeInternal(Node *child, Node *cursor, int x) {

    if (cursor == root) {
        if (cursor->size == 1) {

            if (cursor->children[1] == child) {
                delete[] child->key;
                delete[] child->children;
                delete[] child->pointer;
                delete[] child->linkedList;
                delete child;
                numNodes--;
                numDeletes++;
                root = cursor->children[0];
                root->leftSib = NULL;
                root->rightSib = NULL;
                delete[] cursor->key;
                delete[] cursor->children;
                delete[] cursor->pointer;
                delete[] cursor->linkedList;
                delete cursor;
                numNodes--;
                numDeletes++;
                cout << "Root node changed\n";
                return;
            } else if (cursor->children[0] == child) {
                delete[] child->key;
                delete[] child->children;
                delete[] child->pointer;
                delete[] child->linkedList;
                delete child;
                numNodes--;
                numDeletes++;
                root = cursor->children[1];
                root->leftSib = NULL;
                root->rightSib = NULL;
                delete[] cursor->key;
                delete[] cursor->children;
                delete[] cursor->pointer;
                delete[] cursor->linkedList;
                delete cursor;
                numNodes--;
                numDeletes++;
                cout << "Root node changed\n";
                return;
            }
        }
    }

    int pos;


    cursor->delKeyInternal(child, x);

    if (cursor->size >= (maxSize + 1) / 2 - 1) {
        cout << "Deleted key=" << x << "\n";
        return;
    }

    if (cursor == root) {
        return;
    }
    Node *parent = findParent(root, cursor);
    int leftIndex, rightIndex;

    for (pos = 0; pos < parent->size + 1; pos++) {
        if (parent->children[pos] == cursor) {
            leftIndex = pos - 1;
            rightIndex = pos + 1;
            break;
        }
    }
    if (leftIndex >= 0 &&
        parent->children[leftIndex]->canInternalBorrow()) {
        Node *sibling = parent->children[leftIndex];


        for (int i = cursor->size + 1; i > 0; i--) {
            cursor->children[i] = cursor->children[i - 1];
        }
        for (int i = cursor->size; i > 0; i--) {
            cursor->key[i] = cursor->key[i - 1];
        }

        cursor->children[0] = sibling->children[sibling->size];

        cursor->key[0] = parent->key[leftIndex];
        parent->key[leftIndex] = sibling->key[sibling->size - 1];


        sibling->size--;
        cursor->size++;
        return;

    }
    if (rightIndex <= parent->size &&
        parent->children[rightIndex]->canInternalBorrow()) {
        Node *sibling = parent->children[rightIndex];

        cursor->children[cursor->size + 1] = sibling->children[0];
        for (int i = 0; i < sibling->size; ++i) {
            sibling->children[i] = sibling->children[i + 1];
        }

        cursor->key[cursor->size] = parent->key[pos];
        parent->key[pos] = sibling->key[0];
        for (int i = 0; i < sibling->size - 1; i++) {
            sibling->key[i] = sibling->key[i + 1];
        }
        sibling->size--;
        cursor->size++;
        return;

    }

    if (leftIndex >= 0) {

        Node *sibling = parent->children[leftIndex];
        sibling->key[sibling->size] = parent->key[leftIndex];
        int i = sibling->size + 1;
        for (int j = 0; j < cursor->size + 1; j++) {
            sibling->children[i] = cursor->children[j];
            cursor->children[j] = NULL;
        }
        for (int j = 0; j < cursor->size; j++) {
            sibling->key[i] = cursor->key[j];
        }
        sibling->size += cursor->size + 1;
        cursor->size = 0;

        numNodes--;
        numDeletes++;
        removeInternal(cursor, parent, parent->key[leftIndex]);


    } else if (rightIndex <= parent->size) {

        Node *sibling = parent->children[rightIndex];
        cursor->key[cursor->size] = parent->key[rightIndex - 1];
        int i = cursor->size + 1;
        for (int j = 0; j < sibling->size + 1; j++) {
            cursor->children[i] = sibling->children[j];
            sibling->children[j] = NULL;
        }
        for (int j = 0; j < sibling->size; j++) {
            cursor->key[i] = sibling->key[j];
        }
        cursor->size += sibling->size + 1;
        sibling->size = 0;
        numNodes--;
        numDeletes++;
        removeInternal(sibling, parent, parent->key[rightIndex - 1]);

    }
}

Node *BPlusTree::getRoot() {
    return root;
}
