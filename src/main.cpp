#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <tgmath.h>

#include "record.h"
#include "block.h"
#include "disk.h"
#include "b_plus_tree.h"
#include "tree_node.h"

using namespace std;

int MAX;/
class BPlusTree;

int main(int argc, char** argv) {
    int BlockSize;
    cout << "Enter Block Size (in bytes)" << endl;
    cin >> BlockSize;
    cout << "Block Size " << BlockSize << " bytes\n" << endl;

    BPlusTree bpt(MAX);
    string command;
    string line;
    std::vector<std::string> fields;
    bool skipline = true;
    int i = 0, j = 0;
    int blocksUsed = 1;
    int numIO = 1;
    int numRecords = -1;

    string DATAFILE = "../data/data.tsv";

    ifstream fin1(DATAFILE);
    while (getline(fin1, line)) {
        numRecords++;
    }
    fin1.close();
    cout << "numRecords = " << numRecords << endl;

    int n;
    if (BlockSize == 200) {
        n = 6;
    }
    else {
        n = 15;
    }
    cout << "n = " << n << endl;
    MAX = n;

    int numNodes = ceil(numRecords/n);
    cout << "num B+ leaf nodes = " << numNodes << endl;

    int heightOfTree = ceil(log2(numNodes));
    cout << "height/degree of B+ Tree = " << heightOfTree << endl;

    Disk Disk;
    Block newBlock(BlockSize);
    std::shared_ptr<Block> newBlockPtr = std::make_shared<Block>(std::move(newBlock));
    Disk.addBlock(newBlockPtr);
    cout << "Building Disk Struc..." << endl;

    Block blkToBeInserted = newBlock;

    ifstream fin(DATAFILE);
    cout << "Reading File......" << endl;

    while (getline(fin, line)) {
        if (skipline){
            skipline = false;
            continue;
        }

        std::istringstream iss(line);
        std::string afield;

        while(std::getline(iss, afield, '\t')){
            fields.push_back(afield);
        }

        Record newRecord;
        newRecord.tconst = fields[i++];
        std::istringstream(fields[i++]) >> newRecord.averageRating;
        std::istringstream(fields[i++]) >> newRecord.numVotes;
        std::shared_ptr<Block> blockPointer;

        if (Disk.blockVector[blocksUsed-1]->numRecordsInBlock() < Disk.blockVector[blocksUsed-1]->maximumRecords){
            Disk.blockVector[blocksUsed-1]->insertRecord(newRecord);
            blockPointer = Disk.blockVector[blocksUsed-1];

            cout << "New record inserted into block with ID " << newRecord.retrieveTCONST() << endl;

            Block* blockToInsert = blockPointer.get();
            bpt.insert(newRecord.retrieveNumVotes(), blockToInsert);
            numIO++;
        }

        else{
            cout << "Block Full, initialising new Block..." << endl;
            numIO++;

            Block additionalBlock(BlockSize);

            additionalBlock.insertRecord(newRecord);
            cout << "New record inserted into block with ID " << newRecord.retrieveTCONST() << endl;
            blockPointer = std::make_shared<Block>(additionalBlock);
            Disk.addBlock(blockPointer);

            Block* blockToInsert = blockPointer.get();
            bpt.insert(newRecord.retrieveNumVotes(), blockToInsert);
            numIO++;

            blocksUsed++;
        }
    }

    fin.close();

    cout << "--- All Data Stored in Disk ---" << endl;
    cout << " " << endl;

    cout << "---Experiment 1: Storing Data on Disk---" << endl;
    cout << "Storage Stats:" << endl;
    cout << "Number of Blocks Used: " << blocksUsed << endl;
    cout << "Number of I/Os Used: " << numIO << endl;
    cout << "Number of Records: " << Disk.getNumOfRecords() << endl;
    cout << "Size of 1 Record: " << sizeof(Record) << endl;

    int totalSize = Disk.getSizeOfStorage(); //to add on B+ tree size
    totalSize += bpt.getNumNodes() * sizeof(Node);

    cout << "Size of Database: " << totalSize << " Bytes" << endl;
    cout << " " << endl;
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

    cout << "---Experiment 2: Building B+ tree using insertion---" << endl;
    cout << "Parameter n of B+ tree: " << MAX << endl;
    cout << "Number of Nodes in BP Tree: " << bpt.getNumNodes() << endl;
    cout << "Height of BP tree: " << bpt.getHeight(bpt.getRoot()) << endl;
    cout << "Content of Root Node: " << endl;
    bpt.printNode(bpt.getRoot());
    cout << " " << endl;

    cout << "Content of first child: " << endl;
    bpt.printNode(bpt.getFirstChild(bpt.getRoot()));
    cout << " " << endl;
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

    cout << "---Experiment 3: Retrieve movies with numVotes = 500---" << endl;
    bpt.search(500);
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";


    cout << "---Experiment 4: INSERT HERE---" << endl;
    bpt.searchRange(30000, 40000);
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

    cout << "---Experiment 5: Delete movies given numVotes---" << endl;
    int nodeBeforeRemove = bpt.getNumNodes();
    int heightBeforeRemove = bpt.getHeight(bpt.getRoot());
    bpt.remove(1000);

    cout << "Number of Nodes in BP Tree before removal: " << nodeBeforeRemove << endl;
    cout << "Number of Nodes in BP Tree after removal: " << bpt.getNumNodes() << endl;
    cout << "Number of Nodes removed: " << bpt.getNumDeletes() << endl;
    cout << "Height of BP tree before removal: " << heightBeforeRemove << endl;
    cout << "Height of BP tree after removal: " << bpt.getHeight(bpt.getRoot()) << endl;
    cout << "Content of root node after removal: " << endl;
    bpt.printNode(bpt.getRoot());
    cout << " " << endl;
    cout<<"\n";
    cout << "Content of first child: " << endl;
    bpt.printNode(bpt.getFirstChild(bpt.getRoot()));
    cout << " " << endl;
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";


    return 0;
}