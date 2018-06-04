#include <string>
#include <ctype.h>

#pragma once

const std::string metahelp = "help";

const std::string metaexit = "exit";

//create a new stack
const std::string pushstack = "pushstack";

//delete the top stack
const std::string popstack = "popstack";

//move to a diffrent stack
const std::string setstack = "setstack";

//print the current stack
const std::string printstack = "printstack";



//move the first element of another stack to current
const std::string movestack = "movestack";

//copy another stack to current
const std::string copystack = "copystack";



const std::string pushcur = "push";

const std::string popcur = "pop";



const std::string addcur = "add";
const std::string subcur = "sub";
const std::string multcur = "mult";
const std::string modcur = "mod";
const std::string divcur = "div";
const std::string inccur = "inc";
const std::string deccur = "dec";


const std::string equals = "==";
const std::string noequals = "!=";
const std::string greaterthan = ">";
const std::string greatorequal = ">=";
const std::string lesser = "<";
const std::string lessorequal = "<=";
const std::string spaceship = "<=>";

const std::string logicif = "if";
const std::string logicifsplit = "do";

const std::string logicendif = "endif";

const std::string bitwiseand = "and";
const std::string bitwiseor = "or";
const std::string bitwisexor = "xor";
const std::string bitwisenot = "not";
const std::string bitwiseleft = "left";
const std::string bitwiseright = "right";

const std::string functionbegindefine = "define";
const std::string functionundefine = "undefine";
const std::string functionlist = "listfunctions";

const std::string functionescape = "escape";

const std::string functiondefinesplit = "as";
const std::string functioncallsplit = "then";

const std::string functioncall = "call";

const std::string converttochar = "tochar";

const std::string valcreate = "val";
const std::string valassign = "=";
const std::string valget = "get";
const std::string vallist = "allval";

std::string trimlead(const std::string& in)
{
    std::string temp = in;
    while(isspace(temp.front()))
    {
        temp.erase(0, 1);
    }
    return temp;
}

std::string trimtrail(const std::string& in)
{
    std::string temp = in;
    while(isspace(temp.back()))
    {
        temp.pop_back();
    }
    return temp;
}

#define Trim(str) trimlead(trimtrail(str))