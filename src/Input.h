#ifndef __INPUT_H__
#define	__INPUT_H__

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
#include <sys/wait.h>

#include "BaseNode.h"
class baseNode;


class Input {
    protected: 
        std::string userInput; 
        std::vector<baseNode*> parsedNode; // this vector holds the parsed baseExec objects with arg
        std::vector<std::vector<std::string> > parsedNoSpace; // this vector holds the parsed string w/o spaces
        std::vector<std::string> parsedStrings; // these two vectors are just to help in storing 
        std::vector<Connector* > connectors;    // the data to create the executable tree
        baseNode* head; // pointer to top of executable tree

        // ADDITION FOR ASSIGNMENT 3
        std::vector<std::string> parenthesis;
    
    public:
		Input();
        ~Input();
        Input(std::string userString);
        void clearInput();
        void removeComment();

        std::vector<baseNode* > returnParsedNode();
        std::vector<std::vector <std::string> > returnParsedNoSpace();
        std::string returnStrings();
        std::vector<Connector* > returnConnectors();
        baseNode* returnHead();

        void callExit();
		bool checkExit(); // returns true if needs to exit
        // The program will first call runInput to get the full userString
        // Then, the program will call parsePar to construct the first tree
        // will need to add a helper function just to concatenate based on paranthesis and connectors -> will be used for second pass
        // ***TO DO*** need to adjust makeExecutableTree to work with paranthesis
        void runInput();
        // ****** NEW ADDITIONS FOR ASSN3 ******//
        std::vector<std::string> parsePar(std::string &userString);
        void parseTest(std::string &userString);
        // ****** NEW ADDITIONS FOR ASSN3 ******//
        void parseInput();
        std::vector<std::string>parseOutConnectors(std::string withConnectors);
        std::vector<std::string> parseSpaces(std::string withSpaces); // helper function to remove spaces from withSpaces input
        void parseConnectors();
        baseNode* makeNode(std::vector<std::string> exec); // instantiates baseExec objects and arglist pointer

        void makeExecutableTree(); // instantiates baseExec tree with connectors
        void callExecute(); //executes on top head node of the tree, execute function should go down tree 
        std::string returnUser();
        std::string returnHost();
};


#endif



