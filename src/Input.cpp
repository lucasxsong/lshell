#include "Input.h"

//Input Implementation

bool exitBool = false;
/*****
// Base constructors for input object creation, includes constructor with one parameter
// to make gtest instantiation easier
*****/
Input::Input() { 

}

Input::~Input() { }

Input::Input(std::string userString) {
    userInput = userString;
}

/*****
// Flushes implicit vectors/data members for next input
*****/
void Input::clearInput() {
    userInput = "";
    parsedStrings.clear();
    connectors.clear();
    parsedNoSpace.clear();
    parsedExec.clear();
    head = NULL;
}

/*****
// Helper functions to return data members for gtest
*****/
std::vector<baseExec* > Input::returnParsedExec() {
    return parsedExec;
}

std::vector<std::vector <std::string> > Input::returnParsedNoSpace() {
    return parsedNoSpace;
}

std::string Input::returnStrings() {
    return userInput;
}

std::vector<Connector* > Input::returnConnectors() {
    return connectors;
}

baseNode* Input::returnHead() {
    return head;
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

    parseInput();
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
    

    // parsedNoSpace vector creation
    for (int i = 0; i < parsedStrings.size(); ++i) {
        std::vector<std::string> toPush = parseSpaces(parsedStrings.at(i));
        parsedNoSpace.push_back(toPush);
    }

    // parsedExec vector creation
    for (int i = 0; i < parsedNoSpace.size(); ++i) {
        baseExec* toPush = makeExec(parsedNoSpace.at(i));
        parsedExec.push_back(toPush);
    }

    parseConnectors();
    makeExecutableTree();
    head->execute();

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
// This is a helper function that returns a baseExec object based on the zero index of
// the vector passed in and takes the rest of the vector as the argument list // exec = nospace
*****/
baseExec* Input::makeExec(std::vector<std::string> exec) {
    if (exec.at(0) == "echo") {
        echo* b = new echo();
        b->addArg(exec);
        return b;
    }
    if (exec.at(0) == "exit") {
        exitCall* b = new exitCall();
        b->addArg(exec);
        return b;
    }
    if (exec.at(0) == "mkdir") {
        baseExec* b = new baseExec();
        b->addArg(exec);
        return b;
    }
    if (exec.at(0) == "ls") {
        baseExec* b = new baseExec();
        b->addArg(exec);
        return b;
    }
    if (exec.at(0) == "cd") {
        baseExec* b = new baseExec();
        b->addArg(exec);
        return b;
    }
    else { //error test case
        error* b = new error();
        b->addArg(exec);
        return b;
    }
}

/*****
// This function parses the user string for connectors to add to the connectors vector
*****/
void Input::parseConnectors() {
    std::vector<std::string> temp; //initial vector used to store found connectors

    for (int pos = 0; pos < userInput.size(); pos++) {
        if (userInput.at(pos) == '&') {
            if (userInput.at(pos + 1) == '&') {
                temp.push_back("&&");
                pos += 2; //should now be at whitespace after "&&"
            }
        }
        if (userInput.at(pos) == '|') {
            if (userInput.at(pos + 1) == '|') {
                temp.push_back("||");
                pos += 2; //should now be at whitespace after "||"
            }
        }
        if (userInput.at(pos) == ';') {
            temp.push_back(";");
            pos++; //should now be at whitespace after ";"
        }
    }

//Iterate through vector of connector strings ("temp") and creates connector objects and pushes into vector of connectors ("connectors")
//Child pointers not set yet
    for (int i = 0; i < temp.size(); i++) {
	    if (temp.at(i) == "&&") {
	        And* c = new And();
	        connectors.push_back(c);
	    }
	    if (temp.at(i) == "||") {
	        Or* c = new Or();
	        connectors.push_back(c);
	    }
	    if (temp.at(i) == ";") {
	        SemiColon* c = new SemiColon();
	        connectors.push_back(c);
	    }
    }
}

/*****
// Constructs executable tree based on 2d vector and connector vector, sets baseExec* head to the 
// head node of  this tree. head-> eval should execute the tree with respect to the connectors
*****/
void Input::makeExecutableTree() {
    // Case for no connectors
    if (connectors.size() == 0) {
        head = parsedExec.at(0); 
    }

    // Case for connectors
    if (connectors.size() > 0) {
        head = connectors.at(0);
        baseNode* temp = head;
        temp->setLeft(parsedExec.at(0));
        
        // If there is no more than one connector, 
        for (int i = 0; i < connectors.size(); ++i) {
            temp->setRight(connectors.at(i));
            temp = temp->getRight();
            temp->setLeft(parsedExec.at(i)); 
        }
        temp->setRight(parsedExec.at(connectors.size()));

    }

    return;
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
    perror("host()");
    return "Local";
}

std::string Input::returnUser() {
    char* name = getlogin();
    return name;
}

