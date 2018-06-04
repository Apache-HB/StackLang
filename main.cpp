#include <iostream>
#include <vector>
#include <utility>
#include "functionstrings.h"
#include <stdio.h>
#define CheckStack(x, y) if(stacks[currentstack].size() < y){ cout << x << endl; return; }

#define PerformStackAction(x) int ret = stacks[currentstack].end()[-1] x stacks[currentstack].end()[-2]; \
                              stacks[currentstack].push_back(ret); \
                              cout << "added " << ret << " to the stack" << endl;

using namespace std;

typedef vector<int> stack;
static vector<stack> stacks;

typedef pair<string, vector<string>> functionpair;
static vector<functionpair> functions;

string input = "";

bool running = true;

int currentstack = 0;

void generalproccess(string inputstring)
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
            return;
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
                return;
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
            return;
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
            return;
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
                return;
            }

            if(stacks[target].size() <= 0)
            {
                cerr << "stack: " << target << " is empty" << endl;
                return;
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
                return;
            }

            if(stacks[target].size() <= 0)
            {
                cerr << "stack: " << target << " is empty" << endl;
                return;
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
        CheckStack("cannot add the top two items of the stack if the stack has less than 2 items", 2)
        PerformStackAction(+)
    }

    else if(inputstring.find(subcur) == 0)
    {
        CheckStack("cannot subtract the top two items of the stack if the stack has less than 2 items", 2)
        PerformStackAction(-)
    }

    else if(inputstring.find(multcur) == 0)
    {
        CheckStack("cannot multiply the top two items of the stack if the stack has less than 2 items", 2)
        PerformStackAction(*)
    }

    else if(inputstring.find(modcur) == 0)
    {
        CheckStack("cannot get modulus the top two items of the stack if the stack has less than 2 items", 2)
        PerformStackAction(%)
    }

    else if(inputstring.find(divcur) == 0)
    {
        CheckStack("cannot divide the top two items of the stack if the stack has less than 2 items", 2)
        PerformStackAction(/)
    }

    else if(inputstring.find(inccur) == 0)
    {
        CheckStack("cannot increment the top item if the stack is empty", 1)
        stacks[currentstack].end()[-1]++;
        cout << "incrememented in stack: " << currentstack << endl;
    }

    else if(inputstring.find(deccur) == 0)
    {
        CheckStack("cannot increment the top item if the stack is empty", 1)
        stacks[currentstack].end()[-1]--;
        cout << "decremented in stack: " << currentstack << endl;

    }

    //bitwise operations

    else if(inputstring.find(bitwiseand) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(&)
    }

    else if(inputstring.find(bitwiseor) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(|)
    }

    else if(inputstring.find(bitwisexor) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(^)
    }

    else if(inputstring.find(bitwisenot) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        int ret = ~stacks[currentstack].end()[-1];
        stacks[currentstack].push_back(ret);
        cout << "added " << ret << " to the stack" << endl;
    }

    else if(inputstring.find(bitwiseleft) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(<<)
    }

    else if(inputstring.find(bitwiseright) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(>>)
    }
    //logic operations

    else if(inputstring.find(equals) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(==)
    }
    else if(inputstring.find(noequals) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(!=)
    }
    else if(inputstring.find(greaterthan) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(>)
    }
    else if(inputstring.find(greatorequal) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(>=)
    }
    else if(inputstring.find(lesser) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(<)
    }
    else if(inputstring.find(lessorequal) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
        PerformStackAction(<=)
    }
    else if(inputstring.find(spaceship) == 0)
    {
        CheckStack("cannot perform operation if the stack has less than 2 items", 2)
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
        inputstring.erase(0, functionbegindefine.length());
        size_t pos = 0;

        string name = "__function_definition__";

        while((pos = inputstring.find(functiondefinesplit)) != string::npos)
        {
            name = Trim(inputstring.substr(0, pos));
            inputstring.erase(0, pos + functiondefinesplit.length());
            break;
        }
        if(name == "__function_definition__")
        {
            cerr << "function must have a name" << endl;
            return;
        }
        for(auto& func : functions)
        {
            if(func.first == name)
            {
                cerr << "cannot have functions with the same name" << endl;
                return;
            }
        }
        vector<string> commands;

        pos = 0;
        while((pos = inputstring.find(functioncallsplit)) != string::npos)
        {
            commands.push_back(inputstring.substr(0, pos));
            inputstring.erase(0, pos + functioncallsplit.length());
        }
        commands.push_back(inputstring);

        if(commands.size() == 0)
        {
            cout << "function must cannot be empty and must do more than one thing" << endl;
            return;
        }

        functionpair toadd = functionpair(name, commands);
        functions.push_back(toadd);
        cout << "added function: " << name << endl;
        cout << "this executes commands" << endl;
        for(auto& command : commands)
        {
            cout << command << endl;
        }
    }
    else if(inputstring.find(functionundefine) == 0)
    {

    }
    else if(inputstring.find(functionescape) == 0)
    {//todo: this

    }
    else if(inputstring.find(functioncall) == 0)
    {
        inputstring.erase(0, functioncall.length());
        for(auto& func : functions)
        {
            if(func.first == Trim(inputstring))
            {
                for(auto& com : func.second)
                {
                    input = Trim(com);
                    generalproccess(input);
                }
                //cout << "executed command " << inputstring << endl;
                return;
            }
        }
        cout << "could not find a command called " << inputstring << endl;
    }

    else if(inputstring.find(functionlist) == 0)
    {
        if(functions.size() == 0)
        {
            cout << "there are no functions defined" << endl;
            return;
        }
        cout << "all defined functions" << endl;
        for(auto& func : functions)
        {
            cout << func.first << endl;
            for(auto& command : func.second)
            {
                cout << command << endl;
            }
        }
    }

    //exit the program
    else if(inputstring.find(metaexit) == 0)
    {
        running = false;
    }

    else
    {
        cout << "instruction: " << input << " was not recognised" << endl;
    }
    return;
}

int main(int argc, char const *argv[])
{
    while(true)
    {
        stacks.push_back(vector<int>());
        if(running)
        {
            cout << ">>> ";
            getline(cin, input);
            generalproccess(Trim(input));
        }
    }
    cout << "exiting..." << endl;
    return 0;
}