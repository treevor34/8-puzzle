/*---------------------------------------------------------------------
Test cases given on worksheet do not seem to work.
Any test case with a height greater than 12 will likely take some time.
Has been thouroughly tested working up to 16 steps (for bfs)
---------------------------------------------------------------------*/
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
using namespace std;
#include "class_node.h"

//prints the vector out
void print(vector<int> vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec.at(i) << " ";
        if((i+1) % 3 == 0)
            cout << endl;
    }
}

//returns true if both vectors are the same
//returns false if not
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

//returns the index location for the "0"
int findZero(vector<int> tmp)
{
    for(int i = 0; i < 9; i++)
        if(tmp.at(i) == 0)
            return i;
    cout << "No 0 piece of the puzzle." << endl;
    exit(0);
}

//returns a vector of the move specified with the 0
//returns empty if it cannot make that move
vector<int> move(vector<int> tmpy, int exp)
{
    vector<int> tmp = tmpy;
    int swapped, num = findZero(tmp);
    vector<int> empty;
    switch(exp) {
        case 0: //left
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
            if(num == 0 || num == 1 || num == 2)
                return empty;
            //records the value being swapped left with
            swapped = tmp.at(num - 3);

            //swapped the values
            tmp.at(num - 3) = 0;
            tmp.at(num) = swapped;
            return tmp;
            break;
        case 2: //right
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

//does bfs search. Has two queues, one with the vectors to find the correct iteration
//the other vector of nodes so it can climb back up to find the height(# of steps)
int bfs(vector<int> cur, vector<int> solution)
{
    int ret = -2;

    BigTree tree;
    queue<vector<int>> myqueue;
    queue<node*> tracking;
    int counter = 1;
    node *rooty = tree.insert();
    tracking.push(rooty);

    vector<int> tmp = cur;
    myqueue.push(tmp);

    //this while loop is the brute force bfs
    while(!myqueue.empty() && ret < 0)
    {
        //queues storing vectors and tracking nodes
        vector<int> top = myqueue.front();
        myqueue.pop();
        
        node *cur = tracking.front();
        tracking.pop();

        //the four vectors to hold the possible movements
        vector<int> left = move(top, 0);
        vector<int> up = move(top, 1);
        vector<int> right = move(top, 2);
        vector<int> down = move(top, 3);

        //if the move vector empty, then it cannot move
        if(!left.empty())
        {
            if(isSame(top, left) == false)
            {
                counter++;
                node *tmp = tree.insertLeft(cur, counter);
                tracking.push(tmp);
                if(isSame(solution, left) == true)
                {
                    //print(left);
                    ret = tree.height(tmp);
                    return ret;
                }
                myqueue.push(left);
            }
        }
        if(!up.empty())
        {
            if(isSame(top, up) == false)
            {
                counter++;
                node *tmp = tree.insertUp(cur, counter);
                tracking.push(tmp);
                if(isSame(solution, up) == true)
                {
                    //print(up);
                    ret = tree.height(tmp);
                    return ret;
                }
                myqueue.push(up);
            }
        }
        if(!right.empty())
        {
            if(isSame(top, right) == false)
            {
                counter++;
                node *tmp = tree.insertRight(cur, counter);
                tracking.push(tmp);
                if(isSame(solution, right) == true)
                {
                    //print(right);
                    ret = tree.height(tmp);
                    return ret;
                }
                myqueue.push(right);
            }
        }
        if(!down.empty())
        {
            if(isSame(top, down) == false)
            {
                counter++;
                node *tmp = tree.insertDown(cur, counter);
                tracking.push(tmp);
                if(isSame(solution, down) == true)
                {
                    //print(down);
                    ret = tree.height(tmp);
                    return ret;
                }
                myqueue.push(down);
            }
        }    
    }
    return ret;
}

int dfs(vector<int> start, vector<int> solution)
{
    int ret = 347;

    BigTree tree;

    stack<vector<int>> mystack;
    stack<node*> tracking;

    int counter = 1;
    node *rooty = tree.insert();
    tracking.push(rooty);

    vector<int> tmp = start;
    mystack.push(tmp);

    while(!mystack.empty())
    {

        vector<int> top = mystack.top();
        mystack.pop();
        
        node *cur = tracking.top();
        tracking.pop();
        int pp = tree.height(cur);
        
        if(pp < 20 && pp < ret)
        {
            vector<int> left = move(top, 0);
            vector<int> up = move(top, 1);
            vector<int> right = move(top, 2);
            vector<int> down = move(top, 3);
            if(!left.empty())
            {
                if(isSame(top, left) == false)
                {
                    counter++;
                    node *tmp = tree.insertLeft(cur, counter);
                    tracking.push(tmp);
                    if(isSame(solution, left) == true)
                    {
                        //print(left);
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                        cout << ret << endl;
                        //return ret;
                    }
                    mystack.push(left);
                }
            }
            if(!up.empty())
            {
                if(isSame(top, up) == false)
                {
                    counter++;
                    node *tmp = tree.insertUp(cur, counter);
                    tracking.push(tmp);
                    if(isSame(solution, up) == true)
                    {
                        //print(up);
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                        cout << ret << endl;
                        //return ret;
                    }
                    mystack.push(up);
                }
            }
            if(!right.empty())
            {
                if(isSame(top, right) == false)
                {
                    counter++;
                    node *tmp = tree.insertRight(cur, counter);
                    tracking.push(tmp);
                    if(isSame(solution, right) == true)
                    {
                        //print(right);
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                        cout << ret << endl;
                        //return ret;
                    }
                    mystack.push(right);
                }
            }
            if(!down.empty())
            {
                if(isSame(top, down) == false)
                {
                    counter++;
                    node *tmp = tree.insertDown(cur, counter);
                    tracking.push(tmp);
                    if(isSame(solution, down) == true)
                    {
                        //print(down);
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                        cout << ret << endl;
                        //return ret;
                    }
                    mystack.push(down);
                }
            }
        }    
    }
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
        if(tmp < 0 || tmp > 8)
        {
            cout << "Value must be between 0 and 8." << endl;
            return 0;
        }
        start.push_back(tmp);
    }

    for(z = 0; z < 9; z++)
    {
        cout << "Solution value #"<< z+1 << ": ";
        cin >> tmp;
        if(tmp < 0 || tmp > 8)
        {
            cout << "Value must be between 0 and 8." << endl;
            return 0;
        }
        solution.push_back(tmp);
    }

    cout << endl << "Starting State: "<< endl;
    print(start);
    cout << endl << "Solution State: "<< endl;
    print(solution);
    cout << endl;

    if(isSame(start, solution) == true)
    {
        cout << "Start state and solution are already the same." << endl;
        return 0;
    }

    int check = 0;
    for(int j = 0; j < start.size(); j++)
    {
        for(int t = 0; t < solution.size(); t++)
        {
            if(start.at(j) != solution.at(t))
                check++;
        }
        if(check > 8)
        {
            cout << "A solution is impossible." << endl;
            return 0;
        }
        check = 0;
    }
     
    //cout << "Start bfs" << endl;
    int answer = dfs(start, solution);
    cout << "Total steps needed: " << answer << endl;
    return 0;
}