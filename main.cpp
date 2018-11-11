#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

using namespace std;

bool runShell = true;

void callExit() {
    runShell = false;
}

// *****
// Takes in user input and tokenizes string into substrings based on connectors, and then
// tokenizes yet again to remove spaces in the substrings. Returns a vector of strings to
// be then used to generate argument objects. 
// *****
vector<string> parseInput (string userInput) {
    string delimiters("&" "||" ";");
    vector<string> parsedStrings;

    return parsedStrings;
}

string printHost() {
   /*
    char* name;
    size_t size = 1023;
    if (gethostname(name, size) != -1) {
        cout << name;
    } */
    return getenv("LOGIN");
}

string printUser() {
    char* name = getlogin();
    return name;
}

//*****
// Takes in user input and passes it onto parseInput, to eventually create an Argument object 
// that will make it easier to link together arguments with connectors
//*****
void runInput() {
    string userInput;
    string name = printUser();
    //string host = printHost();

    cout << "@" << name << "$ ";
    getline(cin, userInput);

    if (userInput == "exit" ||userInput == "Exit") { 
        callExit();
    }
    
    vector<string> parsedInput = parseInput(userInput);
}






int main () {
    while (runShell) {
        runInput();
    }

    return 0;
}


