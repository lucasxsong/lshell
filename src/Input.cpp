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

    std::cout << name << "@" << host << "$ ";
    getline(std::cin, userLine);
    userInput = userLine;

    parseInput();
}

/*****
// This function traverses through the substring and tries to find parenthesis. If one is found,
// it will continue until the matching end parenthesis is found and remove that portion from the string,
// pushing the removed substring into parenthesis for par object creation during makeExecutableTree and 
// replacing the removed portion with a string replacement
*****/
std::vector<std::string> Input::parsePar(std::string &userString) {
    int parCounter = 0;
    int parStart;
    int parEnd;
    bool foundEnd = false;
    std::vector<std::string> parSubStrings;
    // This vector holds the substrings so that makeExecutable tree can match the location of 
    // par with the substrings later for par object creation
    
    // For loop to find the beginning par
    for (int i = 0; i < userString.size(); ++i) {
        if (foundEnd == true) {
            i = parEnd;
            foundEnd = false;
            //std::cout << i << std::endl;
        }
        if (userString.at(i) == '(') {
            parStart = i;
            // For loop to find the index of the ending par
            for (int j = i; j < userString.size(); ++j) {
                //std::cout << parCounter << std::endl;
                if (userString.at(j) == '(') {
                    ++parCounter;
                    // Found a starting nested par
                }
                if (parCounter > 0 && userString.at(j) == ')') {
                    --parCounter;
                    //  Found an ending nested par
                }
                if (parCounter == 0 && userString.at(j) == ')') {
                    parEnd = j;
                    foundEnd = true;
                    break;
                    // Successfully found the end par

                }
            }
            if (foundEnd == false) {
                // Throw error if ending parenthesis could not be found
                std::cout << "Could not find ending parenthesis" << std::endl;
                return parSubStrings;
            }
            else {
                // Remove the substring from the original string
                std::string subString = userString.substr(parStart, parEnd);
                parSubStrings.push_back(subString);
                // Replaces original substring with unique parID xD
                std::cout << parEnd << std::endl;
                userString.replace(parStart, parEnd - parStart + 1, "par482309812");
                std::cout << userString << std::endl;
            }  
        }
    }
    return parSubStrings;
}

/*****
// This function takes in the userInput as a parameter and updates it to add "test" as a 
// string instead of of
*****/
void Input::parseTest(std::string &userString) {
    int testStart;
    int testEnd;
    bool foundEnd = false;
    // This vector holds the substrings so that makeExecutable tree can match the location of 
    // par with the substrings later for par object creation
    
    // For loop to find the beginning bracket
    for (int i = 0; i < userString.size(); ++i) {
        if (foundEnd == true) {
            i = testEnd;
            foundEnd = false;
            std::cout << i << std::endl;
        }
        if (userString.at(i) == '[') {
            testStart = i;
            // For loop to find the index of the ending bracket
            // The problem is that this forloop iterates through the end of the string and doesn't stop when the end is found
            for (int j = i; j < userString.size(); ++j) {
                if (userString.at(j) == ']') {
                    testEnd = j;
                    userString.erase(testStart, 1);
                    userString.erase(testEnd - 1, 1);
                    userString.insert(testStart, "test ");
                    std::cout << userString << std::endl;
                    foundEnd = true;
                    break;
                    // Successfully found the end bracket
                }
            }
            if (foundEnd == false) {
                // Throw error if ending parenthesis could not be found
                std::cout << "Could not find ending bracket" << std::endl;
                return;
            }
        }
    }
    return;
}

// After this function, the individual par objects will need to be parsed to created individual trees, 
// and will replace the par object with a connector pointing to  two or more arguments in the executable tree


/*****
// Takes in user input and tokenizes string into substrings based on connectors, and then
// tokenizes yet again to remove spaces in the substrings. Returns a vector of strings to
// be then used to generate argument objects. 
// ***EDITED NOV28***
// Editing function to add support for parenthesis
*****/
void Input::parseInput() {
    // If there are any parenthesis in userInput, call parsePar to remove those sections
    if (userInput.find('(') != std::string::npos) {
        parsePar(this->userInput);     
    }
    if (userInput.find('[') != std::string::npos) {
        parseTest(this->userInput);
    }
    parsedStrings = parseOutConnectors(userInput);

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
// This is a helper function adapted out of the original parseInput function that takes 
// in a string and parses out the substrings that are separated by the connectors.
// This is useful as two steps of this parsing need to be completed, once for the paranthesis
// and once again for the substrings inside each parenthesis
******/
std::vector<std::string> Input::parseOutConnectors(std::string withConnectors) {
    std::string delimiters("&&" "||" ";");
    std::vector<std::string> parsedSubStrings;

    std::stringstream ss(withConnectors);
    std::string argument;

    // This while loop separates the user input into substrings based on the connectors 
    //"&& || ; ". White space still need to be removed.
    while (getline(ss, argument)) {
        size_t prev = 0;
        size_t pos;
        while ((pos = argument.find_first_of(delimiters, prev)) != std::string::npos) {
            if (pos > prev) {
                int connector = pos - prev + 1;
                parsedSubStrings.push_back(withConnectors.substr(prev, pos-prev));
            }
            prev = pos + 1;
        }
        if (prev < argument.length()) {
            int connector = pos - prev + 1;
            parsedSubStrings.push_back(withConnectors.substr(prev, std::string::npos));
        }
    }

    return parsedSubStrings;
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
    // ****** NEW ADDITIONS FOR ASSN3 ******//
    if (exec.at(0) == "test") {
        test* b = new test();
        b->addArg(exec);
        return b;
    }

    if (exec.at(0) == "par482309812") {
        // Instantiates a new par object with the first parenthesis entry being the substring data member
        // Then, removes the first entry so that if there are more par objects they will be able to be properly created
        Par* b = new Par();
        std::string subString = parenthesis.at(0);
        b->setSubString(subString);
        parenthesis.erase(parenthesis.begin());
        return b;
    }

    // ****** NEW ADDITIONS FOR ASSN3 ******//

    else { //error test case
        baseExec* b = new baseExec();
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

/****
// FOR ASSIGNMENT 3
// Need to adapt the 
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

