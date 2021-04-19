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
#include <fstream>
using namespace std;
#include "class_node.h"

//prints the vector out
void print(vector<int> vec)
{
    int n = vec.size()/3;
    for (int i = 0; i < 3; i++)
    {
        cout << "\t";
        for (int j = 0; j < 3; j++)
        {
            cout << vec.at(i*n+j) << " ";
        }
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
int bfs(vector<int> start, vector<int> solution)
{
    int ret = -2;

    BigTree tree;
    queue<node*> tracking;
    node *rooty = tree.insert(start);

    tracking.push(rooty);

    //this while loop is the brute force bfs
    while(!tracking.empty() && ret < 0)
    {
        node *cur = tracking.front();
        tracking.pop();

        vector<int> top = cur->puzzle;

        //the four vectors to hold the possible movements
        vector<int> left = move(top, 0);
        vector<int> up = move(top, 1);
        vector<int> right = move(top, 2);
        vector<int> down = move(top, 3);

        //to check parent's
        vector<int> prev;
        if(cur->parent != NULL)
            prev = cur->parent->puzzle;
        else
            prev = top;

        //if the move vector empty, then it cannot move
        if(!left.empty() && (isSame(prev, left) == 0))
        {
            if(isSame(top, left) == false)
            {
                node *tmp = tree.insertLeft(cur, left);
                tracking.push(tmp);
                if(isSame(solution, left) == true)
                {
                    ret = tree.height(tmp);
                    return ret;
                }
            }
        }
        if(!up.empty() && (isSame(prev, up) == 0))
        {
            if(isSame(top, up) == false)
            {
                node *tmp = tree.insertUp(cur, up);
                tracking.push(tmp);
                if(isSame(solution, up) == true)
                {
                    ret = tree.height(tmp);
                    return ret;
                }
            }
        }
        if(!right.empty() && (isSame(prev, right) == 0))
        {
            if(isSame(top, right) == false)
            {
                node *tmp = tree.insertRight(cur, right);
                tracking.push(tmp);
                if(isSame(solution, right) == true)
                {
                    ret = tree.height(tmp);
                    return ret;
                }
            }
        }
        if(!down.empty() && (isSame(prev, down) == 0))
        {
            if(isSame(top, down) == false)
            {
                node *tmp = tree.insertDown(cur, down);
                tracking.push(tmp);
                if(isSame(solution, down) == true)
                {
                    ret = tree.height(tmp);
                    return ret;
                }
            }
        }
    }
    return ret;
}

int dfs(vector<int> start, vector<int> solution)
{
    int ret = 347;

    BigTree tree;

    stack<node*> tracking;

    node *rooty = tree.insert(start);
    tracking.push(rooty);

    while(!tracking.empty())
    {
        node *cur = tracking.top();
        tracking.pop();
        vector<int> top = cur->puzzle;
        int pp = tree.height(cur);

        //to check parent's
        vector<int> prev;
        if(cur->parent != NULL)
            prev = cur->parent->puzzle;
        else
            prev = top;

        if(pp < 40 && pp < ret)
        {
            vector<int> left = move(top, 0);
            vector<int> up = move(top, 1);
            vector<int> right = move(top, 2);
            vector<int> down = move(top, 3);
            if(!left.empty() && (isSame(prev, left) == 0))
            {
                if(isSame(top, left) == false)
                {
                    node *tmp = tree.insertLeft(cur, left);
                    tracking.push(tmp);

                    if(isSame(solution, left) == true)
                    {
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                    }
                }
            }
            if(!up.empty() && (isSame(prev, up) == 0))
            {
                if(isSame(top, up) == false)
                {
                    node *tmp = tree.insertUp(cur, up);
                    tracking.push(tmp);
                    if(isSame(solution, up) == true)
                    {
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                    }
                }
            }
            if(!right.empty() && (isSame(prev, right) == 0))
            {
                if(isSame(top, right) == false)
                {
                    node *tmp = tree.insertRight(cur, right);
                    tracking.push(tmp);
                    if(isSame(solution, right) == true)
                    {
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                    }
                }
            }
            if(!down.empty() && (isSame(prev, down) == 0))
            {
                if(isSame(top, down) == false)
                {
                    node *tmp = tree.insertDown(cur, down);
                    tracking.push(tmp);
                    if(isSame(solution, down) == true)
                    {
                        if(tree.height(tmp) < ret)
                            ret = tree.height(tmp);
                    }
                }
            }
        }
    }
    return ret;
}

int main()
{
    ifstream inFile;
    vector<int> solution;
    vector<int> start;
    int z, tmp, selection = 0;

    inFile.open("input.txt");
    for(z = 0; z < 9; z++)
    {
        inFile >> tmp;
        if(tmp < 0 || tmp > 8)
        {
            cout << "Value must be between 0 and 8. Value entered: " << tmp << endl;
            return 0;
        }
        start.push_back(tmp);
    }

    for(z = 0; z < 9; z++)
    {
        inFile >> tmp;
        if(tmp < 0 || tmp > 8)
        {
            cout << "Value must be between 0 and 8. Value entered: " << tmp << endl;
            return 0;
        }
        solution.push_back(tmp);
    }
    inFile.close();

    cout << endl << "*/*/*/*/*/*/*/*/*/*/*";
    cout << endl << "   Starting State"<< endl;
    print(start);
    cout << endl << "   Solution State"<< endl;
    print(solution);
    cout << "*/*/*/*/*/*/*/*/*/*/*" << endl << endl;

    if(isSame(start, solution))
    {
        cout << "Start state and solution are already the same." << endl;
        return 0;
    }

    while (selection > 2 || selection < 1)
    {
        cout << "Which Search Algorithm?\n1. Breadth First Search\n2. Depth First Search\n\nSelection: ";
        cin >> selection;
        if (selection > 2 || selection < 1)
            cout << "\nIncorrect Selection Choice" << endl;
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

    if (selection == 1)
        cout << "\nBreadth First-\n" << "\tSolutions needed: " << bfs(start, solution) << endl;
    if (selection == 2)
        cout << "\nDepth First-\n" << "\tSolutions needed: " << dfs(start, solution) << endl << endl;
    return 0;
}
/*
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
*/
