#include "class_node.h"
using namespace std;

//constructor
BigTree::BigTree()
{
    root = NULL;
}
node* BigTree::insertLeft(node *papi, vector<int> val)
{
    papi->left = new node;
    papi->left->puzzle = val;
    papi->left->parent = papi;
    papi->left->left = NULL;
    papi->left->right = NULL;
    papi->left->up = NULL;
    papi->left->down = NULL;
    return papi->left;
}
node* BigTree::insertRight(node *papi, vector<int> val)
{
    papi->right = new node;
    papi->right->puzzle = val;
    papi->right->parent = papi;
    papi->right->left = NULL;
    papi->right->right = NULL;
    papi->right->up = NULL;
    papi->right->down = NULL;
    return papi->right;
}
node* BigTree::insertUp(node *papi, vector<int> val)
{
    papi->up = new node;
    papi->up->puzzle = val;
    papi->up->parent = papi;
    papi->up->left = NULL;
    papi->up->right = NULL;
    papi->up->up = NULL;
    papi->up->down = NULL;
    return papi->up;
}
node* BigTree::insertDown(node *papi, vector<int> val)
{
    papi->down = new node;
    papi->down->puzzle = val;
    papi->down->parent = papi;
    papi->down->left = NULL;
    papi->down->right = NULL;
    papi->down->up = NULL;
    papi->down->down = NULL;
    return papi->down;
}
//for initializing the tree
node* BigTree::insert(vector<int> val)
{
    root = new node;
    root->puzzle = val;
    root->left = NULL;
    root->right = NULL;
    root->up = NULL;
    root->down = NULL;
    root->parent = NULL;
    return root;
}
//returns an int of the height from a specific node, useful for bfs
int BigTree::height(node *nood)
{

    int count = 0;
    node *tmp = nood;
    while(tmp->parent != NULL)
    {
        count++;
        tmp = tmp->parent;
    }
    return count;
}
