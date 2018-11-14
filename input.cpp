#include "input.h"
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

bool input::runShell() {
    if (userInput != "quit" && userInput != "Quit") {
        cout << "See you next time!" << endl;
        return false;
    }
    return true;
}

// *****
// Takes in user input and tokenizes string into substrings based on connectors, and then
// tokenizes yet again to remove spaces in the substrings. Returns a vector of strings to
// be then used to generate argument objects. 
// *****
void input::parseInput() {
    string delimiters("&&" "||" ";");

    stringstream ss(userInput);
    string argument;

    // This while loop separates the user input into substrings based on the connectors 
    //"&& || ; ". White space still need to be removed.
    while (getline(ss, argument)) {
        size_t prev = 0;
        size_t pos;
        while ((pos = argument.find_first_of(delimiters, prev)) != string::npos) {
            if (pos > prev) {
                this->preExec.push_back(userInput.substr(prev, pos-prev));
            }
            prev = pos + 1;
        }
        if (prev < argument.length()) {
            this->preExec.push_back(userInput.substr(prev, string::npos));
        }
    }

    return;
}

// still need to edit function to note what connector tokenizes each exec list


void input::parseArguments() {
    
}

//*****
// These two functions call local user and local host to be printed in terminal
//*****
string input::printHost() {
    size_t size = 1024;
    char name[size];
    if (gethostname(name, size) != -1) {
        string s(name);
        return s;
    } 
    return "Local";
}

string input::printUser() {
    char* name = getlogin();
    return name;
}

//*****
// Takes in user input and passes it onto parseInput, to eventually create an Argument object 
// that will make it easier to link together arguments with connectors
//*****
void input::runInput() {
    string name = printUser();
    string host = printHost();

    cout << host << "@" << name << "$ ";
    getline(cin, this->userInput);
    
    parseInput();
}

