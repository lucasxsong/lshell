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
        std::vector<baseExec*> parsedExec; // this vector holds the parsed baseExec objects with arg
        std::vector<std::vector<std::string> > parsedNoSpace; // this vector holds the parsed string w/o spaces
        std::vector<std::string> parsedStrings; // these two vectors are just to help in storing 
        std::vector<Connector* > connectors;    // the data to create the executable tree
        baseNode* head; // pointer to top of executable tree

    public:
		Input();
        ~Input();
        Input(std::string userString);
        void clearInput();
        void removeComment();

        std::vector<baseExec* > returnParsedExec();
        std::vector<std::vector <std::string> > returnParsedNoSpace();
        std::string returnStrings();
        std::vector<Connector* > returnConnectors();
        baseNode* returnHead();

        void callExit();
		bool checkExit(); // returns true if needs to exit

        void runInput();
        void parsePar();
        void parseInput();
        std::vector<std::string>parseOutConnectors(std::string withConnectors);
        std::vector<std::string> parseSpaces(std::string withSpaces); // helper function to remove spaces from withSpaces input
        void parseConnectors();
        baseExec* makeExec(std::vector<std::string> exec); // instantiates baseExec objects and arglist pointer

        void makeExecutableTree(); // instantiates baseExec tree with connectors
        void callExecute(); //executes on top head node of the tree, execute function should go down tree 
        std::string returnUser();
        std::string returnHost();
};


#endif



