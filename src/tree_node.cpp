#include "tree_node.h"
#include "block.h"
#include "linked_list.h"

Node::Node(int max)
{
    //dynamic memory allocation
    key = new int[MAX];
    children = new Node*[MAX+1];
    ptr = new Block*[MAX+1];
    LLholder = new LL*[MAX+1];
}

void Node::getContent() {
    for(int i=0;i < size; i++)
    {
        cout << key[i] << '|';
    }
}


bool Node::canLeafBorrow() {
    return size >= (MAX+1)/2+1;
}

bool Node::canInternalBorrow() {
    return size >= (MAX+1)/2;
}


bool Node::addKey(int x, Block* block) // std::shared_ptr<Block> block)
{

    if (x >= key[size-1]) {
        key[size] = x;
        ptr[size] = block;
        LLholder[size] = NULL;
        size++;
        cout<<"Inserted "<<x<<" successfully\n";
    }

    else {
        int i, m=0;
        for(i=0;i < size; i++)
        {
            if (x <= key[i]) {
                break;
            }
            m++;
        }

        for(int j = size;j > m; j--)
        {
            key[j] = key[j-1];
            ptr[j] = ptr[j-1];
            LLholder[j] = LLholder[j-1];
        }
        key[m] = x;
        ptr[m] = block;
        LLholder[m] = NULL;
        size++;
        cout<<"Inserted "<<x<<" successfully\n";
    }

    return true;
}

void Node::delKeyInternal(Node* child, int x) {
    int pos;
    //Deleting the pointer child
    for(int j = 0; j < size+1; j++)
    {
        if(children[j] == child)
        {
            pos = j;
        }
    }
    for(int i = pos; i < size+1; i++)
    {
        children[i] = children[i+1];
    }
    for(int j = 0; j < size; j++)
    {
        if(key[j] == x)
        {
            pos = j;
        }
    }
    for(int i = pos; i < size; i++)
    {
        key[i] = key[i+1];
    }
    size--;
};