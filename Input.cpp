#include "Input.h"

/*****
// Base constructors for input object creation, includes constructor with one parameter
// to make gtest instantiation easier
*****/
Input::Input() { 
    exit = false;
}

Input::~Input() { }

Input::Input(std::string userString) {
    userInput = userString;
    exit = false;
}

/*****
// Flushes implicit vectors/data members for next input
*****/
void Input::clearInput() {
    userInput = "";
    parsedStrings.clear();
    connectors.clear();
    parsedExec.clear();
}

/*****
// Helper functions to return vectors for gtest
*****/
std::vector<std::string> Input::returnStrings() {
    return parsedStrings;
}

std::vector<std::string> Input::returnConnectors() {
    return connectors;
}

std::vector<std::vector <std::string> > Input::returnParsedExec() {
    return parsedExec;
}

/*****
// Takes in user input and passes it onto parseInput, to eventually create an Argument object 
// that will make it easier to link together arguments with connectors
*****/
//*** MARKED AS RESOLVED*** 
// Not 100% sure but I think there could be issues in the future with scope of these variables
// The vectors life expectancy exists only in this function so it could cause problems later if
// we call other functions in main.cpp other than runInput() 
//*** MARKED AS RESOLVED*** 
void Input::runInput() {
    std::string name = returnUser();
    std::string host = returnHost();
    std::string userLine;

    std::cout << host << "@" << name << "$ ";
    getline(std::cin, userLine);
    userInput = userLine;

    if (userInput == "exit" ||userInput == "Exit") { 
        callExit();
	return;
    }
}

void Input::callExit() {
    std::cout << "See you soon" << std::endl;
    exit = true;
    return;
}

bool Input::checkExit() {
    if (exit) {
        return true;
    }
    return false;
}

/*****
// Takes in user input and tokenizes string into substrings based on connectors, and then
// tokenizes yet again to remove spaces in the substrings. Returns a vector of strings to
// be then used to generate argument objects. 
*****/
void Input::parseInput() {
    std::string delimiters("&&" "||" ";");

    std::stringstream ss(this->userInput);
    std::string argument;

    // This while loop separates the user input into substrings based on the connectors 
    //"&& || ; ". White space still need to be removed.
    while (getline(ss, argument)) {
        size_t prev = 0;
        size_t pos;
        while ((pos = argument.find_first_of(delimiters, prev)) != std::string::npos) {
            if (pos > prev) {
                int connector = pos - prev + 1;
                parsedStrings.push_back(userInput.substr(prev, pos-prev));
                //connectors.push_back(userInput.substr(connector, 1));
            }
            prev = pos + 1;
        }
        if (prev < argument.length()) {
            int connector = pos - prev + 1;
            parsedStrings.push_back(userInput.substr(prev, std::string::npos));
        }
    }
    

    // This for loop removes the spaces from the parsed substrings so that the exec object creation is easier
    for (int i = 0; i < parsedStrings.size(); ++i) {
        std::vector<std::string> toPush = parseSpaces(parsedStrings.at(i));
        parsedExec.push_back(toPush);
    }

    //*** TESTER ***//
    // Following 3 lines of code can be removed later, the purpose of this is to print contents
    // of parsedInput vector
    // Each line printed should be the executable + any/all arguments for said executable
    for (int i = 0; i < parsedExec.size(); i++) {
        std::cout << "vector " << i << ":";
        for (int j = 0; j < parsedExec.at(i).size(); ++j) {
            std::cout << parsedExec.at(i).at(j);
        }
        std::cout << std::endl;
    }

    return;
}

/*****
// This is a helper function that is virtually the same as the first step of parse input, using spaces as
// delimiters instead of the connectors to remove spaces from string withSpaces
*****/
std::vector<std::string> Input::parseSpaces(std::string withSpaces) {
    std::string delimiters(" ");

    std::stringstream ss(withSpaces);
    std::string argument;
    std::vector<std::string> noSpaces;

    // This while loop separates the user input into substrings based on the connectors 
    //"&& || ; ". White space still need to be removed.
    while (getline(ss, argument)) {
        size_t prev = 0;
        size_t pos;
        while ((pos = argument.find_first_of(delimiters, prev)) != std::string::npos) {
            if (pos > prev) {
                noSpaces.push_back(withSpaces.substr(prev, pos-prev));
            }
            prev = pos + 1;
        }
        if (prev < argument.length()) {
            noSpaces.push_back(withSpaces.substr(prev, std::string::npos));
        }
    }

    return noSpaces;
}

/*****
// This function parses the user string for connectors to add to the connectors vector
*****/
void Input::parseConnectors() {
    std::string connectors("&&" "||" ";");
    // ** TO DO ** //
}

/*****
// Constructs executable tree based on 2d vector and connector vector, sets baseExec* head to the 
// head node of  this tree. head-> eval should execute the tree with respect to the connectors
*****/
void Input::makeExecutableTree() {
    // ** TO DO ** // 
}

/*****
// These two functions call local user and local host to be printed in terminal
*****/
std::string Input::returnHost() {
    size_t size = 1024;
    char name[size];
    if (gethostname(name, size) != -1) {
        std::string s(name);
        return s;
    } 
    return "Local";
}

std::string Input::returnUser() {
    char* name = getlogin();
    return name;
}

