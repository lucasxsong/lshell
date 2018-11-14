#ifndef INPUT_H
#define	INPUT_H 

#include "baseExec.h"
#include <iostream>

using namespace std;

class baseExec;

class input {
    protected: 
        string userInput;
        vector<string> preExec;
        baseExec* e;
    public:
        input(){}
        bool runShell();
        void runInput();
        void parseInput();
        void parseArguments();
        string printUser();
        string printHost();
};

#endif
