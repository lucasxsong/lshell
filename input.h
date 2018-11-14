#ifndef INPUT_H
#define	INPUT_H 

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

using namespace std;

bool runShell = true;

void callExit() {
    cout << "See you soon" << endl;
    runShell = false;
}

// *****
// Takes in user input and tokenizes string into substrings based on connectors, and then
// tokenizes yet again to remove spaces in the substrings. Returns a vector of strings to
// be then used to generate argument objects. 
// *****
vector<string> parseInput(string userInput) {
    string delimiters("&&" "||" ";");
    vector<string> parsedStrings;

    stringstream ss(userInput);
    string argument;

    // This while loop separates the user input into substrings based on the connectors 
    //"&& || ; ". White space still need to be removed.
    while (getline(ss, argument)) {
        size_t prev = 0;
        size_t pos;
        while ((pos = argument.find_first_of(delimiters, prev)) != string::npos) {
            if (pos > prev) {
                parsedStrings.push_back(userInput.substr(prev, pos-prev));
            }
            prev = pos + 1;
        }
        if (prev < argument.length()) {
            parsedStrings.push_back(userInput.substr(prev, string::npos));
        }
    }

    return parsedStrings;
}

// *****
// Takes in vector of previously parsed user input and separates substrings into list of 
// executables (e.g., ls, echo, mkdir, etc.) and list of arguments (i.e., flags, filename,
// or comment)
// I split this up into two parts for now, one for executables and one for the arguments
// *****
vector<string> parseExecutable(vector<string> ) {
    
}

//*****
// These two functions call local user and local host to be printed in terminal
//*****
string printHost() {
    size_t size = 1024;
    char name[size];
    if (gethostname(name, size) != -1) {
        string s(name);
        return s;
    } 
    return "Local";
}

string printUser() {
    char* name = getlogin();
    return name;
}

// *****
// Takes in user input and passes it onto parseInput, to eventually create an Argument object 
// that will make it easier to link together arguments with connectors
// *****
// Not 100% sure but I think there could be issues in the future with scope of these variables
// The vectors life expectancy exists only in this function so it could cause problems later if
// we call other functions in main.cpp other than runInput()
void runInput() {
    string userInput;
    string name = printUser();
    string host = printHost();

    cout << host << "@" << name << "$ ";
    getline(cin, userInput);

    if (userInput == "exit" ||userInput == "Exit") { 
        callExit();
	return;
    }
    
    vector<string> parsedInput = parseInput(userInput);
    
    // Following 3 lines of code can be removed later, the purpose of this is to print contents
    // of parsedInput vector
    // Each line printed should be the executable + any/all arguments for said executable
    for (int i = 0; i < parsedInput.size(); i++) {
	cout << parsedInput.at(i) << endl;
    }

    
}

#endif

