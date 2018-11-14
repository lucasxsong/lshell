#include "Input.h"

Input::Input() {

}

Input::~Input() {
}

// *****
// Takes in user input and passes it onto parseInput, to eventually create an Argument object 
// that will make it easier to link together arguments with connectors
// *****
// Not 100% sure but I think there could be issues in the future with scope of these variables
// The vectors life expectancy exists only in this function so it could cause problems later if
// we call other functions in main.cpp other than runInput()
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
    
    // Following 3 lines of code can be removed later, the purpose of this is to print contents
    // of parsedInput vector
    // Each line printed should be the executable + any/all arguments for said executable
    //for (int i = 0; i < parsedInput.size(); i++) {
	//cout << parsedInput.at(i) << endl;
    //}
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

// *****
// Takes in user input and tokenizes string into substrings based on connectors, and then
// tokenizes yet again to remove spaces in the substrings. Returns a vector of strings to
// be then used to generate argument objects. 
// *****
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
                parsedStrings.push_back(userInput.substr(prev, pos-prev));
            }
            prev = pos + 1;
        }
        if (prev < argument.length()) {
            parsedStrings.push_back(userInput.substr(prev, std::string::npos));
        }
    }

    return;
}

// *****
// Takes in vector of previously parsed user input and separates substrings into list of 
// executables (e.g., ls, echo, mkdir, etc.) and list of arguments (i.e., flags, filename,
// or comment)
// I split this up into two parts for now, one for executables and one for the arguments
// *****
void Input::parseExecutable() {
    
}

//*****
// These two functions call local user and local host to be printed in terminal
//*****
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

