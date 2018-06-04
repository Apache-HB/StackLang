#include <iostream>
#include <vector>
#include <utility>
#include "functionstrings.h"

#define CheckStackSingle(x) if(stacks[currentstack].size() < 1){ cout << x << endl; return true; }

#define CheckStackDouble(x) if(stacks[currentstack].size() < 2){ cout << x << endl; return true; }

#define PerformStackAction(x) int ret = stacks[currentstack].end()[-1] x stacks[currentstack].end()[-2]; \
                              stacks[currentstack].push_back(ret); \
                              cout << "added " << ret << " to the stack" << endl;


using namespace std;

typedef vector<int> stack;
static vector<stack> stacks;

typedef pair<string, string> functionpair;
static vector<functionpair> functions;

string input = "";

bool running = true;

int currentstack = 0;

bool generalproccess(string inputstring)
{
    //stack managment

    //create a new stack
    if(inputstring.find(pushstack) == 0)
    {
        stacks.push_back(vector<int>());
        cout << "added stack: " << stacks.size() -1 << endl;
    }

    //remove the last stack
    else if(inputstring.find(popstack) == 0)
    {
        if(stacks.size() <= 0)
        {
            cerr << "cannt pop a stack if there is only one stack" << endl;
            return true;
        }
        stacks.pop_back();

        if(currentstack > stacks.size())
        {
            currentstack = 0;
            cout << "you popped the current stack, setting current stack to 0" << endl;
        }

        cout << "popped stack: " << stacks.size() + 1 << endl;
    }

    //single stack operations

    //set the currentstack
    else if(inputstring.find(setstack) == 0)
    {
        inputstring.erase(0, setstack.length());

        try {
            int want = stoi(inputstring);
            if(want > stacks.size()-1)
            {
                cerr << "cannot set the working stack out of range" << endl;
                return true;
            }
            currentstack = want;
            cout << "set the working stack to: " << want << endl;
        } catch(const exception& e) {
            cerr << "cannot set the working stack to: " << inputstring << endl;
        }

    }

    //push an item onto the current stack
    else if(inputstring.find(pushcur) == 0)
    {
        inputstring.erase(0, pushcur.length());
        //clean string for stoi
        try {
            int toadd = stoi(inputstring);//make sure noone trys any funny business
            stacks[currentstack].push_back(toadd);
            cout << "added: " << toadd << " to stack: " << currentstack << endl;
        } catch(const exception& e) {
            cerr << "cannot convert" << inputstring << " to an integer" << endl;;
        }
    }

    //pop an item off the current stack
    else if(inputstring.find(popcur) == 0)
    {
        if(stacks[currentstack].size() <= 0)
        {
            cerr << "stack " << currentstack << " is already empty" << endl;
            return true;
        }

        cout << "popped: "
             << stacks[currentstack].end()[-1]
             << " off stack: "
             << currentstack
             << endl;

        stacks[currentstack].pop_back();
    }

    //print the current stack
    else if(inputstring.find(printstack) == 0)
    {
        if(stacks[currentstack].size() == 0)
        {
            cerr << "stack: " << currentstack << " is empty" << endl;
            return true;
        }

        cout << "all items in stack: " << currentstack << endl;

        for(auto& item : stacks[currentstack])
        {
            cout << item << endl;
        }
    }

    //cross stack operations

    //move first element of another stack to current
    else if(inputstring.find(movestack) == 0)
    {
        inputstring.erase(0, movestack.length());

        try {
            int target = stoi(inputstring);

            if(target > stacks.size())
            {
                cerr << "stack: " << target << " done not exist" << endl;
                return true;
            }

            if(stacks[target].size() <= 0)
            {
                cerr << "stack: " << target << " is empty" << endl;
                return true;
            }

            stacks[currentstack].push_back(stacks[target].back());
            cout << "pushed: " << stacks[currentstack].back() << " to the working stack" << endl;
        } catch(const exception& e) {
            cerr << "cannot take items from: " << inputstring << endl;
        }
    }

    //copy another stack over to current
    else if(inputstring.find(copystack) == 0)
    {
        input.erase(0, copystack.length());

        try {
            int target = stoi(inputstring);

            if(target > stacks.size())
            {
                cerr << "stack: " << target << " is out of range" << endl;
                return true;
            }

            if(stacks[target].size() <= 0)
            {
                cerr << "stack: " << target << " is empty" << endl;
                return true;
            }

            stacks[currentstack].insert(stacks[currentstack].end(),
                                            stacks[target].begin(),
                                            stacks[target].end());

            cout << "copied stack: " << target << " to the current stack" << endl;
        } catch(const exception& e) {
            cerr << "cannot copy from stack: " << inputstring << endl;
        }
    }

    //math operations

    else if(inputstring.find(addcur) == 0)
    {
        CheckStackDouble("cannot add the top two items of the stack if the stack has less than 2 items")
        PerformStackAction(+)
    }

    else if(inputstring.find(subcur) == 0)
    {
        CheckStackDouble("cannot subtract the top two items of the stack if the stack has less than 2 items")
        PerformStackAction(-)
    }

    else if(inputstring.find(multcur) == 0)
    {
        CheckStackDouble("cannot multiply the top two items of the stack if the stack has less than 2 items")
        PerformStackAction(*)
    }

    else if(inputstring.find(modcur) == 0)
    {
        CheckStackDouble("cannot get modulus the top two items of the stack if the stack has less than 2 items")
        PerformStackAction(%)
    }

    else if(inputstring.find(divcur) == 0)
    {
        CheckStackDouble("cannot divide the top two items of the stack if the stack has less than 2 items")
        PerformStackAction(/)
    }

    else if(inputstring.find(inccur) == 0)
    {
        CheckStackSingle("cannot increment the top item if the stack is empty")
        stacks[currentstack].end()[-1]++;
        cout << "incrememented in stack: " << currentstack << endl;
    }

    else if(inputstring.find(deccur) == 0)
    {
        CheckStackSingle("cannot increment the top item if the stack is empty")
        stacks[currentstack].end()[-1]--;
        cout << "decremented in stack: " << currentstack << endl;

    }

    //bitwise operations

    else if(inputstring.find(bitwiseand) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(&)
    }

    else if(inputstring.find(bitwiseor) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(|)
    }

    else if(inputstring.find(bitwisexor) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(^)
    }

    else if(inputstring.find(bitwisenot) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        int ret = ~stacks[currentstack].end()[-1];
        stacks[currentstack].push_back(ret);
        cout << "added " << ret << " to the stack" << endl;
    }

    else if(inputstring.find(bitwiseleft) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(<<)
    }

    else if(inputstring.find(bitwiseright) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(>>)
    }
    //logic operations

    else if(inputstring.find(equals) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(==)
    }
    else if(inputstring.find(noequals) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(!=)
    }
    else if(inputstring.find(greaterthan) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(>)
    }
    else if(inputstring.find(greatorequal) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(>=)
    }
    else if(inputstring.find(lesser) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(<)
    }
    else if(inputstring.find(lessorequal) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        PerformStackAction(<=)
    }
    else if(inputstring.find(spaceship) == 0)
    {
        CheckStackDouble("cannot perform operation if the stack has less than 2 items")
        int first = stacks[currentstack].end()[-1];
        int second = stacks[currentstack].end()[-2];
        int ret;
        if(first > second) {ret = 1;}
        else if(first < second) {ret = -1;}
        else {ret = 0;}
        stacks[currentstack].push_back(ret);
        cout << "added: " << ret << " to current stack" << endl;
    }
    //flow control operations

    else if(inputstring.find(logicif) == 0)
    {

    }
    else if(inputstring.find(logicendif) == 0)
    {

    }

    //function operations

    else if(inputstring.find(functionbegindefine) == 0)
    {

    }
    else if(inputstring.find(functionenddefine) == 0)
    {

    }
    else if(inputstring.find(functionundefine) == 0)
    {

    }
    else if(inputstring.find(functionescape) == 0)
    {

    }
    else if(inputstring.find(functioncall) == 0)
    {

    }


    //exit the program
    else if(inputstring.find(metaexit) == 0)
    {
        return false;
    }

    else
    {
        cout << "instruction: " << input << " was not recognised" << endl;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    while(true)
    {
        cout << ">>> ";
        getline(cin, input);
        stacks.push_back(vector<int>());

        if (!generalproccess(input))
        {
            break;
        }
    }
    cout << "exiting..." << endl;
    return 0;
}