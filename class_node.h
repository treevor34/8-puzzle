#ifndef __CLASS_NODE_H
#define __CLASS_NODE_H

#include <iostream>
#include <vector>
using namespace std;

//node
struct node {
    //vector<int> puzzle;
    int val;
    node *left;
    node *up;
    node *right;
    node *down;
    node *parent; 
};

//tree for nodes
class BigTree
{
private:
    node *root;

    //search function
public:
    BigTree();
    //~BigTree();
    node* insert();
    //these return the new nodes created from directions in the puzzle, so they can be put in queue
    node* insertLeft(node *papi, int value);
    node* insertRight(node *papi, int value);
    node* insertUp(node *papi, int value);
    node* insertDown(node *papi, int value);
    int height(node *nood);
};


#endif