#ifndef __CLASS_NODE_H
#define __CLASS_NODE_H

#include <iostream>
#include <vector>
using namespace std;

//node
struct node {
    vector<int> puzzle;
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
public:
    BigTree();
    //~BigTree();
    node* insert(vector<int> val);
    //these return the new nodes created from directions in the puzzle, so they can be put in queue
    node* insertLeft(node *papi, vector<int> val);
    node* insertRight(node *papi, vector<int> val);
    node* insertUp(node *papi, vector<int> val);
    node* insertDown(node *papi, vector<int> val);
    int height(node *nood);
};


#endif