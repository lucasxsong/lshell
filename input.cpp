#include "input.h"

void callExit() {
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

// still need to edit function to note what connector tokenizes each exec list


void parseArguments() {
    
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

//*****
// Takes in user input and passes it onto parseInput, to eventually create an Argument object 
// that will make it easier to link together arguments with connectors
//*****
void runInput() {
    string userInput;
    string name = printUser();
    string host = printHost();

    cout << host << "@" << name << "$ ";
    getline(cin, userInput);

    if (userInput == "exit" ||userInput == "Exit") { 
        callExit();
    }
    
    vector<string> parsedInput = parseInput(userInput);
}

#endif
