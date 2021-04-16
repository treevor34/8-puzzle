#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
using namespace std;
//#include "class_node.h"
/*
struct node {
    vector<int> puzzle;
    node* left;
    node* up;
    node* right;
    node* down;
    node* parent; 
};
*/
void print(vector<int> vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec.at(i) << " ";
        if((i+1) % 3 == 0)
            cout << endl;
    }
}

bool isSame(vector<int> un, vector<int> dos)
{
    for(int i = 0; i < 9; i++)
    {
        if(un.at(i) == dos.at(i))
            continue;
        else
            return false;
    }
    return true;
}

int findZero(vector<int> tmp)
{
    for(int i = 0; i < 9; i++)
        if(tmp.at(i) == 0)
            return i;
    cout << "No 0 piece of the puzzle." << endl;
    exit(0);
}

vector<int> move(vector<int> tmpy, int exp)
{
    cout << "Move:" << exp << endl;
    vector<int> tmp = tmpy;
    int swapped, num = findZero(tmp);
    vector<int> empty;
    switch(exp) {
        case 0: //left
            cout << "left" << endl;
            if(num == 0 || num == 3 || num == 6)
                return empty;
            
            //records the value being swapped left with
            swapped = tmp.at(num - 1);

            //swapped the values
            tmp.at(num - 1) = 0;
            tmp.at(num) = swapped;
            return tmp;
            break;
        case 1: //up
            cout << "up" << endl;
            if(num == 0 || num == 1 || num == 2)
                return empty;
            cout << "past the up" << endl;
            //records the value being swapped left with
            swapped = tmp.at(num - 3);

            //swapped the values
            tmp.at(num - 3) = 0;
            tmp.at(num) = swapped;
            return tmp;
            break;
        case 2: //right
            cout << "right" << endl;
            if(num == 2 || num == 5 || num == 8)
                return empty;
            
            //records the value being swapped left with
            swapped = tmp.at(num + 1);

            //swapped the values
            tmp.at(num + 1) = 0;
            tmp.at(num) = swapped;
            return tmp;
            break;
        case 3://down
            cout << "down" << endl;
            if(num == 6 || num == 7 || num == 8)
                return empty;
            
            //records the value being swapped left with
            swapped = tmp.at(num + 3);

            //swapped the values
            tmp.at(num + 3) = 0;
            tmp.at(num) = swapped;
            return tmp;
            break;
    }
    cout << "This is wrong lol" << endl;
    return tmp;
}
int bfs(vector<int> cur, vector<int> solution)
{
    int ret = -2;

    queue<vector<int>> myqueue;

    vector<int> tmp = cur;
    myqueue.push(tmp);
    //this while loop is the brute force bfs
    //needs many checks in it though
    while(!myqueue.empty() && ret < 0)
    {
        vector<int> top = myqueue.front();
        myqueue.pop();
        vector<int> left = move(top, 0);
        print(left);
        vector<int> up = move(top, 1);
        print(up);
        vector<int> right = move(top, 2);
        print(right);
        vector<int> down = move(top, 3);
        print(down);
        cout<< "confused" << endl;
        if(!left.empty())
            myqueue.push(left);
        if(!up.empty())
            myqueue.push(up);
        if(!right.empty())
            myqueue.push(right);
        if(!down.empty())
            myqueue.push(down);
            
        ret++;
    }

    //myqueue.push();
    /*while(!myqueue.empty() && ret == -1)
    {
    }*/


    return ret;
}


int main()
{
    string input;
    vector<int> solution;
    vector<int> start;
    int z, tmp;
    //should check for repeats but i have not yet
    cout << "Values must range from 0-8, with only one occurence of each." << endl << "Please enter 9 seperate values for the puzzle start state:" << endl;
    
    for(z = 0; z < 9; z++)
    {
        cout << "Start value #"<< z+1 << ": ";
        cin >> tmp;
        start.push_back(tmp);
    }

    for(z = 0; z < 9; z++)
    {
        cout << "Solution value #"<< z+1 << ": ";
        cin >> tmp;
        solution.push_back(tmp);
    }

    cout << endl << "Starting State: "<< endl;
    print(start);
    cout << endl << "Solution State: "<< endl;
    print(solution);
     
    cout << "Start bfs" << endl;
    int answer = bfs(start, solution);
    return 0;
}